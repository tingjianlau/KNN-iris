#define	 _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include "struct.h"

/**************************
函数原型
***************************/
double*		caculateDistance(struct SAMPLE_ST* trainSet, int trainCnt, struct SAMPLE_ST curTest, int featrueCnt);
double*		getNearestSet(int k, double* distance, int*, int trainCnt);
void		quickSort(double* A, int p, int r, int*);
int			getExtremumIndex(const int nums[], int numsSize, int mode);
int	decisionRule(int k, int* indexList, struct SAMPLE_ST* trainSet, int trainCnt, int classCnt);
/**************************
KNN分类器
***************************/
int knnClassifier(int k, struct SAMPLE_ST* trainSet, int trainCnt, struct SAMPLE_ST curTest, int classCnt, int featrueCnt) {
	int i, j, g, f;
	double*	distanceSet = NULL;
	double* nearestSet = NULL;
	int* indexList = (int*)malloc(trainCnt*sizeof(int));
	//double* tempDis = (double*)calloc(trainCnt, sizeof(double));
	double temp = 0;
	int	isClass;
	int errCnt = 0;
	// 循环每个测试样例
	//for (i = 0; i < testCnt; i++)
	//{
	for (j = 0; j < trainCnt; j++)
	{
		indexList[j] = j;
	}

	distanceSet = caculateDistance(trainSet, trainCnt, curTest, featrueCnt);
	/*for (i = 0; i < trainCnt; i++)
	{
		if (i % 5 == 0)
		{
			printf("\n");
		}
		printf("%lf ", distanceSet[i]);

	}*/
	nearestSet = getNearestSet(k, distanceSet, indexList, trainCnt);
	isClass = decisionRule(k, indexList, trainSet, trainCnt, classCnt);

	/*for ( i = 0; i < 1; i++)
	{
		printf("%d ", indexList[i]);
	}
	for ( i = 0; i < 149; i++)
	{
		printf("=%lf ", trainSet[i].fv[0]);
	}*/
	/*for ( i = 0; i < 149; i++)
	{*/
		/*for (j = 0; j < 4; j++)
		{
			temp += (trainSet[indexList[0]].fv[j] - curTest.fv[j]) * (trainSet[indexList[0]].fv[j] - curTest.fv[j]);
		}
		printf("====%lf+++++++ \n", temp);*/
	//}
	
	//if (isClass != curTest[i].iClass)
	//{
	//	//printf("%d    ", i);
	//	errCnt++;
	//}
	//}

	//printf("测试样本总数:%d, 错误个数:%d, 错误率:%lf \n", testCnt, errCnt, errCnt / (testCnt*1.0));

	free(indexList);
	free(distanceSet);
	free(nearestSet);

	return isClass;
}

/**************************
计算当前测试样例和每个训练样例之间的欧式距离

param return	返回距离矩阵
***************************/
double*	caculateDistance(struct SAMPLE_ST* trainSet, int trainCnt, struct SAMPLE_ST curTest, int featrueCnt) {
	int	i, j;
	double* dis = (double*)calloc(trainCnt, sizeof(double));

	for (i = 0; i < trainCnt; i++)
	{
		for (j = 0; j < featrueCnt; j++)
		{
			dis[i] += (trainSet[i].fv[j] - curTest.fv[j]) * (trainSet[i].fv[j] - curTest.fv[j]);
		}
	}

	return dis;
}

/**************************
选择离测试样例最近的k个训练样本的集合
***************************/
double*	getNearestSet(int k, double* distance, int* indexList, int trainCnt) {
	int	i;
	double* nearestSet = (double*)malloc(k*sizeof(double));

	quickSort(distance, 0, trainCnt - 1, indexList);
	
	/*for ( i = 0; i < trainCnt; i++)
	{
		if (i % 5 == 0)
		{
			printf("\n");
		}
		printf("%lf ", distance[i]);
		
	}*/
	/*printf("\n");
	for (i = 0; i < k; i++)
	{
		nearestSet[i] = distance[i];
		printf("***%lf**** ", nearestSet[i]);
	}
	printf("\n");*/
	return nearestSet;
}

/**************************
决策函数，采用多数表决法
***************************/
int	decisionRule(int k, int* indexList, struct SAMPLE_ST* trainSet, int trainCnt, int classCnt) {
	int* isClass = (int*)calloc(classCnt, sizeof(int)); // 用来统计各个类的个数
	int i;

	for (i = 0; i < k; i++)
	{
		//printf("%d ", trainSet[indexList[i]].iClass);
		++isClass[trainSet[indexList[i]].iClass];
	}

	//printf("\n");
	return getExtremumIndex(isClass, classCnt, 1); // 返回多数的类
}

void exchange(double* a, double* b) {
	double temp = *a;
	*a = *b;
	*b = temp;
}

void exchange2(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int	partition(double* A, int p, int r, int* indexList) {
	double	x = A[r];
	int		i = p - 1, j;

	for (j = p; j < r; j++)
	{
		if (A[j] < x)
		{
			++i;
			exchange(&A[i], &A[j]);
			exchange2(&indexList[i], &indexList[j]);
		}
	}

	exchange(&A[i + 1], &A[r]);
	exchange2(&indexList[i + 1], &indexList[r]);
	return i + 1;
}

/**************************
快排
***************************/
void quickSort(double* A, int p, int r, int* indexList) {
	int	q;
	if (p < r)
	{
		q = partition(A, p, r, indexList);
		quickSort(A, p, q - 1, indexList);
		quickSort(A, q + 1, r, indexList);
	}
}

int		getExtremumIndex(const int nums[], int numsSize, int mode) {
	int i, maxIndex, minIndex;

	maxIndex = minIndex = 0;
	for (i = 0; i<numsSize; ++i) {
		maxIndex = (nums[maxIndex]>nums[i]) ? maxIndex : i;
		minIndex = (nums[minIndex]<nums[i]) ? minIndex : i;
	}

	return (mode == 0) ? minIndex : maxIndex;
}