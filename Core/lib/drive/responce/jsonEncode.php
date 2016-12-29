<?php

/**
 * author:LSGOZJ
 * time:2016/10/19 9:02
 * description:<添加简要说明>
 */

namespace Core\lib\drive\responce;

class jsonEncode extends responce
{
    /**
     *按json方式输出通信数据
     * @param int $code 状态码
     * @param string $msg 提示信息
     * @param array $data 数据
     * @return string
     */
    public function Encode($code, $msg, array $data)
    {
        if (!is_numeric($code)) {
            throw new Exception('状态码异常！');
        }
        $result = array(
            'code' => $code,
            'msg' => $msg,
            'data' => $data,
        );
        //header("Access-Control-Allow-Origin: *");//定义输出的类型
        return json_encode($result);
    }
}