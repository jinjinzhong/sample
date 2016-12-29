<?php
/**
 * author:LSGOZJ
 * time:2016/10/19 9:29
 * description:<添加简要说明>
 */


namespace Core\lib\drive\responce;


abstract class responce
{
    public abstract function Encode($code, $msg, array $data);
}