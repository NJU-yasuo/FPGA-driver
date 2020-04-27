/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YKLiu
 * @Date: 2020-02-09 02:12:22
 * @LastEditTime: 2020-03-05 17:54:03
 */
/**
 * @file fx_hpca.h
 * @author Yizhi
 * @brief top header file for driver.
 * @version 0.1
 * @date 2019-06-26
 * top driver header
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef __FX_HPCA_TOP_HEADER_H__
#define __FX_HPCA_TOP_HEADER_H__
#include "op_conf.h"
//#include "config_regs.h"
#include "util.h"
#include "time.h"

// bool write_files_to_fpga(op_config_t *op_config);
bool read_files_from_fpga(op_config_t *op_config);

bool launch_op(op_config_t *op_config);
// bool launch_2X2_pooling(op_config_t *op_config);
bool initial_weight2(task2_weight_ini_t *weight_ini);
bool initial_weight_resnet50(int net_type, int block_id);
bool write_files_to_ddr(op_config_t *op_config);
//bool test_skip_write(op_config_t *op_config);
#endif
