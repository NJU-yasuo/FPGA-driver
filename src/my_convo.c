
#include "my_convo.h"

void print_out_data(float *out, int Channels, int Rows, int Cols);
void get_data_bin(float *data, char *filename, int size)
{
    FILE *fp = fopen(filename, "rb");
    size_t st __attribute__((unused)) = fread(data, sizeof(float), size, fp);
    fclose(fp);
}

bool compare_files_two(float *array1, char *filename, int size)
{
    // copy file to buffer.
    bool rv = true;
    float *array2 = calloc(size, sizeof(float));
    get_data_bin(array2, filename, size);
    int i;
    for (i = 0; i < size; ++i)
    {
        if (((array1[i] / array2[i]) < 0.95) || ((array1[i] / array2[i]) > 1.05))
        {
            printf("%s:: mismatch at %d!!!\n", __FUNCTION__, i);
            printf("C result:%f\tPython result:%f\n", array1[i], array2[i]);
            rv = false;
            break;
        }
    }
    free(array2);
    if (rv)
        printf("Success!\n");
    else
        printf("Fail!\n");

    return rv;
}

void get_data(float *data, char *filename)
{
    FILE *fp = fopen(filename, "r");
    double dbtmp;
    int x = 0;
    while (!feof(fp))
    {
        size_t st __attribute__((unused)) = fscanf(fp, "%lf", &dbtmp);
        data[x++] = dbtmp;
    }
}

void BN_layer(float *data, char *filename, char *filename_x, int channels, int height, int width)
{
    float *bn_parameter = malloc(channels * sizeof(float));
    float *bn_parameter_x = malloc(channels * sizeof(float));

    get_data_bin(bn_parameter, filename, channels);
    get_data_bin(bn_parameter_x, filename_x, channels);
    for (int index = 0; index < channels * height * width; index++)
    {
        data[index] = data[index] * bn_parameter_x[index / (height * width)] + bn_parameter[index / (height * width)];
    }
    free(bn_parameter);
    free(bn_parameter_x);
}

int convolutional_out_height(int pad, int stride, int h, int size)
{
    return ((h + pad - size) / stride + 1);
}

int convolutional_out_width(int pad, int stride, int w, int size)
{
    return ((w + pad - size) / stride + 1);
}

float im2col_get_pixel(float *im, int height, int width, int channels,
                       int row, int col, int channel, int pad)
{
    row -= pad;
    col -= pad;

    if (row < 0 || col < 0)
        return 0;
    return im[col + width * (row + height * channel)];
}

void im2col_cpu(float *data_im,
                int channels, int height, int width,
                int ksize, int stride, int pad, float *data_col)
{
    int c, h, w;
    int height_col = (height + pad - ksize) / stride + 1;
    int width_col = (width + pad - ksize) / stride + 1;

    int channels_col = channels * ksize * ksize;
    for (c = 0; c < channels_col; ++c)
    {
        int w_offset = c % ksize;
        int h_offset = (c / ksize) % ksize;
        int c_im = c / ksize / ksize;
        for (h = 0; h < height_col; ++h)
        {
            for (w = 0; w < width_col; ++w)
            {
                int im_row = h_offset + h * stride;
                int im_col = w_offset + w * stride;
                int col_index = (c * height_col + h) * width_col + w;
                data_col[col_index] = im2col_get_pixel(data_im, height, width, channels,
                                                       im_row, im_col, c_im, pad);
            }
        }
    }
}

void forward_convolutional_layer(int c, int m, int size, int stride, int pad, float *img_ptr, int w, int h, float *out_ptr, char *weights_name, char *bias_name)
{
    float *weight1 = malloc(c * m * size * size * sizeof(float)); //16*3*3*3
    float *bias1 = malloc(m * sizeof(float));                     //16

    if ((stride == 1) && (pad == 1))
        pad++;

    get_data_bin(weight1, weights_name, c * m * size * size);
    get_data_bin(bias1, bias_name, m);

    int out_h = convolutional_out_height(pad, stride, h, size);
    int out_w = convolutional_out_width(pad, stride, w, size);

    for (int i = 0; i < out_h * out_w * m; i++)
    {
        out_ptr[i] = 0;
    }

    int k = size * size * c; // 该层每个卷积核的参数元素个数
    int n = out_h * out_w;   // 该层每个特征图的尺寸（元素个数）
                             // printf("%d\n", out_h * out_w * size * size * c);

    float *workspace = calloc(out_h * out_w * size * size * c, sizeof(float));

    float *a = weight1;   // 所有卷积核（也即权重），元素个数为l.n*l.c*l.size*l.size，按行存储，共有l*n行，l.c*l.size*l.size列
    float *b = workspace; // 对输入图像进行重排之后的图像数据

    //printf("before im2col\n");
    im2col_cpu(img_ptr, c, h, w, size, stride, pad, b);

    gemm(0, 0, m, n, k, 1, a, k, b, n, 1, out_ptr, n);

    for (int i = 0; i < m * n; i++)
    {
        out_ptr[i] += bias1[i / n];
    }
    free(weight1);
    free(bias1);
    free(workspace);
}

void print_out_data(float *out, int Channels, int Rows, int Cols)
{
    for (int ch = 0; ch < Channels; ++ch)
    {
        for (int row = 0; row < Rows; ++row)
        {
            for (int col = 0; col < Cols; ++col)
            {
                printf("%6.6f ", out[ch * Rows * Cols + row * Cols + col]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void relu_layer(float *out_ptr, int size)
{
    for (int i = 0; i < size; i++)
        out_ptr[i] = out_ptr[i] < 0 ? 0 : out_ptr[i];
}
