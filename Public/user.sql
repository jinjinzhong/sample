/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 50617
Source Host           : localhost:3306
Source Database       : test

Target Server Type    : MYSQL
Target Server Version : 50617
File Encoding         : 65001

Date: 2016-10-25 21:41:45
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `user`
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `name` char(25) NOT NULL DEFAULT '',
  `mobile` char(11) NOT NULL DEFAULT '0',
  `regtime` timestamp NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=31 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES ('1', 'lsgozj', '12345678910', '2016-10-08 21:11:34');
INSERT INTO `user` VALUES ('2', 'test', '21345678', '2016-10-07 06:43:11');
INSERT INTO `user` VALUES ('3', 'zhongjin', '453464564', '2016-10-09 12:41:02');
INSERT INTO `user` VALUES ('4', 'jinjin', '908765', '2016-10-09 12:41:19');
INSERT INTO `user` VALUES ('30', '???', '12345678910', '2016-10-08 21:11:34');
