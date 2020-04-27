#ifndef __MY_CONVO_H__
#define __MY_CONVO_H__

#include <stdio.h>
#include <stdlib.h>
#include "gemm.h"
#include <stdbool.h>
void BN_layer(float *data, char *filename, char *filename_x, int channels, int height, int width);

void relu_layer(float *out_ptr, int size);

void forward_convolutional_layer(int c, int m, int size, int stride, int pad, float *img_ptr, int w, int h, float *out_ptr, char *weights_name, char *bias_name);

void print_out_data(float *out, int Channels, int Rows, int Cols);

void test_task1();

void get_data_bin(float *data, char *filename, int size);

bool compare_files_two(float *array1, char *filename, int size);

typedef struct box
{
    float xmin;
    float ymin;
    float xmax;
    float ymax;
    float score;
} Bbox;

#endif