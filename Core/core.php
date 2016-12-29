<?php

/**
 * author:LSGOZJ
 * time:2016/10/9 21:09
 * description:加载框架的核心文件
 */
namespace core;

class core
{
    public $assign;
    public static $classMap = array();

    //启动框架所要调用的方法
    public static function run()
    {
        //写日志
//        logData('modified by zhongjin');
        //写缓存
//        cacheData('name','zhongjin',3600);
        //加载路由

        $route = new \Core\lib\route();
        $controller = $route->controller;
        $action = $route->action;
        $controllerFile = APP . '/Controller/' . $controller . 'Controller.php';
        $controllerClass = CONTROLLER . '\\' . $controller . 'Controller';
        if (file_exists($controllerFile)) {
            include $controllerFile;
            $ctrl = new $controllerClass();
            if (method_exists($ctrl, $action)) {
                $ctrl->$action();
            } else {
                //控制器中的方法不存在
                throw new \Exception($controller . "控制器中不存在" . $action . '方法！');
            }
        } else {
            //控制器对应的类文件不存在
            throw new \Exception($controller . "控制器不存在！");
        }
    }

    //自动加载类库
    public static function load($class)
    {
        if (isset(self::$classMap[$class])) {
            //避免重复加载
            return true;
        } else {
            //替换反斜线
            $class = str_replace('\\', '/', $class);
            $file = BASEDIR . '/' . $class . '.php';
            if (file_exists($file)) {
                include $file;
                self::$classMap[$class] = $class;
            } else {
                throw new \Exception("类文件".$file."不存在！");
                return false;
            }
        }
    }

    //mvc中用到
//    public function assign($name,$value)
//    {
//        $this->assign[$name] = $value;
//    }
//
//    public function display($file)
//    {
//        $file = APP.'/Views/'.$file;
//        if(file_exists($file)){
//            //该函数使用数组键名作为变量名，使用数组键值作为变量值
//            extract($this->assign);
//            include $file;
//        }
//    }
}