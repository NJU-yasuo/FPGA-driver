/**
 * @file init.h
 * @author Yizhi (you@domain.com)
 * @brief Reset the IP. And do memory map to get the virtual address of the peripheral config registers
 * @version 0.1
 * @date 2019-06-27
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __FX_HPCA_INIT_H__
#define __FX_HPCA_INIT_H__
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdio.h>
#include "generate/peripheral_addr_header.h"

#define HPS_H2F_LW_BASE		(0xF9000000 + 0x00100000) // BASE + OFFSET
#define HPS_H2F_LW_SPAN		(0x00000800)
#define HPS_DDR_BASE    	(0x40000000) //512MB is smallest base addr.
#define HPS_DDR_SPAN      	(0x20000000) //the scale of mmp addr.(512MB)
#define HPS_DDR_ADDR_LIMIT     	(uint32_t) (HPS_DDR_BASE + HPS_DDR_SPAN - sysconf(_SC_PAGE_SIZE))
//#define HPS_DDR_ADDR_LIMIT     	(HPS_DDR_BASE + HPS_DDR_SPAN - 0x1000)
#define FPGA_DDR_BASE      	(0x00000000)

bool init_cnn_accelerator();

bool map_ip_to_user_space();

void* get_peripheral_virtual_addr_base();

bool close_cnn_accelerator();

bool copy_file_to_ddr(char *filename, uint32_t hps_ddr_addr, uint32_t *size);

bool copy_mem_to_ddr(void *buffer_address, uint32_t hps_ddr_addr, uint32_t hps_ddr_span);

bool read_file_from_ddr(char *filename, uint32_t hps_ddr_addr, uint32_t hps_ddr_span);

bool copy_ddr_to_mem(void *buffer_address, uint32_t hps_ddr_addr, uint32_t hps_ddr_span);

bool compare_files(char *f1, char *f2);

bool buf2file(char *file_out,void *buffer, uint32_t size);

bool bin2json(char *filename, int h, int w, int pad, uint8_t *img);

bool bin2json2(char *filename, int h, int w, int pad, uint8_t *img);

void assemble_trunks_to_whole_picture(uint8_t *whole_picture, int pad, uint8_t *img_trunks_ptr[]);

#endif
