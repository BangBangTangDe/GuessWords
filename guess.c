#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define ERROR_TIMES 15   //错误最大数
//文件路径
#define PATH1 "words.txt"                           
#define PATH2 "record.txt"                        
#define PATH3 "user.txt"



char* randomExtract();             
void showWelcome();               
void showMain();                   
void setNumber();                  
void showSet();                   
void showSetSuccess();             
void setName();        
void showCheck();                  
void showRank();                  
void showAbout();                 
void quit();                       
void sleep(clock_t wait);       
void start();                      
void showFailure();             
void showSuccess(int correctTimes, int runTimes, double  duration);              
double score(int correctTimes, int runTimes,double usetime);  
void showTips();                  
void scoreInput(char *name, double scores, double duration);  
int compareScore();              
void showEnter();               
void showTemporarySuccess(int Number); 
void showTemporaryFailure(int Number);  


struct player                       //玩家信息
{
	char name[10];
	char password[10];
	double score;
	double time;
};
typedef struct player player;


char word[10];
int  NUMBER = 2;                          //游戏玩的回合数，玩家可设定
player allPlayer[20];                   //定义一个玩家结构体数组，储存所有玩家的信息
player playerTemp;                      //储存操作玩家的信息
char tempWord[100][20];               //定义一个字符二维数组，用于储存玩家所猜的单词，并输出到屏幕
int Number;								//记录回合数目
char used[20];							//使用过的字符数组
char ch0[1];                         //连接字符使用

//主函数

int main() {
	showWelcome();
	return 0;
}
//显示欢迎界面
void showWelcome() {
	int choice;
	while (1)
	{
		printf("\n\n\n\n");
		printf("　　　　　　　*******************************************************\n");
		printf("　　　　　　　*******************************************************\n");
		printf("　　　　　　　*******************************************************\n");
		printf("　　　　　　　************************************** ****************\n");
		printf("　　　　　　　******************   欢迎来到猜字游戏  ***************\n");
		printf("　　　　　　　******************     1.登陆        ******************\n");
		printf("　　　　　　　******************     2.注册        ******************\n");
		printf("　　　　　　　******************     0.退出        ******************\n");
		printf("　　　　　　　*******************************************************\n");
		printf("请输入:");
		scanf("%d", &choice);
		if (choice == 1) {
			if (login() == 1)
			{
				sleep((clock_t)1 * CLOCKS_PER_SEC);
				showMain();
			}
			else
			{
				system("CLS");                                                      //清屏
				printf("用户不存在或者是密码错误！\n");
				continue;
			}
		}
		else if (choice == 2)
		{
			
			int back = regist_user();
			if (back == -1)
			{
				system("CLS");                                                      //清屏
				printf("用户名存在，注册失败！\n");
				continue;
			}
			else if (back == 1)
			{
				{
					system("CLS");                                                      //清屏
					printf("注册成功！\n");
					continue;
				}
			}
		}
		else
		{
			break;
		}

	}
	

}
//登陆界面
int login()
{
	char name1[10];
	char password1[10];
	while (1)
	{

		printf("*************用户登陆**************\n");
		printf("输入用户名：");
		scanf("%s", name1);
		printf("输入密码：");
		scanf("%s", password1);
		if (query(name1, password1))
		{
			strcpy(playerTemp.name, name1);
			strcpy(playerTemp.password, password1);
			return 1;
		}
			
		else
			return 0;
	}
}
int regist_user()
{
	char name1[10];
	char password1[10];
	printf("*************注册**************\n");
	printf("输入用户名：");
	scanf("%s",name1);
	printf("输入密码：");
	scanf("%s", password1);

	if (queryusername(name1))
	{
		return -1;
	}
	FILE *p=fopen(PATH3, "a+");
	fprintf(p,"%s\t%s\n", name1, password1);
	fclose(p);
	return 1;
}
int queryusername(char name[])
{
	FILE *fp;
	char ch1[10];
	char ch2[10];
	fp = fopen(PATH3, "r");
	if (fp == 0)
	{
		printf("file error");
		exit(1);
	}
	while (fscanf(fp, "%s%s", ch1, ch2) != EOF)
	{
		if (strcmp(ch1, name) == 0)
		{
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}
//查询用户密码是否存在
int query(char name[], char password[])
{
	FILE *fp;
	char ch1[10];
	char ch2[10];
	fp = fopen(PATH3,"r");
	if (fp == 0)
	{
		printf("file error");
		exit(1);
	}
	while (fscanf(fp, "%s%s", ch1, ch2)!=EOF)
	{
		if (strcmp(ch1, name) == 0 && strcmp(ch2, password) == 0)
		{
			fclose(fp);
			return 1;
		}
	}
	fclose(fp);
	return 0;
}
//显示主菜单界面                    
void showMain() {
	char button;                                                          //储存用户输入操作数

	system("CLS");                                                           //清屏

	printf("\n\n\n\n");
	printf("　　　　　　　***********************猜字游戏************************\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　	\t\t*   1、开 始 *\n");
	printf("　　　　　　　	\t\t*   2、设 置 *\n");
	printf("　　　　　　　	\t\t*   3、查 看 *\n");
	printf("　　　　　　　	\t\t*   4、退 出 *\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　 ");

	do {
		button = getchar();                                              //用户输入操作对象
		fflush(stdin);
		if (button != '1'&&button != '2'&&button != '3'&&button != '4') {
			printf("　　　　　　　 输入出错，请重新输入！！！\n　　　　　　　 ");
		}
	} while (button != '1'&&button != '2'&&button != '3'&&button != '4');


	if (button == '1') {                                                           //根据操作数做对应操作
		start();
	}

	if (button == '2') {
		showSet();
	}
	if (button == '3') {
		showCheck();
	}

	if (button == '4') {
		quit();
	}

}
//显示设置菜单
void showSet() {
	char button;                                                               //储存用户输入操作数

	system("CLS");                                                                 //清屏

	printf("\n\n\n\n");
	printf("　　　　　　　*************************设置**************************\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*  1、修改猜单词的数目                                *\n");
	printf("　　　　　　　*  2、修改名字                                        *\n");
	printf("　　　　　　　*  3、返回                                            *\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　 ");

	do {
		button = getchar();                                              //用户输入操作对象
		fflush(stdin);
		if (button == ' ') {
			showMain();
		}
		if (button <= '0' || button >= '4') {
			printf("　　　　　　　 输入出错，请重新输入！！！\n　　　　　　　 ");
		}
	} while (button != '1'&&button != '2'&&button != '3');


	if (button == '1') {                                                           //根据操作数做对应操作
		setNumber();
	}

	if (button == '2') {
		setName();
	}
	if (button == '3') {
		showMain();
	}


}
//修改猜默认猜单词数
void setNumber() {

	system("CLS");                                                                  //清屏

	printf("\n\n\n\n");
	printf("　　　　　　　******************修改默认所猜回合数*******************\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*请修改默认所猜回合个数                               *\n");
	printf("　　　　　　　 number=");
	scanf("%d", &NUMBER);
	showSetSuccess();
}
//提示修改成功
void showSetSuccess() {
	char button;                                                                        //储存用户输入操作数

	system("CLS");

	printf("\n\n\n\n");
	printf("　　　　　　　*************************提示**************************\n");
	printf("         　　 *                                                     *\n");
	printf("         　　 *                      修改成功！                     *\n");
	printf("         　　 *                                                     *\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　*  1、返回主菜单                         2、开始游戏  *\n");
	printf("　　　　　　　 ");



	do {
		fflush(stdin);
		button = getchar();                                                     //用户输入操作对象
		fflush(stdin);
		if (button <= '0' || button >= '3') {
			printf("　　　　　　　 输入出错，请重新输入！！！\n　　　　　　　 ");
		}
	} while (button != '1'&&button != '2');


	if (button == '1') {                                                           //根据操作数做对应操作
		showMain();
	}
	if (button == '2') {
		start();
	}
}
//修改玩家姓名
void setName() {
	char newName[20];

	system("CLS");                                                                 //清屏

	printf("\n\n\n\n");
	printf("　　　　　　　***********************修改名字************************\n");
	printf("         　　 *                                                     *\n");
	printf("         　　 *   请输入名字                                        *\n");
	printf("　　　　　　　     newName:");

	scanf("%s", newName);                                                            //用户输入新名字       

	strcpy(playerTemp.name, newName);                                                           //设置新名字

	showSetSuccess();                                                                  //显示修改成功
}
//查看信息
void showCheck() {
	char button;                                                                 //储存用户输入操作数

	system("CLS");                                                                    //清屏  

	printf("\n\n\n\n");
	printf("　　　　　　　*************************查看**************************\n");
	printf("         　　 *                                                     *\n");
	printf("　　　　　　　*  1、排名                                            *\n");
	printf("　　　　　　　*  2、关于                                            *\n");
	printf("　　　　　　　*  3、返回                                            *\n");
	printf("         　　 *                                                     *\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　 ");

	do {
		button = getchar();                                                  //用户输入操作对象
		fflush(stdin);
		if (button != '1'&&button != '2'&&button != '3') {
			printf("　　　　　　　 输入出错，请重新输入！！！\n　　　　　　　 ");
		}
	} while (button != '1'&&button != '2'&&button != '3');

	if (button == '1') {                                                             //根据操作数做对应操作                                                        
		showRank();
	}

	if (button == '2') {
		showAbout();
	}

	if (button == '3') {
		showMain();
	}
}
//查看排名
void showRank() {

	int i = 0,                                                              //定义一个循环变量
		playerNumber;                                                   //用于储存玩家数量   

	playerNumber = compareScore();

	system("CLS");                                                                    //清屏

	printf("\n\n\n\n");
	printf("　　　　　　　*************************排名**************************\n");
	printf("         　　 *                                                     *\n");
	printf("         　　 *        姓名            用时            得分         *\n");
	printf("         　　 *                                                     *\n");

	if (playerNumber>3) {

		printf("         　　 * NO.1: %-10s       %-6.2lf秒         %6.2lf分     *\n", allPlayer[i].name, allPlayer[i].time, allPlayer[i].score, i++);
		printf("         　　 * NO.2: %-10s       %-6.2lf秒         %6.2lf分     *\n", allPlayer[i].name, allPlayer[i].time, allPlayer[i].score, i++);
		printf("         　　 * NO.5: %-10s       %-6.2lf秒         %6.2lf分     *\n", allPlayer[i].name, allPlayer[i].time, allPlayer[i].score);
		printf("         　　 *                                                     *\n");
		printf("　　　　　　　*******************************************************\n");
		printf("　　　　　　　 ");
		sleep((clock_t)4 * CLOCKS_PER_SEC);
		showCheck();

	}
	else {
		switch (playerNumber) {
		case 0:
			printf("         　　 *                     没有记录！                      *\n");
			printf("         　　 *                                                     *\n");
			printf("　　　　　　　*******************************************************\n");
			printf("　　　　　　　 ");
			sleep((clock_t)6 * CLOCKS_PER_SEC);
			showCheck();
			break;
		case 1:
			printf("         　　 * NO.1: %-10s       %-6.2lf秒         %-6.2lf分    *\n", allPlayer[0].name, allPlayer[0].time, allPlayer[0].score);
			printf("         　　 *                                                     *\n");
			printf("　　　　　　　*******************************************************\n");
			printf("　　　　　　　 ");
			sleep((clock_t)6 * CLOCKS_PER_SEC);
			showCheck();
			break;
		case 2:
			printf("         　　 * NO.1: %-10s       %-6.2lf秒         %-6.2lf分    *\n", allPlayer[0].name, allPlayer[0].time, allPlayer[0].score);
			printf("         　　 * NO.2: %-10s       %-6.2lf秒         %-6.2lf分    *\n", allPlayer[1].name, allPlayer[1].time, allPlayer[1].score);
			printf("         　　 *                                                     *\n");
			printf("　　　　　　　*******************************************************\n");
			printf("　　　　　　　 ");
			sleep((clock_t)6 * CLOCKS_PER_SEC);
			showCheck();
			break;
		case 3:
			printf("         　　 * NO.1: %-10s       %-6.2lf秒         %-6.2lf分    *\n", allPlayer[0].name, allPlayer[0].time, allPlayer[0].score);
			printf("         　　 * NO.2: %-10s       %-6.2lf秒         %-6.2lf分    *\n", allPlayer[1].name, allPlayer[1].time, allPlayer[1].score);
			printf("         　　 * NO.3: %-10s       %-6.2lf秒         %-6.2lf分    *\n", allPlayer[2].name, allPlayer[2].time, allPlayer[2].score);
			printf("         　　 *                                                     *\n");
			printf("　　　　　　　*******************************************************\n");
			printf("　　　　　　　 ");
			sleep((clock_t)6 * CLOCKS_PER_SEC);
			showCheck();
			break;
		case 4:
			printf("         　　 * NO.1: %-10s       %-6.2lf秒        %-6.2lf分     *\n", allPlayer[0].name, allPlayer[0].time, allPlayer[0].score);
			printf("         　　 * NO.2: %-10s       %-6.2lf秒        %-6.2lf分     *\n", allPlayer[1].name, allPlayer[1].time, allPlayer[1].score);
			printf("         　　 * NO.3: %-10s       %-6.2lf秒        %-6.2lf分     *\n", allPlayer[2].name, allPlayer[2].time, allPlayer[2].score);
			printf("         　　 * NO.4: %-10s       %-6.2lf秒        %-6.2lf分     *\n", allPlayer[3].name, allPlayer[3].time, allPlayer[3].score);
			printf("         　　 *                                                     *\n");
			printf("　　　　　　　*******************************************************\n");
			printf("　　　　　　　 ");
			sleep((clock_t)6 * CLOCKS_PER_SEC);
			showCheck();
			break;
		}
	}


}
//查看版权信息
void showAbout() {

	system("CLS");                                                                    //清屏 

	printf("\n\n\n\n");
	printf("　　　　　　　*************************关于**************************\n");
	printf("         　　 *                                                     \n");
	printf("         　　 *		           版本：1.0.0                     \n");
	printf("         　　 *                                                     \n");
	printf("         　　 *               猜单词小游戏（c语言实现)			    \n");
	printf("         　　 *                      2020.4.15                      \n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　 ");

	sleep((clock_t)3 * CLOCKS_PER_SEC);
	showCheck();


}
//退出询问
void quit() {
	char button;                                                           //储存用户输入操作数

	system("CLS");                                                        //清屏 

	printf("\n\n\n\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　******************                   ******************\n");
	printf("　　　　　　　***************      真的要退出吗？    ****************\n");
	printf("　　　　　　　******************                   ******************\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　*  1、是                                       2、否  *\n");
	printf("　　　　　　　 ");


	do {
		button = getchar();                                               //用户输入操作对象
		fflush(stdin);
		if (button != '1') {
			printf("　　　　　　　 输入出错，请重新输入！！！\n　　　　　　　 ");
		}
	} while (button <= '0' || button >= '3');

	if (button == '1') {                                                             //根据操作数做对应操作
		system("CLS");
		system("EXIT");
	}

	if (button == '2') {
		showMain();
	}
}
//成功界面函数
void showSuccess(int correctTimes, int errorTimes, double duration) {

	int i;

	system("CLS");                                                        //清屏 

	printf("\n\n\n\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*                    猜对单词 ：%s                   \n", tempWord[0]);

	for (i = 1; i<NUMBER; i++) {
		printf("　　　　　　　*                                %s                   \n", tempWord[i]);
	}
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*                         (^o^)                       *\n");
	printf("　　　　　　　*  猜了：%2d 次                                        *\n", correctTimes+errorTimes);
	printf("　　　　　　　*  用时：%5.2lf 秒              得分：%5.2lf分          *\n", duration, score(correctTimes, correctTimes+errorTimes,duration));
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　 ");

	scoreInput(playerTemp.name, score(correctTimes, correctTimes+errorTimes,duration), duration);
	sleep((clock_t)6 * CLOCKS_PER_SEC);
	showTips();
}
//失败界面函数
void showFailure() {

	int i;
	system("CLS");                                                        //清屏 

	printf("\n\n\n\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*                       游戏失败！！                  *\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*                    正确单词是：%s                   \n", tempWord[0]);

	for (i = 1; i<NUMBER; i++) {
		printf("　　　　　　　*                                %s                   \n", tempWord[i]);
	}
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*                       ~~O(_)O~~                     *\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　 ");

	sleep((clock_t)6 * CLOCKS_PER_SEC);
	showTips();

}
//随机提取单词函数
char* randomExtract() {

	char wordTemp[5000];

	FILE *fp;                                                               //定义一个文件指针，指向文件字母
	int i = 0;                                                                 //定义一个循环变量
	int randomFigure;                                                        //定义一个随机数变量           
	char ch;                                                                 //定义一个字符变量，用于读取文件字母


	srand(time(NULL));                                                        //产生随机种子 
	randomFigure = rand() % 500 + 1;                                               //产生一个随机数


	fp = fopen(PATH1, "r");                                                       //打开文件
	if (fp == 0) {
		printf("file error!\n");
		exit(1);
	}


	while ((ch = fgetc(fp)) != EOF) {                                        //读取文件
		wordTemp[i++] = ch;
	}
	wordTemp[i] = '\0';
	fclose(fp);                                                               //关闭文件
																			  //  if

	while (wordTemp[randomFigure] != ' '&&wordTemp[randomFigure] != '\n') {                               //随机从读取的文本抽取单词并获得完整的单词
		randomFigure++;
	}
	randomFigure++;
	i = 0;
	while (wordTemp[randomFigure] != ' '&&wordTemp[randomFigure] != '\n') {
		word[i] = wordTemp[randomFigure];
		i++;
		randomFigure++;
	}
	word[i] = '\0';
	return word;                                                             //返回获得的单词
}
//时间函数定义
void sleep(clock_t wait)
{
	clock_t goal;
	goal = wait + clock();
	while (goal > clock());
}
//求助提示函数
char gethelp(char a[], char b[],int len)
{

	int i=0; 
	for (i; i < len; i++)
	{
		if (a[i] == '-')
			return b[i];
	}
}
//定义了一个游戏过程中单词判断函数
void start() {
	int help = 1;//提示机会次数
	char *ps;
	int length,
		i, k = 0,                                                            //循环变量i,k
		runTimes = 1,                                                       //猜次循环次数  
		flag, flag1 = 0,                                                       //标志变量

		correctTimes = 0,
		number,                                                         //控制回合数
		tempErrorTimes = 0,
		tempCorrectTimes;

	char ch1[15];
	char ch;
	clock_t start, finish;
	double  duration;

	showEnter();
	system("CLS");                                                      //清屏 

	start = clock();

	number = NUMBER;                                                      //初始化要进行的回合数

	Number = 0;
	int pos = 0;  //判断标志

	while (number>0) {

		memset(used, 0, sizeof(char)*20);
		tempErrorTimes = 0;
		tempCorrectTimes = 0;

		ps = randomExtract();
		/*ps = "abcdcba";*/
		length = strlen(ps);                                           //计算随机抽取的单词的长度

		strcpy(tempWord[Number], ps);

		printf("\n\n\n\n");
		printf("　　　　　　　*******************************************************\n");
		printf("              *                     第 %1d 回合                       *\n", NUMBER - number + 1);
		printf("              *                      ");
		for (i = 0; i<length; i++)
		{
			ch1[i] = '-';
			printf("-");
		}
		printf("\n");
		printf("              *请输入一个字母进行猜测!                              *\n");        //玩家输入一个字母进行游戏
		printf("　　　　　　　 ");
		while (tempErrorTimes<ERROR_TIMES)
		{
			flag = 0;
			rewind(stdin);
			scanf("%c",&ch);
			
			for (i = 0; i<length; i++)
			{
				if ((*(ps + i) == ch) && (ch != ch1[i]))
				{
					ch1[i] = *(ps + i);
					
					tempCorrectTimes++;
					
					if (!pos)
					{
						correctTimes++;
						k++;
					}
					pos = 1;
				}
			}
			pos = 0;
			if (k == 0)
			{
				tempErrorTimes++;
				printf("              *玩家输入错误!,请再次输入一个字母，你还有 %d 次出错机会\n               ", ERROR_TIMES - tempErrorTimes);	//提示玩家输入信息错误	
				ch0[0] = ch;
				strcat(used, ch0);
				printf("              错误字母========%s\n", used);
				printf("              ");
				if (help > 0)
				{
					
					printf("              需要提示机会吗？y/n  \n");
					printf("              ");
					char ch0;
					rewind(stdin);
					scanf("%c", &ch0);
					
					if (ch0 == 'y')
					{
						help--;
						printf("              单词中字母%c还未识别，请输入，同时提示机会用完！\n", gethelp(ch1, ps, length));
						printf("              ");
						runTimes++;
					
					}
					else
					{
						printf("              ");
						runTimes++;
					
					}

				}
			}
			else
			{
				printf("\n              错误字母========%s\n\n", used);
				printf("　　　　　　　 ");
				for (i = 0; i<length; i++)
				{
					printf("%c", ch1[i]);
				}
				printf("\n");
				printf("　　　　　　　 ");
				k--;
			}
			if (tempCorrectTimes == length)
			{
				flag = 1;
				flag1++;
				if (Number<NUMBER - 1) {
					showTemporarySuccess(Number);
					Number++;
				}
				break;
			}
			runTimes++;
		}
		if (Number<NUMBER - 1) {
			showTemporaryFailure(Number);
		}
		Number++;
		system("CLS");
		number--;
	}
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	if (flag == 1 && flag1 == NUMBER)
	{
		showSuccess(correctTimes, tempErrorTimes , duration);                     //打开成功界面函数
	}
	else {

		showFailure();                                                   //打开失败界面

	}
}
//计算得分函数声明
double score(int correctTimes, int runTimes,double usetime) {

	double scores;

	scores = (double)(correctTimes*1.0/ runTimes * 100+100-usetime);   //得分计算规则

	return scores;
}
//提示信息函数
void showTips() {
	char button;                                                                        //储存用户输入操作数

	system("CLS");                                                                         //清屏

	printf("\n\n\n\n");
	printf("　　　　　　　*************************提示**************************\n");
	printf("         　　 *                                                     *\n");
	printf("         　　 *                      再来一局？！                   *\n");
	printf("          　　*                                                     *\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　*  1、是                                        2、否 *\n");
	printf("　　　　　　　 ");

	do {
		fflush(stdin);
		button = getchar();                                                                 //用户输入操作对象
		if (button == '\n') {
			showTips();
		}
		fflush(stdin);
		if (button != '1') {
			printf("　　　　　　　 输入出错，请重新输入！！！\n　　　　　　　 ");
		}
	} while (button <= '0' || button >= '3');

	if (button == '1') {                                                                        //根据操作数做对应操作
		start();
	}

	if (button == '2') {
		showMain();
	}
}
//分数记录保存文件
void scoreInput(char *name, double scores, double duration)
{
	FILE *fp;

	strcpy(playerTemp.name, name);
	playerTemp.score = scores;
	playerTemp.time = duration;
	fp = fopen(PATH2, "a+");
	if (fp == 0)
	{
		printf("file error");
		exit(1);
	}
	fprintf(fp, "%s %.2lf %.2lf\n", playerTemp.name, playerTemp.time, playerTemp.score);
	fclose(fp);
}
//比较玩家分数函数
int compareScore()
{
	int i, j,                                                                
	playerNumber = 0;                                                                                  
	double temp1, temp2;
	char temp3[20];

	FILE *fp;
	fp = fopen(PATH2, "r");
	if (fp == 0)
	{
		printf("file error");
		exit(1);
	}



	while (fscanf(fp, "%s%lf%lf", playerTemp.name, &playerTemp.time, &playerTemp.score)!=EOF)
	{
		strcpy(allPlayer[playerNumber].name, playerTemp.name);
		allPlayer[playerNumber].score = playerTemp.score;
		allPlayer[playerNumber].time = playerTemp.time;
		playerNumber++;
	}


	if (playerNumber == 0 || playerNumber == 1) {

		return playerNumber;
	}                                                                        
	else {
		//排序
		for (i = 0; i<playerNumber; i++)
			for (j = playerNumber - 1; j>i; j--)
			{
				if (allPlayer[j].score>allPlayer[j - 1].score)
				{
					temp1 = allPlayer[j - 1].score;
					allPlayer[j - 1].score = allPlayer[j].score;
					allPlayer[j].score = temp1;

					strcpy(temp3, allPlayer[j - 1].name);
					strcpy(allPlayer[j - 1].name, allPlayer[j].name);
					strcpy(allPlayer[j].name, temp3);

					temp2 = allPlayer[j - 1].time;
					allPlayer[j - 1].time = allPlayer[j].time;
					allPlayer[j].time = temp2;
				}
			}
		return playerNumber;

	}
	fclose(fp);
}
//显示进入游戏函数
void showEnter() {
	int i = 3, j = 1, k = 1, n;                                              //定义一个循环变量，用于计算闪屏次数
	int randomFigure;                                               //定义了一个随机变量

	for (; i>0; i--) {

		srand(time(NULL));
		randomFigure = rand() % 3 + 1;

		system("CLS");
		printf("\n\n\n\n");
		printf("　　　　　　　*************************进入游戏**********************\n");
		printf("         　　 *                                                     *\n");
		printf("         　　 *                                                     *\n");
		switch (randomFigure) {
		case 1:                                                                          //随机输出提示
			printf("              *    提示：游戏只有一次提示机会！！               *\n");
			break;
		case 2:
			printf("              *    提示：游戏分几个回合，猜对所有单词才算成功！！   *\n");
			break;
		case 3:
			printf("              *    提示：猜单词最多猜错15次，否则失败！！           *\n");
			break;
		}
		printf("         　　 *                                                     *\n");
		printf("         　　 *                                                     *\n");
		printf("         　　    正在加载游戏，请稍后…………\n\n");

		switch (j) {
		case 1:
			printf("         　　 ");
			break;
		case 2:
			printf("         　　 >>>>>>>>>>>>>>>>>>");
			break;
		case 3:
			printf("         　　 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
			break;
		}

		for (n = 0; n<6; n++) {
			printf(">>>");
			sleep((clock_t)1*0.1 * CLOCKS_PER_SEC);
		}

		j++;
	}
}
//回合成功界面显示函数
void showTemporarySuccess(int Number) {
	system("CLS");                                                        //清屏 

	printf("\n\n\n\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*                    猜对单词 ：%s                   \n", tempWord[Number]);
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*                    正在进入下一回合...              *\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　");
	sleep((clock_t)6 * CLOCKS_PER_SEC);

}
//回合失败界面显示函数
void showTemporaryFailure(int Number) {
	system("CLS");                                                        //清屏 

	printf("\n\n\n\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*          猜错了，正确的是 ：%s                        \n", tempWord[Number]);
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*          不要灰心，还有下一回合，正在进入...        *\n");
	printf("　　　　　　　*                                                     *\n");
	printf("　　　　　　　*******************************************************\n");
	printf("　　　　　　　");
	sleep((clock_t)6 * CLOCKS_PER_SEC);

}


