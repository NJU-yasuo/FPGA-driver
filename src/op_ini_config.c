#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "op_ini_config.h"
#include "op_conf.h"
#include "parameter_addr.h"
#include "task2_parameter_addr.h"

#define V_WEI_BANK_DEPTH (1024)
#define V_MAX_GROUP (8)
#define DDR_BASE_ADDR (0x40000000)
#define V_ACT_TILE (64)
#define V_WEI_WIDTH (24)
#define V_WEI_BANK (8)

uint8_t log2_lookup(uint16_t val)
{
	if (val < 2)
		return 0;
	else if (val < 4)
		return 1;
	else if (val < 8)
		return 2;
	else if (val < 16)
		return 3;
	else if (val < 32)
		return 4;
	else if (val < 64)
		return 5;
	else if (val < 128)
		return 6;
	else if (val < 256)
		return 7;
	else if (val < 512)
		return 8;
	else if (val < 1024)
		return 9;
	else if (val < 2048)
		return 10;
	else
		return 11;
};

uint32_t Act_Output_Addr(int block_id, int sub_id, uint32_t Base_Addr, uint32_t Offset_unit)
{
	uint32_t Out_Addr;
	if ((block_id == 0) || (block_id == 2))
	{
		Out_Addr = Base_Addr + ((sub_id - 1) / 10) * (10 * Offset_unit);
		switch ((sub_id - 1) % 10)
		{
		case 0:
			Out_Addr = Out_Addr + Offset_unit * 0;
			break;
		case 5:
			Out_Addr = Out_Addr + Offset_unit * 1;
			break;
		case 1:
			Out_Addr = Out_Addr + Offset_unit * 2;
			break;
		case 6:
			Out_Addr = Out_Addr + Offset_unit * 3;
			break;
		case 2:
			Out_Addr = Out_Addr + Offset_unit * 4;
			break;
		case 7:
			Out_Addr = Out_Addr + Offset_unit * 5;
			break;
		case 3:
			Out_Addr = Out_Addr + Offset_unit * 6;
			break;
		case 8:
			Out_Addr = Out_Addr + Offset_unit * 7;
			break;
		case 4:
			Out_Addr = Out_Addr + Offset_unit * 8;
			break;
		case 9:
			Out_Addr = Out_Addr + Offset_unit * 9;
			break;
		default:
			printf("Act_Output_Addr Address error! \n");
		}
	}
	else
		Out_Addr = Base_Addr + Offset_unit * (sub_id - 1);
	return Out_Addr;
}

static void pick_up_runtime_conf_p3(op_ini_param_t *op_param, int col_num, int row_num)
{

	uint8_t max = 0;
	for (int i = 0; i < 4; i++)
	{
		if (op_param->p_out[i] > max)
			max = op_param->p_out[i];
	}
	op_param->FirstTile = col_num == 0;
	op_param->RowOlapValid = row_num != 0;
	op_param->write_both_banks = !((max == 2) & (!(col_num & 0x1)));
}

static int ddr_transfer_byte_num_gen(int trans_unit, int origin_byte_num)
{
	int res;
	res = origin_byte_num % trans_unit;
	if (res != 0)
		return origin_byte_num - res + trans_unit;
	else
		return origin_byte_num;
}

static void pick_up_runtime_conf_p1(op_ini_param_t *op_param)
{

	op_param->Act_IN_TILE_SIZE = op_param->in_channels[0] * V_ACT_TILE * (V_MAX_GROUP / op_param->p_in[0]);
	op_param->Act_OUT_TILE_SIZE = op_param->out_channels[op_param->v_layer - 1] * V_ACT_TILE * (V_MAX_GROUP / (op_param->p_in[op_param->v_layer - 1] * op_param->p_out[op_param->v_layer - 1]));
	op_param->Act_TOTAL_IN_SIZE = op_param->col * op_param->row * op_param->Act_IN_TILE_SIZE;
}

static void pick_up_runtime_conf_p2(op_ini_param_t *op_param, int col_num)
{
	if (op_param->net_type == 1 || op_param->net_type == 3)
	{
		if (op_param->blockstride != 1)
		{
			if (op_param->v_layer == 4)
			{
				if (col_num % 2 == 0)
				{
					op_param->act_bank_in_seq[0] = 3;
					op_param->act_bank_in_seq[1] = 3;
					op_param->act_bank_in_seq[2] = 3;
					op_param->act_bank_in_seq[3] = 1;
					op_param->act_bank_out_seq[0] = 3;
					op_param->act_bank_out_seq[1] = 1;
					op_param->act_bank_out_seq[2] = 1;
					op_param->act_bank_out_seq[3] = 1;
					op_param->res_act_bank_in = 1;
				}
				else
				{
					op_param->act_bank_in_seq[0] = 3;
					op_param->act_bank_in_seq[1] = 3;
					op_param->act_bank_in_seq[2] = 3;
					op_param->act_bank_in_seq[3] = 2;
					op_param->act_bank_out_seq[0] = 3;
					op_param->act_bank_out_seq[1] = 2;
					op_param->act_bank_out_seq[2] = 2;
					op_param->act_bank_out_seq[3] = 2;
					op_param->res_act_bank_in = 2;
				}
			}
			else if (op_param->v_layer == 1)
			{
				if (col_num % 2 == 0)
				{
					op_param->act_bank_in_seq[0] = 3;
					op_param->act_bank_in_seq[1] = 3;
					op_param->act_bank_in_seq[2] = 3;
					op_param->act_bank_in_seq[3] = 1;
					op_param->act_bank_out_seq[0] = 1;
					op_param->act_bank_out_seq[1] = 3;
					op_param->act_bank_out_seq[2] = 3;
					op_param->act_bank_out_seq[3] = 1;
					op_param->res_act_bank_in = 3;
				}
				else
				{
					op_param->act_bank_in_seq[0] = 3;
					op_param->act_bank_in_seq[1] = 3;
					op_param->act_bank_in_seq[2] = 3;
					op_param->act_bank_in_seq[3] = 1;
					op_param->act_bank_out_seq[0] = 2;
					op_param->act_bank_out_seq[1] = 3;
					op_param->act_bank_out_seq[2] = 3;
					op_param->act_bank_out_seq[3] = 1;
					op_param->res_act_bank_in = 3;
				}
			}
		}
	}
	else if (op_param->net_type == 2)
	{
		//renet_18
		if (op_param->v_layer == 3)
		{
			if (col_num % 2 == 0)
			{
				op_param->act_bank_in_seq[0] = 3;
				op_param->act_bank_in_seq[1] = 3;
				op_param->act_bank_in_seq[2] = 1;
				op_param->act_bank_in_seq[3] = 3;
				op_param->act_bank_out_seq[0] = 1;
				op_param->act_bank_out_seq[1] = 1;
				op_param->act_bank_out_seq[2] = 1;
				op_param->act_bank_out_seq[3] = 0xf;
				op_param->res_act_bank_in = 3;
			}
			else
			{
				op_param->act_bank_in_seq[0] = 3;
				op_param->act_bank_in_seq[1] = 3;
				op_param->act_bank_in_seq[2] = 2;
				op_param->act_bank_in_seq[3] = 3;
				op_param->act_bank_out_seq[0] = 2;
				op_param->act_bank_out_seq[1] = 2;
				op_param->act_bank_out_seq[2] = 2;
				op_param->act_bank_out_seq[3] = 0xf;
				op_param->res_act_bank_in = 3;
			}
		}
	}
}

void config_runtime_p1(op_config_t *op, op_ini_param_t *op_param)
{
	//set OUT_CHANNEL_01
	op->value_at_reg_0x11c = (op_param->out_channels[1] << 16) | op_param->out_channels[0];
	//set OUT_CHANNEL_23
	op->value_at_reg_0x120 = op_param->out_channels[3] << 16 | op_param->out_channels[2];
	//set kernel_sizesS
	op->value_at_reg_0x130 = op_param->kernel_sizes[3] << 24 | op_param->kernel_sizes[2] << 16 | op_param->kernel_sizes[1] << 8 | op_param->kernel_sizes[0];
	//set p_in_AXI
	op->value_at_reg_0x13c = op_param->p_in[3] << 12 | op_param->p_in[2] << 8 | op_param->p_in[1] << 4 | op_param->p_in[0];
	//set p_out_AXI
	op->value_at_reg_0x140 = op_param->p_out[3] << 12 | op_param->p_out[2] << 8 | op_param->p_out[1] << 4 | op_param->p_out[0];
	//set WHO_PROVIDE_INPUT
	op->value_at_reg_0xfc = (op_param->which_prebn_act_bank & 0b111) << 12 | op_param->input_buffer_seq[3] << 9 | op_param->input_buffer_seq[2] << 6 | op_param->input_buffer_seq[1] << 3 | op_param->input_buffer_seq[0];
	//set who_provide_output
	op->value_at_reg_0x100 = op_param->output_buffer_seq[3] << 9 | op_param->output_buffer_seq[2] << 6 | op_param->output_buffer_seq[1] << 3 | op_param->output_buffer_seq[0];
	//set SELOV_RAM_TO_READ
	op->value_at_reg_0x15c = 6;
	//set frac_in_CONFIG
	op->value_at_reg_0x170 = op_param->frac_in;
	//set frac_out_cCONFIG
	op->value_at_reg_0x174 = op_param->frac_out;
	//set QUAN_VALUE_OF_SIX
	op->value_at_reg_0x158 = op_param->QuanValueOfSix;
	//set RESADDER_LAYER
	op->value_at_reg_0x150 = op_param->ResAddLayer;
	//set BN_LAYER
	op->value_at_reg_0x148 = op_param->pre_bn << 4 | op_param->BNLayer;
	//set RELU_LAYER
	op->value_at_reg_0x14c = op_param->ReLULayer;
	//set v_layer_CONFIG
	op->value_at_reg_0x144 = op_param->v_layer;
}

void config_runtime_p2(op_config_t *op, op_ini_param_t *op_param, int row_num, int col_2)
{
	// uint32_t conf_word;A
	uint32_t MAX_FETCH_WEI_BUF_main, MAX_FETCH_WEI_BUF_part, MAX_FETCH_WEI_BUF;
	uint32_t VALID_WEIGHT_WORD_NUMBER = (op_param->num_valid_weights + V_MAX_GROUP - 1) / V_MAX_GROUP;

	MAX_FETCH_WEI_BUF_main = VALID_WEIGHT_WORD_NUMBER >> (log2_lookup(V_WEI_BANK_DEPTH));

	MAX_FETCH_WEI_BUF_part = (VALID_WEIGHT_WORD_NUMBER & ((uint32_t)1023)) > 0;
	MAX_FETCH_WEI_BUF = MAX_FETCH_WEI_BUF_main + MAX_FETCH_WEI_BUF_part + 0b01;
	//TODO:
	// ColOvlapOffset = 1 == -1 ? 0 : (op_param->in_channels[1] / op_param->p_in[1]);
	// RowOvlapOffset = 1 == -1 ? 0 : (op_param->out_channels[1] / op_param->p_out[1]);

	uint32_t ColOvlapRAMStartAddr = row_num * op_param->ColOvlapOffset;
	uint32_t RowOvlapRAMStartAddr = col_2 * op_param->RowOvlapOffset;
	//set WHICH_ACT_BANK_IN
	op->value_at_reg_0x108 = op_param->act_bank_in_seq[3] << 6 | op_param->act_bank_in_seq[2] << 4 | op_param->act_bank_in_seq[1] << 2 | op_param->act_bank_in_seq[0];
	//set WHICH_ACT_BANK_OUT
	op->value_at_reg_0x10c = op_param->act_bank_out_seq[3] << 6 | op_param->act_bank_out_seq[2] << 4 | op_param->act_bank_out_seq[1] << 2 | op_param->act_bank_out_seq[0];
	//set WHO_PROVIDE_RES_INPUT
	op->value_at_reg_0x104 = op_param->res_input_buffer;
	//set WHICH_RES_ACT_BANK_IN
	op->value_at_reg_0x110 = op_param->res_act_bank_in;
	//set FIRST_TILE
	op->value_at_reg_0x164 = op_param->FirstTile;
	//set SEL_RELUSIX
	op->value_at_reg_0x168 = op_param->SelRelu6;
	//set LAST_BLOCK_STRIDE_CON
	op->value_at_reg_0x160 = op_param->LastlayerStride << 1 | op_param->Last_block_stride;
	//set ROW_OLAP_VALID
	op->value_at_reg_0x16c = op_param->RowOlapValid;
	//set MAX_FETCH_WEI_BUF_CON
	op->value_at_reg_0x154 = MAX_FETCH_WEI_BUF;
	//set COL_OLAP_RAM_ADDR_OFFSET
	op->value_at_reg_0xf4 = ColOvlapRAMStartAddr;
	//set ROW_OLAP_RAM_ADDR_OFFSET
	op->value_at_reg_0xf8 = RowOvlapRAMStartAddr;
}

void config_ddr_dma_p2(op_config_t *op, op_ini_param_t *op_param, int row_num, int col_1, int col_2)
{
	op->value_at_reg_0x80 = op_param->act_ram_rd_base_addr + (op_param->sub_id - 1) * op_param->Act_IN_TILE_SIZE;
	// if ((op_param->block_id == 0) || (op_param->block_id == 1) || (op_param->block_id == 3) || (op_param->block_id == 7) || (op_param->block_id == 12) || (op_param->block_id == 16))
	// {
	// 	if ((op_param->sub_id % 2) == 0)
	// 	{
	// 		op->value_at_reg_0x90 = Act_Output_Addr(op_param->block_id, (op_param->sub_id - 1) / 2 + 1, op_param->act_ram_write_base_addr, op_param->Act_OUT_TILE_SIZE);
	// 	}
	// }
	// else
	// {
	// 	op->value_at_reg_0x90 = Act_Output_Addr(op_param->block_id, op_param->sub_id, op_param->act_ram_write_base_addr, op_param->Act_OUT_TILE_SIZE);
	// }

	op->value_at_reg_0x90 = op_param->act_ram_write_base_addr + op_param->Act_OUT_TILE_SIZE * (op_param->sub_id - 1);

	//TODO: 连测修改地址
	// op->value_at_reg_0x90 =ddr_transfer_byte_num_gen(0x1000, op->value_at_reg_0x90);
}

void config_ddr_dma_p1(op_config_t *op, op_ini_param_t *op_param)
{
	// uint32_t stride;
	uint32_t wram_transfer_word_num_first;
	// uint32_t wram_transfer_start_addr_first;
	uint32_t wei_fetcher_transfer_word;
	// uint32_t wei_fetcher_start_addr;
	// uint32_t SINGLE_WEI_WORD_ADDR_INCREMENT;
	uint32_t och_sum;
	uint32_t bn_och_sum;
	// uint32_t ddr_base_addr;
	// ddr_base_addr = DDR_BASE_ADDR;
	//----------------------------------------------------------------
	uint32_t VALID_WEIGHT_WORD_NUMBER = (op_param->num_valid_weights + V_MAX_GROUP + 64 - 1) / V_MAX_GROUP;
	// wram_transfer_start_addr_first = DDR_BASE_ADDR + 0;
	// decide how many words for WB0 to fetch(1K or all weights in one block)
	//wram_transfer_word_num_first = wei_ram_transfer_word_num_gen(wram_transfer_word_num_first); // 8in8out s2 case, 46->48
	wram_transfer_word_num_first = VALID_WEIGHT_WORD_NUMBER * 24;

	// the number of weights for second weight buffer is going to be fetched from dram.
	wei_fetcher_transfer_word = VALID_WEIGHT_WORD_NUMBER - V_WEI_BANK_DEPTH + 16;
	if (wei_fetcher_transfer_word < 0)
		wei_fetcher_transfer_word = 0;
	// the ddr address of weight controller on IP is going to access.
	// SINGLE_WEI_WORD_ADDR_INCREMENT = (V_WEI_WIDTH * V_WEI_BANK) / 8;
	// wei_fetcher_start_addr = wram_transfer_start_addr_first + SINGLE_WEI_WORD_ADDR_INCREMENT * (wram_transfer_word_num_first - 16);
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	bn_och_sum = 0;
	for (int i = 0; i < op_param->v_layer; i++)
		if (op_param->BNLayer & (1 << i))
			bn_och_sum += op_param->out_channels[i];
	if (op_param->pre_bn)
		bn_och_sum += op_param->out_channels[op_param->v_layer - 1];
	//----------------------------------------------------------------

	//----------------------------------------------------------------
	och_sum = 0;
	for (int i = 0; i < op_param->v_layer; i++)
		och_sum += op_param->out_channels[i];
	//----------------------------------------------------------------

	//set dma_wractram_datanum
	op->value_at_reg_0x84 = ddr_transfer_byte_num_gen(64, op_param->Act_IN_TILE_SIZE);
	//set dma_rdactram_datanum
	op->value_at_reg_0x94 = ddr_transfer_byte_num_gen(64, op_param->Act_OUT_TILE_SIZE);
	//set sel_dram_sram_bank
	op->value_at_reg_0xf0 = 0;
	op->value_at_reg_0xf0 |= log2_lookup(op_param->output_buffer_seq[op_param->v_layer - 1]) << 16; //IP读出RAM选择
	op->value_at_reg_0xf0 |= log2_lookup(op_param->input_buffer_seq[0]) << 8;						//IP写入RAM选择
	// op->value_at_reg_0xf0 |= 0b11;
	op->value_at_reg_0xf0 |= 0b11;
	//set dma_weiram_startaddr
	op->value_at_reg_0x70 = op_param->wei_base_addr;
	//set dma_weiram_datanum
	op->value_at_reg_0x74 = ddr_transfer_byte_num_gen(192, wram_transfer_word_num_first);
	//set dma_bnmulram_startaddr
	op->value_at_reg_0x50 = op_param->bn_wei_base_addr;
	//set dma_bnmulram_datanum
	op->value_at_reg_0x54 = ddr_transfer_byte_num_gen(64, bn_och_sum);
	//set dma_bnbiasram_startaddr
	op->value_at_reg_0x60 = op_param->bn_bias_base_addr;
	//set dma_bnbiasram_datanum
	op->value_at_reg_0x64 = ddr_transfer_byte_num_gen(64, bn_och_sum);
	//set dma_biasram_startaddr
	op->value_at_reg_0x40 = op_param->bias_base_addr;
	//set dma_biasram_datanum
	op->value_at_reg_0x44 = ddr_transfer_byte_num_gen(64, och_sum);

	if (op_param->sub_id == 1 && op_param->block_id == op_param->start_block)
	{
		// sprintf(op->write_to_ddr[0].filename, "block_op/task2_bin/block%d/inputb.all.bin", op_param->block_id);
		if (op_param->net_type == 1)
		{
			sprintf(op->write_to_ddr[0].filename, "block_op/resnet50_bin/block%d/inputb.all.bin", op_param->block_id);
		}
		else if (op_param->net_type == 2)
		{
			sprintf(op->write_to_ddr[0].filename, "block_op/resnet18_bin/block%d/inputb.all.bin", op_param->block_id);
		}
		else if (op_param->net_type == 3)
		{
			sprintf(op->write_to_ddr[0].filename, "block_op/mobilenet_bin/block%d/inputb.all.bin", op_param->block_id);
		}

		op->write_to_ddr[0].ddr_base_address = op_param->act_ram_rd_base_addr;
	}
}

void config_op_p1(op_config_t *op, op_ini_param_t *op_param)
{
	config_runtime_p1(op, op_param);
	config_ddr_dma_p1(op, op_param);
}

void config_op_p2(op_config_t *op, op_ini_param_t *op_param, int row_num, int col_1, int col_2)
{
	config_runtime_p2(op, op_param, row_num, col_2);
	config_ddr_dma_p2(op, op_param, row_num, col_1, col_2);
}

void print_reg(op_config_t *op)
{
	printf("value_at_reg_0x11c:%08x\n", op->value_at_reg_0x11c);
	printf("value_at_reg_0x120:%08x\n", op->value_at_reg_0x120);
	printf("value_at_reg_0x130:%08x\n", op->value_at_reg_0x130);
	printf("value_at_reg_0x13c:%08x\n", op->value_at_reg_0x13c);
	printf("value_at_reg_0x140:%08x\n", op->value_at_reg_0x140);
	printf("value_at_reg_0x100:%08x\n", op->value_at_reg_0x100);
	printf("value_at_reg_0x15c:%08x\n", op->value_at_reg_0x15c);
	printf("value_at_reg_0x170:%08x\n", op->value_at_reg_0x170);
	printf("value_at_reg_0x174:%08x\n", op->value_at_reg_0x174);
	printf("value_at_reg_0x158:%08x\n", op->value_at_reg_0x158);
	printf("value_at_reg_0x150:%08x\n", op->value_at_reg_0x150);
	printf("value_at_reg_0x148:%08x\n", op->value_at_reg_0x148);
	printf("value_at_reg_0x13c:%08x\n", op->value_at_reg_0x13c);
	printf("value_at_reg_0x14c:%08x\n", op->value_at_reg_0x14c);
	printf("value_at_reg_0x144:%08x\n", op->value_at_reg_0x144);
	printf("value_at_reg_0x108:%08x\n", op->value_at_reg_0x108);
	printf("value_at_reg_0x10c:%08x\n", op->value_at_reg_0x10c);
	printf("value_at_reg_0x104:%08x\n", op->value_at_reg_0x104);
	printf("value_at_reg_0x110:%08x\n", op->value_at_reg_0x110);
	printf("value_at_reg_0x164:%08x\n", op->value_at_reg_0x164);
	printf("value_at_reg_0x168:%08x\n", op->value_at_reg_0x168);
	printf("value_at_reg_0x160:%08x\n", op->value_at_reg_0x160);
	printf("value_at_reg_0x16c:%08x\n", op->value_at_reg_0x16c);
	printf("value_at_reg_0x154:%08x\n", op->value_at_reg_0x154);
	printf("value_at_reg_0xf4:%08x\n", op->value_at_reg_0xf4);
	printf("value_at_reg_0xf8:%08x\n", op->value_at_reg_0xf8);
	printf("value_at_reg_0x040:%08x\n", op->value_at_reg_0x40);
	printf("value_at_reg_0x044:%08x\n", op->value_at_reg_0x44);
	printf("value_at_reg_0x070:%08x\n", op->value_at_reg_0x70);
	printf("value_at_reg_0x074:%08x\n", op->value_at_reg_0x74);
	printf("value_at_reg_0x060:%08x\n", op->value_at_reg_0x60);
	printf("value_at_reg_0x064:%08x\n", op->value_at_reg_0x64);
	printf("value_at_reg_0x050:%08x\n", op->value_at_reg_0x50);
	printf("value_at_reg_0x054:%08x\n", op->value_at_reg_0x54);
	printf("value_at_reg_0x080:%08x\n", op->value_at_reg_0x80);
	printf("value_at_reg_0x084:%08x\n", op->value_at_reg_0x84);
	printf("value_at_reg_0x090:%08x\n", op->value_at_reg_0x90);
}

void test_set(op_config_t *op_config, op_ini_param_t *op_param, int row_num, int col_1, int col_2)
{
	pick_up_runtime_conf_p1(op_param);
	int col_num;
	col_num = col_1 * op_param->blockstride + col_2;
	pick_up_runtime_conf_p2(op_param, col_num);
	pick_up_runtime_conf_p3(op_param, col_num, row_num);
	config_op_p1(op_config, op_param);
	config_op_p2(op_config, op_param, row_num, col_1, col_2);
	// print_reg(op_config);
	// exit(0);
}