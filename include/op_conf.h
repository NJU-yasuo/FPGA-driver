/**
 * @file op_conf.h
 * @author Yizhi
 * @brief Data Structures and Functions for the users' of the driver to give the op's runtime info. 
 * @version 0.1
 * @date 2019-06-26
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __FX_HPCA_OP_CONF_H__
#define __FX_HPCA_OP_CONF_H__
#include <stdint.h>
#include <stdbool.h>
#define V_MAX_LAYER 4

typedef enum
{
	TASK_NULL = 0,
	TASK_01,
	TASK_02,
	TASK_03
} task_id_enum_t;

// this struct controls how to write to / read from FPGA DDR
// filename and buffer_address cannot be NON-NULL at the same time.
// if both filename and buffer_address are NULL, then not DDR access will happen.
// if filename is non NULL, then memcpy between file and DDR
// if buffer_address is non NULL, then memcpy between buffer_address and DDR
typedef struct
{
	char filename[100];
	void *buffer_address;
	uint32_t ddr_base_address;
	uint32_t info_size;
} fpga_access_info_t;

#define NUM_INPUT 5
#define NUM_OUTPUT 3

#define SKIP_REG_SIZE 14 * 4
typedef struct
{
	uint32_t value_at_reg_0x400;
	uint32_t value_at_reg_0x404;
	uint32_t value_at_reg_0x408;
	uint32_t value_at_reg_0x40c;
	fpga_access_info_t write_to_ddr[14];
} task1_weight_ini_t;

typedef struct
{
	uint32_t value_at_reg_0x400;
	uint32_t value_at_reg_0x404;
	uint32_t value_at_reg_0x408;
	uint32_t value_at_reg_0x40c;
	fpga_access_info_t write_to_ddr[60];

} task2_weight_ini_t;

typedef struct
{
	fpga_access_info_t write_to_ddr[NUM_INPUT];
	fpga_access_info_t read_from_ddr[NUM_OUTPUT];
	fpga_access_info_t read_verify[NUM_OUTPUT];
	//--------------------------------系统寄存器--------------------------------
	uint32_t value_at_reg_0x0; // sys_soft_rstn
	uint32_t value_at_reg_0x4; // intr_state
	uint32_t value_at_reg_0x8; // intr_mask
	uint32_t value_at_reg_0xc; // intr_clear
	//--------------------------------DMA寄存器--------------------------------
	//bias相关寄存器
	uint32_t value_at_reg_0x40; // dma_biasram_startaddr
	uint32_t value_at_reg_0x44; // dma_biasram_datanum
	uint32_t value_at_reg_0x48; // dma_biasram_start
	uint32_t value_at_reg_0x4c; // dma_biasram_done
	//bn_weight相关寄存器
	uint32_t value_at_reg_0x50; // dma_bnmulram_startaddr
	uint32_t value_at_reg_0x54; // dma_bnmulram_datanum
	uint32_t value_at_reg_0x58; // dma_bnmulram_start
	uint32_t value_at_reg_0x5c; // dma_bnmulram_done
	//bn_bias相关寄存器
	uint32_t value_at_reg_0x60; // dma_bnbiasram_startaddr
	uint32_t value_at_reg_0x64; // dma_bnbiasram_datanum
	uint32_t value_at_reg_0x68; // dma_bnbiasram_start
	uint32_t value_at_reg_0x6c; // dma_bnbiasram_done
	//weight相关寄存器
	uint32_t value_at_reg_0x70; // dma_weiram_startaddr
	uint32_t value_at_reg_0x74; // dma_weiram_datanum
	uint32_t value_at_reg_0x78; // dma_weiram_start
	uint32_t value_at_reg_0x7c; // dma_weiram_done
	//待处理数据写入相关寄存器
	uint32_t value_at_reg_0x80; // dma_wractram_startaddr
	uint32_t value_at_reg_0x84; // dma_wractram_datanum
	uint32_t value_at_reg_0x88; // dma_wractram_start
	uint32_t value_at_reg_0x8c; // dma_wractram_done
	//待处理数据读取相关寄存器
	uint32_t value_at_reg_0x90; // dma_rdactram_startaddr
	uint32_t value_at_reg_0x94; // dma_rdactram_datanum
	uint32_t value_at_reg_0x98; // dma_rdactram_start
	uint32_t value_at_reg_0x9c; // dma_rdactram_done
	//dma控制相关寄存器
	uint32_t value_at_reg_0xa0; // dam_ctrl_src
	uint32_t value_at_reg_0xa4; // dam_repeat_threshold
	//--------------------------------IPCore子系统寄存器--------------------------------
	uint32_t value_at_reg_0xf0;  // sel_dram_sram_bank
	uint32_t value_at_reg_0xf4;  // col_olap_ram_addr_offset
	uint32_t value_at_reg_0xf8;  // row_olap_ram_addr_offset
	uint32_t value_at_reg_0xfc;  // who_provide_input
	uint32_t value_at_reg_0x100; // who_provide_output
	uint32_t value_at_reg_0x104; // who_provide_res_input
	uint32_t value_at_reg_0x108; // which_act_bank_in
	uint32_t value_at_reg_0x10c; // which_act_bank_out
	uint32_t value_at_reg_0x110; // which_res_act_bank_in
	uint32_t value_at_reg_0x118; // need_fetch_another_wei_buff
	uint32_t value_at_reg_0x11c; // out_channel_01
	uint32_t value_at_reg_0x120; // out_channel_23
	uint32_t value_at_reg_0x130; // kernel_size
	uint32_t value_at_reg_0x13c; // p_in
	uint32_t value_at_reg_0x140; // p_out
	uint32_t value_at_reg_0x144; // v_layer
	uint32_t value_at_reg_0x148; // bn_layer
	uint32_t value_at_reg_0x14c; // relu_layer
	uint32_t value_at_reg_0x150; // resaddr_layer
	uint32_t value_at_reg_0x154; // max_fetch_wei_buf
	uint32_t value_at_reg_0x158; // quan_value_of_six
	uint32_t value_at_reg_0x15c; // selov_ram_to_read
	uint32_t value_at_reg_0x160; // last_layer_stride
	uint32_t value_at_reg_0x164; // first_tile
	uint32_t value_at_reg_0x168; // sel_relu6
	uint32_t value_at_reg_0x16c; // row_olap_valid
	uint32_t value_at_reg_0x170; // frac_in
	uint32_t value_at_reg_0x174; // frac_out
	uint32_t value_at_reg_0x178; // pool_state
	uint32_t value_at_reg_0x17c; // start_run_op
	uint32_t value_at_reg_0x180; // pool_start
	uint32_t value_at_reg_0x184; // ram2ddr_start_addr
	uint32_t value_at_reg_0x188; // ram2ddr_byte_num
	uint32_t value_at_reg_0x18c; // ddr2ram_start_addr1
	uint32_t value_at_reg_0x190; // ddr2ram_start_addr2
	uint32_t value_at_reg_0x194; // ddr2ram_start_addr3
	uint32_t value_at_reg_0x198; // ddr2ram_start_addr4
	uint32_t value_at_reg_0x19c; // ddr2ram_byte_num
	uint32_t value_at_reg_0x1a0; // pool_finish
	uint32_t value_at_reg_0x1a4; // pool_finish_flag
	uint32_t value_at_reg_0x1a8; // pool_busy
	uint32_t value_at_reg_0x1ac; // compute_done
	uint32_t value_at_reg_0x1b0; // actram_master
} op_config_t;					 //存储全部寄存器信息的结构体

typedef struct
{
	/*  
		net_type = 0 : task2 
		net_type = 1 : resnet_50; 
		net_type = 2 : resnet_18;
		net_type = 3 : mobilenet;
	*/
	uint8_t net_type;
	uint8_t sub_id;
	uint8_t block_id;
	uint8_t start_block;

	//结构图给出
	uint8_t col;
	uint8_t row;
	uint8_t blockstride;
	uint32_t in_channels[4];
	uint32_t out_channels[4]; //12bit
	uint8_t kernel_sizes[4];  //8bit
	uint8_t p_out[4];
	uint8_t p_in[4];

	//V_layer相关
	uint8_t v_layer;
	uint8_t ResAddLayer;
	uint8_t BNLayer;
	uint8_t ReLULayer;
	uint8_t QuanValueOfSix;

	uint16_t ColOvlapOffset;
	uint16_t RowOvlapOffset;
	uint8_t SelOvRAMtoRead;
	uint8_t input_buffer_seq[4];
	uint8_t output_buffer_seq[4];
	uint8_t res_input_buffer;

	//col相关
	uint8_t act_bank_in_seq[4];
	uint8_t act_bank_out_seq[4];
	uint8_t res_act_bank_in;

	//其他
	uint8_t frac_in;
	uint8_t frac_out;
	uint8_t which_prebn_act_bank;
	uint8_t pre_bn;
	uint8_t DWConv;
	uint8_t LastlayerStride;

	uint32_t Act_IN_TILE_SIZE;
	uint32_t Act_OUT_TILE_SIZE;
	uint32_t Act_TOTAL_IN_SIZE;

	//每个Tile需要改变的值
	uint8_t FirstTile;
	uint8_t RowOlapValid;
	uint8_t write_both_banks;

	//block change
	uint8_t SelRelu6;
	// uint8_t V_MAX_GROUP;
	// uint32_t V_WEI_BANK_DEPTH;
	uint8_t Last_block_stride;
	uint32_t num_valid_weights;

	//addr 相关
	uint32_t wei_base_addr;
	uint32_t bias_base_addr;
	uint32_t bn_wei_base_addr;
	uint32_t bn_bias_base_addr;
	uint32_t act_ram_rd_base_addr;
	uint32_t act_ram_write_base_addr;

} op_ini_param_t; //存储所有计算寄存器需要值的结构体

#endif
