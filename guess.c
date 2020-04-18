#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define ERROR_TIMES 15   //���������
//�ļ�·��
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


struct player                       //�����Ϣ
{
	char name[10];
	char password[10];
	double score;
	double time;
};
typedef struct player player;


char word[10];
int  NUMBER = 2;                          //��Ϸ��Ļغ�������ҿ��趨
player allPlayer[20];                   //����һ����ҽṹ�����飬����������ҵ���Ϣ
player playerTemp;                      //���������ҵ���Ϣ
char tempWord[100][20];               //����һ���ַ���ά���飬���ڴ���������µĵ��ʣ����������Ļ
int Number;								//��¼�غ���Ŀ
char used[20];							//ʹ�ù����ַ�����
char ch0[1];                         //�����ַ�ʹ��

//������

int main() {
	showWelcome();
	return 0;
}
//��ʾ��ӭ����
void showWelcome() {
	int choice;
	while (1)
	{
		printf("\n\n\n\n");
		printf("��������������*******************************************************\n");
		printf("��������������*******************************************************\n");
		printf("��������������*******************************************************\n");
		printf("��������������************************************** ****************\n");
		printf("��������������******************   ��ӭ����������Ϸ  ***************\n");
		printf("��������������******************     1.��½        ******************\n");
		printf("��������������******************     2.ע��        ******************\n");
		printf("��������������******************     0.�˳�        ******************\n");
		printf("��������������*******************************************************\n");
		printf("������:");
		scanf("%d", &choice);
		if (choice == 1) {
			if (login() == 1)
			{
				sleep((clock_t)1 * CLOCKS_PER_SEC);
				showMain();
			}
			else
			{
				system("CLS");                                                      //����
				printf("�û������ڻ������������\n");
				continue;
			}
		}
		else if (choice == 2)
		{
			
			int back = regist_user();
			if (back == -1)
			{
				system("CLS");                                                      //����
				printf("�û������ڣ�ע��ʧ�ܣ�\n");
				continue;
			}
			else if (back == 1)
			{
				{
					system("CLS");                                                      //����
					printf("ע��ɹ���\n");
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
//��½����
int login()
{
	char name1[10];
	char password1[10];
	while (1)
	{

		printf("*************�û���½**************\n");
		printf("�����û�����");
		scanf("%s", name1);
		printf("�������룺");
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
	printf("*************ע��**************\n");
	printf("�����û�����");
	scanf("%s",name1);
	printf("�������룺");
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
//��ѯ�û������Ƿ����
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
//��ʾ���˵�����                    
void showMain() {
	char button;                                                          //�����û����������

	system("CLS");                                                           //����

	printf("\n\n\n\n");
	printf("��������������***********************������Ϸ************************\n");
	printf("��������������*                                                     *\n");
	printf("��������������	\t\t*   1���� ʼ *\n");
	printf("��������������	\t\t*   2���� �� *\n");
	printf("��������������	\t\t*   3���� �� *\n");
	printf("��������������	\t\t*   4���� �� *\n");
	printf("��������������*                                                     *\n");
	printf("��������������*******************************************************\n");
	printf("�������������� ");

	do {
		button = getchar();                                              //�û������������
		fflush(stdin);
		if (button != '1'&&button != '2'&&button != '3'&&button != '4') {
			printf("�������������� ����������������룡����\n�������������� ");
		}
	} while (button != '1'&&button != '2'&&button != '3'&&button != '4');


	if (button == '1') {                                                           //���ݲ���������Ӧ����
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
//��ʾ���ò˵�
void showSet() {
	char button;                                                               //�����û����������

	system("CLS");                                                                 //����

	printf("\n\n\n\n");
	printf("��������������*************************����**************************\n");
	printf("��������������*                                                     *\n");
	printf("��������������*                                                     *\n");
	printf("��������������*  1���޸Ĳµ��ʵ���Ŀ                                *\n");
	printf("��������������*  2���޸�����                                        *\n");
	printf("��������������*  3������                                            *\n");
	printf("��������������*                                                     *\n");
	printf("��������������*******************************************************\n");
	printf("�������������� ");

	do {
		button = getchar();                                              //�û������������
		fflush(stdin);
		if (button == ' ') {
			showMain();
		}
		if (button <= '0' || button >= '4') {
			printf("�������������� ����������������룡����\n�������������� ");
		}
	} while (button != '1'&&button != '2'&&button != '3');


	if (button == '1') {                                                           //���ݲ���������Ӧ����
		setNumber();
	}

	if (button == '2') {
		setName();
	}
	if (button == '3') {
		showMain();
	}


}
//�޸Ĳ�Ĭ�ϲµ�����
void setNumber() {

	system("CLS");                                                                  //����

	printf("\n\n\n\n");
	printf("��������������******************�޸�Ĭ�����»غ���*******************\n");
	printf("��������������*                                                     *\n");
	printf("��������������*���޸�Ĭ�����»غϸ���                               *\n");
	printf("�������������� number=");
	scanf("%d", &NUMBER);
	showSetSuccess();
}
//��ʾ�޸ĳɹ�
void showSetSuccess() {
	char button;                                                                        //�����û����������

	system("CLS");

	printf("\n\n\n\n");
	printf("��������������*************************��ʾ**************************\n");
	printf("         ���� *                                                     *\n");
	printf("         ���� *                      �޸ĳɹ���                     *\n");
	printf("         ���� *                                                     *\n");
	printf("��������������*******************************************************\n");
	printf("��������������*  1���������˵�                         2����ʼ��Ϸ  *\n");
	printf("�������������� ");



	do {
		fflush(stdin);
		button = getchar();                                                     //�û������������
		fflush(stdin);
		if (button <= '0' || button >= '3') {
			printf("�������������� ����������������룡����\n�������������� ");
		}
	} while (button != '1'&&button != '2');


	if (button == '1') {                                                           //���ݲ���������Ӧ����
		showMain();
	}
	if (button == '2') {
		start();
	}
}
//�޸��������
void setName() {
	char newName[20];

	system("CLS");                                                                 //����

	printf("\n\n\n\n");
	printf("��������������***********************�޸�����************************\n");
	printf("         ���� *                                                     *\n");
	printf("         ���� *   ����������                                        *\n");
	printf("��������������     newName:");

	scanf("%s", newName);                                                            //�û�����������       

	strcpy(playerTemp.name, newName);                                                           //����������

	showSetSuccess();                                                                  //��ʾ�޸ĳɹ�
}
//�鿴��Ϣ
void showCheck() {
	char button;                                                                 //�����û����������

	system("CLS");                                                                    //����  

	printf("\n\n\n\n");
	printf("��������������*************************�鿴**************************\n");
	printf("         ���� *                                                     *\n");
	printf("��������������*  1������                                            *\n");
	printf("��������������*  2������                                            *\n");
	printf("��������������*  3������                                            *\n");
	printf("         ���� *                                                     *\n");
	printf("��������������*******************************************************\n");
	printf("�������������� ");

	do {
		button = getchar();                                                  //�û������������
		fflush(stdin);
		if (button != '1'&&button != '2'&&button != '3') {
			printf("�������������� ����������������룡����\n�������������� ");
		}
	} while (button != '1'&&button != '2'&&button != '3');

	if (button == '1') {                                                             //���ݲ���������Ӧ����                                                        
		showRank();
	}

	if (button == '2') {
		showAbout();
	}

	if (button == '3') {
		showMain();
	}
}
//�鿴����
void showRank() {

	int i = 0,                                                              //����һ��ѭ������
		playerNumber;                                                   //���ڴ����������   

	playerNumber = compareScore();

	system("CLS");                                                                    //����

	printf("\n\n\n\n");
	printf("��������������*************************����**************************\n");
	printf("         ���� *                                                     *\n");
	printf("         ���� *        ����            ��ʱ            �÷�         *\n");
	printf("         ���� *                                                     *\n");

	if (playerNumber>3) {

		printf("         ���� * NO.1: %-10s       %-6.2lf��         %6.2lf��     *\n", allPlayer[i].name, allPlayer[i].time, allPlayer[i].score, i++);
		printf("         ���� * NO.2: %-10s       %-6.2lf��         %6.2lf��     *\n", allPlayer[i].name, allPlayer[i].time, allPlayer[i].score, i++);
		printf("         ���� * NO.5: %-10s       %-6.2lf��         %6.2lf��     *\n", allPlayer[i].name, allPlayer[i].time, allPlayer[i].score);
		printf("         ���� *                                                     *\n");
		printf("��������������*******************************************************\n");
		printf("�������������� ");
		sleep((clock_t)4 * CLOCKS_PER_SEC);
		showCheck();

	}
	else {
		switch (playerNumber) {
		case 0:
			printf("         ���� *                     û�м�¼��                      *\n");
			printf("         ���� *                                                     *\n");
			printf("��������������*******************************************************\n");
			printf("�������������� ");
			sleep((clock_t)6 * CLOCKS_PER_SEC);
			showCheck();
			break;
		case 1:
			printf("         ���� * NO.1: %-10s       %-6.2lf��         %-6.2lf��    *\n", allPlayer[0].name, allPlayer[0].time, allPlayer[0].score);
			printf("         ���� *                                                     *\n");
			printf("��������������*******************************************************\n");
			printf("�������������� ");
			sleep((clock_t)6 * CLOCKS_PER_SEC);
			showCheck();
			break;
		case 2:
			printf("         ���� * NO.1: %-10s       %-6.2lf��         %-6.2lf��    *\n", allPlayer[0].name, allPlayer[0].time, allPlayer[0].score);
			printf("         ���� * NO.2: %-10s       %-6.2lf��         %-6.2lf��    *\n", allPlayer[1].name, allPlayer[1].time, allPlayer[1].score);
			printf("         ���� *                                                     *\n");
			printf("��������������*******************************************************\n");
			printf("�������������� ");
			sleep((clock_t)6 * CLOCKS_PER_SEC);
			showCheck();
			break;
		case 3:
			printf("         ���� * NO.1: %-10s       %-6.2lf��         %-6.2lf��    *\n", allPlayer[0].name, allPlayer[0].time, allPlayer[0].score);
			printf("         ���� * NO.2: %-10s       %-6.2lf��         %-6.2lf��    *\n", allPlayer[1].name, allPlayer[1].time, allPlayer[1].score);
			printf("         ���� * NO.3: %-10s       %-6.2lf��         %-6.2lf��    *\n", allPlayer[2].name, allPlayer[2].time, allPlayer[2].score);
			printf("         ���� *                                                     *\n");
			printf("��������������*******************************************************\n");
			printf("�������������� ");
			sleep((clock_t)6 * CLOCKS_PER_SEC);
			showCheck();
			break;
		case 4:
			printf("         ���� * NO.1: %-10s       %-6.2lf��        %-6.2lf��     *\n", allPlayer[0].name, allPlayer[0].time, allPlayer[0].score);
			printf("         ���� * NO.2: %-10s       %-6.2lf��        %-6.2lf��     *\n", allPlayer[1].name, allPlayer[1].time, allPlayer[1].score);
			printf("         ���� * NO.3: %-10s       %-6.2lf��        %-6.2lf��     *\n", allPlayer[2].name, allPlayer[2].time, allPlayer[2].score);
			printf("         ���� * NO.4: %-10s       %-6.2lf��        %-6.2lf��     *\n", allPlayer[3].name, allPlayer[3].time, allPlayer[3].score);
			printf("         ���� *                                                     *\n");
			printf("��������������*******************************************************\n");
			printf("�������������� ");
			sleep((clock_t)6 * CLOCKS_PER_SEC);
			showCheck();
			break;
		}
	}


}
//�鿴��Ȩ��Ϣ
void showAbout() {

	system("CLS");                                                                    //���� 

	printf("\n\n\n\n");
	printf("��������������*************************����**************************\n");
	printf("         ���� *                                                     \n");
	printf("         ���� *		           �汾��1.0.0                     \n");
	printf("         ���� *                                                     \n");
	printf("         ���� *               �µ���С��Ϸ��c����ʵ��)			    \n");
	printf("         ���� *                      2020.4.15                      \n");
	printf("��������������*******************************************************\n");
	printf("�������������� ");

	sleep((clock_t)3 * CLOCKS_PER_SEC);
	showCheck();


}
//�˳�ѯ��
void quit() {
	char button;                                                           //�����û����������

	system("CLS");                                                        //���� 

	printf("\n\n\n\n");
	printf("��������������*******************************************************\n");
	printf("��������������*******************************************************\n");
	printf("��������������*******************************************************\n");
	printf("��������������******************                   ******************\n");
	printf("��������������***************      ���Ҫ�˳���    ****************\n");
	printf("��������������******************                   ******************\n");
	printf("��������������*******************************************************\n");
	printf("��������������*******************************************************\n");
	printf("��������������*******************************************************\n");
	printf("��������������*  1����                                       2����  *\n");
	printf("�������������� ");


	do {
		button = getchar();                                               //�û������������
		fflush(stdin);
		if (button != '1') {
			printf("�������������� ����������������룡����\n�������������� ");
		}
	} while (button <= '0' || button >= '3');

	if (button == '1') {                                                             //���ݲ���������Ӧ����
		system("CLS");
		system("EXIT");
	}

	if (button == '2') {
		showMain();
	}
}
//�ɹ����溯��
void showSuccess(int correctTimes, int errorTimes, double duration) {

	int i;

	system("CLS");                                                        //���� 

	printf("\n\n\n\n");
	printf("��������������*******************************************************\n");
	printf("��������������*                                                     *\n");
	printf("��������������*                    �¶Ե��� ��%s                   \n", tempWord[0]);

	for (i = 1; i<NUMBER; i++) {
		printf("��������������*                                %s                   \n", tempWord[i]);
	}
	printf("��������������*                                                     *\n");
	printf("��������������*                         (^o^)                       *\n");
	printf("��������������*  ���ˣ�%2d ��                                        *\n", correctTimes+errorTimes);
	printf("��������������*  ��ʱ��%5.2lf ��              �÷֣�%5.2lf��          *\n", duration, score(correctTimes, correctTimes+errorTimes,duration));
	printf("��������������*                                                     *\n");
	printf("��������������*******************************************************\n");
	printf("�������������� ");

	scoreInput(playerTemp.name, score(correctTimes, correctTimes+errorTimes,duration), duration);
	sleep((clock_t)6 * CLOCKS_PER_SEC);
	showTips();
}
//ʧ�ܽ��溯��
void showFailure() {

	int i;
	system("CLS");                                                        //���� 

	printf("\n\n\n\n");
	printf("��������������*******************************************************\n");
	printf("��������������*                                                     *\n");
	printf("��������������*                       ��Ϸʧ�ܣ���                  *\n");
	printf("��������������*                                                     *\n");
	printf("��������������*                    ��ȷ�����ǣ�%s                   \n", tempWord[0]);

	for (i = 1; i<NUMBER; i++) {
		printf("��������������*                                %s                   \n", tempWord[i]);
	}
	printf("��������������*                                                     *\n");
	printf("��������������*                       ~~O(_)O~~                     *\n");
	printf("��������������*                                                     *\n");
	printf("��������������*                                                     *\n");
	printf("��������������*******************************************************\n");
	printf("�������������� ");

	sleep((clock_t)6 * CLOCKS_PER_SEC);
	showTips();

}
//�����ȡ���ʺ���
char* randomExtract() {

	char wordTemp[5000];

	FILE *fp;                                                               //����һ���ļ�ָ�룬ָ���ļ���ĸ
	int i = 0;                                                                 //����һ��ѭ������
	int randomFigure;                                                        //����һ�����������           
	char ch;                                                                 //����һ���ַ����������ڶ�ȡ�ļ���ĸ


	srand(time(NULL));                                                        //����������� 
	randomFigure = rand() % 500 + 1;                                               //����һ�������


	fp = fopen(PATH1, "r");                                                       //���ļ�
	if (fp == 0) {
		printf("file error!\n");
		exit(1);
	}


	while ((ch = fgetc(fp)) != EOF) {                                        //��ȡ�ļ�
		wordTemp[i++] = ch;
	}
	wordTemp[i] = '\0';
	fclose(fp);                                                               //�ر��ļ�
																			  //  if

	while (wordTemp[randomFigure] != ' '&&wordTemp[randomFigure] != '\n') {                               //����Ӷ�ȡ���ı���ȡ���ʲ���������ĵ���
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
	return word;                                                             //���ػ�õĵ���
}
//ʱ�亯������
void sleep(clock_t wait)
{
	clock_t goal;
	goal = wait + clock();
	while (goal > clock());
}
//������ʾ����
char gethelp(char a[], char b[],int len)
{

	int i=0; 
	for (i; i < len; i++)
	{
		if (a[i] == '-')
			return b[i];
	}
}
//������һ����Ϸ�����е����жϺ���
void start() {
	int help = 1;//��ʾ�������
	char *ps;
	int length,
		i, k = 0,                                                            //ѭ������i,k
		runTimes = 1,                                                       //�´�ѭ������  
		flag, flag1 = 0,                                                       //��־����

		correctTimes = 0,
		number,                                                         //���ƻغ���
		tempErrorTimes = 0,
		tempCorrectTimes;

	char ch1[15];
	char ch;
	clock_t start, finish;
	double  duration;

	showEnter();
	system("CLS");                                                      //���� 

	start = clock();

	number = NUMBER;                                                      //��ʼ��Ҫ���еĻغ���

	Number = 0;
	int pos = 0;  //�жϱ�־

	while (number>0) {

		memset(used, 0, sizeof(char)*20);
		tempErrorTimes = 0;
		tempCorrectTimes = 0;

		ps = randomExtract();
		/*ps = "abcdcba";*/
		length = strlen(ps);                                           //���������ȡ�ĵ��ʵĳ���

		strcpy(tempWord[Number], ps);

		printf("\n\n\n\n");
		printf("��������������*******************************************************\n");
		printf("              *                     �� %1d �غ�                       *\n", NUMBER - number + 1);
		printf("              *                      ");
		for (i = 0; i<length; i++)
		{
			ch1[i] = '-';
			printf("-");
		}
		printf("\n");
		printf("              *������һ����ĸ���в²�!                              *\n");        //�������һ����ĸ������Ϸ
		printf("�������������� ");
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
				printf("              *����������!,���ٴ�����һ����ĸ���㻹�� %d �γ������\n               ", ERROR_TIMES - tempErrorTimes);	//��ʾ���������Ϣ����	
				ch0[0] = ch;
				strcat(used, ch0);
				printf("              ������ĸ========%s\n", used);
				printf("              ");
				if (help > 0)
				{
					
					printf("              ��Ҫ��ʾ������y/n  \n");
					printf("              ");
					char ch0;
					rewind(stdin);
					scanf("%c", &ch0);
					
					if (ch0 == 'y')
					{
						help--;
						printf("              ��������ĸ%c��δʶ�������룬ͬʱ��ʾ�������꣡\n", gethelp(ch1, ps, length));
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
				printf("\n              ������ĸ========%s\n\n", used);
				printf("�������������� ");
				for (i = 0; i<length; i++)
				{
					printf("%c", ch1[i]);
				}
				printf("\n");
				printf("�������������� ");
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
		showSuccess(correctTimes, tempErrorTimes , duration);                     //�򿪳ɹ����溯��
	}
	else {

		showFailure();                                                   //��ʧ�ܽ���

	}
}
//����÷ֺ�������
double score(int correctTimes, int runTimes,double usetime) {

	double scores;

	scores = (double)(correctTimes*1.0/ runTimes * 100+100-usetime);   //�÷ּ������

	return scores;
}
//��ʾ��Ϣ����
void showTips() {
	char button;                                                                        //�����û����������

	system("CLS");                                                                         //����

	printf("\n\n\n\n");
	printf("��������������*************************��ʾ**************************\n");
	printf("         ���� *                                                     *\n");
	printf("         ���� *                      ����һ�֣���                   *\n");
	printf("          ����*                                                     *\n");
	printf("��������������*******************************************************\n");
	printf("��������������*  1����                                        2���� *\n");
	printf("�������������� ");

	do {
		fflush(stdin);
		button = getchar();                                                                 //�û������������
		if (button == '\n') {
			showTips();
		}
		fflush(stdin);
		if (button != '1') {
			printf("�������������� ����������������룡����\n�������������� ");
		}
	} while (button <= '0' || button >= '3');

	if (button == '1') {                                                                        //���ݲ���������Ӧ����
		start();
	}

	if (button == '2') {
		showMain();
	}
}
//������¼�����ļ�
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
//�Ƚ���ҷ�������
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
		//����
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
//��ʾ������Ϸ����
void showEnter() {
	int i = 3, j = 1, k = 1, n;                                              //����һ��ѭ�����������ڼ�����������
	int randomFigure;                                               //������һ���������

	for (; i>0; i--) {

		srand(time(NULL));
		randomFigure = rand() % 3 + 1;

		system("CLS");
		printf("\n\n\n\n");
		printf("��������������*************************������Ϸ**********************\n");
		printf("         ���� *                                                     *\n");
		printf("         ���� *                                                     *\n");
		switch (randomFigure) {
		case 1:                                                                          //��������ʾ
			printf("              *    ��ʾ����Ϸֻ��һ����ʾ���ᣡ��               *\n");
			break;
		case 2:
			printf("              *    ��ʾ����Ϸ�ּ����غϣ��¶����е��ʲ���ɹ�����   *\n");
			break;
		case 3:
			printf("              *    ��ʾ���µ������´�15�Σ�����ʧ�ܣ���           *\n");
			break;
		}
		printf("         ���� *                                                     *\n");
		printf("         ���� *                                                     *\n");
		printf("         ����    ���ڼ�����Ϸ�����Ժ󡭡�����\n\n");

		switch (j) {
		case 1:
			printf("         ���� ");
			break;
		case 2:
			printf("         ���� >>>>>>>>>>>>>>>>>>");
			break;
		case 3:
			printf("         ���� >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
			break;
		}

		for (n = 0; n<6; n++) {
			printf(">>>");
			sleep((clock_t)1*0.1 * CLOCKS_PER_SEC);
		}

		j++;
	}
}
//�غϳɹ�������ʾ����
void showTemporarySuccess(int Number) {
	system("CLS");                                                        //���� 

	printf("\n\n\n\n");
	printf("��������������*******************************************************\n");
	printf("��������������*                                                     *\n");
	printf("��������������*                    �¶Ե��� ��%s                   \n", tempWord[Number]);
	printf("��������������*                                                     *\n");
	printf("��������������*                    ���ڽ�����һ�غ�...              *\n");
	printf("��������������*                                                     *\n");
	printf("��������������*******************************************************\n");
	printf("��������������");
	sleep((clock_t)6 * CLOCKS_PER_SEC);

}
//�غ�ʧ�ܽ�����ʾ����
void showTemporaryFailure(int Number) {
	system("CLS");                                                        //���� 

	printf("\n\n\n\n");
	printf("��������������*******************************************************\n");
	printf("��������������*                                                     *\n");
	printf("��������������*          �´��ˣ���ȷ���� ��%s                        \n", tempWord[Number]);
	printf("��������������*                                                     *\n");
	printf("��������������*          ��Ҫ���ģ�������һ�غϣ����ڽ���...        *\n");
	printf("��������������*                                                     *\n");
	printf("��������������*******************************************************\n");
	printf("��������������");
	sleep((clock_t)6 * CLOCKS_PER_SEC);

}


