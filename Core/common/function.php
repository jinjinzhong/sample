<?php
/**
 * author:LSGOZJ
 * time:2016/10/9 21:01
 * description:公共函数库
 */

//引入配置文件
use Core\lib\config;

/**
 * 写日志
 * @param $content 存日志的内容 $file 指定日志文件
 * @return null
 */
function logData($content, $file = 'log')
{
    \Core\lib\log::init();
    \Core\lib\log::log($content, $file);
}

/**
 * 将返回信息格式化后返回给客户端
 * @param $key 键 $value 键值 $time 缓存时间
 * @说明：1、cacheData($key)获取键值  2、cacheData($key,$val)缓存键值  3、cacheData($key,$val,$time)缓存键值，时间$time  4、cacheData($key,null)删除缓存$key
 * @return null
 */
function cacheData($key, $value = '', $time = 0)
{
    \Core\lib\cache::init();
    return \Core\lib\cache::cache($key, $value, $time);
}

/**
 * 将返回信息格式化后返回给客户端
 * @param $code 状态码 $msg 提示信息 $data 返回数据 $type 返回格式 json : xml
 * @return null
 */
function responce($code, $msg = '', $data = array())
{
    \Core\lib\responce::init();
    \Core\lib\responce::Encode($code, $msg, $data);
}

/**
 * 生成token
 * param $uid 用户id
 * return string token
 */
function getToken($uid = 0)
{
    $str = null;
    $strPol = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz";
    $max = strlen($strPol) - 1;
    for ($i = 0; $i < 20; $i++) {
        $str .= $strPol[rand(0, $max)];//rand($min,$max)生成介于min和max两个数之间的一个随机整数
    }
    $str .= time();
    $str .= $uid;
    return md5($str);
}

/**
 * 检测用户是否是登录
 * param $token 用户token
 * return
 */
function is_login($token)
{
    if (!cacheData($token)) {
        $code = 401;
        $msg = '请重新登录！';
        responce($code, $msg);
    }
}

/**
 * 发送邮件方法
 * @param $to ：接收者 $title：标题 $content：邮件内容
 */
function sendMail($to, $title, $content)
{
    //实例化PHPMailer核心类
    $mail = new PHPMailer;

    $config = config::all('email');

    //使用smtp鉴权方式发送邮件
    $mail->isSMTP();
    //链接qq域名邮箱的服务器地址
    $mail->Host = $config['MAIL_HOST'];
    //smtp需要鉴权 这个必须是true
    $mail->SMTPAuth = $config['MAIL_SMTPAUTH'];
    //smtp登录的账号 这里填入字符串格式的qq号即可
    $mail->Username = $config['MAIL_USERNAME'];
    //smtp登录的密码 使用生成的授权码
    $mail->Password = $config['MAIL_PASSWORD'];
    //设置使用ssl加密方式登录鉴权
    $mail->SMTPSecure = 'ssl';
    //设置ssl连接smtp服务器的远程服务器端口号 可选465或587
    $mail->Port = $config['MAIL_PORT'];
    //设置发送的邮件的编码 可选GB2312 我喜欢utf-8 据说utf8在某些客户端收信下会乱码
    $mail->CharSet = $config['MAIL_CHARSET'];
    $mail->setFrom($config['MAIL_FROM'], $config['MAIL_FROMNAME']);
    //设置收件人邮箱地址 该方法有两个参数 第一个参数为收件人邮箱地址 第二参数为给该地址设置的昵称 不同的邮箱系统会自动进行处理变动 这里第二个参数的意义不大
    //添加多个收件人 则多次调用方法即可
    // $mail->addAddress('xxx@163.com','晶晶在线用户');
    $mail->addAddress($to);

    //设置用户回复的邮箱
    $mail->addReplyTo($config['MAIL_REPLYTO']);

    //设置抄送人
    $mail->addCC($config['MAIL_CC']);
    //密送者，Mail Header不会显示密送者信息
    $mail->addBCC($config['MAIL_BCC']);

//    $mail->addAttachment('/var/tmp/file.tar.gz');         // 添加附件
//    $mail->addAttachment('/tmp/image.jpg', 'new.jpg');    // Optional name
    //邮件正文是否为html编码 注意此处是一个方法 不再是属性 true或false
    $mail->isHTML($config['MAIL_ISHTML']);

    //添加该邮件的主题
    $mail->Subject = $title;
    //添加邮件正文 上方将isHTML设置成了true，则可以是完整的html字符串 如：使用file_get_contents函数读取本地的html文件
    $mail->Body = $content;
    //添加邮件正文 上方将isHTML设置成了false时调用
    $mail->AltBody = strip_tags($content);

    if (!$mail->send()) {
        throw new \Exception('邮件发送失败！请检查相关配置！');
    }

}