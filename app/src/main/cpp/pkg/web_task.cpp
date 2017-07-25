#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "../network/web_task.h"


static int get_filesize(const char *fpath) {
    return 1;
}

static size_t web_write_mem(void *ptr, size_t size, size_t nmemb, void *data) {
    //ignore data
    if (!data) return size * nmemb;

    web_buffer_t *buf = (web_buffer_t *) data;

    size_t left_size = buf->size - buf->datalen;
    size_t copy_size = size * nmemb > left_size ? left_size : size * nmemb;

    memcpy(buf->buf + buf->datalen, ptr, copy_size);
    buf->datalen += copy_size;
    return size * nmemb;
}

static size_t web_write_file(void *ptr, size_t size, size_t nmemb, void *stream) {
    return fwrite(ptr, size, nmemb, (FILE *) stream);
}

WebTask::WebTask() {
    m_formpost = m_lastptr = NULL;
    m_headerlist = NULL;

    memset(&m_web_buf, 0, sizeof(m_web_buf));

    m_cb = NULL;

    m_file = NULL;

    m_is_getfile = 0;

    m_do_func_called = false;

    _init();
}

WebTask::~WebTask() {
    if (m_web_buf.buf){
        free(m_web_buf.buf);
        m_web_buf.buf = NULL;
    }
}


void WebTask::SetUrl(const char *url) {
    curl_easy_setopt(m_curl, CURLOPT_URL, url);
    m_url = url;
}

void WebTask::SetCallback(on_web_done_t cb, void *para) {
    m_cb = cb;
    m_cb_para = para;
}

int debug_callback(CURL *handle,
                   curl_infotype type,
                   char *data,
                   size_t size,
                   void *userptr) {
    if (type == 0)
        printf("db: %s\n", data);
    return 0;
}

void WebTask::_init() {
    m_curl = curl_easy_init();

    /* no progress meter please */
    curl_easy_setopt(m_curl, CURLOPT_NOPROGRESS, 1L);
    /* connect time out set */
    curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT, 10L);
    /* no signal */
    curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1L);

    curl_easy_setopt(m_curl, CURLOPT_LOW_SPEED_LIMIT, 1024);

    curl_easy_setopt(m_curl, CURLOPT_LOW_SPEED_TIME, 30);

    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);

    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 2L);

    curl_easy_setopt(m_curl, CURLOPT_CAINFO, "/tmp/ca.pem");

    curl_easy_setopt(m_curl, CURLOPT_DNS_CACHE_TIMEOUT, 60 * 60 * 72);

}

void WebTask::_add_post_file(const char *item_name, const char *file_path, const char *file_name,
                             const char *content_type) {
    curl_formadd(&m_formpost,
                 &m_lastptr,
                 CURLFORM_COPYNAME, item_name,
                 CURLFORM_FILE, file_path,
                 CURLFORM_FILENAME, file_name,
                 CURLFORM_CONTENTTYPE, content_type,
                 CURLFORM_END);
}

void WebTask::AddPostString(const char *item_name, const char *item_data) {
    curl_formadd(&m_formpost,
                 &m_lastptr,
                 CURLFORM_COPYNAME, item_name,
                 CURLFORM_COPYCONTENTS, item_data,
                 CURLFORM_END);
}

void WebTask::AddPostPicture(const char *item_name, const char *file_path, const char *file_name) {
    if (access(file_path, F_OK) != 0)
        return;

    if (!file_name) {
        file_name = strrchr(file_path, '/');

        if (!file_name)
            file_name = file_path;
        else
            file_name += 1;
    }
    _add_post_file(item_name, file_path, file_name, "image/jpeg");
}

int WebTask::DoGetString() {

    if (m_formpost)
        curl_easy_setopt(m_curl, CURLOPT_HTTPPOST, m_formpost);

    /* send all data to this function  */
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, web_write_mem);

    /* we want the headers be written to this file handle */
    curl_easy_setopt(m_curl, CURLOPT_WRITEHEADER, NULL);

    m_web_buf.size = 200 * 1024;
    m_web_buf.buf = (char *) malloc(m_web_buf.size);
    m_web_buf.datalen = 0;
    memset(m_web_buf.buf, 0, m_web_buf.size);

    /* we want the body be written to this file handle instead of stdout */
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_web_buf);

    m_do_func_called = true;
    return 0;
}

int WebTask::WaitTaskDone() {
    /* get it! */
    CURLcode res = curl_easy_perform(m_curl);

    res = (CURLcode) _on_work_done((int) res);

    //clean up

    if (m_formpost)
        curl_formfree(m_formpost);
    /* free slist */
    if (m_headerlist)
        curl_slist_free_all(m_headerlist);

    curl_easy_cleanup(m_curl);
    return (int) res;
}

int WebTask::DoGetFile(const char *range) {
    if (m_formpost)
        curl_easy_setopt(m_curl, CURLOPT_HTTPPOST, m_formpost);

    if (range)
        curl_easy_setopt(m_curl, CURLOPT_RANGE, range);


    char fpath[128];

    strcpy(fpath, "/tmp/XXXXXX");

    int fd = mkstemp(fpath);
    if (fd < 0) {
        return -1;
    }

    fcntl(fd, F_SETFD, FD_CLOEXEC);

    m_file = fdopen(fd, "wb");
    if (!m_file) {
        return -1;
    }
    m_is_getfile = 1;


    m_filepath = fpath;

    /* send all data to this function  */
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, web_write_file);

    /* we want the headers be written to this file handle */
    curl_easy_setopt(m_curl, CURLOPT_WRITEHEADER, NULL);

    /* we want the body be written to this file handle instead of stdout */
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, m_file);

    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1);

    m_do_func_called = true;
    return 0;
}

int WebTask::_on_work_done(int result) {
    if (m_is_getfile == 0 && m_web_buf.buf) {
        if (m_web_buf.buf) {
            if (m_web_buf.datalen > 0)
                m_web_buf.buf[m_web_buf.size - 1] = '\0';
            std::string get_string = m_web_buf.buf;
            if (m_cb) m_cb(result, get_string, m_cb_para);
        }
    } else if (m_is_getfile) {
        double filesize = 0;
        curl_easy_getinfo(m_curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &filesize);

        if (m_file)
            fclose(m_file);
        if (result != 0)
            unlink(m_filepath.c_str());
        if (get_filesize(m_filepath.c_str()) != (long) filesize) {
            unlink(m_filepath.c_str());
            result = -1;
        }
        if (m_cb) {
            m_cb(result, m_filepath, m_cb_para);
        }
    }
    return result;
}

const char *WebTask::GetResultString() {
    if (m_is_getfile == 0 && m_web_buf.buf)
        return m_web_buf.buf;
    else
        return NULL;
}

const char *WebTask::GetFilePath() {
    if (m_is_getfile == 1)
        return m_filepath.c_str();
    else
        return NULL;
}

/**
 * 打开ssl
 * @param used
 */
void WebTask::useSSl(bool used) {
    if (used) {
        curl_easy_setopt(m_curl, CURLOPT_USE_SSL, used);
//        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);
//        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(m_curl, CURLOPT_SSLVERSION, 3); //设定SSL版本
        curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, false);
    } else{
        curl_easy_setopt(m_curl, CURLOPT_USE_SSL, used);
    }
}


void WebTask::setDebugMode(bool debug) {
    if (debug) {
        curl_easy_setopt(m_curl, CURLOPT_DEBUGFUNCTION, my_trace);//打印完整的调试信息
        curl_easy_setopt(m_curl, CURLOPT_VERBOSE, 1);//打印调试信息
    }
}

/**
 * 设置用户代理
 * @param agent 用户代理
 */
void WebTask::userAgent(const char *agent) {
    curl_easy_setopt(m_curl, CURLOPT_USERAGENT, agent);
}

/**
 * 添加请求头
 * @param header
 */
void WebTask::addHeader(JNIEnv *env, jobjectArray header) {
    try {
        curl_slist *plist = NULL;
        jsize alen = (env)->GetArrayLength(header);
        //给以维数据填充值  
        for (int i = 0; i < alen; i++) {
            jstring tmp = NULL; /* make sure it is large enough! */
            //第i个元素值  
            tmp = (jstring) env->GetObjectArrayElement(header, i);
            char *arg = jstring2char(env, tmp);
            curl_slist_append(plist, arg);
            //删除临时元素iarr数组
            env->DeleteLocalRef(tmp);
        }
        curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, plist);
        if (plist != NULL)
            curl_slist_free_all(plist);
    } catch (std::exception *e) {
        const char *w = e->what();
        printMsg(w);
    }
}

void WebTask::SetConnectTimeout(int timeo) {
    /* connect time out set */
    curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT, timeo);
}

bool WebTask::checkNetWorkAvailable() {
    //检查联网状态
    //创建curl对象
    CURL *curl;
    //创建curlcode对象
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        //设置一个请求文件地址
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.xxxx.tv/release/remote.update");
        //执行请求操作,将返回值交给res
        res = curl_easy_perform(curl);
        //res=0的情况表示接收到信息,反之则没有收到信息
        if (res != 0) {
            //没有联网
            return false;
        } else {
            //已经联网
            return true;

        }
        /* 释放资源 */
        curl_easy_cleanup(curl);
    }
    return false;
}


