<?php
/**
 * author:LSGOZJ
 * time:2016/10/9 21:15
 * description:处理路由，解析控制器和方法，获取函数列表
 */
namespace Core\lib;
//引入配置文件
use Core\lib\config;

class route
{

    public $controller;
    //在restful中，action又$_SERVER['REQUEST_METHOD']获取
    public $action;

    public function __construct()
    {
        //xxx.com/Index/Index   访问Index控制器下的Index方法
        /*
         * 1、隐藏index.php（利用apache的URL重写规则（.htaccess）实现）
         * 2、获取URL参数部分
         * 3、返回对应控制器和方法
         */
       
        //开始解析URL
        if (isset($_SERVER['PATH_INFO']) && $_SERVER['PATH_INFO'] != '/') {
            //  /Index/Index => Index/Index
            $path = $_SERVER['PATH_INFO'];
            
            $path = trim($path, '/');
            $pathArr = explode('/', $path);
            if (isset($pathArr[0])) {
                $this->controller = ucfirst($pathArr[0]);
                unset($pathArr[0]);
            }

            //在restful中，action部分用$_SERVER['REQUEST_METHOD']来辨别
//            if (isset($pathArr[1])) {
//                $this->action = $pathArr[1];
//                unset($pathArr[1]);
//            } else {
//                $this->action = config::get('ACTION','route');
//            }

            if(in_array(strtolower($_SERVER['REQUEST_METHOD']),array('get','post','put','delete'))){
                $this->action = ucfirst(strtolower($_SERVER['REQUEST_METHOD']));
            }else{
                $this->action = config::get('ACTION','route');
            }

            //为了获取参数，需要将URL中的多余部分转换成GET
            //用这种形式 /id/3/name/zhongjin

            $count = count($pathArr) + 1;
            $i = 1;
            while ($i < $count) {
                //避免第5个参数
                if (isset($pathArr[$i + 1])) {
                    $_GET[$pathArr[$i]] = $pathArr[$i + 1];
                }
                $i += 2;
            }

        } else {
            //取访问的默认值
            $this->controller = config::get('CONTROLLER','route');
            $this->action = config::get('ACTION','route');
        }
    }
}