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

#if 1
void task1_loop_single_pic()
{
	uint8_t resized_img[16][4][32][8];
	uint8_t *img_trunks_ptr[] = {
		&resized_img[0][0][0][0], &resized_img[1][0][0][0], &resized_img[2][0][0][0], &resized_img[3][0][0][0],
		&resized_img[4][0][0][0], &resized_img[5][0][0][0], &resized_img[6][0][0][0], &resized_img[7][0][0][0],
		&resized_img[8][0][0][0], &resized_img[9][0][0][0], &resized_img[10][0][0][0], &resized_img[11][0][0][0],
		&resized_img[12][0][0][0], &resized_img[13][0][0][0], &resized_img[14][0][0][0], &resized_img[15][0][0][0]};
	uint8_t op_output[4][256][8][8];
	float fc_result[2];

	printf("Start preprocess!\n");
	if (task1_pre_process("/home/root/pictures/Neg.1.jpg", img_trunks_ptr) == false)
		return;
	printf("Start call_ops!\n");
	task1_call_ops(&resized_img[0][0][0][0], &op_output[0][0][0][0]);
	post_process(op_output, fc_result);
	printf("result:\t%08f\t%08f", fc_result[0], fc_result[1]);
}
#endif

void task1_loop_1000(int maxpics, int negpics)
{
	//task1_initial_weight();
	clock_t start, finish;
	double duration_pre = 0;
	double duration_ops = 0;
	double duration_post = 0;

	uint8_t resized_img[16][4][32][8];
	uint8_t *img_trunks_ptr[] = {
		&resized_img[0][0][0][0], &resized_img[1][0][0][0], &resized_img[2][0][0][0], &resized_img[3][0][0][0],
		&resized_img[4][0][0][0], &resized_img[5][0][0][0], &resized_img[6][0][0][0], &resized_img[7][0][0][0],
		&resized_img[8][0][0][0], &resized_img[9][0][0][0], &resized_img[10][0][0][0], &resized_img[11][0][0][0],
		&resized_img[12][0][0][0], &resized_img[13][0][0][0], &resized_img[14][0][0][0], &resized_img[15][0][0][0]};
	uint8_t op_output[4][256][8][8];

	int neg_good_cnt = 0;
	int neg_fail_cnt = 0;
	int pos_good_cnt = 0;
	int pos_fail_cnt = 0;
	//int neg_equal_cnt = 0;
	//int pos_equal_cnt = 0;

	for (int index = 1; index <= maxpics; index++)
	{
		float fc_result[2];
		char filename[50];
		if (index <= negpics)
			sprintf(filename, "/home/root/pictures/Neg.%d.jpg", index);
		else
			sprintf(filename, "/home/root/pictures/Pos.%d.jpg", index - negpics);

		printf("*Procecing                      %.02f%%finished\r", (float)(index) / (float)maxpics * 100);
		fflush(stdout);

		start = clock();
		if (task1_pre_process(filename, img_trunks_ptr) == false)
			return;
		finish = clock();
		duration_pre += (float)(finish - start) / CLOCKS_PER_SEC;

		start = clock();
		task1_call_ops(&resized_img[0][0][0][0], &op_output[0][0][0][0]);
		finish = clock();
		duration_ops += (float)(finish - start) / CLOCKS_PER_SEC;

		start = clock();
		post_process(op_output, fc_result);
		finish = clock();
		duration_post += (float)(finish - start) / CLOCKS_PER_SEC;

		if (index <= negpics)
		{
			if (fc_result[0] < fc_result[1])
				neg_good_cnt++;
			else
				neg_fail_cnt++;
		}
		else
		{
			if (fc_result[0] > fc_result[1])
				pos_good_cnt++;
			else
				pos_fail_cnt++;
		}
	}
	float totaltime;
	printf("******************************************************************\n");
	printf("*\tneg_good,  neg_fail,   acc: \t%d, \t%d, %f\n", neg_good_cnt, neg_fail_cnt, ((float)neg_good_cnt / (float)(neg_fail_cnt + neg_good_cnt)));
	printf("*\tpos_good,  pos_fail,   acc: \t%d, \t%d, %f\n", pos_good_cnt, pos_fail_cnt, ((float)pos_good_cnt / (float)(pos_fail_cnt + pos_good_cnt)));
	printf("*\tacc:%.02f%%\n", ((float)(neg_good_cnt + pos_good_cnt) * 100 / (float)(neg_fail_cnt + neg_good_cnt + pos_fail_cnt + pos_good_cnt)));
	printf("*\tTime of pre:%f   Time of ops:%f    Time of post:%f\n", duration_pre, duration_ops, duration_post);

	totaltime = duration_pre + duration_ops + duration_post;
	printf("*\tTotal time is :%f\t frame persec:%f\n", totaltime, maxpics / totaltime);
	printf("******************************************************************\n");
}
