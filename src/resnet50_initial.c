#include "op_ini_config.h"
op_ini_param_t resnet50_block00_ini = {
    //从图中看出
    .net_type = 1,
    .block_id = 0,
    .row = 4,
    .col = 32,
    .blockstride = 2,
    .frac_out = 4,
    .frac_in = 11,
    .p_in = {1, 1, 1, 1},  //group
    .p_out = {2, 1, 1, 1}, // stride
    .in_channels = {4, 4095, 4095, 4095},
    .out_channels = {64, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .v_layer = 1,
    .BNLayer = 1,         //0001
    .ReLULayer = 1,       //0001
    .ColOvlapOffset = 4,  // k=3 layer, InChannels/Group = 4/1
    .RowOvlapOffset = 32, // k=3 layer, OutChannels/Stride = 64/2
    //待定
    .pre_bn = 0,

    .wei_base_addr = 0x40000000,
    .bias_base_addr = 0x40100000,
    .bn_wei_base_addr = 0x40200000,
    .bn_bias_base_addr = 0x40300000,
    .act_ram_rd_base_addr = 0x40400000,
    .act_ram_write_base_addr = 0x40800000,
    // .num_valid_weights = 276, //weight number
    .num_valid_weights = 616, //weight number
    .Last_block_stride = 0};

op_ini_param_t resnet50_block01_ini = {
    //从图中看出
    .net_type = 1,
    .block_id = 1,
    .col = 32,
    .row = 4,
    .blockstride = 2,
    .frac_out = 4,
    .frac_in = 11,
    .in_channels = {4, 4095, 4095, 4095},
    .out_channels = {64, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .v_layer = 1,
    .BNLayer = 1,         //0001
    .ReLULayer = 1,       //0001
    .ColOvlapOffset = 4,  // k=3 layer, InChannels/Group = 4/1
    .RowOvlapOffset = 32, // k=3 layer, OutChannels/Stride = 64/2
    //待定
    .pre_bn = 0,

    .wei_base_addr = 0x40000000,
    .bias_base_addr = 0x40100000,
    .bn_wei_base_addr = 0x40200000,
    .bn_bias_base_addr = 0x40300000,
    .act_ram_rd_base_addr = 0x40400000,
    .act_ram_write_base_addr = 0x40800000,
    // .num_valid_weights = 276, //weight number
    .num_valid_weights = 44768, //weight number
    .Last_block_stride = 0};

op_ini_param_t resnet50_block02_ini = {
    //从图中看出
    .net_type = 1,
    .block_id = 2,
    .row = 1,
    .col = 8,
    .in_channels = {256, 64, 64, 4095},
    .out_channels = {64, 64, 256, 4095},
    .kernel_sizes = {1, 3, 1, 255},
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,
    .p_in = {1, 1, 1, 1},  //group
    .p_out = {1, 1, 1, 1}, // stride
    .v_layer = 3,

    .BNLayer = 0b0011,    //0111
    .ReLULayer = 0b0111,  //1101
    .ColOvlapOffset = 64, // k=3 layer, InChannels/Group = 4/1
    .RowOvlapOffset = 64, // k=3 layer, OutChannels/Stride = 64/2
    .pre_bn = 1,

    .wei_base_addr = 0x40000000,
    .bias_base_addr = 0x40100000,
    .bn_wei_base_addr = 0x40200000,
    .bn_bias_base_addr = 0x40300000,
    .act_ram_rd_base_addr = 0x40400000,
    .act_ram_write_base_addr = 0x40800000,
    // .num_valid_weights = 276, //weight number
    .num_valid_weights = 40784, //weight number
    .Last_block_stride = 0};

op_ini_param_t resnet50_block03_ini = {
    //从图中看出
    .net_type = 1,
    .block_id = 3,
    .row = 1,
    .col = 8,
    .in_channels = {256, 256, 128, 128},
    .out_channels = {128, 512, 128, 512},
    .kernel_sizes = {1, 1, 3, 1},
    .p_in = {1, 1, 1, 2},  //group
    .p_out = {1, 2, 2, 1}, // stride
    .blockstride = 2,
    .v_layer = 4,

    .BNLayer = 0b0111,     //1111
    .ReLULayer = 0b1101,   //1101
    .ColOvlapOffset = 128, // k=3 layer, InChannels/Group =
    .RowOvlapOffset = 64,  // k=3 layer, OutChannels/Stride = 64/2

    .frac_out = 4,
    .frac_in = 11,
    //待定
    .pre_bn = 1,

    .wei_base_addr = 0x40000000,
    .bias_base_addr = 0x40100000,
    .bn_wei_base_addr = 0x40200000,
    .bn_bias_base_addr = 0x40300000,
    .act_ram_rd_base_addr = 0x40400000,
    .act_ram_write_base_addr = 0x40800000,
    // .num_valid_weights = 276, //weight number
    .num_valid_weights = 269800, //weight number
    .Last_block_stride = 0};

op_ini_param_t resnet18_block00_ini = {
    //从图中看出
    .net_type = 2,
    .block_id = 0,
    .row = 1,
    .col = 8,
    .in_channels = {64, 64, 4095, 4095},
    .out_channels = {64, 64, 4095, 4095},
    .kernel_sizes = {3, 3, 255, 255},
    .p_in = {1, 1, 1, 15},  //group
    .p_out = {1, 1, 1, 15}, // stride
    .blockstride = 1,
    .v_layer = 2,

    .BNLayer = 0b0001,    //1111
    .ReLULayer = 0b0011,  //1101
    .ColOvlapOffset = 64, // k=3 layer, InChannels/Group =
    .RowOvlapOffset = 64, // k=3 layer, OutChannels/Stride = 64/2

    .frac_out = 4,
    .frac_in = 11,
    //待定
    .pre_bn = 1,

    .wei_base_addr = 0x40000000,
    .bias_base_addr = 0x40100000,
    .bn_wei_base_addr = 0x40200000,
    .bn_bias_base_addr = 0x40300000,
    .act_ram_rd_base_addr = 0x40400000,
    .act_ram_write_base_addr = 0x40800000,
    // .num_valid_weights = 276, //weight number
    .num_valid_weights = 15735, //weight number
    .Last_block_stride = 0};

op_ini_param_t resnet18_block01_ini = {

    //从图中看出
    .net_type = 2,
    .block_id = 1,
    .row = 1,
    .col = 8,
    .in_channels = {64, 64, 128, 4095},
    .out_channels = {128, 128, 128, 4095},
    .kernel_sizes = {3, 1, 3, 255},
    .p_in = {1, 1, 2, 0xf},  //group
    .p_out = {2, 2, 1, 0xf}, // stride
    .blockstride = 2,
    .v_layer = 3,

    .BNLayer = 0b0011,    //1111
    .ReLULayer = 0b0101,  //1101
    .ColOvlapOffset = 64, // k=3 layer, InChannels/Group =
    .RowOvlapOffset = 16, // k=3 layer, OutChannels/Stride = 64/2

    .frac_out = 4,
    .frac_in = 11,
    //待定
    .pre_bn = 1,

    .wei_base_addr = 0x40000000,
    .bias_base_addr = 0x40100000,
    .bn_wei_base_addr = 0x40200000,
    .bn_bias_base_addr = 0x40300000,
    .act_ram_rd_base_addr = 0x40400000,
    .act_ram_write_base_addr = 0x40800000,
    // .num_valid_weights = 276, //weight number
    .num_valid_weights = 61508, //weight number
    .Last_block_stride = 0};

op_ini_param_t mobilenet_block00_ini = {
    //从图中看出
    .net_type = 3,
    .block_id = 0,
    .row = 2,
    .col = 16,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,
    .p_in = {1, 1, 1, 1},  //group
    .p_out = {1, 1, 1, 1}, // stride
    .in_channels = {32, 4095, 4095, 4095},
    .out_channels = {32, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .v_layer = 1,
    .BNLayer = 1,         //0001
    .ReLULayer = 1,       //0001
    .ColOvlapOffset = 32, // k=3 layer, InChannels/Group = 4/1
    .RowOvlapOffset = 32, // k=3 layer, OutChannels/Stride = 64/2
    //待定
    .pre_bn = 0,

    .wei_base_addr = 0x40000000,
    .bias_base_addr = 0x40100000,
    .bn_wei_base_addr = 0x40200000,
    .bn_bias_base_addr = 0x40300000,
    .act_ram_rd_base_addr = 0x40400000,
    .act_ram_write_base_addr = 0x40800000,
    // .num_valid_weights = 276, //weight number
    .num_valid_weights = 94, //weight number
    .Last_block_stride = 0};

op_ini_param_t mobilenet_block01_ini = {
    //从图中看出
    .net_type = 3,
    .block_id = 1,
    .row = 2,
    .col = 16,
    .blockstride = 2,
    .frac_out = 4,
    .frac_in = 11,
    .p_in = {1, 1, 1, 1},  //group
    .p_out = {2, 1, 1, 1}, // stride
    .in_channels = {64, 4095, 4095, 4095},
    .out_channels = {64, 4095, 4095, 4095},
    .kernel_sizes = {3, 255, 255, 255},
    .v_layer = 1,
    .BNLayer = 1,         //0001
    .ReLULayer = 1,       //0001
    .ColOvlapOffset = 64, // k=3 layer, InChannels/Group = 4/1
    .RowOvlapOffset = 32, // k=3 layer, OutChannels/Stride = 64/2
    //待定
    .pre_bn = 0,

    .wei_base_addr = 0x40000000,
    .bias_base_addr = 0x40100000,
    .bn_wei_base_addr = 0x40200000,
    .bn_bias_base_addr = 0x40300000,
    .act_ram_rd_base_addr = 0x40400000,
    .act_ram_write_base_addr = 0x40800000,
    // .num_valid_weights = 276, //weight number
    .num_valid_weights = 368, //weight number
    .Last_block_stride = 0};

op_ini_param_t mobilenet_block02_ini = {

    //从图中看出
    .net_type = 3,
    .block_id = 2,
    .row = 1,
    .col = 1,
    .blockstride = 1,
    .frac_out = 4,
    .frac_in = 11,
    .p_in = {1, 1, 1, 1},  //group
    .p_out = {1, 1, 1, 1}, // stride
    .in_channels = {24, 144, 144, 4095},
    .out_channels = {144, 144, 24, 4095},
    .kernel_sizes = {1, 3, 1, 255},
    .v_layer = 3,
    .BNLayer = 0b011,      //0001
    .ReLULayer = 0b011,    //0001
    .ColOvlapOffset = 144, // k=3 layer, InChannels/Group = 4/1
    .RowOvlapOffset = 144, // k=3 layer, OutChannels/Stride = 64/2
    //待定
    .pre_bn = 1,

    .wei_base_addr = 0x40000000,
    .bias_base_addr = 0x40100000,
    .bn_wei_base_addr = 0x40200000,
    .bn_bias_base_addr = 0x40300000,
    .act_ram_rd_base_addr = 0x40400000,
    .act_ram_write_base_addr = 0x40800000,
    // .num_valid_weights = 276, //weight number
    .num_valid_weights = 7352, //weight number
    .Last_block_stride = 0};
