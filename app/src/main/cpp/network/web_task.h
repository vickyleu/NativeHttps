#ifndef WEB_ASYNC_TASK_HHHHHH_
#define WEB_ASYNC_TASK_HHHHHH_

#include <string>
#include "curl/curl.h"
#include "../Utils/log.h"
#include "../Utils/CDebuger.h"
#include "../Utils/StringUtil.h"


typedef struct _web_buffer_t {
    char *buf;
    //buffer orignal size
    int size;
    //length of data that wrote to buffer
    int datalen;
} web_buffer_t;

typedef void (*on_web_done_t)(int, const std::string &, void *);

static
void dump(const char *text, unsigned char *ptr, size_t size) {
    size_t i;
    size_t c;
    unsigned int width = 0x10;
    char buf[1024];
    sprintf(buf,"%s, %10.10ld bytes (0x%8.8lx)\n",
            text, (long) size, (long) size);
    std::string string1(buf);
    printMsg2("Data::::::",string2char(string1));
    for (i = 0; i < size; i += width) {
        std::string merge;
        /* show hex to the left */
        for (c = 0; c < width; c++) {
            if (i + c < size){
                char buf3[30];
                sprintf(buf3, "%02x ", ptr[i + c]);
                merge.append(buf3);
            }
            else{
                merge.append("   ");
            }
        }
        /* show data on the right */
        for (c = 0; (c < width) && (i + c < size); c++) {
            char x = (ptr[i + c] >= 0x20 && ptr[i + c] < 0x80) ? ptr[i + c] : '.';
            char *p = &x;
            merge.append(p);
        }
        printMsg2("left:::right>>>>>>>>>>",string2char(merge));
    }

}

static
int my_trace(CURL *handle, curl_infotype type,
             char *data, size_t size,
             void *userp) {
    const char *text;
    (void) handle; /* prevent compiler warning */
    (void) userp;

    switch (type) {
        case CURLINFO_TEXT:
            printMsg2("cURL Info>>>>>>>>>", data);
//            fprintf(stderr, "== Info: %s", data);
        default: /* in case a new one is introduced to shock us */
            return 0;

        case CURLINFO_HEADER_OUT:
            text = "=> Send header";
            break;
        case CURLINFO_DATA_OUT:
            text = "=> Send data";
            break;
        case CURLINFO_SSL_DATA_OUT:
            text = "=> Send SSL data";
            break;
        case CURLINFO_HEADER_IN:
            text = "<= Recv header";
            break;
        case CURLINFO_DATA_IN:
            text = "<= Recv data";
            break;
        case CURLINFO_SSL_DATA_IN:
            text = "<= Recv SSL data";
            break;
    }

//    dump(text,  (unsigned char *) data, size);
    return 0;
}


class WebTask {
public:
    WebTask();

    ~WebTask();


    void SetUrl(const char *url);

    void SetCallback(on_web_done_t cb, void *para = NULL);

    void AddPostString(const char *item_name, const char *item_data);

    void AddPostPicture(const char *item_name, const char *file_path, const char *file_name = NULL);

    // must call DoGetString() or DoGetFile() before start task
    int DoGetString();

    // must call DoGetString() or DoGetFile() before start task
    // range like "0-255"
    int DoGetFile(const char *range = NULL);

    int WaitTaskDone();

    const char *GetResultString();

    const char *GetFilePath();

    /**
     * @timeo seconds
     */
    void SetConnectTimeout(int timeo);

    bool  checkNetWorkAvailable();

    void useSSl(bool used);

    void userAgent(const char *agent);

    void addHeader(JNIEnv *env,_jobjectArray * header);

    void setDebugMode(bool debug);


    CURL *m_curl;
    //CURLM *m_curl_m;

    int m_is_getfile;

    // if call DoGetString or DoGetFile
    bool m_do_func_called;

    //for post
    struct curl_httppost *m_formpost;
    struct curl_httppost *m_lastptr;
    struct curl_slist *m_headerlist;

    on_web_done_t m_cb;
    void *m_cb_para;

    //for download file
    FILE *m_file;
    std::string m_filepath;

    int m_web_result;

    //for tracer
    std::string m_url;

private:
    void _init();

    void _add_post_file(const char *item_name, const char *file_path, const char *file_name,
                        const char *content_type);

    int _on_work_done(int result);

    web_buffer_t m_web_buf;

private:
    WebTask(const WebTask &);

    WebTask &operator=(const WebTask &);
};

#endif




