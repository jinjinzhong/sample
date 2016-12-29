<?php
/**
 * Created by PhpStorm.
 * User: zhongjin
 * Date: 2016/11/1
 * Time: 8:52
 */

namespace App\Controller;

class UserController extends Controller
{
    //默认的方法
    public function Index(){
        responce(200,'信息获取成功！','这是默认的方法');
    }
    public function Get(){
        responce(200,'信息获取成功！',$_GET);
    }
    public function Post(){
        responce(200,'信息获取成功！',file_get_contents('php://input'));
    }

    public function Put(){
        responce(tn200,'信息获取成功！',file_get_contents('php://input'));
    }

    public function Delete(){
        responce(200,'信息获取成功！',file_get_contents('php://input'));
    }
}