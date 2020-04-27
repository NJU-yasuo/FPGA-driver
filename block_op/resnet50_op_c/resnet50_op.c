/*
 * @Descripttion: Set restnet50 op
 * @version: 1.0
 * @Author: wuwei
 * @Date: 2020-03-02 09:46:59
 * @LastEditTime: 2020-03-05 18:07:05
 */
#include <stdio.h>
#include "fx_hpca.h"
#include <stdbool.h>
#include "op_ini_config.h"
#include "op_api.h"

bool set_50_verify_parameter(op_config_t *op_config, int block_id, int sub_id, int row, int col_1, int col_2)
{

    // sprintf(op_config->read_verify[0].filename, "block_op/task2_bin/relu_outb.tile_idx_%d_%d.3.bin", row, col_1);
    if (block_id == 0)
    {
        if (sub_id % 2 == 0)
        {
            sprintf(op_config->read_verify[0].filename, "block_op/resnet50_bin/block%d/relu_outb.tile_idx_%d_%d.1.bin", block_id, row, col_1 * 2 + col_2);
            sprintf(op_config->read_from_ddr[0].filename, "block_op/resnet50_bin/block%d/Block%d_Tile%d_row%d_col1_%d.bin", block_id, block_id, sub_id, row, col_1);
            op_config->read_from_ddr[0].ddr_base_address = op_config->value_at_reg_0x90;
            op_config->read_from_ddr[0].info_size = op_config->value_at_reg_0x94;
        }
    }
    else if (block_id == 2)
    {
        sprintf(op_config->read_verify[0].filename, "block_op/resnet50_bin/block%d/relu_outb.tile_idx_%d_%d.3.bin", block_id, row, col_1);
        sprintf(op_config->read_from_ddr[0].filename, "block_op/resnet50_bin/block%d/Block%d_Tile%d_row%d_col1_%d.bin", block_id, block_id, sub_id, row, col_1);
        op_config->read_from_ddr[0].ddr_base_address = op_config->value_at_reg_0x90;
        op_config->read_from_ddr[0].info_size = op_config->value_at_reg_0x94;
    }
    else if (block_id == 3)
    {
        if (sub_id % 2 == 0)
        {
            sprintf(op_config->read_verify[0].filename, "block_op/resnet50_bin/block%d/relu_outb.tile_idx_%d_%d.4.bin", block_id, row, col_1 * 2 + col_2);
            sprintf(op_config->read_from_ddr[0].filename, "block_op/resnet50_bin/block%d/Block%d_Tile%d_row%d_col1_%d.bin", block_id, block_id, sub_id, row, col_1);
            op_config->read_from_ddr[0].ddr_base_address = op_config->value_at_reg_0x90;
            op_config->read_from_ddr[0].info_size = op_config->value_at_reg_0x94;
        }
    }
    // else
    // {
    //     sprintf(op_config->read_verify[0].filename, "block_op/task2_bin/block%d/relu_outb.tile_idx_%d_%d.3.bin", block_id, row, col_1);
    //     sprintf(op_config->read_from_ddr[0].filename, "block_op/task2_bin/block%d/Block%d_Tile%d_row%d_col1_%d.bin", block_id, block_id, sub_id, row, col_1);
    //     op_config->read_from_ddr[0].ddr_base_address = op_config->value_at_reg_0x90;
    //     op_config->read_from_ddr[0].info_size = op_config->value_at_reg_0x94;
    // }
    return true;
}

void set_50_parameter(op_ini_param_t *op_param)
{
    op_param->net_type = 1;
    if (op_param->v_layer == 1)
    {
        op_param->input_buffer_seq[0] = 1;  // {1, 0, 0, 0},
        op_param->input_buffer_seq[1] = 0;  // {1, 0, 0, 0},
        op_param->input_buffer_seq[2] = 0;  //{1, 0, 0, 0},
        op_param->input_buffer_seq[3] = 0;  //{1, 0, 0, 0},
        op_param->output_buffer_seq[0] = 2; //{2, 0, 0, 0},
        op_param->output_buffer_seq[1] = 0; //{2, 0, 0, 0},
        op_param->output_buffer_seq[2] = 0; //{2, 0, 0, 0},
        op_param->output_buffer_seq[3] = 0; //{2, 0, 0, 0},
        op_param->res_input_buffer = 1,
        op_param->act_bank_in_seq[0] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_in_seq[1] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_in_seq[2] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_in_seq[3] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_out_seq[0] = 1; //{1, 3, 3, 3},
        op_param->act_bank_out_seq[1] = 3; //{1, 3, 3, 3},
        op_param->act_bank_out_seq[2] = 3; //{1, 3, 3, 3},
        op_param->act_bank_out_seq[3] = 3; //{1, 3, 3, 3},

        op_param->res_act_bank_in = 3;
        op_param->ResAddLayer = 15; // -1
        op_param->QuanValueOfSix = 96;
        op_param->SelOvRAMtoRead = 0;
        op_param->SelRelu6 = 0;
        // .DWConv = 0b0000,
        op_param->which_prebn_act_bank = 2;
    }
    else if (op_param->v_layer == 3)
    {
        op_param->input_buffer_seq[0] = 1;  // {1, 0, 0, 0},
        op_param->input_buffer_seq[1] = 2;  // {1, 0, 0, 0},
        op_param->input_buffer_seq[2] = 4;  //{1, 0, 0, 0},
        op_param->input_buffer_seq[3] = 0;  //{1, 0, 0, 0},
        op_param->output_buffer_seq[0] = 2; //{2, 0, 0, 0},
        op_param->output_buffer_seq[1] = 4; //{2, 0, 0, 0},
        op_param->output_buffer_seq[2] = 1; //{2, 0, 0, 0},
        op_param->output_buffer_seq[3] = 0; //{2, 0, 0, 0},
        op_param->res_input_buffer = 1,
        op_param->act_bank_in_seq[0] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_in_seq[1] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_in_seq[2] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_in_seq[3] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_out_seq[0] = 3; //{1, 3, 3, 3},
        op_param->act_bank_out_seq[1] = 3; //{1, 3, 3, 3},
        op_param->act_bank_out_seq[2] = 3; //{1, 3, 3, 3},
        op_param->act_bank_out_seq[3] = 3; //{1, 3, 3, 3},
        op_param->res_act_bank_in = 3;
        op_param->ResAddLayer = 3; // -1
        op_param->QuanValueOfSix = 96;
        op_param->SelOvRAMtoRead = 0b0110;
        op_param->SelRelu6 = 0;
        op_param->which_prebn_act_bank = 2;
    }
    else if (op_param->v_layer == 4)
    {
        op_param->input_buffer_seq[0] = 1;  // {1, 0, 0, 0},
        op_param->input_buffer_seq[1] = 1;  // {1, 0, 0, 0},
        op_param->input_buffer_seq[2] = 2;  //{1, 0, 0, 0},
        op_param->input_buffer_seq[3] = 1;  //{1, 0, 0, 0},
        op_param->output_buffer_seq[0] = 2; //{2, 0, 0, 0},
        op_param->output_buffer_seq[1] = 4; //{2, 0, 0, 0},
        op_param->output_buffer_seq[2] = 1; //{2, 0, 0, 0},
        op_param->output_buffer_seq[3] = 4; //{2, 0, 0, 0},
        op_param->res_input_buffer = 4,
        op_param->act_bank_in_seq[0] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_in_seq[1] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_in_seq[2] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_in_seq[3] = 3;  //{3, 3, 3, 3},
        op_param->act_bank_out_seq[0] = 3; //{1, 3, 3, 3},
        op_param->act_bank_out_seq[1] = 3; //{1, 3, 3, 3},
        op_param->act_bank_out_seq[2] = 3; //{1, 3, 3, 3},
        op_param->act_bank_out_seq[3] = 3; //{1, 3, 3, 3},

        op_param->res_act_bank_in = 3;
        op_param->ResAddLayer = 4; // -1
        op_param->QuanValueOfSix = 96;
        op_param->SelOvRAMtoRead = 0;
        op_param->SelRelu6 = 0;
        op_param->which_prebn_act_bank = 2;
    }
}

bool resnet50_set_op(op_ini_param_t *op_param, void *img_ptr, void *output_ptr, int start_block, int test_block)
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
                set_50_parameter(op_param);
                test_set(&op_config, op_param, row, col_1, col_2);
                if (start_block == op_param->block_id)
                {
                    op_param->Last_block_stride = 0;
                }
                if (op_param->block_id == test_block)
                {
                    set_50_verify_parameter(&op_config, test_block, op_param->sub_id, row, col_1, col_2);
                }
                rv = call_op(&op_config);
                //TODO:TEST;
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