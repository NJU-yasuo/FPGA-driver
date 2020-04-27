/**
 * @file runtime_config.h
 * @author Yizhi
 * @brief This file includes the data structures for writting the IP's config register
 * @version 0.1
 * @date 2019-06-26
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef __FX_HPCA_CONFIG_REGS_H__
#define __FX_HPCA_CONFIG_REGS_H__
#include <stdint.h>
#define __RD_ACTRAM_BIT_OFFSET 2
#define __WR_ACTRAM_BIT_OFFSET 0
typedef uint32_t actram_ctrl_info_t;
// actram_ctrl_info_t info = DDR_WR_ACTRAM_0 | DDR_RD_ACTRAM_1;
#define DDR_WR_ACTRAM_0  (0x0 << __WR_ACTRAM_BIT_OFFSET)
#define DDR_WR_ACTRAM_1  (0x1 << __WR_ACTRAM_BIT_OFFSET)
#define DDR_WR_ACTRAM_2  (0x2 << __WR_ACTRAM_BIT_OFFSET)

#define DDR_RD_ACTRAM_0  (0x0 << __RD_ACTRAM_BIT_OFFSET)
#define DDR_RD_ACTRAM_1  (0x1 << __RD_ACTRAM_BIT_OFFSET)
#define DDR_RD_ACTRAM_2  (0x2 << __RD_ACTRAM_BIT_OFFSET)


typedef uint32_t rd_ddr_starts_t;
// rd_ddr_starts_t starts = ACT_RAM_RD_START | WEI_RAM_RD_START | BNWEI_RAM_RD_START | BNBIAS_RAM_RD_START | BIAS_RAM_RD_START | COMPUTE_START_AFTER_DDR_TRANS_FINISH;
#define ACT_RAM_RD_START (0x1 << 0)
#define WEI_RAM_RD_START (0x1 << 1)
#define BNWEI_RAM_RD_START  (0x1 << 2)
#define BNBIAS_RAM_RD_START (0x1 << 3)
#define BIAS_RAM_RD_START   (0x1 << 4)
#define COMPUTE_START       (0x1 << 5)
#define COMPUTE_START_AFTER_DDR_TRANS_FINISH (0x1 << 6)
#define ACT_WRITE_BACK_AFTER_COMPUTE_DONE (0x1 << 7)

typedef uint32_t compute_misc_ctrl_t;
#define FIRST_TILE  (0x1 << 0)
#define NEED_FETCH_BN_PARAM  (0x1 << 1)
#define NEED_FETCH_BIAS_PARAM (0x1 << 2)
#define RES_BLOCK_HAS_BN  (0x1 << 3)

typedef struct{
    uint32_t num_in_chs_part0;
    uint32_t num_in_chs_part1;
    uint32_t num_out_chs_part0;
    uint32_t num_out_chs_part1;
    uint32_t kernel_sizes;
    uint32_t group_stride;
    uint32_t buffer_flow;
    uint32_t buffer_flow_res_and_banking;
    uint32_t col_ovlap_ram_start_addr;
    uint32_t quantization_info;
    uint32_t block_layer_info;
    compute_misc_ctrl_t compute_misc_ctrls;
} runtime_conf_regs_t;
#endif
