<?php
/**
 * author:LSGOZJ
 * time:2016/10/9 20:46
 * description:入口文件
 * 入口文件功能：
 * 1、定义常量 2、加载函数库 3、启动框架
 */

date_default_timezone_set('Asia/Shanghai');

//定义全局常量

//当前框架的根目录
define('BASEDIR', __DIR__);
//框架核心文件所处目录
define('CORE', BASEDIR . '/Core');
//应用逻辑及模型所在目录
define('APP', BASEDIR . '/App');
//这里使用命名空间，所以是反斜杠
define('CONTROLLER', 'App\Controller');

//引入composer添加的类
include 'vendor/autoload.php';

//是否开启调试模式
define('DEBUG', TRUE);

if (DEBUG) {
    //错误类展现形式
    $whoops = new \Whoops\Run;
    $errorTitle = "我们的框架出错啦！";
    $option = new \Whoops\Handler\PrettyPageHandler;
    $option->setPageTitle($errorTitle);
    $whoops->pushHandler($option);
    $whoops->register();

    ini_set('display_error', 'On');
} else {
    ini_set('display_error', 'Off');
}

//加载函数库
include CORE . '/common/function.php';

//加载框架的核心文件
include CORE . '/core.php';

//实现类文件自动加载
spl_autoload_register("core\\core::load");

try {
    core\core::run();
} catch (Exception $e) {
    //定制错误输出
    dump($e->getMessage());
}
