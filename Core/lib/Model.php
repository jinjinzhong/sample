<?php
/**
 * author:LSGOZJ
 * time:2016/10/10 22:00
 * description:<添加简要说明>
 */


namespace Core\lib;
//引入配置文件
use Core\lib\config;

//use PDO as PDO; //引入PDO命名空间

//class Model extends PDO
//{
//    public function __construct(){
//
////        $dsn = config::get('DB_MS','database').':host='.config::get('DB_HOST','database').';dbname='.config::get('DB_NAME','database');
////        $user = config::get('DB_USER','database');
////        $pwd = config::get('DB_PWD','database');
//        $dbconfig = config::all('database');
//        $dsn = $dbconfig['DB_MS'].':host='.$dbconfig['DB_HOST'].';dbname='.$dbconfig['DB_NAME'];
//        $user = $dbconfig['DB_USER'];
//        $pwd = $dbconfig['DB_PWD'];
//        try{
//            parent::__construct($dsn,$user,$pwd);
//        }catch (\PDOException $pdoerror){
//            echo $pdoerror->getMessage();
//        }
//    }
//}

//使用medoo轻量级数据库
class Model extends \medoo{
    public function __construct(){
        $option = config::all('database');
        parent::__construct($option);
    }
}