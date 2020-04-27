#include "op_ini_config.h"
#include "task2_parameter_addr.h"

op_ini_param_t block000_ini = {

    .block_id = 0,
    .col = 40,
    .row = 5,
    .blockstride = 2,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {3, 4095, 4095, 4095},
    .out_channels = {32, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},

    .p_in = {1, 1, 1, 1},
    .p_out = {2, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {1, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 1,
    .ReLULayer = 1,

    .ColOvlapOffset = 3,  // k=3 layer, InChannels/Group = 3/1
    .RowOvlapOffset = 16, // k=3 layer, OutChannels/Stride = 32/2

    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 3,

    .wei_base_addr = WEIGHT_block00_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block00_RW_BASE_ADDR,
    .bn_wei_base_addr = BN_mul_block00_RW_BASE_ADDR,
    .bn_bias_base_addr = BN_BIAS_block00_RW_BASE_ADDR,
    .act_ram_rd_base_addr = ACT_block00_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block00_HW_WR_BASE_ADDR,

    // .num_valid_weights = 276, //weight number
    .num_valid_weights = 212, //weight number
    .Last_block_stride = 0};

op_ini_param_t block001_ini = {

    .block_id = 1,
    .col = 20,
    .row = 5,
    .blockstride = 2,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {32, 32, 16, 16},
    .out_channels = {16, 64, 16, 64},
    .kernel_sizes = {1, 1, 3, 1},
    .p_in = {2, 2, 2, 4},
    .p_out = {1, 2, 2, 1},
    .input_buffer_seq = {1, 1, 2, 1},
    .output_buffer_seq = {2, 4, 1, 4},
    .res_input_buffer = 4,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 4,
    .ResAddLayer = 4,
    .BNLayer = 5,        // 0101
    .ReLULayer = 13,     // 1101
    .ColOvlapOffset = 8, // k=3 layer, InChannels/Group = 16/2
    .RowOvlapOffset = 8, // k=3 layer, OutChannels/Stride = 16/2
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    // .num_valid_weights = 2756, //weight number

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 3,

    .wei_base_addr = WEIGHT_block01_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block01_RW_BASE_ADDR,
    .bn_wei_base_addr = BN_mul_block01_RW_BASE_ADDR,
    .bn_bias_base_addr = BN_BIAS_block01_RW_BASE_ADDR,
    .act_ram_rd_base_addr = ACT_block01_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block01_HW_WR_BASE_ADDR,
    .num_valid_weights = 2244,
    .Last_block_stride = 1,
};

op_ini_param_t block002_ini = {

    .block_id = 2,
    .col = 10,
    .row = 5,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {64, 16, 16, 4095},
    .out_channels = {16, 16, 64, 4095},
    .kernel_sizes = {1, 3, 1, 255},
    .p_in = {4, 4, 4, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 2, 4, 0},
    .output_buffer_seq = {2, 4, 1, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 3,
    .ResAddLayer = 3,
    .BNLayer = 0b0011,
    .ReLULayer = 0b0111,
    .ColOvlapOffset = 4,  // k=3 layer, InChannels/Group = 16/4
    .RowOvlapOffset = 16, // k=3 layer, OutChannels/Stride = 16/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0b0110,
    .SelRelu6 = 0,
    // .num_valid_weights = 1512, //weight number

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block02_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block02_RW_BASE_ADDR,
    .bn_wei_base_addr = BN_mul_block02_RW_BASE_ADDR,
    .bn_bias_base_addr = BN_BIAS_block02_RW_BASE_ADDR,
    .act_ram_rd_base_addr = ACT_block02_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block02_HW_WR_BASE_ADDR,

    .num_valid_weights = 1244, //weight number
    .Last_block_stride = 1,
};

op_ini_param_t block003_ini = {

    .block_id = 3,
    .col = 10,
    .row = 5,
    .blockstride = 2,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {64, 64, 32, 32},
    .out_channels = {32, 128, 32, 128},
    .kernel_sizes = {1, 1, 3, 1},
    .p_in = {4, 4, 4, 8},
    .p_out = {1, 2, 2, 1},
    .input_buffer_seq = {1, 1, 2, 1},
    .output_buffer_seq = {2, 4, 1, 4},
    .res_input_buffer = 4,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 4,
    .ResAddLayer = 4,
    .BNLayer = 5,    // 0101
    .ReLULayer = 13, // 1101

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,

    .ColOvlapOffset = 8,  // k=3 layer, InChannels/Group = 32/4
    .RowOvlapOffset = 16, // k=3 layer, OutChannels/Stride = 32/2
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .wei_base_addr = WEIGHT_block03_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block03_RW_BASE_ADDR,
    .bn_wei_base_addr = BN_mul_block03_RW_BASE_ADDR,
    .bn_bias_base_addr = BN_BIAS_block03_RW_BASE_ADDR,
    .act_ram_rd_base_addr = ACT_block03_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block03_HW_WR_BASE_ADDR,
    .num_valid_weights = 12448, //weight number
    .Last_block_stride = 0};

op_ini_param_t block004_ini = {

    .block_id = 4,
    .col = 5,
    .row = 5,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {128, 32, 32, 4095},
    .out_channels = {32, 32, 128, 4095},
    .kernel_sizes = {1, 3, 1, 255},
    .p_in = {8, 8, 8, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 2, 4, 0},
    .output_buffer_seq = {2, 4, 1, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 3,
    .ResAddLayer = 3,
    .BNLayer = 11,   // 0011
    .ReLULayer = 15, // 0111

    .ColOvlapOffset = 4,  // k=3 layer, InChannels/Group = 32/8
    .RowOvlapOffset = 32, // k=3 layer, OutChannels/Stride = 32/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block04_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block04_RW_BASE_ADDR,
    .bn_wei_base_addr = BN_mul_block04_RW_BASE_ADDR,
    .bn_bias_base_addr = BN_BIAS_block04_RW_BASE_ADDR,
    .act_ram_rd_base_addr = ACT_block04_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block04_HW_WR_BASE_ADDR,
    .num_valid_weights = 5688, //weight number

    .Last_block_stride = 1};

op_ini_param_t block005_ini = {

    .block_id = 5,
    .col = 5,
    .row = 5,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {128, 4095, 4095, 4095},
    .out_channels = {16, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {8, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 0,

    .ColOvlapOffset = 16, // k=3 layer, InChannels/Group = 128/8
    .RowOvlapOffset = 16, // k=3 layer, OutChannels/Stride = 16/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block05_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block05_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block05_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block05_HW_WR_BASE_ADDR,

    .num_valid_weights = 4024, //weight number
    .Last_block_stride = 0};

op_ini_param_t block006_ini = {

    .block_id = 6,
    .col = 5,
    .row = 5,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {128, 4095, 4095, 4095},
    .out_channels = {8, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {8, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 0,
    .ColOvlapOffset = 16, // k=3 layer, InChannels/Group = 128/8
    .RowOvlapOffset = 8,  // k=3 layer, OutChannels/Stride = 8/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block06_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block06_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block06_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block06_HW_WR_BASE_ADDR,
    .num_valid_weights = 2336, //weight number
    .Last_block_stride = 0};

op_ini_param_t block007_ini = {

    .block_id = 7,
    .col = 8,
    .row = 1,
    .blockstride = 2,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {128, 128, 64, 64},
    .out_channels = {64, 256, 64, 256},
    .kernel_sizes = {1, 1, 3, 1},
    .p_in = {1, 1, 1, 2},
    .p_out = {1, 2, 2, 1},
    .input_buffer_seq = {1, 1, 2, 1},
    .output_buffer_seq = {2, 4, 1, 4},
    .res_input_buffer = 4,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 4,
    .ResAddLayer = 4,
    .BNLayer = 5,    // 0101
    .ReLULayer = 13, // 1101

    .ColOvlapOffset = 64, // k=3 layer, InChannels/Group = 64/1
    .RowOvlapOffset = 32, // k=3 layer, OutChannels/Stride = 64/2
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block07_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block07_RW_BASE_ADDR,
    .bn_wei_base_addr = BN_mul_block07_RW_BASE_ADDR,
    .bn_bias_base_addr = BN_BIAS_block07_RW_BASE_ADDR,
    .act_ram_rd_base_addr = ACT_block07_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block07_HW_WR_BASE_ADDR,
    .num_valid_weights = 21476, //weight number
    .Last_block_stride = 0};

op_ini_param_t block008_ini = {

    .block_id = 8,
    .col = 4,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {256, 64, 64, 4095},
    .out_channels = {64, 64, 256, 4095},
    .kernel_sizes = {1, 3, 1, 255},
    .p_in = {2, 2, 2, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 2, 4, 0},
    .output_buffer_seq = {2, 4, 1, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 3,
    .ResAddLayer = 3,
    .BNLayer = 11,   // 0011
    .ReLULayer = 15, // 0111

    .ColOvlapOffset = 32, // k=3 layer, InChannels/Group = 64/2
    .RowOvlapOffset = 64, // k=3 layer, OutChannels/Stride = 64/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block08_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block08_RW_BASE_ADDR,
    .bn_wei_base_addr = BN_mul_block08_RW_BASE_ADDR,
    .bn_bias_base_addr = BN_BIAS_block08_RW_BASE_ADDR,
    .act_ram_rd_base_addr = ACT_block08_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block08_HW_WR_BASE_ADDR,
    .num_valid_weights = 11912, //weight number
    .Last_block_stride = 1};

op_ini_param_t block009_ini = {

    .block_id = 9,
    .col = 4,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {256, 4095, 4095, 4095},
    .out_channels = {24, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {2, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 0,

    .ColOvlapOffset = 128, // k=3 layer, InChannels/Group = 256/2
    .RowOvlapOffset = 24,  // k=3 layer, OutChannels/Stride = 24/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block09_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block09_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block09_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block09_HW_WR_BASE_ADDR,
    .num_valid_weights = 8966, //weight number
    .Last_block_stride = 0};

op_ini_param_t block010_ini = {

    .block_id = 10,
    .col = 4,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {256, 4095, 4095, 4095},
    .out_channels = {12, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {2, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 0,

    .ColOvlapOffset = 256, // k=3 layer, InChannels/Group = 256/2
    .RowOvlapOffset = 12,  // k=3 layer, OutChannels/Stride = 12/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block10_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block10_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block10_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block10_HW_WR_BASE_ADDR,
    .num_valid_weights = 4348, //weight number
    .Last_block_stride = 0};

op_ini_param_t block011_ini = {

    .block_id = 11,
    .col = 4,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {256, 4095, 4095, 4095},
    .out_channels = {128, 4095, 4095, 4095},
    .kernel_sizes = {1, 255, 255, 255}, // this layer kernel size is 1x1
    .p_in = {2, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 1,

    .ColOvlapOffset = 0, // k=3 layer, No 3x3 conv
    .RowOvlapOffset = 0, // k=3 layer, No 3x3 conv
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block11_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block11_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block11_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block11_HW_WR_BASE_ADDR,
    .num_valid_weights = 5486, //weight number
    .Last_block_stride = 0};

op_ini_param_t block012_ini = {

    .block_id = 12,
    .col = 4,
    .row = 1,
    .blockstride = 2,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {128, 4095, 4095, 4095},
    .out_channels = {256, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {2, 1, 1, 1},
    .p_out = {2, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 1,

    .ColOvlapOffset = 64,  // k=3 layer, InChannels/Group = 128/2
    .RowOvlapOffset = 256, // k=3 layer, OutChannels/Stride = 256/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block12_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block12_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block12_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block12_HW_WR_BASE_ADDR,
    .num_valid_weights = 89600, //weight number
    .Last_block_stride = 0};

op_ini_param_t block013_ini = {

    .block_id = 13,
    .col = 2,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {256, 4095, 4095, 4095},
    .out_channels = {24, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {4, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 0,

    .ColOvlapOffset = 64, // k=3 layer, InChannels/Group = 256/4
    .RowOvlapOffset = 24, // k=3 layer, OutChannels/Stride = 24/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block11_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block11_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block11_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block11_HW_WR_BASE_ADDR,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block13_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block13_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block13_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block13_HW_WR_BASE_ADDR,

    .num_valid_weights = 19740, //weight number
    .Last_block_stride = 1};

op_ini_param_t block014_ini = {
    .block_id = 14,
    .col = 2,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {256, 4095, 4095, 4095},
    .out_channels = {12, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {4, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 0,

    .ColOvlapOffset = 64, // k=3 layer, InChannels/Group = 256/4
    .RowOvlapOffset = 12, // k=3 layer, OutChannels/Stride = 12/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block14_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block14_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block14_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block14_HW_WR_BASE_ADDR,
    .num_valid_weights = 4916, //weight number
    .Last_block_stride = 1};

op_ini_param_t block015_ini = {

    .block_id = 15,
    .col = 2,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {256, 4095, 4095, 4095},
    .out_channels = {64, 4095, 4095, 4095},
    .kernel_sizes = {1, 255, 255, 255}, // this layer kernel size is 1x1
    .p_in = {4, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 1,

    .ColOvlapOffset = 0, // k=3 layer, No 3x3 conv
    .RowOvlapOffset = 0, // k=3 layer, No 3x3 conv
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block15_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block15_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block15_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block15_HW_WR_BASE_ADDR,
    .num_valid_weights = 3124, //weight number
    .Last_block_stride = 1};

op_ini_param_t block016_ini = {

    .block_id = 16,
    .col = 2,
    .row = 1,
    .blockstride = 2,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {64, 4095, 4095, 4095},
    .out_channels = {128, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {4, 1, 1, 1},
    .p_out = {2, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 1,

    .ColOvlapOffset = 16, // k=3 layer, InChannels/Group = 64/4
    .RowOvlapOffset = 64, // k=3 layer, OutChannels/Stride = 128/2
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block16_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block16_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block16_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block16_HW_WR_BASE_ADDR,

    .num_valid_weights = 28472, //weight number
    .Last_block_stride = 0};

op_ini_param_t block017_ini = {

    .block_id = 17,
    .col = 1,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {128, 4095, 4095, 4095},
    .out_channels = {24, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {8, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 0,

    .ColOvlapOffset = 16, // k=3 layer, InChannels/Group = 128/8
    .RowOvlapOffset = 24, // k=3 layer, OutChannels/Stride = 24/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block17_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block17_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block17_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block17_HW_WR_BASE_ADDR,
    .num_valid_weights = 6024, //weight number
    .Last_block_stride = 1};

op_ini_param_t block018_ini = {

    .block_id = 18,
    .col = 1,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {128, 4095, 4095, 4095},
    .out_channels = {12, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {8, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 0,

    .ColOvlapOffset = 16, // k=3 layer, InChannels/Group = 128/8
    .RowOvlapOffset = 12, // k=3 layer, OutChannels/Stride = 12/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block18_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block18_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block18_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block18_HW_WR_BASE_ADDR,
    .num_valid_weights = 2872, //weight number
    .Last_block_stride = 1};

op_ini_param_t block019_ini = {

    .block_id = 19,
    .col = 1,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {128, 4095, 4095, 4095},
    .out_channels = {64, 4095, 4095, 4095},
    .kernel_sizes = {1, 255, 255, 255}, // this layer kernel size is 1x1
    .p_in = {8, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 1,

    .ColOvlapOffset = 0, // k=3 layer, No 3x3 conv
    .RowOvlapOffset = 0, // k=3 layer, No 3x3 conv
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block19_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block19_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block19_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block19_HW_WR_BASE_ADDR,
    .num_valid_weights = 2344, //weight number
    .Last_block_stride = 1};

op_ini_param_t block020_ini = {

    .block_id = 20,
    .col = 1,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {64, 4095, 4095, 4095},
    .out_channels = {128, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {8, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 1,

    .ColOvlapOffset = 8,   // k=3 layer, InChannels/Group = 64/8
    .RowOvlapOffset = 128, // k=3 layer, OutChannels/Stride = 128/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block20_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block20_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block20_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block20_HW_WR_BASE_ADDR,
    .num_valid_weights = 18080, //weight number
    .Last_block_stride = 0};

op_ini_param_t block023_ini = {

    .block_id = 23,
    .col = 1,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {128, 4095, 4095, 4095},
    .out_channels = {64, 4095, 4095, 4095},
    .kernel_sizes = {1, 255, 255, 255},
    .p_in = {8, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 1,

    .ColOvlapOffset = 16, // k=3 layer, InChannels/Group = 128/8
    .RowOvlapOffset = 16, // k=3 layer, OutChannels/Stride = 16/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block23_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block23_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block23_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block23_HW_WR_BASE_ADDR,
    .num_valid_weights = 2312, //weight number
    .Last_block_stride = 0};

op_ini_param_t block024_ini = {

    .block_id = 24,
    .col = 1,
    .row = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,

    .in_channels = {64, 4095, 4095, 4095},
    .out_channels = {128, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .p_in = {8, 1, 1, 1},
    .p_out = {1, 1, 1, 1},
    .input_buffer_seq = {1, 0, 0, 0},
    .output_buffer_seq = {2, 0, 0, 0},
    .res_input_buffer = 1,

    .act_bank_in_seq = {3, 3, 3, 3},
    .act_bank_out_seq = {3, 3, 3, 3},
    .res_act_bank_in = 3,

    .v_layer = 1,
    .ResAddLayer = 15, // -1
    .BNLayer = 0,
    .ReLULayer = 1,

    .ColOvlapOffset = 8,   // k=3 layer, InChannels/Group = 64/8
    .RowOvlapOffset = 128, // k=3 layer, OutChannels/Stride = 128/1
    .QuanValueOfSix = 96,
    .SelOvRAMtoRead = 0,
    .SelRelu6 = 0,

    .pre_bn = 0,
    .DWConv = 0b0000,
    .which_prebn_act_bank = 2,
    .wei_base_addr = WEIGHT_block24_RW_BASE_ADDR,
    .bias_base_addr = BIAS_block24_RW_BASE_ADDR,
    .bn_wei_base_addr = 0,
    .bn_bias_base_addr = 0,
    .act_ram_rd_base_addr = ACT_block24_HW_RD_BASE_ADDR,
    .act_ram_write_base_addr = ACT_block24_HW_WR_BASE_ADDR,
    .num_valid_weights = 17728, //weight number
    .Last_block_stride = 0};

task2_weight_ini_t task2_weight = {

    .value_at_reg_0x400 = T2_HPS2FPGA_SRC_BASE_ADDR, //hps ddr
    .value_at_reg_0x404 = T2_PARAM_HPS2FPGA_SRC_SCALE,
    .value_at_reg_0x408 = T2_HPS2FPGA_DES_BASE_ADDR, //fpga ddr
    .value_at_reg_0x40c = T2_PARAM_HPS2FPGA_SRC_SCALE,
    //block_0
    .write_to_ddr[0].filename = "block_op/task2_bin/block0/weightb0.bin",
    .write_to_ddr[1].filename = "block_op/task2_bin/block0/biasb0.bin",
    .write_to_ddr[2].filename = "block_op/task2_bin/block0/bn_weib0.bin",
    .write_to_ddr[3].filename = "block_op/task2_bin/block0/bn_biasb0.bin",
    .write_to_ddr[0].ddr_base_address = WEIGHT_block00_RW_BASE_ADDR,
    .write_to_ddr[1].ddr_base_address = BIAS_block00_RW_BASE_ADDR,
    .write_to_ddr[2].ddr_base_address = BN_mul_block00_RW_BASE_ADDR,
    .write_to_ddr[3].ddr_base_address = BN_BIAS_block00_RW_BASE_ADDR,

    //block1
    .write_to_ddr[4].filename = "block_op/task2_bin/block1/weightb1.bin",
    .write_to_ddr[5].filename = "block_op/task2_bin/block1/biasb1.bin",
    .write_to_ddr[6].filename = "block_op/task2_bin/block1/bn_weib1.bin",
    .write_to_ddr[7].filename = "block_op/task2_bin/block1/bn_biasb1.bin",
    .write_to_ddr[4].ddr_base_address = WEIGHT_block01_RW_BASE_ADDR,
    .write_to_ddr[5].ddr_base_address = BIAS_block01_RW_BASE_ADDR,
    .write_to_ddr[6].ddr_base_address = BN_mul_block01_RW_BASE_ADDR,
    .write_to_ddr[7].ddr_base_address = BN_BIAS_block01_RW_BASE_ADDR,

    //block2
    .write_to_ddr[8].filename = "block_op/task2_bin/block2/weightb2.bin",
    .write_to_ddr[9].filename = "block_op/task2_bin/block2/biasb2.bin",
    .write_to_ddr[10].filename = "block_op/task2_bin/block2/bn_weib2.bin",
    .write_to_ddr[11].filename = "block_op/task2_bin/block2/bn_biasb2.bin",
    .write_to_ddr[8].ddr_base_address = WEIGHT_block02_RW_BASE_ADDR,
    .write_to_ddr[9].ddr_base_address = BIAS_block02_RW_BASE_ADDR,
    .write_to_ddr[10].ddr_base_address = BN_mul_block02_RW_BASE_ADDR,
    .write_to_ddr[11].ddr_base_address = BN_BIAS_block02_RW_BASE_ADDR,

    //block3
    .write_to_ddr[12].filename = "block_op/task2_bin/block3/weightb3.bin",
    .write_to_ddr[13].filename = "block_op/task2_bin/block3/biasb3.bin",
    .write_to_ddr[14].filename = "block_op/task2_bin/block3/bn_weib3.bin",
    .write_to_ddr[15].filename = "block_op/task2_bin/block3/bn_biasb3.bin",
    .write_to_ddr[12].ddr_base_address = WEIGHT_block03_RW_BASE_ADDR,
    .write_to_ddr[13].ddr_base_address = BIAS_block03_RW_BASE_ADDR,
    .write_to_ddr[14].ddr_base_address = BN_mul_block03_RW_BASE_ADDR,
    .write_to_ddr[15].ddr_base_address = BN_BIAS_block03_RW_BASE_ADDR,

    //block4
    .write_to_ddr[16].filename = "block_op/task2_bin/block4/weightb4.bin",
    .write_to_ddr[17].filename = "block_op/task2_bin/block4/biasb4.bin",
    .write_to_ddr[18].filename = "block_op/task2_bin/block4/bn_weib4.bin",
    .write_to_ddr[19].filename = "block_op/task2_bin/block4/bn_biasb4.bin",
    .write_to_ddr[16].ddr_base_address = WEIGHT_block04_RW_BASE_ADDR,
    .write_to_ddr[17].ddr_base_address = BIAS_block04_RW_BASE_ADDR,
    .write_to_ddr[18].ddr_base_address = BN_mul_block04_RW_BASE_ADDR,
    .write_to_ddr[19].ddr_base_address = BN_BIAS_block04_RW_BASE_ADDR,

    //block5
    .write_to_ddr[20].filename = "block_op/task2_bin/block5/weightb5.bin",
    .write_to_ddr[21].filename = "block_op/task2_bin/block5/biasb5.bin",
    .write_to_ddr[20].ddr_base_address = WEIGHT_block05_RW_BASE_ADDR,
    .write_to_ddr[21].ddr_base_address = BIAS_block05_RW_BASE_ADDR,

    //block6
    .write_to_ddr[22].filename = "block_op/task2_bin/block6/weightb6.bin",
    .write_to_ddr[23].filename = "block_op/task2_bin/block6/biasb6.bin",
    .write_to_ddr[22].ddr_base_address = WEIGHT_block06_RW_BASE_ADDR,
    .write_to_ddr[23].ddr_base_address = BIAS_block06_RW_BASE_ADDR,

    //block7
    .write_to_ddr[24].filename = "block_op/task2_bin/block7/weightb7.bin",
    .write_to_ddr[25].filename = "block_op/task2_bin/block7/biasb7.bin",
    .write_to_ddr[26].filename = "block_op/task2_bin/block7/bn_weib7.bin",
    .write_to_ddr[27].filename = "block_op/task2_bin/block7/bn_biasb7.bin",
    .write_to_ddr[24].ddr_base_address = WEIGHT_block07_RW_BASE_ADDR,
    .write_to_ddr[25].ddr_base_address = BIAS_block07_RW_BASE_ADDR,
    .write_to_ddr[26].ddr_base_address = BN_mul_block07_RW_BASE_ADDR,
    .write_to_ddr[27].ddr_base_address = BN_BIAS_block07_RW_BASE_ADDR,

    //block8
    .write_to_ddr[28].filename = "block_op/task2_bin/block8/weightb8.bin",
    .write_to_ddr[29].filename = "block_op/task2_bin/block8/biasb8.bin",
    .write_to_ddr[30].filename = "block_op/task2_bin/block8/bn_weib8.bin",
    .write_to_ddr[31].filename = "block_op/task2_bin/block8/bn_biasb8.bin",
    .write_to_ddr[28].ddr_base_address = WEIGHT_block08_RW_BASE_ADDR,
    .write_to_ddr[29].ddr_base_address = BIAS_block08_RW_BASE_ADDR,
    .write_to_ddr[30].ddr_base_address = BN_mul_block08_RW_BASE_ADDR,
    .write_to_ddr[31].ddr_base_address = BN_BIAS_block08_RW_BASE_ADDR,

    //block9
    .write_to_ddr[32].filename = "block_op/task2_bin/block9/weightb9.bin",
    .write_to_ddr[33].filename = "block_op/task2_bin/block9/biasb9.bin",
    .write_to_ddr[32].ddr_base_address = WEIGHT_block09_RW_BASE_ADDR,
    .write_to_ddr[33].ddr_base_address = BIAS_block09_RW_BASE_ADDR,

    //block10
    .write_to_ddr[34].filename = "block_op/task2_bin/block10/weightb10.bin",
    .write_to_ddr[35].filename = "block_op/task2_bin/block10/biasb10.bin",
    .write_to_ddr[34].ddr_base_address = WEIGHT_block10_RW_BASE_ADDR,
    .write_to_ddr[35].ddr_base_address = BIAS_block10_RW_BASE_ADDR,

    //block11
    .write_to_ddr[36].filename = "block_op/task2_bin/block11/weightb11.bin",
    .write_to_ddr[37].filename = "block_op/task2_bin/block11/biasb11.bin",
    .write_to_ddr[36].ddr_base_address = WEIGHT_block11_RW_BASE_ADDR,
    .write_to_ddr[37].ddr_base_address = BIAS_block11_RW_BASE_ADDR,

    //block12
    .write_to_ddr[38].filename = "block_op/task2_bin/block12/weightb12.bin",
    .write_to_ddr[39].filename = "block_op/task2_bin/block12/biasb12.bin",
    .write_to_ddr[38].ddr_base_address = WEIGHT_block12_RW_BASE_ADDR,
    .write_to_ddr[39].ddr_base_address = BIAS_block12_RW_BASE_ADDR,

    //block13
    .write_to_ddr[40].filename = "block_op/task2_bin/block13/weightb13.bin",
    .write_to_ddr[41].filename = "block_op/task2_bin/block13/biasb13.bin",
    .write_to_ddr[40].ddr_base_address = WEIGHT_block13_RW_BASE_ADDR,
    .write_to_ddr[41].ddr_base_address = BIAS_block13_RW_BASE_ADDR,

    //block14
    .write_to_ddr[42].filename = "block_op/task2_bin/block14/weightb14.bin",
    .write_to_ddr[43].filename = "block_op/task2_bin/block14/biasb14.bin",
    .write_to_ddr[42].ddr_base_address = WEIGHT_block14_RW_BASE_ADDR,
    .write_to_ddr[43].ddr_base_address = BIAS_block14_RW_BASE_ADDR,

    //block15
    .write_to_ddr[44].filename = "block_op/task2_bin/block15/weightb15.bin",
    .write_to_ddr[45].filename = "block_op/task2_bin/block15/biasb15.bin",
    .write_to_ddr[44].ddr_base_address = WEIGHT_block15_RW_BASE_ADDR,
    .write_to_ddr[45].ddr_base_address = BIAS_block15_RW_BASE_ADDR,

    //block16
    .write_to_ddr[46].filename = "block_op/task2_bin/block16/weightb16.bin",
    .write_to_ddr[47].filename = "block_op/task2_bin/block16/biasb16.bin",
    .write_to_ddr[46].ddr_base_address = WEIGHT_block16_RW_BASE_ADDR,
    .write_to_ddr[47].ddr_base_address = BIAS_block16_RW_BASE_ADDR,

    //block17
    .write_to_ddr[48].filename = "block_op/task2_bin/block17/weightb17.bin",
    .write_to_ddr[49].filename = "block_op/task2_bin/block17/biasb17.bin",
    .write_to_ddr[48].ddr_base_address = WEIGHT_block17_RW_BASE_ADDR,
    .write_to_ddr[49].ddr_base_address = BIAS_block17_RW_BASE_ADDR,

    //block18
    .write_to_ddr[50].filename = "block_op/task2_bin/block18/weightb18.bin",
    .write_to_ddr[51].filename = "block_op/task2_bin/block18/biasb18.bin",
    .write_to_ddr[50].ddr_base_address = WEIGHT_block18_RW_BASE_ADDR,
    .write_to_ddr[51].ddr_base_address = BIAS_block18_RW_BASE_ADDR,

    //block19
    .write_to_ddr[52].filename = "block_op/task2_bin/block19/weightb19.bin",
    .write_to_ddr[53].filename = "block_op/task2_bin/block19/biasb19.bin",
    .write_to_ddr[52].ddr_base_address = WEIGHT_block19_RW_BASE_ADDR,
    .write_to_ddr[53].ddr_base_address = BIAS_block19_RW_BASE_ADDR,

    //block20
    .write_to_ddr[54].filename = "block_op/task2_bin/block20/weightb20.bin",
    .write_to_ddr[55].filename = "block_op/task2_bin/block20/biasb20.bin",
    .write_to_ddr[54].ddr_base_address = WEIGHT_block20_RW_BASE_ADDR,
    .write_to_ddr[55].ddr_base_address = BIAS_block20_RW_BASE_ADDR,

    //block23
    .write_to_ddr[56].filename = "block_op/task2_bin/block23/weightb23.bin",
    .write_to_ddr[57].filename = "block_op/task2_bin/block23/biasb23.bin",
    .write_to_ddr[56].ddr_base_address = WEIGHT_block23_RW_BASE_ADDR,
    .write_to_ddr[57].ddr_base_address = BIAS_block23_RW_BASE_ADDR,

    //block24
    .write_to_ddr[58].filename = "block_op/task2_bin/block24/weightb24.bin",
    .write_to_ddr[59].filename = "block_op/task2_bin/block24/biasb24.bin",
    .write_to_ddr[58].ddr_base_address = WEIGHT_block24_RW_BASE_ADDR,
    .write_to_ddr[59].ddr_base_address = BIAS_block24_RW_BASE_ADDR,
};