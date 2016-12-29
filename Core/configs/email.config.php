<?php
/**
 * author:LSGOZJ
 * time:2016/10/17 12:06
 * description:邮箱配置文件
 */
namespace Core\configs;

$config = array(
    // 配置邮件发送服务器
    'MAIL_DEBUG'     =>  0,   // 是否启用smtp的debug进行调试
    'MAIL_HOST'      =>  'smtp.qq.com',   // SMTP服务器地址
    'MAIL_HOSTNAME'  =>  'http://lsgozj.cn',   // 设置发件人的主机域
    'MAIL_PORT'  	 =>  465,  //设置ssl连接smtp服务器的远程服务器端口号 可选465或587
    'MAIL_SMTPAUTH'  =>  TRUE, //启用smtp认证
    'MAIL_USERNAME'  =>  '1054840542@qq.com',  // 用户名
    'MAIL_FROM'      =>  '1054840542@qq.com',  // 邮箱地址
    'MAIL_FROMNAME'  =>  '华北电力大学数理系美国数学建模报名系统',  // 发件人姓名
    'MAIL_PASSWORD'  =>  'yacytiiryfzsbbif',  //smtp登录的密码 使用生成的授权码
    'MAIL_CHARSET'   =>  'UTF-8',   // 字符集
    'MAIL_ISHTML'    =>  TRUE, // 是否HTML格式邮件
    'MAIL_REPLYTO'   =>  '1054840542@qq.com',   //用户回复邮件时的接收邮箱，可以与原始邮箱分开
    //抄送就是 你写的这封邮件除了传送给收件人，还会传送给你在抄送一栏里写的邮箱地址，并且收件人知道你把这封邮件发给了他和抄送一栏里输入的邮件地址的人
    //密送就是 你写的这封邮件除了传送给收件人，还会传送给你在暗送一栏里写的邮箱地址，但是收件人不知道你把这封邮件发给了暗送一栏里输入的邮件地址的人
    'MAIL_CC'        =>  '',    //抄送者
    'MAIL_BCC'       =>  '',    //密送着
);

return $config;