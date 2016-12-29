<?php
//使用PHP实现Hash表
// class HashTable{
// 	//存储数据的数组
// 	private $buckets;
// 	//存储数组的大小
// 	private $size = 10;

// 	public function __construct(){
// 		//为$buckets数组分配内存
// 		$this->buckets = new SplFixedArray($this->size);
// 	}
// 	//hash函数
// 	private function HashFunc($key){
// 		$strlen = strlen($key);
// 		$hashval = 0;
// 		for($i = 0;$i < $strlen;$i ++){
// 			$hashval += ord($key{$i});	//取字符的ASCII码
// 		}
// 		return $hashval % $this->size;
// 	}
// 	//插入
// 	public function Insert($key,$value){
// 		$hash = $this->HashFunc($key);
// 		$this->buckets[$hash] = $value;
// 	}
// 	//查找
// 	public function Find($key){
// 		$hash = $this->HashFunc($key);
// 		return $this->buckets[$hash];
// 	}
// }
// 

//拉链法解决Hash冲突
//结点
class HashNode{
	public $key;
	public $value;
	public $nextNode;
	public function __construct($key,$value,$nextNode = NULL){
		$this->key = $key;
		$this->value = $value;
		$this->nextNode = $nextNode;
	}
}
class HashTable{
	//存储数据的数组
	private $buckets;
	//存储数组的大小
	private $size = 10;

	public function __construct(){
		//为$buckets数组分配内存
		$this->buckets = new SplFixedArray($this->size);
	}
	//hash函数
	private function HashFunc($key){
		$strlen = strlen($key);
		$hashval = 0;
		for($i = 0;$i < $strlen;$i ++){
			$hashval += ord($key{$i});	//取字符的ASCII码
		}
		return $hashval % $this->size;
	}
	//插入
	public function Insert($key,$value){
		$hash = $this->HashFunc($key);
		//新创建一个结点
		if(isset($this->buckets[$hash])){
			$newNode = new HashNode($key,$value,$this->buckets[$hash]);
		}else{
			$newNode = new HashNode($key,$value,NULL);
		}
		$this->buckets[$hash] = $newNode;	//保存新节点
	}
	//查找
	public function Find($key){
		$hash = $this->HashFunc($key);
		$current = $this->buckets[$hash];
		while(isset($current)){
			if($current->key == $key){
				return $current->value;
			}
			$current = $current->nextNode;
		}
		return NULL;
	}
}



class Client{
	public static function Main(){
		$hashtable = new HashTable();
		$hashtable->Insert("key1","value1");
		$hashtable->Insert("key12","value2");

		echo $hashtable->Find("key1");
		echo $hashtable->Find("key12");
	}
}

Client::Main();