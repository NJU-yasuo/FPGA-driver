#include "fx_hpca.h"
// #include <math.h>
#include "socal.h"
#include <time.h>
//#include "alt_gpio.h"

void *vir_addr_base;

#ifdef WRITE_ON_CHANGE
static bool shadow_op_config_written = false;
static op_config_t shadow_op_config;
static op_config_t *pshadow_op_config = &shadow_op_config;
#endif

static void fx_write_word(void *addr, uint32_t val)
{
#ifdef PRINT_REG_VALUE
	printf("Write To Addr: \t0x%8x\n", (unsigned int)(addr - vir_addr_base));
	printf("Write Value: \t0x%8x\n\n", val);
#endif
	alt_write_word(addr, val);
	return;
}
#ifdef WRITE_ON_CHANGE
#define skip_fx_write_if_no_change(addr, xyz) \
	if (shadow_op_config_written == false)    \
	{                                         \
		shadow_op_config_written = true;      \
		fx_write_word((addr), (xyz));         \
		pshadow_##xyz = xyz;                  \
	}                                         \
	else                                      \
	{                                         \
		if (pshadow_##xyz != xyz)             \
		{                                     \
			fx_write_word((addr), (xyz));     \
			pshadow_##xyz = xyz;              \
		}                                     \
	}
#endif

#define PRINT_ERR printf("%s::%d failed!!!\n", __FUNCTION__, __LINE__);

static bool polling(uint32_t reg_addr_offset, time_t time_out_val)
{

	time_t start_time, end_time;
	bool time_out = false;
	start_time = time(NULL);

	while (!alt_read_word(vir_addr_base + reg_addr_offset) && !time_out)
	{
		// waiting
		end_time = time(NULL);
		time_out = (end_time - start_time) > time_out_val;
		//usleep(10000); //sleep 10000ms or 10 milli
	}
	if (time_out)
	{
#ifdef PRINT_REG_VALUE
		printf("polling from Addr: \t0x%8x FAILED after %d seconds\n", reg_addr_offset, (uint32_t)time_out_val);
#endif
		return false;
	}
	else

	{
#ifdef PRINT_REG_VALUE
		printf("polling from Addr: \t0x%8x PASSED\n", reg_addr_offset);
#endif
		return true;
	}
}

//------------------------等待文件写入结束信号--------------------------------
static bool polling_write_bias_done(time_t time_out_val)
{
	return polling(DMA_BIASRAM_DONE, time_out_val);
}
static bool polling_write_bnbias_done(time_t time_out_val)
{
	return polling(DMA_BNBIASRAM_DONE, time_out_val);
}
static bool polling_write_bnmul_done(time_t time_out_val)
{
	return polling(DMA_BNMULRAM_DONE, time_out_val);
}
static bool polling_write_weight_done(time_t time_out_val)
{
	return polling(DMA_WEIRAM_DONE, time_out_val);
}
static bool polling_write_actram_done(time_t time_out_val)
{
	return polling(DMA_WRACTRAM_DONE, time_out_val);
}
//-------------------------------------------------------------------------

//------------------------写出信号------------------------------------------
static bool polling_compute_done(time_t time_out_val)
{
	return polling(COMPUTE_DONE, time_out_val);
}
static bool polling_writeback_to_ddr(time_t time_out_val)
{
	return polling(DMA_RDACTRAM_DONE, time_out_val);
}
//--------------------------------------------------------------------------

static bool write_files_to_IP(op_config_t *op)
{
	if (op->value_at_reg_0x40 != 0)
	{
#ifdef DEBUG_PRINT
		printf("---------- Start Write files to IP ----------\n");
		printf("---------- Set Register of Write Bias RAM: ----------\n");
#endif
		fx_write_word(vir_addr_base + DMA_BIASRAM_STARTADDR, op->value_at_reg_0x40);
		fx_write_word(vir_addr_base + DMA_BIASRAM_DATANUM, op->value_at_reg_0x44);
#ifdef DEBUG_PRINT
		printf("---------- Write Bias to IP: ----------\n");
#endif
		fx_write_word(vir_addr_base + DMA_BIASRAM_START, 0x1);
		fx_write_word(vir_addr_base + DMA_BIASRAM_START, 0x0);
		if (!polling_write_bias_done(1))
		{
			PRINT_ERR
			return false;
		}
	}

	if (op->value_at_reg_0x70 != 0)
	{
#ifdef DEBUG_PRINT
		printf("---------- Set Register of Write Weight RAM: ----------\n");
#endif
		fx_write_word(vir_addr_base + DMA_WEIRAM_STARTADDR, op->value_at_reg_0x70);
		fx_write_word(vir_addr_base + DMA_WEIRAM_DATANUM, op->value_at_reg_0x74);
#ifdef DEBUG_PRINT
		printf("---------- Write weight to IP: ----------\n");
#endif
		fx_write_word(vir_addr_base + DMA_WEIRAM_START, 0x1);
		fx_write_word(vir_addr_base + DMA_WEIRAM_START, 0x0);
		if (!polling_write_weight_done(1))
		{
			PRINT_ERR
			return false;
		}
	}
	if (op->value_at_reg_0x60 != 0)
	{
#ifdef DEBUG_PRINT
		printf("---------- Set Register of Write BN Bias RAM: ----------\n");
#endif
		fx_write_word(vir_addr_base + DMA_BNBIASRAM_STARTADDR, op->value_at_reg_0x60);
		fx_write_word(vir_addr_base + DMA_BNBIASRAM_DATANUM, op->value_at_reg_0x64);
#ifdef DEBUG_PRINT
		printf("---------- Write BN Bias to IP: ----------\n");
#endif
		fx_write_word(vir_addr_base + DMA_BNBIASRAM_START, 0x1);
		fx_write_word(vir_addr_base + DMA_BNBIASRAM_START, 0x0);
		if (!polling_write_bnbias_done(1))
		{
			PRINT_ERR
			return false;
		}
	}

	if (op->value_at_reg_0x50 != 0)
	{
#ifdef DEBUG_PRINT
		printf("---------- Set Register of Write BN Weight RAM: ----------\n");
#endif
		fx_write_word(vir_addr_base + DMA_BNMULRAM_STARTADDR, op->value_at_reg_0x50);
		fx_write_word(vir_addr_base + DMA_BNMULRAM_DATANUM, op->value_at_reg_0x54);
#ifdef DEBUG_PRINT
		printf("---------- Write BN weight to IP: ----------\n");
#endif
		fx_write_word(vir_addr_base + DMA_BNMULRAM_START, 0x1);
		fx_write_word(vir_addr_base + DMA_BNMULRAM_START, 0x0);
		if (!polling_write_bnmul_done(1))
		{
			PRINT_ERR
			return false;
		}
	}
	return true;
}

static bool write_actram_to_IPcore(op_config_t *op_config)
{
#ifdef DEBUG_PRINT
	printf("---------- Set Register of Write ACT RAM: ----------\n");
#endif
	fx_write_word(vir_addr_base + DMA_WRACTRAM_STARTADDR, op_config->value_at_reg_0x80);
	fx_write_word(vir_addr_base + DMA_WRACTRAM_DATANUM, op_config->value_at_reg_0x84);
#ifdef DEBUG_PRINT
	printf("---------- Write ActRam to IP: ----------\n");
#endif
	fx_write_word(vir_addr_base + DMA_WRACTRAM_START, 0x1);
	fx_write_word(vir_addr_base + DMA_WRACTRAM_START, 0x0);
	if (!polling_write_actram_done(1))
	{
		PRINT_ERR
		return false;
	}
	return true;
}

bool write_files_to_ddr(op_config_t *op_config)
{
	bool rv = true;
	if ((op_config->write_to_ddr[0].buffer_address != NULL) && (op_config->write_to_ddr[0].info_size != 0))
	{
		rv = copy_mem_to_ddr(op_config->write_to_ddr[0].buffer_address, op_config->write_to_ddr[0].ddr_base_address, op_config->write_to_ddr[0].info_size);
		if (rv == false)
		{
			PRINT_ERR
			return rv;
		}
	}

	if (op_config->write_to_ddr[0].filename[0] != 0)
	{
		rv = copy_file_to_ddr(op_config->write_to_ddr[0].filename, op_config->write_to_ddr[0].ddr_base_address, &op_config->write_to_ddr[0].info_size);

		if (rv == false)
		{
			PRINT_ERR
			return rv;
		}
	}
	return rv;
}

bool initial_weight2(task2_weight_ini_t *weight_ini)
{
	bool rv = false;
	printf("write_files_to_fapge\n");
#if 1
	for (int i = 0; i < 60; i++)
	{
		rv = copy_file_to_ddr(weight_ini->write_to_ddr[i].filename, weight_ini->write_to_ddr[i].ddr_base_address, &weight_ini->write_to_ddr[i].info_size);
		printf("Nnumber of weight or bias write to fpga,%d\n", i);
		if (rv == false)
		{
			PRINT_ERR
			return rv;
		}
	}
#endif
	return true;
}

bool initial_weight_resnet50(int net_type, int block_id)
{
	bool rv = false;
	uint32_t info_size = 0;
	char filename_weight[80];
	char filename_bias[80];
	char filename_bn_wei[80];
	char filename_bn_bias[80];

	if (net_type == 1)
	{
		sprintf(filename_weight, "block_op/resnet50_bin/block%d/weightb.bin", block_id);
		sprintf(filename_bias, "block_op/resnet50_bin/block%d/biasb.bin", block_id);
		sprintf(filename_bn_wei, "block_op/resnet50_bin/block%d/bn_weib.bin", block_id);
		sprintf(filename_bn_bias, "block_op/resnet50_bin/block%d/bn_biasb.bin", block_id);
	}
	else if (net_type == 2)
	{
		sprintf(filename_weight, "block_op/resnet18_bin/block%d/weightb.bin", block_id);
		sprintf(filename_bias, "block_op/resnet18_bin/block%d/biasb.bin", block_id);
		sprintf(filename_bn_wei, "block_op/resnet18_bin/block%d/bn_weib.bin", block_id);
		sprintf(filename_bn_bias, "block_op/resnet18_bin/block%d/bn_biasb.bin", block_id);
	}
	else if (net_type == 3)
	{
		sprintf(filename_weight, "block_op/mobilenet_bin/block%d/weightb.bin", block_id);
		sprintf(filename_bias, "block_op/mobilenet_bin/block%d/biasb.bin", block_id);
		sprintf(filename_bn_wei, "block_op/mobilenet_bin/block%d/bn_weib.bin", block_id);
		sprintf(filename_bn_bias, "block_op/mobilenet_bin/block%d/bn_biasb.bin", block_id);
	}
	rv = copy_file_to_ddr(filename_weight, 0x40000000, &info_size);
	rv = copy_file_to_ddr(filename_bias, 0x40100000, &info_size);
	rv = copy_file_to_ddr(filename_bn_wei, 0x40200000, &info_size);
	rv = copy_file_to_ddr(filename_bn_bias, 0x40300000, &info_size);
	return rv;
}

bool read_files_from_fpga(op_config_t *op_config)
{
	bool rv = true;

	for (int i = 0; i < NUM_OUTPUT; i++)
	{
		if ((op_config->read_from_ddr[i].buffer_address != NULL) && (op_config->read_from_ddr[i].info_size != 0))
		{
			rv = copy_ddr_to_mem(op_config->read_from_ddr[i].buffer_address, op_config->read_from_ddr[i].ddr_base_address, op_config->read_from_ddr[i].info_size);
			if (rv == false)
			{
				PRINT_ERR
				return rv;
			}
		}
		else if (op_config->read_from_ddr[i].filename[0] != 0)
		{
			rv = read_file_from_ddr(op_config->read_from_ddr[i].filename, op_config->read_from_ddr[i].ddr_base_address, op_config->read_from_ddr[i].info_size);
			if (rv == false)
			{
				PRINT_ERR
				close_cnn_accelerator();
				break;
			}
			if (op_config->read_verify[i].filename[0] != 0) // want to compare file
			{
				printf("Compare file name:%s\n", op_config->read_verify[i].filename);
				rv = compare_files(op_config->read_from_ddr[i].filename, op_config->read_verify[i].filename);
#ifdef DEBUG_PRINT
				printf("compare %s %s %s\n", op_config->read_from_ddr[i].filename, op_config->read_verify[i].filename, (rv == true) ? "PASSED" : "FAILED");

#else
				if (rv == false)
				{
					printf("compare %s %s FAILED.\n", op_config->read_from_ddr[i].filename, op_config->read_verify[i].filename);
					//keep going on compare error
				}
#endif
			}
		}
	}
	return rv;
}

bool start_read_actram_from_IPcore(op_config_t *op_config, uint32_t ram_select)
{

	/**********************************/
	if (op_config->value_at_reg_0x90)
	{
#ifdef DEBUG_PRINT
		printf("---------- Set Register of Read Act RAM: ----------\n");
#endif
		// fx_write_word(vir_addr_base + DMA_RDACTRAM_STARTADDR, op_config->value_at_reg_0x90 + op_config->value_at_reg_0x94 * ((ram_select - 0x3) / 0x10000));
		// fx_write_word(vir_addr_base + SEL_DRAM_SRAM_BANK, ram_select);
		fx_write_word(vir_addr_base + DMA_RDACTRAM_STARTADDR, op_config->value_at_reg_0x90);
		fx_write_word(vir_addr_base + SEL_DRAM_SRAM_BANK, op_config->value_at_reg_0xf0);
		fx_write_word(vir_addr_base + DMA_RDACTRAM_DATANUM, op_config->value_at_reg_0x94);
#ifdef DEBUG_PRINT
		printf("---------- Read ActRam from IP: ----------\n");
#endif
		fx_write_word(vir_addr_base + DMA_RDACTRAM_START, 0x1);
		fx_write_word(vir_addr_base + DMA_RDACTRAM_START, 0x0);
		if (!polling_writeback_to_ddr(2))
		{
			PRINT_ERR
			return false;
		}
	}
	return true;
}

static bool start_compute(op_config_t *op_config)
{
	if (1)
	{
#ifdef DEBUG_PRINT
		printf("---------- Set STRAT COMPUTE REG: ----------\n");
#endif
		fx_write_word(vir_addr_base + DAM_CTRL_SRC, 0x10);
		fx_write_word(vir_addr_base + ACTRAM_MASTER, 0x1);
#ifdef DEBUG_PRINT
		printf("---------- START COMPUTE: ----------\n");
#endif
		fx_write_word(vir_addr_base + START_RUN_OP, 0x1);
		fx_write_word(vir_addr_base + START_RUN_OP, 0x0);
		if (!polling_compute_done(2))
		{
			PRINT_ERR
			return false;
		}
#ifdef DEBUG_PRINT
		printf("---------- Clear Set: ----------\n");
#endif
		fx_write_word(vir_addr_base + DAM_CTRL_SRC, 0x0);
		fx_write_word(vir_addr_base + ACTRAM_MASTER, 0x0);
	}
	start_read_actram_from_IPcore(op_config, 0x3);
	// start_read_actram_from_IPcore(op_config, 0x10003);
	// start_read_actram_from_IPcore(op_config, 0x20003);
	// write back to DRAM
	/**********************************/
	return true;
}

#if 0
static bool start_2X2_pooling(op_config_t *op_config)
{
#ifdef DEBUG_PRINT
	printf("---------- Write RD_DDR_START_CTRL: ----------\n");
#endif
	fx_write_word(vir_addr_base + 0x134, 0x1);
	fx_write_word(vir_addr_base + 0x134, 0x0);

	// wait for compute
	if (!polling_compute_done(2))
	{
		PRINT_ERR
		// return false;
	}
	// write back to DRAM
	/**********************************/
	if ((op_config->value_at_reg_0x200 & 0x80) == 0x80)
	{
		if (!polling_writeback_to_ddr(2))
		{
			PRINT_ERR
			return false;
		}
	}
#ifdef DEBUG_PRINT
	printf("-------------Write COMPUTE_DONE_CLR: ----------\n");
#endif
	fx_write_word(vir_addr_base + 0x130, 0x0); //0x204
	return true;
}
#endif

bool launch_op(op_config_t *op_config)
{

	bool rv = false;
	if (init_cnn_accelerator() == false)
	{
		PRINT_ERR
		return false;
	}
#ifdef DEBUG_PRINT
	printf("---------- Write Runtime: ----------\n");
#endif
	fx_write_word(vir_addr_base + OUT_CHANNEL_01, op_config->value_at_reg_0x11c);
	fx_write_word(vir_addr_base + OUT_CHANNEL_23, op_config->value_at_reg_0x120);
	fx_write_word(vir_addr_base + KERNEL_SIZE, op_config->value_at_reg_0x130);
	fx_write_word(vir_addr_base + P_IN, op_config->value_at_reg_0x13c);
	fx_write_word(vir_addr_base + P_OUT, op_config->value_at_reg_0x140);
	fx_write_word(vir_addr_base + WHO_PROVIDE_INPUT, op_config->value_at_reg_0xfc);
	fx_write_word(vir_addr_base + WHO_PROVIDE_OUTPUT, op_config->value_at_reg_0x100);
	fx_write_word(vir_addr_base + SELOV_RAM_TO_READ, op_config->value_at_reg_0x15c);
	fx_write_word(vir_addr_base + FRAC_IN, op_config->value_at_reg_0x170);
	fx_write_word(vir_addr_base + FRAC_OUT, op_config->value_at_reg_0x174);
	fx_write_word(vir_addr_base + QUAN_VALUE_OF_SIX, op_config->value_at_reg_0x158);
	fx_write_word(vir_addr_base + RESADDR_LAYER, op_config->value_at_reg_0x150);
	fx_write_word(vir_addr_base + BN_LAYER, op_config->value_at_reg_0x148);
	fx_write_word(vir_addr_base + RELU_LAYER, op_config->value_at_reg_0x14c);
	fx_write_word(vir_addr_base + V_LAYER, op_config->value_at_reg_0x144);
	fx_write_word(vir_addr_base + SEL_DRAM_SRAM_BANK, op_config->value_at_reg_0xf0);
	fx_write_word(vir_addr_base + WHICH_ACT_BANK_IN, op_config->value_at_reg_0x108);
	fx_write_word(vir_addr_base + WHICH_ACT_BANK_OUT, op_config->value_at_reg_0x10c);
	fx_write_word(vir_addr_base + WHO_PROVIDE_RES_INPUT, op_config->value_at_reg_0x104);
	fx_write_word(vir_addr_base + WHICH_RES_ACT_BANK_IN, op_config->value_at_reg_0x110);
	fx_write_word(vir_addr_base + FIRST_TILE, op_config->value_at_reg_0x164);
	fx_write_word(vir_addr_base + SEL_RELU6, op_config->value_at_reg_0x168);
	fx_write_word(vir_addr_base + LAST_LAYER_STRIDE, op_config->value_at_reg_0x160);
	fx_write_word(vir_addr_base + ROW_OLAP_VALID, op_config->value_at_reg_0x16c);
	fx_write_word(vir_addr_base + MAX_FETCH_WEI_BUF, op_config->value_at_reg_0x154);
	fx_write_word(vir_addr_base + COL_OLAP_RAM_ADDR_OFFSET, op_config->value_at_reg_0xf4);
	fx_write_word(vir_addr_base + ROW_OLAP_RAM_ADDR_OFFSET, op_config->value_at_reg_0xf8);

	rv = write_files_to_IP(op_config);
	rv = write_actram_to_IPcore(op_config);
	if (!(rv = start_compute(op_config)))
	{
		PRINT_ERR
		close_cnn_accelerator();
	}
	return rv;
}
