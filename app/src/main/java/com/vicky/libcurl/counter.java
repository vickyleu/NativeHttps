package com.vicky.libcurl;


import java.text.DecimalFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.Scanner;

public class counter {
    public static final String day = "天";
    public static final String hour = "小时";
    public static final String min = "分钟";
    public static final String sec = "秒";

    public static final List<String> list = new ArrayList<String>() {
        {
            add(day);
            add(hour);
            add(min);
            add(sec);
        }
    };

    public static void main(String[] args) {
        counter counter = new counter();
        counter.begin();

    }

    long bet = 0;

    public void begin() {
        Scanner scanner = new Scanner(System.in);
        int type = -1;
        System.out.println("输入1为累加,输入其他为减,5为转换时间为小时");
        try {
            type = scanner.nextInt();
        } catch (Exception e) {
        }

        currentTime = "";
        try {
            long d1 = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.CHINA).parse("1970-01-01 00:00:00").getTime();
//            long d2 = new SimpleDateFormat("dd HH:mm:ss", Locale.CHINA).parse("02 00:00:00").getTime();
//            long d3 = d2 - d1;
            bet = d1 /*- d3*/;
        } catch (ParseException e) {
            e.printStackTrace();
        }
        if (bet == 0) {
            System.out.println("运行时错误");
            return;
        }

        if (type == 5) {
            start(type, scanner, "请输入待转换时间!!!");
            return;
        }


        start(type, scanner, "请输入起始时间!!!");
    }

    private String currentTime = "";


    private void start(int type, Scanner scanner, String tips) {
        System.out.println(tips);
        String str = null;
        try {
            str = scanner.next();
        } catch (Exception E) {

        }
        boolean var = false;
        for (int i = 0; i < list.size(); i++) {
            boolean b = str.contains(list.get(i));
            if (!b) continue;
            var = true;
            break;
        }

        if (TextUtils.isEmpty(str) || !var) {
            if (type != 5)
                System.out.println("起始时间不正确");
            else System.out.println("待转换时间不正确");
            start(type, scanner, tips);
            return;
        }
        if (type == 5) {
            try {
                Date d1 = getDate(str);
                System.out.println(d1);
                int sec = (int) ((d1.getTime() - bet) / 1000);
                float sec2 = (float) ((d1.getTime() - bet) / 1000);
                float h2 = sec2 / 3600;
                DecimalFormat fnum = new DecimalFormat("##0.0");
                String dd = fnum.format(h2);
                System.out.println(dd+"小时");
                if (sec < 60) {
                    System.out.println(0 + "时" + 0 + "分" + sec + "秒");
                    exit(type,scanner);
                    return;
                }
                int h = sec / 3600;
                int m = (sec % 3600) / 60;
                int s = (sec % 3600) % 60;
                System.out.println(h + "时" + m + "分" + s + "秒");
                exit(type,scanner);
            } catch (ParseException e) {
                e.printStackTrace();
            }

            return;
        }
        if (TextUtils.isEmpty(currentTime)) {
            currentTime = str;
            start(type, scanner, "请输入结束时间!!!");
        } else {
            try {
                Date d1 = getDate(currentTime);
                Date d2 = getDate(str);
//                long dt1 = d1.getTime() - bet;
//                long dt2 = d2.getTime() - bet;

                Calendar cal = Calendar.getInstance();
                cal.setTime(d1);
                Calendar cal2 = Calendar.getInstance();
                cal2.setTime(d2);
                int day_of_month = cal2.get(Calendar.DAY_OF_MONTH) - 1;
                //当前时：HOUR_OF_DAY-24小时制；HOUR-12小时制
                int hour = cal2.get(Calendar.HOUR_OF_DAY);
                //当前分
                int minute = cal2.get(Calendar.MINUTE);
                //当前秒
                int second = cal2.get(Calendar.SECOND);

                if (type == 1) {
                    if (day_of_month >= 1)
                        cal.add(Calendar.DAY_OF_MONTH, day_of_month);//加时
                    cal.add(Calendar.HOUR_OF_DAY, hour);//加时
                    cal.add(Calendar.MINUTE, minute);//加分
                    cal.add(Calendar.SECOND, second);//加秒
                } else {
                    if (day_of_month >= 1)
                        cal.add(Calendar.DAY_OF_MONTH, -day_of_month);//加时
                    cal.add(Calendar.HOUR_OF_DAY, -hour);//加时
                    cal.add(Calendar.MINUTE, -minute);//加分
                    cal.add(Calendar.SECOND, -second);//加秒
                }

                System.out.println(cal.getTime());

//                long d3 = dt1 + dt2 + bet;
//                Date dResult = new Date();
//                dResult.setTime(d3);
//                Calendar calendar = Calendar.getInstance();
//                calendar.setTime(dResult);
//                int day_of_month = calendar.get(Calendar.DAY_OF_MONTH);

                String result = getStr(cal, cal2);
//                result = sdf1.format(cal.getTime());

                System.out.println("d1 = [" + d1 + "], d2 = [" + d2 + "]");
                System.out.println("result = [" + result + "]");
                currentTime = result;
                exit(type, scanner);

            } catch (ParseException e) {
                e.printStackTrace();
            }
        }
    }

    private String getStr(Calendar cal, Calendar cal2) {
        //当前月的第几天：即当前日
        int day_of_month = cal.get(Calendar.DAY_OF_MONTH) - 1;
        //当前时：HOUR_OF_DAY-24小时制；HOUR-12小时制
        int hour = cal.get(Calendar.HOUR_OF_DAY);
        //当前分
        int minute = cal.get(Calendar.MINUTE);
        //当前秒
        int second = cal.get(Calendar.SECOND);


//        int m = cal.get(Calendar.MONTH) - cal2.get(Calendar.MONTH);
//        if (m > 0) {
//
//        }
        String days = day_of_month < 0 ? "" : day_of_month + "天";
        String hours = hour < 0 ? "" : hour + "小时";
        String minutes = minute < 0 ? "" : minute + "分钟";
        String seconds = second < 0 ? "" : second + "秒";
        String s = days + hours + minutes + seconds;
        return s;
    }

    private void exit(int type, Scanner scanner) {
        System.out.println("继续计算请输入1,结束请按0,重新计算请按2");
        int exitCode = -1;
        try {
            exitCode = scanner.nextInt();
        } catch (Exception e) {

        }

        if (exitCode == 1) {
            start(type, scanner, "请输入结束时间!!!");
        } else if (exitCode == 0) {
            System.out.println("bye bye");
        } else if (exitCode == 2) {
            begin();
        } else {
            System.out.println("输入无效");
            exit(type, scanner);
        }
    }

    SimpleDateFormat sdf1 = new SimpleDateFormat("dd天HH小时mm分钟ss秒", Locale.CHINA);
    SimpleDateFormat sdf14 = new SimpleDateFormat("dd天mm分钟ss秒", Locale.CHINA);
    SimpleDateFormat sdf2 = new SimpleDateFormat("HH小时mm分钟ss秒", Locale.CHINA);
    SimpleDateFormat sdf3 = new SimpleDateFormat("mm分钟ss秒", Locale.CHINA);
    SimpleDateFormat sdf4 = new SimpleDateFormat("ss秒", Locale.CHINA);
    SimpleDateFormat sdf5 = new SimpleDateFormat("dd天HH小时mm分钟", Locale.CHINA);
    SimpleDateFormat sdf6 = new SimpleDateFormat("dd天HH小时", Locale.CHINA);
    SimpleDateFormat sdf7 = new SimpleDateFormat("dd天mm分钟", Locale.CHINA);
    SimpleDateFormat sdf8 = new SimpleDateFormat("HH小时mm分钟", Locale.CHINA);
    SimpleDateFormat sdf13 = new SimpleDateFormat("HH小时", Locale.CHINA);
    SimpleDateFormat sdf9 = new SimpleDateFormat("mm分钟", Locale.CHINA);
    SimpleDateFormat sdf10 = new SimpleDateFormat("dd天ss秒", Locale.CHINA);
    SimpleDateFormat sdf12 = new SimpleDateFormat("dd天", Locale.CHINA);
    SimpleDateFormat sdf11 = new SimpleDateFormat("HH小时ss秒", Locale.CHINA);


    private Date getDate(String currentTime) throws ParseException {
        Date d = null;
        if (currentTime.contains(day) && currentTime.contains(hour)
                && currentTime.contains(min) && currentTime.contains(sec)) {
            d = sdf1.parse(currentTime);
        } else if (currentTime.contains(day) && currentTime.contains(hour)
                && currentTime.contains(min)) {
            d = sdf5.parse(currentTime);
        } else if (currentTime.contains(day) && currentTime.contains(hour)) {
            d = sdf6.parse(currentTime);
        } else if (currentTime.contains(day)) {
            d = sdf12.parse(currentTime);
        } else if (currentTime.contains(hour)
                && currentTime.contains(min) && currentTime.contains(sec)) {
            d = sdf2.parse(currentTime);
        } else if (currentTime.contains(hour)
                && currentTime.contains(min)) {
            d = sdf8.parse(currentTime);
        } else if (currentTime.contains(hour)
                && currentTime.contains(sec)) {
            d = sdf11.parse(currentTime);
        } else if (currentTime.contains(hour)) {
            d = sdf13.parse(currentTime);
        } else if (currentTime.contains(min) && currentTime.contains(sec)) {
            d = sdf3.parse(currentTime);
        } else if (currentTime.contains(min)) {
            d = sdf9.parse(currentTime);
        } else if (currentTime.contains(sec)) {
            d = sdf4.parse(currentTime);
        } else if (currentTime.contains(day)
                && currentTime.contains(min) && currentTime.contains(sec)) {
            d = sdf14.parse(currentTime);
        } else if (currentTime.contains(day)
                && currentTime.contains(min)) {
            d = sdf7.parse(currentTime);
        } else if (currentTime.contains(day)
                && currentTime.contains(sec)) {
            d = sdf10.parse(currentTime);
        }
        Date dd = d;
        if (currentTime.contains(day)) {
            Calendar cal = Calendar.getInstance();
            cal.setTime(d);
            cal.add(Calendar.DAY_OF_MONTH, 1);
            dd = cal.getTime();
//            int day_of_month = cal.get(Calendar.DAY_OF_MONTH);
        }
        return dd;
    }

    private static class TextUtils {
        public static boolean isEmpty(String s) {
            return s == null || s.length() <= 0;
        }
    }
}