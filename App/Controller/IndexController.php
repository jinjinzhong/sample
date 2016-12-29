<?php

/**
 * author:LSGOZJ
 * time:2016/10/10 21:29
 */
namespace App\Controller;

class IndexController extends Controller{
    public function Index(){
        $user = new \App\Model\UserModel;
        $data = $user->lists();
        responce(200,'信息获取成功！',$data);
    }
    public function Get(){
        echo "Index get";
    }
    public function Post(){
    }
    public function Put(){
    }
    public function Delete(){
    }
}