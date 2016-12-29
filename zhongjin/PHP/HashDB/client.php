<?php
/**
 * Created by PhpStorm.
 * User: zhongjin
 * Date: 2016/11/10
 * Time: 19:26
 */

//测试
class Client{
    public static function Insert(){
        require "HashDB.php";
        $db = new DB();
        $db->open("dbtest");

        $start_time = explode(" ",microtime());
        $start_time = $start_time[0] + $start_time[1];

        for($i = 0;$i < 10000;$i ++){
            $db->insert("key".$i,"value".$i);
        }

        $end_time = explode(" ",microtime());
        $end_time = $end_time[0] + $end_time[1];

        $db->close();
        echo "Process time in ".($end_time-$start_time)." seconds";
    }
    public static function Select(){
        include("HashDB.php");
        $db = new DB();
        $db->open("dbtest");

        $start_time = explode(" ",microtime());
        $start_time = $start_time[0] + $start_time[1];

        for($i = 0;$i < 10000;$i ++){
            $db->fetch("key".$i);
        }
        $end_time = explode(" ",microtime());
        $end_time = $end_time[0] + $end_time[1];

        $db->close();
        echo 'Process time in '.($end_time - $start_time)." seconds";
    }
}
//Client::Insert();
//CLient::Select();