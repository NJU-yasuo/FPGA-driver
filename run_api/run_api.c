/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YKLiu
 * @Date: 2020-03-02 14:39:40
 * @LastEditTime: 2020-03-05 17:58:58
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
#include <getopt.h>

extern void task1_loop_1000(int maxpics, int negpics);
extern void task1_loop_single_pic();
// extern void task2_loop_1000(int maxpics, int negpics);
extern void restnet50_main(char *argpara, int net_type);
int task2_loop_single_pic(char *argpara);
//extern void test_convo();
static void print_usage(void)
{
	printf("-- Usage: \n");
	printf("\t./cnntest -t2 -s00-03\ttest task2 block 00-03\n");
	printf("\t./cnntest -t2 -s03-03\ttest task2 block 03\n");
	printf("\tThe param of s should be between between 00-24\n");
	printf("\tThe block should be presented as two digits, such as 00-01\n");
	printf("***************************************************************\n");
}
extern int task2_test_main();

int main(int argc, char **argv)
{
	char *task_flag = NULL;
	char *scene_flag = NULL;
	bool test_flag = false;
	int c;
	// int start_block = 2;
	// int end_block = 2;
	while ((c = getopt(argc, argv, "ct:s:")) != -1)
	{
		switch (c)
		{
		case 'c':
			test_flag = true;
			break;
		case 't':
			task_flag = optarg;
			break;
		case 's':
			scene_flag = optarg;
			break;
		case '?':
			print_usage();
			return 1;
		default:
			print_usage();
			return 1;
		}
	}
	if ((!scene_flag) || (task_flag && test_flag) || (strlen(scene_flag) != 5))
	{
		printf("%d\n", (int)strlen(scene_flag));
		print_usage();
		return 1;
	}

	if (test_flag)
		switch (scene_flag[0])
		{
		case '1':
			printf("Do test,Scene_01.\n");
			//test_convo();
			return 0;
		case '2':
			printf("Do test,Scene_02.\n");
			return 0;
		default:
			printf("test scene is 1-2");
			return 1;
		}
	if (strlen(task_flag) > 1)
	{
		print_usage();
		return 1;
	}
	if (task_flag[0] == '0')
		task2_loop_single_pic(scene_flag);
	else
		restnet50_main(scene_flag, task_flag[0] - '0');
	return 0;
}
