#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>

#define MAX_NAME_LEN 100
#define SETTING_PATH "setting.bin"
#define RECORD_PATH "record.bin"

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

const char* setNickname(const char* szPath, char* szNickname) 
{
	FILE *fp = 0;
	if (!(fp = fopen(szPath, "wb")))
		return 1;
	printf("请输入你的名字:");
	scanf("%s", szNickname);
	szNickname[MAX_NAME_LEN - 1] = 0;
	fwrite(szNickname, sizeof(szNickname), 1, fp);
	fclose(fp);
	return szNickname;
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
	printf("你猜中了！你猜了%d次！\n", stRecord.nCount);
	if (0 == szNickName || 0 == strlen(szNickName)) 
	{
		printf("这是你第一次玩，");
		setNickname(SETTING_PATH, szNickName);	
	}
	strcpy(stRecord.szName, szNickName);
	return stRecord;
}

int save(struct RECORD stRecord)
{
	FILE * fp = NULL;
	if(!(fp = fopen(RECORD_PATH, "ab")))
	{
		printf("保存记录失败.. \n");
		return 1;
	}   
	fseek(fp, SEEK_END, 0); 

	fwrite(&stRecord, sizeof(struct RECORD), 1, fp);
	fclose(fp);
	return 0;
}

int view()
{
	FILE * fp = NULL;
	struct RECORD stRecord;
	struct tm stTime = {0};
	if (!(fp = fopen(RECORD_PATH, "rb")))
	{
		printf("你还没有玩过呢。 \n");
		return 1;
	}   

	printf("姓名\t所猜数字\t猜测次数\t花费秒数\t开始时间\n");

	while(!feof(fp)) 
	{
		if(fread(&stRecord, sizeof(struct RECORD), 1, fp) <= 0) 
			continue;
		localtime_s(&stTime, &stRecord.tBeginTime);

		printf("%s\t%5d   \t%5d   \t%5d   \t%d/%02d/%02d %02d:%02d:%02d\n",
			stRecord.szName,
			stRecord.nGuess,
			stRecord.nCount,
			stRecord.nCost,
			stTime.tm_year + 1900, stTime.tm_mon, stTime.tm_mday, 
			stTime.tm_hour, stTime.tm_min, stTime.tm_sec);
	}
	printf("\n\n");
	fclose(fp);
	return 0;
}


int menu(char* szNickname) {
	if (szNickname && strlen(szNickname) > 0)
		printf("你好！%s！", szNickname);
	printf("欢迎来玩『 猜数字 』!\n");
	printf("\n");
	printf("1. 开始游戏！\n");
	printf("2. 查看历史！\n");
	printf("3. 更改昵称!\n");
	printf("4. 退出游戏！\n");
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
		case '3': setNickname(SETTING_PATH, szNickname); break;
		case '4': return 0;
		default : continue;		
		}
	}
	return 0;
}

