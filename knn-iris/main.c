#define	 _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "struct.h"
#include <string.h>
/**************************
全局变量
***************************/
struct SAMPLE_ST* trainSet;
//struct SAMPLE_ST* testSet;

/**************************
函数原型
***************************/
void	loadData(const char*, int);


int main() {
	int	i, j, k, label, errCnt = 0;
	struct SAMPLE_ST curTest;
	struct SAMPLE_ST* tempSet = (struct SAMPLE_ST*)calloc(TRAIN_CNT - 1, sizeof(struct SAMPLE_ST));
	trainSet = (struct SAMPLE_ST*)calloc(TRAIN_CNT, sizeof(struct SAMPLE_ST));
	//testSet = (struct SAMPLE_ST*)calloc(TEST_CNT, sizeof(struct SAMPLE_ST));

	// 加载训练和测试样本数据
	loadData(TRAIN_PATH, TRAIN_CNT);

	for ( i = 0; i < TRAIN_CNT; i++)
	{
		curTest = trainSet[i];
		// 去掉当前样例后，剩余的样例充当训练集合
		for ( j = 0, k=0; j < TRAIN_CNT; j++)
		{
			if (j!=i)
			{
				tempSet[k++] = trainSet[j];
				
			}
		}
		label = knnClassifier(K, tempSet, TRAIN_CNT - 1, curTest, CLASS_CNT, FEATURE_CNT);
		//printf("\n");
		if (label != curTest.iClass)
		{
			printf("error%d    ", i);
			errCnt++;
		}
	}
	printf("\n测试样本总数:%d, 错误个数:%d, 错误率:%lf \n", TEST_CNT, errCnt, errCnt / (TEST_CNT*1.0));

	free(trainSet);
	return 0;
}

/**************************
加载训练和测试样本
param trainSrc	训练样本文件路径
param trainCnt	训练样本个数
param testSrc	测试样本文件路径
param testCnt	测试样本文件路径
***************************/
void	loadData(const char* trainSrc, int trainCnt) {
	int	i, j;
	char	className[20];
	FILE	*fpTrain = NULL;

	if ((fpTrain = fopen(trainSrc, "r")) == NULL)
	{
		printf("open file \"%s failed! \n", trainSrc);
		exit(0);
	}

	// 加载训练样本
	for (i = 0; i < trainCnt; i++)
	{
		for (j = 0; j < FEATURE_CNT; j++)
		{
			fscanf(fpTrain, "%lf,", &trainSet[i].fv[j]);
		}
		fscanf(fpTrain, "%s", &className);
		if (strcmp(className, "Iris-setosa") == 0)
		{
			trainSet[i].iClass = 0;
		}
		else if (strcmp(className, "Iris-versicolor") == 0)
		{
			trainSet[i].iClass = 1;
		}
		else if (strcmp(className, "Iris-virginica") == 0)
		{
			trainSet[i].iClass = 2;
		}
	}

	fclose(fpTrain);
}