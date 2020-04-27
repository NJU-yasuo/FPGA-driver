/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: wuwei
 * @Date: 2020-03-05 17:58:16
 * @LastEditTime: 2020-03-05 17:58:24
 */
#include "fx_hpca.h"
#include "op_api.h"
#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>
#include "parameter_addr.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static bool get_start_end(char *argparam, int boundary[2])
{
	boundary[0] = (argparam[0] - '0') * 10 + (argparam[1] - '0');
	boundary[1] = (argparam[3] - '0') * 10 + (argparam[4] - '0');
	if (boundary[1] < boundary[0])
	{
		return false;
	}
	printf("Test Block %d-%d\n", boundary[0], boundary[1]);
	return true;
}

void task2_loop_single_pic(char *argparam)
{

	//设置图片信息空间。存放预处理的结果和op的输出
	// uint8_t resized_img[16][4][32][8];
	// float *resize_conf = calloc(19180, sizeof(float));
	// float *resize_loc = calloc(38360, sizeof(float));

	// int block_id = 2; //将要测试的Block id。
	int boundary[2] = {0, 0};

	clock_t start, finish; //计时变量
	double duration = 0;

	start = clock();
	//调用IP进行计算。
	// task2_call_ops(&resized_img[0][0][0][0], resize_loc, resize_conf);
	//读入一个block地址，对block进行测试。

	if (get_start_end(argparam, boundary))
	{
		task2_initial_weight(0);
		task2_test_block(boundary[0], boundary[1]);
	}
	else
	{
		printf("Wrong Boundary\n");
	}
	finish = clock();

	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Total time %f\n", duration);

	// free(resize_conf);
	// free(resize_loc);
}