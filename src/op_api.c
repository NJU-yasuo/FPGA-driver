#include <stdio.h>
#include "fx_hpca.h"
#include "op_api.h"
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include "op_ini_config.h"
#include "my_convo.h"

op_ini_param_t *array_task2_runtime_parameters[23] = {
	&block000_ini,
	&block001_ini,
	&block002_ini,
	&block003_ini,
	&block004_ini,
	&block005_ini,
	&block006_ini,
	&block007_ini,
	&block008_ini,
	&block009_ini,
	&block010_ini,
	&block011_ini,
	&block012_ini,
	&block013_ini,
	&block014_ini,
	&block015_ini,
	&block016_ini,
	&block017_ini,
	&block018_ini,
	&block019_ini,
	&block020_ini,
	&block023_ini,
	&block024_ini};

op_ini_param_t *array_resnet50_runtime_parameters[4] = {
	&resnet50_block00_ini,
	&resnet50_block01_ini,
	&resnet50_block02_ini,
	&resnet50_block03_ini,
};

op_ini_param_t *array_resnet18_runtime_parameters[4] = {
	&resnet18_block00_ini,
	&resnet18_block01_ini,
};

op_ini_param_t *array_mobilenet_runtime_parameters[4] = {
	&mobilenet_block00_ini,
	&mobilenet_block01_ini,
	&mobilenet_block02_ini,
};

void task2_initial_weight(int block_id)
{
	initial_weight2(&task2_weight);
	printf("Finish loading task2_parameters\n");
}

void resnet50_initial_weight(int net_type, int block_id)
{
	initial_weight_resnet50(net_type, block_id);
	printf("Finish loading resnet50_parameter\n");
}

bool call_op(op_config_t *op_config)
{
	bool rv;

#ifdef DEBUG_PRINT
	printf("******************************************************************\n");
	printf("* START %s, op_id: , sub_id: \n", __FUNCTION__);
	printf("*\n");
#endif

	rv = write_files_to_ddr(op_config);
	if (rv)
	{
		rv = launch_op(op_config);
		if (rv)
		{
			rv = read_files_from_fpga(op_config);
		}
	}

#ifdef DEBUG_PRINT
	printf("*\n");
	printf("* END %s: op_id: , sub_id: ::%s\n", __FUNCTION__, (rv == true) ? "PASSED" : "FAILED");
	printf("******************************************************************\n");
#endif
	return rv;
}
#if 0
bool call_pooling(op_config_t *op_config)
{
	bool rv;

#ifdef DEBUG_PRINT
	printf("******************************************************************\n");
	printf("* START %s, op_id: , sub_id: \n", __FUNCTION__);
	printf("*\n");
#endif

	rv = write_files_to_fpga(op_config);
	if (rv)
	{
		rv = launch_2X2_pooling(op_config);
		if (rv)
		{
			rv = read_files_from_fpga(op_config);
		}
	}

#ifdef DEBUG_PRINT
	printf("*\n");
	printf("* END %s: op_id: , sub_id: ::%s\n", __FUNCTION__, (rv == true) ? "PASSED" : "FAILED");
	printf("******************************************************************\n");
#endif

	return rv;
}
#endif

static float get_abs(float x)
{
	return (x >= 0) ? x : (-x);
}

#define GET_MIN(x, y) ((x) >= (y)) ? (y) : (x)

static int get_sign(float x)
{
	return (x >= 0) ? 1 : -1;
}

float get_min(float x, float y)
{
	return ((x) >= (y)) ? (y) : (x);
}
static void quantize1(float *x)
{
	if (*x)
	{
		float clip = (float)16 - 1.0f / 8.0f;
		float temp;
		temp = get_min(get_abs(*x), clip) * get_sign(*x) * 8 + 0.5;
		*x = floor(temp) * (1.0f / 8.0f);
	}
}
// 1,4,3 quantize
//static void quantize(float *x) {
//	if (*x) {
//		float temp = GET_MIN(get_abs(*x), 16 - 0.125) * get_sign(*x) * 8 + 0.5;
//		*x = floor(temp)*0.125;
//	}
//}

#define FRACT_BITS 3
#define FLOAT2FIXED(x) ((uint8_t)((x) * (1 << FRACT_BITS)))
#define FIXED2FLOAT(x) ((float)(x) / (1 << FRACT_BITS))

uint8_t to_fixed_point(float f)
{
	uint8_t tmp = FLOAT2FIXED(get_abs(f));

	if ((get_sign(f) == -1) && (tmp != 0))
	{
		tmp = ~tmp + 1;
	}
	//printf("%s float = %f, fixed = %x\n", __FUNCTION__, f, tmp);
	return tmp;
}

float to_float_point(uint8_t u)
{
	float tmp;
	if ((u & 0x7F) == 0)
	{
		tmp = 0.0;
	}
	else if (u & 0x80)
	{
		uint8_t ut = ~(u - 1);
		tmp = -1.0 * FIXED2FLOAT(ut);
	}
	else
	{
		tmp = FIXED2FLOAT(u);
	}
	return tmp;
}

#define FRACT_BITS5 5
#define FLOAT2FIXED5(x) ((uint8_t)((x) * (1 << FRACT_BITS5)))
#define FIXED2FLOAT5(x) ((float)(x) / (1 << FRACT_BITS5))

uint8_t to_fixed_point5(float f)
{
	uint8_t tmp = FLOAT2FIXED5(get_abs(f));

	if ((get_sign(f) == -1) && (tmp != 0))
	{
		tmp = ~tmp + 1;
	}
	return tmp;
}

float to_float_point5(uint8_t u)
{
	float tmp;
	if ((u & 0x7F) == 0)
	{
		tmp = 0.0;
	}
	else if (u & 0x80)
	{
		uint8_t ut = ~(u - 1);
		tmp = -1.0 * FIXED2FLOAT5(ut);
	}
	else
	{
		tmp = FIXED2FLOAT5(u);
	}
	return tmp;
}
#if 0
void fc_layer(uint8_t output[4][256][8][8], float matrix1[256][2], float matrix2[1][2], float result[2])
{
	float temp;
	result[0] = 0;
	result[1] = 0;
	for (int i = 0; i < 256; i++)
	{
		temp = 0;
		for (int m = 0; m < 4; m++)
		{
			for (int l = 0; l < 8; l++)
			{
				for (int k = 0; k < 8; k++)
				{
					temp += to_float_point(output[m][i][k][l]);
				}
			}
		}
		result[0] += (temp / (8 * 32)) * matrix1[i][0];
		result[1] += (temp / (8 * 32)) * matrix1[i][1];
	}
	result[0] += matrix2[0][0];
	result[1] += matrix2[0][1];
	//	quantize(&result[0]);
	//	quantize(&result[1]);
}
#endif

// for each element x, do these: convert to float (-1, 1): (x/255 - 0.5)*2.0,
// then quantize1(, 1 ,128, 1.0f/128.0f);
// convert float to fixed bye (1,4,3): bit 7: sign, bits [6:3]-> whole; bits [2:0]-> points
void in_place_image_process(uint8_t *img_trunks_ptr[])
{
	float temp;
	uint8_t *dst_img;
	for (int t = 0; t < 16; t++)
	{ // trunk 0-15
		dst_img = img_trunks_ptr[t];
		for (int i = 0; i < (32 * 8 * 3); i++)
		{ // h 32
			temp = (((float)*(dst_img) / 255.0) - 0.5) * 2.0;
			quantize1(&temp); //1,4,3
			*(dst_img++) = to_fixed_point(temp);
		}
		for (int i = 0; i < (32 * 8); i++)
		{
			*(dst_img++) = (uint8_t)0;
		}
	}
}

#include "fc_weight.h"
#include "fc_bias.h"

void post_process(uint8_t matrix[4][256][8][8], float res[2])
{
	// fc_layer(matrix, fc_weight, fc_bias, res);
}

bool task1_pre_process(char *filename, uint8_t *img_trunks_ptr[])
{
	// uint16_t rsize_h, rsize_w;
	// rsize_w = 128;
	// rsize_h = 32;
	// if (opencv_preprocess(filename, TASK_01, rsize_h, rsize_w, img_trunks_ptr) == false)
	// {
	// 	return false;
	// }

	// in_place_image_process(img_trunks_ptr);

	return true;
}

bool task2_test_block(int start_block, int end_block)
{
	// printf("DO TASK2 TEST BLOCK%d-%d\n", start_block, end_block);

	// if (start_block == 35)
	// {
	// 	task2_test_pooling();
	// 	return true;
	// }

	// if (start_block == 30)
	// {
	// 	task2_test_fc();
	// 	return true;
	// }

	for (int i = start_block; i <= end_block; i++)
	{
		// if (task2_set_op(array_task2_runtime_parameters[block_id], arr_task2_address_parameters[block_id], NULL, NULL, block_id) == false)
		int tmp = i;
		if (i >= 23)
		{
			tmp -= 2;
		}
		if (task2_set_op(array_task2_runtime_parameters[tmp], NULL, NULL, start_block, end_block) == false)
		{
			close_cnn_accelerator();
			return false;
		}
	}
	return true;
}

bool resnet50_test_block(int start_block, int end_block, int net_type)
{
	op_ini_param_t **array_net_parameters;
	if (net_type == 1)
	{
		printf("DO Resnet_50 TEST BLOCK%d-%d\n", start_block, end_block);
		array_net_parameters = array_resnet50_runtime_parameters;
		if (resnet50_set_op(array_net_parameters[start_block], NULL, NULL, start_block, end_block) == false)
		{
			close_cnn_accelerator();
			return false;
		}
	}
	else if (net_type == 2)
	{
		printf("DO Resnet_18 TEST BLOCK%d-%d\n", start_block, end_block);
		array_net_parameters = array_resnet18_runtime_parameters;
		if (resnet18_set_op(array_net_parameters[start_block], NULL, NULL, start_block, end_block) == false)
		{
			close_cnn_accelerator();
			return false;
		}
	}
	else if (net_type == 3)
	{
		printf("DO Mobilenet TEST BLOCK%d-%d\n", start_block, end_block);
		array_net_parameters = array_mobilenet_runtime_parameters;
		if (mobilenet_set_op(array_net_parameters[start_block], NULL, NULL, start_block, end_block) == false)
		{
			close_cnn_accelerator();
			return false;
		}
	}

	return true;
}

void soft_cnn_compute(int block_id)
{
	printf("Comput %d block.\n", block_id);
}
