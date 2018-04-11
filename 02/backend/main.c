#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define MAX_NAME_LEN 100
#define SETTING_PATH "setting.txt"
#define RECORD_PATH "record.txt"

struct RECORD
{
	int nRand;
	int nGuess;
	int nCount;
	time_t tBeginTime;
	int nCost;
	char szName[MAX_NAME_LEN];
};


int loadNickname(const char* szPath, char* szNickname, int nSize) 
{
	FILE *fp = 0;
	if (!(fp = fopen(szPath, "rb")))
		return 1;
	memset(szNickname, 0, nSize);
	fread(szNickname, nSize, 1, fp);
	szNickname[nSize - 1] = 0;
	fclose(fp);
	return 0;
}

int setNickname(const char* szPath) 
{
	FILE *fp = 0;
	char szNickname[MAX_NAME_LEN] = "";
	if (!(fp = fopen(szPath, "wb")))
		return 1;
	printf("Please input your Name:");
	scanf("%s", szNickname);
	szNickname[MAX_NAME_LEN - 1] = 0;
	fwrite(szNickname, sizeof(szNickname), 1, fp);
	fclose(fp);
	return 0;
}

struct RECORD guess(char* szNickName)
{
	struct RECORD stRecord = {0, 0, 0, 0, 0};
	stRecord.tBeginTime = time(NULL);
	stRecord.nRand = rand() % 1000 + 1;
	printf("请输入1~1000的数字：");
	while (stRecord.nGuess != stRecord.nRand)
	{
		while (!scanf("%d", &stRecord.nGuess))
			getchar(); // 防止用户输入非数字导致的死循环
		if (stRecord.nGuess > stRecord.nRand)
		{
			printf("大了！\n");
		}
		else if (stRecord.nGuess < stRecord.nRand)
		{
			printf("小了！\n");
		}
		stRecord.nCount++;
	}
	stRecord.nCost = time(NULL) - stRecord.tBeginTime;
	strcpy(stRecord.szName, szNickName);
	printf("你猜中了！你猜了%d次！\n", stRecord.nCount);
	if (0 == szNickName || 0 == strlen(szNickName)) 
	{
		printf("This is your first play.");
		setNickname(SETTING_PATH);
	}
	return stRecord;
}

int save(struct RECORD stRecord)
{
	FILE * fp = NULL;
	if(!(fp = fopen(RECORD_PATH, "ab")))
	{
		printf("Save Record Failed.. \n");
		return 1;
	}   
	fseek(fp, SEEK_END, 0); 

	fprintf(fp, "%d,%d,%d,%ld,%d,%s\r\n", 
		stRecord.nRand, 
		stRecord.nGuess, 
		stRecord.nCount, 
		(long)stRecord.tBeginTime, 
		stRecord.nCost, 
		stRecord.szName);
	fclose(fp);
	return 0;
}

int view()
{
	FILE * fp = NULL;
	struct RECORD stRecord;
	if (!(fp = fopen(RECORD_PATH, "rb")))
	{
		printf("You must be play first. \n");
		return 1;
	}   

	printf("Name\tGuess\tCount\tCost\tBegin\n");

	while(!feof(fp)) 
	{
		long ltime = 0;
		fscanf(fp, "%d,%d,%d,%ld,%d,%s\r\n",
			&stRecord.nRand,
			&stRecord.nGuess,
			&stRecord.nCount,
			&ltime,
			&stRecord.nCost, 
			stRecord.szName);
		stRecord.tBeginTime = (time_t)ltime;
		printf("%s\t%d\t%d\t%d\t%s",
			stRecord.szName,
			stRecord.nGuess,
			stRecord.nCount,
			stRecord.nCost,
			asctime(gmtime(&stRecord.tBeginTime)));
	}
	printf("\n\n");
	fclose(fp);
	return 0;
}


int menu(char* szNickname) {
	if (szNickname && strlen(szNickname) > 0)
		printf("Hi! %s! ", szNickname);
	printf("Welcome to play 'Guess Number'!\n");
	printf("\n");
	printf("1. Begin to Play!\n");
	printf("2. View the Record!\n");
	printf("3. Change Nickname!\n");
	printf("4. Quit the Game!\n");
	printf("\n");

	return getch();
}

int main()
{
	char szNickname[MAX_NAME_LEN] = "";
	srand((unsigned)time(NULL));
	while(1)
	{
		loadNickname(SETTING_PATH, szNickname, MAX_NAME_LEN);
		switch (menu(szNickname))
		{
		case '1': save(guess(szNickname)); break;
		case '2': view(); break;
		case '3': setNickname(SETTING_PATH); break;
		case '4': return 0;
		default : continue;		
		}
	}
	return 0;
}

