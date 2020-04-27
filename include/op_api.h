/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YKLiu
 * @Date: 2020-03-02 11:27:58
 * @LastEditTime: 2020-03-05 18:02:08
 */
#ifndef __FX_HPCA_OP_API_H__
#define __FX_HPCA_OP_API_H__
#include "op_conf.h"

bool call_op(op_config_t *op_config);

void fc_layer(uint8_t output[4][256][8][8], float matrix1[256][2], float matrix2[1][2], float result[2]);

void global_pool(uint8_t matrix[4][256][8][8], float result[256]);

void image_process(float matrix[3][32][128], float result[3][32][128]);

void in_place_image_process(uint8_t *img_trunks_ptr[]);

uint8_t to_fixed_point(float f);

float to_float_point(uint8_t u);

void post_process(uint8_t matrix[4][256][8][8], float res[2]);

bool task1_pre_process(char *filename, uint8_t *img_trunks_ptr[]);

int task1_call_ops(uint8_t *img_ptr, uint8_t *output_ptr);

void soft_cnn_compute(int block_id);

bool task2_set_op(op_ini_param_t *op_param, void *img_ptr, void *output_ptr, int start_block, int end_block);

bool resnet50_set_op(op_ini_param_t *op_param, void *img_ptr, void *output_ptr, int start_block, int test_block);

bool resnet18_set_op(op_ini_param_t *op_param, void *img_ptr, void *output_ptr, int start_block, int test_block);

bool mobilenet_set_op(op_ini_param_t *op_param, void *img_ptr, void *output_ptr, int start_block, int test_block);

bool resnet50_test_block(int start_block, int end_block, int net_type);

bool task2_test_block(int start_block, int end_block);

void task2_initial_weight(int start_block);

void resnet50_initial_weight(int net_type, int block_id);

void task2_test_fc();

void task2_test_pooling();

bool call_pooling(op_config_t *op_config);

#endif
