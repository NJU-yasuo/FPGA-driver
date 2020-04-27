/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YKLiu
 * @Date: 2020-02-08 23:47:43
 * @LastEditTime: 2020-03-05 17:02:01
 */

#ifndef __OP_INI_H__
#define __OP_INI_H__
#include "op_conf.h"

extern op_ini_param_t block000_ini;
extern op_ini_param_t block001_ini;
extern op_ini_param_t block002_ini;
extern op_ini_param_t block003_ini;
extern op_ini_param_t block004_ini;
extern op_ini_param_t block005_ini;
extern op_ini_param_t block006_ini;
extern op_ini_param_t block007_ini;
extern op_ini_param_t block008_ini;
extern op_ini_param_t block009_ini;
extern op_ini_param_t block010_ini;
extern op_ini_param_t block011_ini;
extern op_ini_param_t block012_ini;
extern op_ini_param_t block013_ini;
extern op_ini_param_t block014_ini;
extern op_ini_param_t block015_ini;
extern op_ini_param_t block016_ini;
extern op_ini_param_t block017_ini;
extern op_ini_param_t block018_ini;
extern op_ini_param_t block019_ini;
extern op_ini_param_t block020_ini;
extern op_ini_param_t block023_ini;
extern op_ini_param_t block024_ini;

extern task1_weight_ini_t task1_weight;
extern task2_weight_ini_t task2_weight;

extern op_ini_param_t resnet50_block00_ini;
extern op_ini_param_t resnet50_block01_ini;
extern op_ini_param_t resnet50_block02_ini;
extern op_ini_param_t resnet50_block03_ini;

extern op_ini_param_t resnet18_block00_ini;
extern op_ini_param_t resnet18_block01_ini;

extern op_ini_param_t mobilenet_block00_ini;
extern op_ini_param_t mobilenet_block01_ini;
extern op_ini_param_t mobilenet_block02_ini;

void test_set(op_config_t *op_config, op_ini_param_t *op_param, int row_num, int col_1, int col_2);
#endif
