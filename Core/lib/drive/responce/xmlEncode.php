<?php
/**
 * author:LSGOZJ
 * time:2016/10/19 9:02
 * description:<添加简要说明>
 */


namespace Core\lib\drive\responce;

class xmlEncode extends responce
{
    /**
     *按xml方式输出通信数据(万能)
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
        //header('Content-Type:text/xml');
        $xml = "<?xml version='1.0' encoding='UTF-8'?>" . PHP_EOL;
        $xml .= "<data>" . PHP_EOL;
        $xml .= $this->data_to_xml($result);
        $xml .= "</data>";

        //header("Access-Control-Allow-Origin: *");//定义输出的类型
        return $xml;
    }

    /**
     * 将数组转换为xml格式的数据（配合xmlEncode()一起使用）
     * @param array $arr 要转换的数组
     * @return string
     */
    private function data_to_xml($arr)
    {
        $xml = $attr = "";
        foreach ($arr as $key => $val) {
            if (is_numeric($key)) {
                $attr = "id='{$key}'";
                $key = "item";
            }
            $xml .= "<{$key} {$attr}>\r\n";
            $xml .= (is_array($val) ? self::data_to_xml($val) : $val) . PHP_EOL;
            $xml .= "</{$key}>" . PHP_EOL;
        }
        return $xml;
    }
}