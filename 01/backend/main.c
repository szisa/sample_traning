#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int nRand = 0, nGuess = 0, nCount = 0;
	srand((unsigned)time(NULL));
	nRand = rand() % 1000 + 1;
	printf("请输入1~1000的数字：");
	while (nGuess != nRand)
	{
		while (!scanf("%d", &nGuess))
			getchar(); // 防止用户输入非数字导致的死循环
		if (nGuess > nRand)
		{
			printf("大了！\n");
		}
		else if (nGuess < nRand)
		{
			printf("小了！\n");
		}
		nCount++;
	}
	printf("你猜中了！你猜了%d次！\n", nCount);
	return 0;
}