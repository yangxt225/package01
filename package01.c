#include <stdio.h>
#include <malloc.h>

/* 
动态规划之01背包:
01背包的状态转换方程: f[i,j] = Max{ f[i-1,j-Wi]+Pi(j>Wi),  f[i-1,j] }
	f[i,j]表示在前i件物品中选择若干件放在承重为 j 的背包中，可以取得的最大价值。
	Pi表示第i件物品的价值。
*/
// 背包容量
int capacity;

void package01(int (*pCostArr)[capacity], int *pItemWeightArr, int *pItemValArr, int num)
{
	int i, j;
	
	// 初始化规划表，背包并非恰好装满
	for(i=0; i<num; i++)
		for(j=0; j<capacity+1; j++)
			pCostArr[i][j] = 0;
	
	int packageWeight = 0;
	for(i=0; i<num; i++) // 5
	{
		for(j=0; j<capacity; j++) // 10
		{
			// j>Wi
			packageWeight = j+1;
			if(i==0)
			{	
				// 初始化第1行
				if(pItemWeightArr[0]<=packageWeight)
				{
					pCostArr[0][j] = pItemValArr[0];
				}
			}
			else
			{
				if(pItemWeightArr[i]<=packageWeight)
				{
					int idx = 0;
					if(pItemWeightArr[i]==packageWeight)
						idx = packageWeight;
					else
						idx = j;
					
					if(pCostArr[i-1][j] < pCostArr[i-1][idx-pItemWeightArr[i]]+pItemValArr[i])
					{
						pCostArr[i][j] = pCostArr[i-1][idx-pItemWeightArr[i]]+pItemValArr[i];
					}
					else
						pCostArr[i][j] = pCostArr[i-1][j];
				}
				else
					pCostArr[i][j] = pCostArr[i-1][j];
			}
		}
	}
	
	for(i=0; i<num; i++)
	{
		for(j=0; j<capacity; j++)
		{
			printf("%d,", pCostArr[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int num;
	printf("Please input item num:");
	scanf("%d", &num);
	
	int *pItemWeightArr = (int*)malloc((num)*sizeof(int));
	int *pItemValArr = (int*)malloc((num)*sizeof(int));
	int i;
	printf("Please input item weight and value:\n");
	pItemWeightArr[0] = pItemValArr[0] = 0;
	for(i=0; i<num; i++)
	{
		scanf("%d%d", &pItemWeightArr[i], &pItemValArr[i]);
	}
	
	printf("Please input package contain:");
	scanf("%d", &capacity);
	
	// 动态申请二维数组(num*capacity)
	int (*pCostArr)[capacity];
	pCostArr = (int(*)[capacity])malloc(num*capacity*sizeof(int));
	
	// 动态规划
	package01(pCostArr, pItemWeightArr, pItemValArr, num);
	
	printf("The package item's weight is %d, %d, %d", num, capacity, pCostArr[num-1][capacity-1]);
	
	return 0;
}

