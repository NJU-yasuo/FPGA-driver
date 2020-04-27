#include "op_ini_config.h"
#include "parameter_addr.h"

op_initial op001_ini = {
    .num_subid = 16,
    .FRAC_OUT = 4,
    .FRAC_IN = 11,

    .IN_CHANNELS = {4, 4095, 4095, 4095},
    .OUT_CHANNELS = {16, 4095, 4095, 4095},
    .KERNEL_SIZES = {3, 255, 255, 255},
    .P_IN = {2, 1, 1, 1},
    .P_OUT = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .V_LAYER = 1,
    .ResAddLayer = 15,
    .BNLayer = 0,
    .ReLULayer = 1,

    .ColOvlapOffset = 0,
    .RowOvlapOffset = 0,

    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,

    .SelReLU6 = 0,
    .V_MAX_GROUP = 8,
    .V_WEI_BANK_DEPTH = 1024,
    .num_valid_weights = 302,

    .Last_block_stride = 0

};

op_addr_initial op001_addr_ini = {
    .block_id = 1,

    .value_at_reg_0x040 = ACT_OP001_RD_BASE_ADDR,
    .value_at_reg_0x044 = ACT_OP001_FETCH_RD_NUM,

    .value_at_reg_0x048 = ACT_OP001_WR_BASE_ADDR,
    .value_at_reg_0x04c = ACT_OP001_FETCH_WR_NUM,

    .value_at_reg_0x080 = WEIGHT_OP001_RW_BASE_ADDR,
    .value_at_reg_0x084 = WEIGHT_OP001_FIRST_FETCH_NUM,

    .value_at_reg_0x08c = WEIGHT_OP001_IP_FETCH_NUM,
    .value_at_reg_0x090 = WEIGHT_OP001_IP_FETCH_ADDR,

    .value_at_reg_0x0d0 = BIAS_OP001_RW_BASE_ADDR,
    .value_at_reg_0x0d4 = BIAS_OP001_FETCH_NUM

};

op_initial op002_ini = {
    .num_subid = 16,
    .FRAC_OUT = 4,
    .FRAC_IN = 11,

    .IN_CHANNELS = {16, 16, 16, 16},
    .OUT_CHANNELS = {16, 64, 16, 64},
    .KERNEL_SIZES = {1, 1, 3, 1},
    .P_IN = {2, 2, 2, 2},
    .P_OUT = {1, 1, 1, 1},
    .input_buffer_seq = {1, 1, 2, 1},
    .output_buffer_seq = {2, 4, 1, 4},
    .res_input_buffer = 4,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .V_LAYER = 4,
    .ResAddLayer = 4,
    .BNLayer = 0, //actual -1,
    .ReLULayer = 13,

    .ColOvlapOffset = 0,
    .RowOvlapOffset = 0,

    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,

    .SelReLU6 = 0,
    .V_MAX_GROUP = 8,
    .V_WEI_BANK_DEPTH = 1024,
    .num_valid_weights = 3608,

    .Last_block_stride = 0

};

op_addr_initial op002_addr_ini = {
    .block_id = 2,

    .value_at_reg_0x040 = ACT_OP002_RD_BASE_ADDR,
    .value_at_reg_0x044 = ACT_OP002_FETCH_RD_NUM,

    .value_at_reg_0x048 = ACT_OP002_WR_BASE_ADDR,
    .value_at_reg_0x04c = ACT_OP002_FETCH_WR_NUM,

    .value_at_reg_0x080 = WEIGHT_OP002_RW_BASE_ADDR,
    .value_at_reg_0x084 = WEIGHT_OP002_FIRST_FETCH_NUM,

    .value_at_reg_0x08c = WEIGHT_OP002_IP_FETCH_NUM,
    .value_at_reg_0x090 = WEIGHT_OP002_IP_FETCH_ADDR,

    .value_at_reg_0x0d0 = BIAS_OP002_RW_BASE_ADDR,
    .value_at_reg_0x0d4 = BIAS_OP002_FETCH_NUM

};

op_initial op031_ini = {
    .num_subid = 16,
    .FRAC_OUT = 4,
    .FRAC_IN = 11,

    .IN_CHANNELS = {64, 16, 16, 4095},
    .OUT_CHANNELS = {16, 16, 64, 4095},
    .KERNEL_SIZES = {1, 3, 1, 255},
    .P_IN = {2, 2, 2, 1},
    .P_OUT = {1, 1, 1, 1},
    .input_buffer_seq = {1, 2, 4, 0},
    .output_buffer_seq = {2, 4, 1, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .V_LAYER = 3,
    .ResAddLayer = 3,
    .BNLayer = 0, //actual -1,
    .ReLULayer = 7,

    .ColOvlapOffset = 0,
    .RowOvlapOffset = 0,

    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,

    .SelReLU6 = 0,
    .V_MAX_GROUP = 8,
    .V_WEI_BANK_DEPTH = 1024,
    .num_valid_weights = 3328,

    .Last_block_stride = 0

};
op_addr_initial op031_addr_ini = {
    .block_id = 31,

    .value_at_reg_0x040 = ACT_OP031_RD_BASE_ADDR,
    .value_at_reg_0x044 = ACT_OP031_FETCH_RD_NUM,
    .value_at_reg_0x048 = ACT_OP031_WR_BASE_ADDR,
    .value_at_reg_0x04c = ACT_OP031_FETCH_WR_NUM,
    .value_at_reg_0x080 = WEIGHT_OP031_RW_BASE_ADDR,
    .value_at_reg_0x084 = WEIGHT_OP031_FIRST_FETCH_NUM,
    .value_at_reg_0x08c = WEIGHT_OP031_IP_FETCH_NUM,
    .value_at_reg_0x090 = WEIGHT_OP031_IP_FETCH_ADDR,
    .value_at_reg_0x0d0 = BIAS_OP031_RW_BASE_ADDR,
    .value_at_reg_0x0d4 = BIAS_OP031_FETCH_NUM

};

op_initial op032_ini = {
    .num_subid = 8,
    .IN_CHANNELS = {128, 32, 32, 4095},
    .OUT_CHANNELS = {32, 32, 128, 4095},
    .KERNEL_SIZES = {1, 3, 1, 255},
    .P_IN = {4, 4, 4, 1},
    .P_OUT = {1, 1, 1, 1},
    .input_buffer_seq = {1, 2, 4, 0},
    .output_buffer_seq = {2, 4, 1, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .V_LAYER = 3,
    .ResAddLayer = 3,
    .BNLayer = 0, //actual -1,
    .ReLULayer = 7,

    .ColOvlapOffset = 0,
    .RowOvlapOffset = 0,

    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,

    .SelReLU6 = 0,
    .V_MAX_GROUP = 8,
    .V_WEI_BANK_DEPTH = 1024,
    .num_valid_weights = 13624,

    .Last_block_stride = 1,

    .FRAC_OUT = 4,
    .FRAC_IN = 11};

op_addr_initial op032_addr_ini = {
    .block_id = 32,

    .value_at_reg_0x040 = ACT_OP032_RD_BASE_ADDR,
    .value_at_reg_0x044 = ACT_OP032_FETCH_RD_NUM,
    .value_at_reg_0x048 = ACT_OP032_WR_BASE_ADDR,
    .value_at_reg_0x04c = ACT_OP032_FETCH_WR_NUM,
    .value_at_reg_0x080 = WEIGHT_OP032_RW_BASE_ADDR,
    .value_at_reg_0x084 = WEIGHT_OP032_FIRST_FETCH_NUM,
    .value_at_reg_0x08c = WEIGHT_OP032_IP_FETCH_NUM,
    .value_at_reg_0x090 = WEIGHT_OP032_IP_FETCH_ADDR,
    .value_at_reg_0x0d0 = BIAS_OP032_RW_BASE_ADDR,
    .value_at_reg_0x0d4 = BIAS_OP032_FETCH_NUM

};

op_initial op033_ini = {
    .num_subid = 4,
    .IN_CHANNELS = {256, 64, 64, 4095},
    .OUT_CHANNELS = {64, 64, 256, 4095},
    .KERNEL_SIZES = {1, 3, 1, 255},
    .P_IN = {8, 8, 8, 1},
    .P_OUT = {1, 1, 1, 1},
    .input_buffer_seq = {1, 2, 4, 0},
    .output_buffer_seq = {2, 4, 1, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .V_LAYER = 3,
    .ResAddLayer = 3,
    .BNLayer = 0, //actual -1,
    .ReLULayer = 7,

    .ColOvlapOffset = 0,
    .RowOvlapOffset = 0,

    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,

    .SelReLU6 = 0,
    .V_MAX_GROUP = 8,
    .V_WEI_BANK_DEPTH = 1024,
    .num_valid_weights = 38998,

    .Last_block_stride = 1,

    .FRAC_OUT = 4,
    .FRAC_IN = 11};

op_addr_initial op033_addr_ini = {
    .block_id = 33,

    .value_at_reg_0x040 = ACT_OP033_RD_BASE_ADDR,
    .value_at_reg_0x044 = ACT_OP033_FETCH_RD_NUM,
    .value_at_reg_0x048 = ACT_OP033_WR_BASE_ADDR,
    .value_at_reg_0x04c = ACT_OP033_FETCH_WR_NUM,
    .value_at_reg_0x080 = WEIGHT_OP033_RW_BASE_ADDR,
    .value_at_reg_0x084 = WEIGHT_OP033_FIRST_FETCH_NUM,
    .value_at_reg_0x08c = WEIGHT_OP033_IP_FETCH_NUM,
    .value_at_reg_0x090 = WEIGHT_OP033_IP_FETCH_ADDR,
    .value_at_reg_0x0d0 = BIAS_OP033_RW_BASE_ADDR,
    .value_at_reg_0x0d4 = BIAS_OP033_FETCH_NUM

};

op_initial op041_ini = {
    .num_subid = 16,
    .IN_CHANNELS = {64, 64, 32, 32},
    .OUT_CHANNELS = {32, 128, 32, 128},
    .KERNEL_SIZES = {1, 1, 3, 1},
    .P_IN = {2, 2, 2, 4},
    .P_OUT = {1, 2, 2, 1},
    .input_buffer_seq = {1, 1, 2, 1},
    .output_buffer_seq = {2, 4, 1, 4},
    .res_input_buffer = 4,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .V_LAYER = 4,
    .ResAddLayer = 4,
    .BNLayer = 0, //actual -1,
    .ReLULayer = 13,

    .ColOvlapOffset = 0,
    .RowOvlapOffset = 0,

    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,

    .SelReLU6 = 0,
    .V_MAX_GROUP = 8,
    .V_WEI_BANK_DEPTH = 1024,
    .num_valid_weights = 432,

    .Last_block_stride = 0,

    .FRAC_OUT = 4,
    .FRAC_IN = 11};

op_addr_initial op041_addr_ini = {
    .block_id = 41,

    .value_at_reg_0x040 = ACT_OP041_RD_BASE_ADDR,
    .value_at_reg_0x044 = ACT_OP041_FETCH_RD_NUM,
    .value_at_reg_0x048 = ACT_OP041_WR_BASE_ADDR,
    .value_at_reg_0x04c = ACT_OP041_FETCH_WR_NUM,
    .value_at_reg_0x080 = WEIGHT_OP041_RW_BASE_ADDR,
    .value_at_reg_0x084 = WEIGHT_OP041_FIRST_FETCH_NUM,
    .value_at_reg_0x08c = WEIGHT_OP041_IP_FETCH_NUM,
    .value_at_reg_0x090 = WEIGHT_OP041_IP_FETCH_ADDR,
    .value_at_reg_0x0d0 = BIAS_OP041_RW_BASE_ADDR,
    .value_at_reg_0x0d4 = BIAS_OP041_FETCH_NUM

};

op_initial op042_ini = {
    .num_subid = 8,
    .IN_CHANNELS = {128, 128, 64, 64},
    .OUT_CHANNELS = {64, 256, 64, 256},
    .KERNEL_SIZES = {1, 1, 3, 1},
    .P_IN = {4, 4, 4, 8},
    .P_OUT = {1, 2, 2, 1},
    .input_buffer_seq = {1, 1, 2, 1},
    .output_buffer_seq = {2, 4, 1, 4},
    .res_input_buffer = 4,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .V_LAYER = 4,
    .ResAddLayer = 4,
    .BNLayer = 0, //actual -1,
    .ReLULayer = 13,

    .ColOvlapOffset = 0,
    .RowOvlapOffset = 0,

    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,

    .SelReLU6 = 0,
    .V_MAX_GROUP = 8,
    .V_WEI_BANK_DEPTH = 1024,
    .num_valid_weights = 40000,

    .Last_block_stride = 0,

    .FRAC_OUT = 4,
    .FRAC_IN = 11};

op_addr_initial op042_addr_ini = {
    .block_id = 42,

    .value_at_reg_0x040 = ACT_OP042_RD_BASE_ADDR,
    .value_at_reg_0x044 = ACT_OP042_FETCH_RD_NUM,
    .value_at_reg_0x048 = ACT_OP042_WR_BASE_ADDR,
    .value_at_reg_0x04c = ACT_OP042_FETCH_WR_NUM,
    .value_at_reg_0x080 = WEIGHT_OP042_RW_BASE_ADDR,
    .value_at_reg_0x084 = WEIGHT_OP042_FIRST_FETCH_NUM,
    .value_at_reg_0x08c = WEIGHT_OP042_IP_FETCH_NUM,
    .value_at_reg_0x090 = WEIGHT_OP042_IP_FETCH_ADDR,
    .value_at_reg_0x0d0 = BIAS_OP042_RW_BASE_ADDR,
    .value_at_reg_0x0d4 = BIAS_OP042_FETCH_NUM

};

task1_weight_ini_t task1_weight = {

    .value_at_reg_0x400 = HPS2FPGA_SRC_BASE_ADDR, //hps ddr
    .value_at_reg_0x404 = HPS2FPGA_SRC_SCALE,
    .value_at_reg_0x408 = HPS2FPGA_DES_BASE_ADDR, //fpga ddr
    .value_at_reg_0x40c = HPS2FPGA_DES_SCALE,
    .write_to_ddr[0].filename = "block_op/task1_bin/task1_weightb_op001.bin",
    .write_to_ddr[0].ddr_base_address = WEIGHT_OP001_RW_BASE_ADDR,
    .write_to_ddr[1].filename = "block_op/task1_bin/task1_biasb_op001.bin",
    .write_to_ddr[1].ddr_base_address = BIAS_OP001_RW_BASE_ADDR,
    .write_to_ddr[2].filename = "block_op/task1_bin/task1_weightb_op002.bin",
    .write_to_ddr[2].ddr_base_address = WEIGHT_OP002_RW_BASE_ADDR,
    .write_to_ddr[3].filename = "block_op/task1_bin/task1_biasb_op002.bin",
    .write_to_ddr[3].ddr_base_address = BIAS_OP002_RW_BASE_ADDR,
    .write_to_ddr[4].filename = "block_op/task1_bin/task1_weightb_op0031.bin",
    .write_to_ddr[4].ddr_base_address = WEIGHT_OP031_RW_BASE_ADDR,
    .write_to_ddr[5].filename = "block_op/task1_bin/task1_biasb_op0031.bin",
    .write_to_ddr[5].ddr_base_address = BIAS_OP031_RW_BASE_ADDR,
    .write_to_ddr[6].filename = "block_op/task1_bin/task1_weightb_op0041.bin",
    .write_to_ddr[6].ddr_base_address = WEIGHT_OP041_RW_BASE_ADDR,
    .write_to_ddr[7].filename = "block_op/task1_bin/task1_biasb_op0041.bin",
    .write_to_ddr[7].ddr_base_address = BIAS_OP041_RW_BASE_ADDR,
    .write_to_ddr[8].filename = "block_op/task1_bin/task1_weightb_op0032.bin",
    .write_to_ddr[8].ddr_base_address = WEIGHT_OP032_RW_BASE_ADDR,
    .write_to_ddr[9].filename = "block_op/task1_bin/task1_biasb_op0032.bin",
    .write_to_ddr[9].ddr_base_address = BIAS_OP032_RW_BASE_ADDR,
    .write_to_ddr[10].filename = "block_op/task1_bin/task1_weightb_op0042.bin",
    .write_to_ddr[10].ddr_base_address = WEIGHT_OP042_RW_BASE_ADDR,
    .write_to_ddr[11].filename = "block_op/task1_bin/task1_biasb_op0042.bin",
    .write_to_ddr[11].ddr_base_address = BIAS_OP042_RW_BASE_ADDR,
    .write_to_ddr[12].filename = "block_op/task1_bin/task1_weightb_op0033.bin",
    .write_to_ddr[12].ddr_base_address = WEIGHT_OP033_RW_BASE_ADDR,
    .write_to_ddr[13].filename = "block_op/task1_bin/task1_biasb_op0033.bin",
    .write_to_ddr[13].ddr_base_address = BIAS_OP033_RW_BASE_ADDR,
};