#include <stdio.h>
#include "fx_hpca.h"
#include <stdbool.h>
#include "op_ini_config.h"
#include "op_api.h"
#include "task2_parameter_addr.h"

#if 1
bool set_verify_parameter(op_config_t *op_config, int block_id, int sub_id, int row, int col_1, int col_2)
{

    // sprintf(op_config->read_verify[0].filename, "block_op/task2_bin/relu_outb.tile_idx_%d_%d.3.bin", row, col_1);
    if (block_id == 1 || block_id == 3 || block_id == 7)
    {
        if (sub_id % 2 == 0)
        {
            sprintf(op_config->read_verify[0].filename, "block_op/task2_bin/block%d/relu_outb.tile_idx_%d_%d.4.bin", block_id, row, col_1 * 2 + col_2);
            sprintf(op_config->read_from_ddr[0].filename, "block_op/task2_bin/block%d/Block%d_Tile%d_row%d_col1_%d.bin", block_id, block_id, sub_id, row, col_1);
            op_config->read_from_ddr[0].ddr_base_address = op_config->value_at_reg_0x90;
            op_config->read_from_ddr[0].info_size = op_config->value_at_reg_0x94;
        }
    }
    else if (block_id == 2 || block_id == 4 || block_id == 8)
    {
        sprintf(op_config->read_verify[0].filename, "block_op/task2_bin/block%d/relu_outb.tile_idx_%d_%d.3.bin", block_id, row, col_1);
        sprintf(op_config->read_from_ddr[0].filename, "block_op/task2_bin/block%d/Block%d_Tile%d_row%d_col1_%d.bin", block_id, block_id, sub_id, row, col_1);
        op_config->read_from_ddr[0].ddr_base_address = op_config->value_at_reg_0x90;
        op_config->read_from_ddr[0].info_size = op_config->value_at_reg_0x94;
    }
    else if (block_id == 12 || block_id == 16)
    {
        if (sub_id % 2 == 0)
        {
            sprintf(op_config->read_verify[0].filename, "block_op/task2_bin/block%d/relu_outb.tile_idx_%d_%d.1.bin", block_id, row, col_1 * 2 + col_2);
            sprintf(op_config->read_from_ddr[0].filename, "block_op/task2_bin/block%d/Block%d_Tile%d_row%d_col1_%d.bin", block_id, block_id, sub_id, row, col_1);
            op_config->read_from_ddr[0].ddr_base_address = op_config->value_at_reg_0x90;
            op_config->read_from_ddr[0].info_size = op_config->value_at_reg_0x94;
        }
    }
    else
    {
        sprintf(op_config->read_verify[0].filename, "block_op/task2_bin/block%d/relu_outb.tile_idx_%d_%d.1.bin", block_id, row, col_1);
        sprintf(op_config->read_from_ddr[0].filename, "block_op/task2_bin/block%d/Block%d_Tile%d_row%d_col1_%d.bin", block_id, block_id, sub_id, row, col_1);
        op_config->read_from_ddr[0].ddr_base_address = op_config->value_at_reg_0x90;
        op_config->read_from_ddr[0].info_size = op_config->value_at_reg_0x94;
    }

    return true;
}
#endif

bool task2_set_op(op_ini_param_t *op_param, void *img_ptr, void *output_ptr, int start_block, int test_block)
{
    op_config_t op_config;
    bool rv = true;
#ifdef DEBUG_PRINT
    printf("******************************************************************\n");
    printf("* START %s,%d\n", __FUNCTION__, op_param->block_id);
    printf("*\n");
#endif
    op_param->sub_id = 0;
    op_param->start_block = start_block;
    for (int col_1 = 0; col_1 < op_param->col / op_param->blockstride; col_1++)
    {
        for (int row = 0; row < op_param->row; row++)
        {
            for (int col_2 = 0; col_2 < op_param->blockstride; col_2++)
            {

                op_param->sub_id++;
                memset(&op_config, 0, sizeof(op_config_t));
                test_set(&op_config, op_param, row, col_1, col_2);
                if (start_block == op_param->block_id)
                {
                    op_param->Last_block_stride = 0;
                }
                if (op_param->block_id == test_block)
                {
                    set_verify_parameter(&op_config, test_block, op_param->sub_id, row, col_1, col_2);
                }
                rv = call_op(&op_config);
            }
        }
    }
#ifdef DEBUG_PRINT
    if (rv == true)
    {
        op_param->sub_id--;
    }
    printf("*\n");
    printf("* END %s::%s at sub_id: %d\n", __FUNCTION__, (rv == true) ? "PASSED" : "FAILED", op_param->sub_id);
    printf("******************************************************************\n");
#endif
    return rv;
}

#if 0
void task2_test_fc()
{
    // bool rv;
    op_config_t op_config;
    memset(&op_config, 0, sizeof(op_config_t));
#ifdef DEBUG_PRINT
    printf("******************************************************************\n");
    printf("* START %s\n", __FUNCTION__);
    printf("*\n");
#endif
    //unchange
    op_config.value_at_reg_0x100 = 0x0fff0800;
    op_config.value_at_reg_0x104 = 0x0fff0fff;
    op_config.value_at_reg_0x108 = 0x0fff0001;
    op_config.value_at_reg_0x10c = 0x0fff0fff;
    op_config.value_at_reg_0x110 = 0xffffff01;
    op_config.value_at_reg_0x114 = 0x11111118;
    op_config.value_at_reg_0x118 = 0x00060100;
    op_config.value_at_reg_0x124 = 0x0060040b;
    op_config.value_at_reg_0x128 = 0x0000100f;
    // op_config.value_at_reg_0x154 = 0x00000000;
    op_config.value_at_reg_0x050 = 0x00000004;
    //change
    op_config.value_at_reg_0x11c = 0x002cffff;
    op_config.value_at_reg_0x12c = 0x0000300c;
    op_config.value_at_reg_0x120 = 0x00000000;
    op_config.value_at_reg_0x200 = 0x000000d3;
    // op_config.value_at_reg_0x040 =
    //address
    sprintf(op_config.write_to_ddr[0].filename, "block_op/task2_bin/testblock/inputb.all.bin");
    op_config.write_to_ddr[0].ddr_base_address = ACT_block03_HW_RD_BASE_ADDR;

    op_config.value_at_reg_0x400 = T2_ACT_HPS2FPGA_SRC_BASE_ADDR; //hps ddr
    op_config.value_at_reg_0x404 = T2_ACT_HPS2FPGA_SRC_SCALE;
    op_config.value_at_reg_0x408 = T2_ACT_HPS2FPGA_DES_BASE_ADDR; //fpga ddr
    op_config.value_at_reg_0x40c = T2_ACT_HPS2FPGA_DES_SCALE;

    op_config.value_at_reg_0x040 = ACT_block03_HW_RD_BASE_ADDR;
    op_config.value_at_reg_0x044 = 0x00020000;
    // act wr fpga_ddr info.
    op_config.value_at_reg_0x048 = ACT_block03_HW_WR_BASE_ADDR;
    op_config.value_at_reg_0x04c = 0x00000200;
    // Weight dma info.
    // arm_rd fpga_ddr.
    op_config.value_at_reg_0x080 = WEIGHT_block03_RW_BASE_ADDR;
    op_config.value_at_reg_0x084 = 0x00000100;
    // fetcher_rd fpga_ddr.
    op_config.value_at_reg_0x08c = 0x00000000;
    op_config.value_at_reg_0x090 = WEIGHT_block03_RW_next_BASE_ADDR;
    //BN mul
    op_config.value_at_reg_0x0c0 = BN_mul_block03_RW_BASE_ADDR;
    op_config.value_at_reg_0x0c4 = 0x00000000;
    //BN bias
    op_config.value_at_reg_0x0c8 = BN_BIAS_block03_RW_BASE_ADDR;
    op_config.value_at_reg_0x0cc = 0x00000000;
    // Bias dma infomake
    op_config.value_at_reg_0x0d0 = BIAS_block03_RW_BASE_ADDR;
    op_config.value_at_reg_0x0d4 = 0x00000010;

    op_config.value_at_reg_0x414 = op_config.value_at_reg_0x048; //fpga_ddr src
    op_config.value_at_reg_0x418 = op_config.value_at_reg_0x04c;
    op_config.value_at_reg_0x41c = HPS_DEBUG_ADDR; //hps_ddr dest
    op_config.value_at_reg_0x420 = op_config.value_at_reg_0x04c;

    sprintf(op_config.read_verify[0].filename, "block_op/task2_bin/testblock/relu_outb.tile_idx_0_0.1.bin");
    sprintf(op_config.read_from_ddr[0].filename, "block_op/task2_bin/testblock/fc_out.bin");
    op_config.read_from_ddr[0].ddr_base_address = HPS_DEBUG_ADDR;
    op_config.read_from_ddr[0].info_size = op_config.value_at_reg_0x04c / 8;

    call_op(&op_config);
    // return rv;
}

void task2_test_pooling()
{
    // bool rv;
    op_config_t op_config;
    memset(&op_config, 0, sizeof(op_config_t));
#ifdef DEBUG_PRINT
    printf("******************************************************************\n");
    printf("* START %s\n", __FUNCTION__);
    printf("*\n");
#endif

    sprintf(op_config.write_to_ddr[0].filename, "block_op/task2_bin/testpooling/input.bin");
    op_config.write_to_ddr[0].ddr_base_address = 0x35000000;
    op_config.value_at_reg_0x400 = 0x35000000; //hps ddr
    op_config.value_at_reg_0x404 = 0x2000;
    op_config.value_at_reg_0x408 = 0x35000000; //fpga ddr
    op_config.value_at_reg_0x40c = 0x2000;

    op_config.value_at_reg_0x414 = 0x36000000; //fpga_ddr src
    op_config.value_at_reg_0x418 = 0x800;
    op_config.value_at_reg_0x41c = HPS_DEBUG_ADDR; //hps_ddr dest
    op_config.value_at_reg_0x420 = 0x800;

    sprintf(op_config.read_from_ddr[0].filename, "block_op/task2_bin/testpooling/pooling_out.bin");
    op_config.read_from_ddr[0].ddr_base_address = HPS_DEBUG_ADDR;
    op_config.read_from_ddr[0].info_size = 0x800;

    call_pooling(&op_config);
    // return rv;
}
#endif