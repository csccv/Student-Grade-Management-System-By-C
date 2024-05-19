/*************************************
*******程序名称：学生成绩管理系统 
*******作    者：
*******开发环境：Dev-C++5.11 
*******创建日期：2022.06.28
*******完成日期：2022.07.02 
**************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
 
#define YES 1
#define NO 0
 
typedef struct
{
	int num;
	float prob_score;
	float disc_score;
	float cpp_score;
	double aver_score;
	double sum_score;
	char sex;
}StudentDate;                                            //学生基本信息
typedef struct student
{
	char name[20];                                       //学生姓名
	StudentDate one;                                     //学生其他信息
	int rank;                                            //成绩排名
	struct student *next;
}Student, *List;
 
Student *startCheck();                                   //登录系统
Student *createListHead();                               //创建链表的头
void menu();                                             //主菜单
void sortList(Student *pHead);                           //排序链表
void readListWithFile(Student *pHead, char *file_name);  //从文件中读取数据，并保存在链表中
int  userChioce(Student *pHead);                         //用户选择
int  sortMenu();                                         //打印选择菜单
void passwordCheck();                                    //密码检测
void correctWord();                                      //修改密码
void addStudentInfo(Student *pHead);                     //向链表的末尾添加数据
int  scanMenu();                                         //浏览菜单
void findStudentInfo(Student *pHead);                    //查找学生信息
void delStudentInfo(Student *pHead);                     //删除某一个学生信息
void alterStudentInfo(Student *pHead);                   //修改学生信息
void saveList(Student *pHead);                           //将链表保存在文件里
void printList(Student *pHead);                          //打印链表
void statisStudentInfo(Student *pHead);                  //查看学生信息
int  statisMenu();                                       //查看菜单
void gotoxy(int x, int y);                               //改变光标位置函数
void inputData(Student *pHead, Student *node);           //输入信息，并检测是否合法
 
int main()
{
	Student *pHead;
 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//得到窗口句柄
	SMALL_RECT rc = { 0, 0, 94 - 1, 30 - 1 };   //{Y位置,X位置,宽,高}
	SetConsoleWindowInfo(hOut, true, &rc);// 重置窗口位置和大小
 
	system("color F1");//设置控制台颜色
	pHead = startCheck();//读取信息
	while (1)
	{
		if (9 == userChioce(pHead)) //按9时退出系统
		{
			break;
		}
	}
 
	return 0;
}
/*================================================
== 函数名：Student *startCheck()
== 功  能：登陆系统 
== 参  数：无 
== 返回值：链表的头指针 
=================================================*/
Student *startCheck()
{
	Student *pHead;
	FILE  *fp1;
	char password[20] = "77137714";
	int i;
 
	if ((fp1 = fopen("password.dat", "rb")) == NULL)//若密码文件不存在，新建密码文件
	{
		fp1 = fopen("password.dat", "wb");
		fwrite(password, 20, 1, fp1);
		fclose(fp1);
		printf("密码初始化完成！（默认密码为：77137714）");
		passwordCheck();
	}
	else
	{
		passwordCheck();
	}
	//读条
	system("CLS");
	system("title 学生成绩统计系统-载入中");//将标题栏命名为“学生成绩统计系统”
	printf("\n\n\t\t\t欢迎进入本系统！正在载入.....");
	printf("\n\n\n\n\t\t\t┏━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t\t┃                    ┃\n");
	printf("\t\t\t┗━━━━━━━━━━━━━━━━━━━━┛\n");
	gotoxy(26, 7);
	for (i = 0; i < 10; i++)
	{
		printf("█");
		Sleep(100);
	}
 
	pHead = createListHead();
	readListWithFile(pHead, "stud.dat");
 
	return pHead;
}
/*================================================
== 函数名：Student *createListHead()
== 功  能：创建一个单链表 
== 参  数：无 
== 返回值：返回链表的头指针 
=================================================*/
Student *createListHead()
{
	Student *pHead;
 
	pHead = (List)malloc(sizeof(Student));
	pHead->next = NULL;
 
	return pHead;
}
/*================================================
== 函数名：void passwordCheck()
== 功  能：密码输入及判定 
== 参  数：无 
== 返回值：无 
=================================================*/
void passwordCheck()
{
	char password[20], inputword[20];
	int i = 0, j = 0;
	char c = 0;
	FILE *fp = fopen("password.dat", "rb");
 
	system("title 学生成绩统计系统-密码输入");//将标题栏命名为“学生成绩统计系统”
	fread(password, 20, 1, fp);
	for (i = 0; i < 3; i++)
	{
		j = 0;
		printf("\n\n\n\t\t你还有%d次机会输入正确密码: ", 3 - i);
		printf("\n\n\n\n\t\t\t┏━━━━━━━━━━━━━━━━┓\n");
		printf("\t\t\t┃                ┃\n");
		printf("\t\t\t┗━━━━━━━━━━━━━━━━┛\n");
		gotoxy(26, 8);
		while ((c = getch()) != 13 && j < 20)
		{
			if (c == '\b' && j >0)
			{
				putchar('\b');
				putchar(' ');
				putchar('\b');
				j--;
			}
			else
			{
				if (isprint(c))//isprint为检测C是否为可打印的函数 
				{
					putchar('*');
					inputword[j] = c;
					j++;
				}
			}
		}
		inputword[j] = '\0';
		if (strcmp(inputword, password) == 0)
		{
			return;
		}
		else
		{
			system("CLS");
			printf("\t\t\t密码输入错误");
		}
	}
	if (3 == i)
	{
		system("CLS");
		printf("\n\n\n\t\t你已浪费所有机会！程序即将退出！");
		Sleep(2000);
		exit(0);
	}
	fclose(fp);
	system("CLS");
 
	return;
}
/*================================================
== 函数名：void readListWithFile(Student *pHead, char *file_name)
== 功  能：将文件内的信息读取到链表中 
== 参  数：Student *pHead：链表头指针 
           char *file_name：文件指针 
== 返回值：无 
=================================================*/
void readListWithFile(Student *pHead, char *file_name)
{
	FILE *fp;
	Student *p1, *p2;
	int count, rank = 0;
	StudentDate dat;
	char stu_name[20];
 
	fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		fp = fopen(file_name, "w");
		fclose(fp);
		return;
	}
	fseek(fp, 0L, 2);
	count = ftell(fp);
	p1 = pHead;
	fp = fopen(file_name, "r");
	while (!feof(fp))
	{
		p2 = (List)malloc(sizeof(Student));
		fscanf(fp, "%d %s %c %f %f %f\n", &p2->one.num, p2->name, &p2->one.sex, &p2->one.prob_score,
			&p2->one.disc_score, &p2->one.cpp_score);
		p2->one.sum_score = (double)(p2->one.prob_score + p2->one.disc_score + p2->one.cpp_score);
		p2->one.aver_score = p2->one.sum_score / 3;
		p2->next = NULL;
		p1->next = p2;
		p1 = p2;
		if (ftell(fp) == count)
		{
			break;
		}
	}
	//将链表排序，并初始化排名
	for (p1 = pHead->next; p1 != NULL; p1 = p1->next)
	{
		for (p2 = p1->next; p2 != NULL; p2 = p2->next)
		{
			if (p2->one.aver_score > p1->one.aver_score)
			{
				dat = p2->one;
				strcpy(stu_name, p2->name);
				p2->one = p1->one;
				strcpy(p2->name, p1->name);
				p1->one = dat;
				strcpy(p1->name, stu_name);
			}
		}
		p1->rank = ++rank;
	}
	fclose(fp);
}
/*================================================
== 函数名：int userChioce(Student *pHead)
== 功  能：用户功能选择 
== 参  数：链表头指针 
== 返回值：功能对应整型数 
=================================================*/
int userChioce(Student *pHead)
{
	int bum;
 
	system("title 学生成绩统计系统-主菜单");//将标题栏命名为“学生成绩统计系统”
	menu();
	printf("请按键选择: ");
	bum = (int)(getch() - '0');
	switch (bum)
	{
	case 1:
		addStudentInfo(pHead);
		break;
	case 2:
		delStudentInfo(pHead);
		break;
	case 3:
		alterStudentInfo(pHead);
		break;
	case 4:
		findStudentInfo(pHead);
		break;
	case 5:
		statisStudentInfo(pHead);
		break;
	case 9:
		break;
	case 6:
		sortList(pHead);
		break;
	case 7:
		correctWord();
		break;
	case 8:
		MessageBox(NULL, TEXT("名称：学生成绩管理系统\n学校：安徽中医药大学\n作者：21大数据2 wyx"), TEXT("关于"), MB_OK);
		break;
	default:
		break;
	}
 
	return bum;
}
/*================================================
== 函数名：void addStudentInfo(Student *pHead)
== 功  能：向链表末尾添加数据 
== 参  数：链表头指针 
== 返回值：无 
=================================================*/
void addStudentInfo(Student *pHead)
{
	FILE *fp;
	Student *p1, *p2, *p3 = pHead;
	StudentDate dat;
	int judge = YES, rank = 0;
	char bum, stu_name[20];
 
	system("title 学生成绩统计系统-添加");//将标题栏命名为“学生成绩统计系统”
	fp = fopen("stud.dat", "a");
	while (pHead->next)
	{
		pHead = pHead->next;
	}
	while (judge)
	{
		p1 = (List)malloc(sizeof(Student));
		inputData(p3, p1);
		p1->next = NULL;
		pHead->next = p1;
		pHead = p1;
		fprintf(fp, "%d %s %c %.1f %.1f %.1f\n", p1->one.num, p1->name, p1->one.sex, p1->one.prob_score,
			p1->one.disc_score, p1->one.cpp_score);
		printf("是否继续添加？(Y/N)");
		bum = getch();
		if (bum == 'n' || bum == 'N')
		{
			break;
		}
 
	}
	//并交换排名
	for (p1 = p3->next; p1 != NULL; p1 = p1->next)
	{
		for (p2 = p1->next; p2 != NULL; p2 = p2->next)
		{
			if (p2->one.aver_score > p1->one.aver_score)
			{
				dat = p2->one;
				strcpy(stu_name, p2->name);
				p2->one = p1->one;
				strcpy(p2->name, p1->name);
				p1->one = dat;
				strcpy(p1->name, stu_name);
			}
		}
		p1->rank = ++rank;
	}
	fclose(fp);
}
/*================================================
== 函数名：void inputData(Student *pHead, Student *node)
== 功  能：输入信息并检测是否合法 
== 参  数：Student *pHead：链表头指针 
           Student *node：链表工作指针 
== 返回值：无 
=================================================*/
void inputData(Student *pHead, Student *node)
{
	Student *p1 = node, *p2, *p3 = pHead;
 
	system("CLS");
	printf("\n\n\t请依次输入学生的学号、姓名、性别、概率、离散、c++成绩\n");
	printf("\t注意:姓名不能有空格，性别男用M表示，女用W表示，\n\t各科成绩应该大于0小于100，输入数据时请用空格隔开\n");
	scanf("%d %s %c %f %f %f", &p1->one.num, p1->name, &p1->one.sex, &p1->one.prob_score, &p1->one.disc_score, &p1->one.cpp_score);
	// 判断输入的学号是否已经存在
	p2 = p3->next;
	while (1)
	{
		if (p2 == NULL)
		{
			break;
		}
		if (p2->one.num == p1->one.num && p2 != node)
		{
			printf("该学号已存在，请重新输入学号:");
			scanf("%d", &p1->one.num);
			p2 = p3->next;
		}
		else
		{
			p2 = p2->next;
		}
	}
	//性别是否合法
	while (1)
	{
		if (p1->one.sex != 'W'&& p1->one.sex != 'M')
		{
			p1->one.sex = getchar();
			printf("性别输入不合法，请重新输入: ");
			p1->one.sex = getchar();
 
		}
		else
		{
			break;
		}
	}
	//成绩是否合法
	while (1)
	{
		if (p1->one.prob_score < 0 || p1->one.prob_score > 100)
		{
			printf("概率成绩输入不合法，请重新输入:");
			scanf("%f", &p1->one.prob_score);
		}
		if (p1->one.disc_score < 0 || p1->one.disc_score > 100)
		{
			printf("离散成绩输入不合法，请重新输入:");
			scanf("%f", &p1->one.disc_score);
		}
		if (p1->one.cpp_score < 0 || p1->one.cpp_score > 100)
		{
			printf("c++成绩输入不合法，请重新输入:");
			scanf("%f", &p1->one.cpp_score);
		}
		if (p1->one.prob_score >= 0 && p1->one.prob_score <= 100 && p1->one.disc_score >= 0
			&& p1->one.disc_score <= 100 && p1->one.cpp_score >= 0 && p1->one.cpp_score <= 100)
		{
			break;
		} 
	}
	p1->one.sum_score = (double)(p1->one.prob_score + p1->one.disc_score + p1->one.cpp_score);
	p1->one.aver_score = p1->one.sum_score / 3;
}
/*================================================
== 函数名：void alterStudentInfo(Student *pHead)
== 功  能：修改学生信息 
== 参  数：链表头指针 
== 返回值：无 
=================================================*/
void alterStudentInfo(Student *pHead)
{
	int bum, count = 0, j = 0;
	int num;
	char student_name[20];
	Student *p1 = pHead->next;
 
	system("title 学生成绩统计系统-修改");//将标题栏命名为“学生成绩统计系统”
	bum = scanMenu();
	if (bum == 1)
	{
		printf("\n\t\t\t请输入要修改学生的学号：");
		scanf("%d", &num);
		while (p1)
		{
			j++;
			if (p1->one.num == num)
			{
				inputData(pHead, p1);
				break;
			}
			p1 = p1->next;
		}
		if (p1 == NULL)
		{
			getch();
			printf("没有该学生信息！");
		}
	}
	else
	{
		if (bum == 2)
		{
			printf("\n\t\t\t请输入要修改学生的姓名：");
			scanf("%s", student_name);
			while (p1)
			{
				j++;
				if (strcmp(p1->name, student_name) == 0)
				{
					inputData(pHead, p1);
					count = 1;
				}
				p1 = p1->next;
			}
			if (count == 0)
			{
				printf("\n\t\t\t没有该学生信息！");
				getch();
			}
		}
		else
		{
			if (3 == bum)
			{
				return;
			}
			else
			{
				alterStudentInfo(pHead);
			}
		}
	}
	saveList(pHead);
}
/*================================================
== 函数名：int scanMenu()
== 功  能：查询菜单显示和选择 
== 参  数：无 
== 返回值：功能对应整型数 
=================================================*/
int scanMenu()
{
	int bum;
 
	system("CLS");
	printf("\n\n\n");
	printf("\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t┃                       以什么方式查询 ？                  ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    1   按学生的学号                      ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    2   按学生的姓名                      ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    3   返回主菜单                        ┃\n");
	printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("请按键选择：");
	bum = (int)(getch() - '0');
	system("CLS");
 
	return bum;
}
/*================================================
== 函数名：void saveList(Student *pHead)
== 功  能：将链表保存在文件 
== 参  数：链表头指针 
== 返回值：无 
=================================================*/
void saveList(Student *pHead)
{
	FILE *fp;
 
	fp = fopen("stud.dat", "w+");
	pHead = pHead->next;
	while (pHead)
	{
		fprintf(fp, "%d %s %c %.1f %.1f %.1f\n", pHead->one.num, pHead->name, pHead->one.sex, pHead->one.prob_score,
			pHead->one.disc_score, pHead->one.cpp_score);
		pHead = pHead->next;
	}
	fclose(fp);
}
/*================================================
== 函数名：void correctWord()
== 功  能：修改密码 
== 参  数：无 
== 返回值：无 
=================================================*/
void correctWord()
{
	char password[20];
	FILE *fp;
	int i = 0;
	char c;
 
	system("title 学生成绩统计系统-修改密码");//将标题栏命名为“学生成绩统计系统”
	system("CLS");
	printf("\n\n\n\n\t\t\t请输入新的密码：");
 
	while ((c = getch()) != 13 && i < 20)
	{
		if (c == '\b'&&i > 0)
		{
			putchar('\b');
			putchar(' ');
			putchar('\b');
			i--;
		}
		else
		{
			if (isprint(c))//isprint为检测C是否为可打印的函数 
			{
				putchar('*');
				password[i] = c;
				i++;
			}
		}
	}
	password[i] = '\0';
	printf("\n\t\t\t是否将密码修改为<%s>? Y or N:", password);
	c = getch();
	if (c == 'Y' || c == 'y')
	{
		fp = fopen("password.dat", "wb");
		fwrite(password, 20, 1, fp);
		fclose(fp);
		printf("\n\t\t\t修改成功！\n");
	}
	else
	{
		return;
	}
	getch();
}
/*================================================
== 函数名：void delStudentInfo(Student *pHead)
== 功  能：删除数据 
== 参  数：链表头指针 
== 返回值：无 
=================================================*/
void delStudentInfo(Student *pHead)
{
	Student *p1, *p2 = pHead;
	int bum;
	int num, count = 0;
	char student_name[20], c;
 
	system("title 学生成绩统计系统-删除");//将标题栏命名为“学生成绩统计系统”
	bum = scanMenu();
	if (bum == 1)
	{
		p1 = pHead->next;
		printf("\n\t\t\t请输入要删除学生的学号：");
		scanf("%d", &num);
		while (p1)
		{
			if (p1->one.num == num)
			{
				count = 1;
				printf("\n\t\t\t删除成功，删除的学生学号为：%d", num);
				if (p1->next == NULL)
				{
					pHead->next = NULL;
					break;
				}
				else
				{
					pHead->next = p1->next;
					free(p1);
					p1 = pHead->next;
				}
			}
			else
			{
				pHead = pHead->next;
				p1 = pHead->next;
			}
		}
	}
	else
	{
		if (bum == 2)
		{
			p1 = pHead->next;
			printf("\n\t\t\t请输入要删除的学生姓名：");
			scanf("%s", student_name);
			//统计一共有多少个学生
			while (p1)
			{
				if (strcmp(p1->name, student_name) == 0)
				{
					count++;
				}
				p1 = p1->next;
			}
			if (count > 0)
			{
				printf("'\n\n\n\t\t\t一共有%d个人的信息 全部删除(Y) or 逐一删除(N)?", count);//选择全部删除，还是逐一删除
				c = getch();
				//全部删除
				if (c == 'y' || c == 'Y')
				{
					p1 = pHead->next;
					while (p1)
					{
						if (strcmp(p1->name, student_name) == 0)
						{
							printf("\n\t\t\t删除成功，姓名为: %s", student_name);
							if (p1->next == NULL)
							{
								pHead->next = NULL;
								break;
							}
							else
							{
								pHead->next = p1->next;
								free(p1);
								p1 = pHead->next;
							}
						}
						else
						{
							pHead = pHead->next;
							p1 = pHead->next;
						}
					}
 
				}
				else
				{
					//逐一删除
					p1 = pHead->next;
					while (p1)
					{
						if (strcmp(p1->name, student_name) == 0)
						{
							printf("\n姓名:%s,学号:%d,性别:%c  是否删除(y or n)?", p1->name, p1->one.num, p1->one.sex);
							c = getch();
							if (c == 'y' || c == 'Y')
							{
								if (p1->next == NULL)
								{
									pHead->next = NULL;
									break;
								}
								else
								{
									pHead->next = p1->next;
									free(p1);
									p1 = pHead->next;
								}
								printf("成功！");
							}
							else
							{
								pHead = pHead->next;
								p1 = pHead->next;
							}
						}
						else
						{
							pHead = pHead->next;
							p1 = pHead->next;
						}
					}
				}
 
			}
		}
		else
		{
			if (bum == 3)
			{
				return;
			}
			else
			{
				delStudentInfo(pHead);
			}
		}
	}
	if (count == 0)
	{
		printf("\n\t\t\t没有该学生信息！");
	}
	else
	{
		saveList(p2);
	}
	getch();
}
/*================================================
== 函数名：void findStudentInfo(Student *pHead)
== 功  能：数据查找 
== 参  数：链表头指针 
== 返回值：无 
=================================================*/
void findStudentInfo(Student *pHead)
{
	int bum, count = 0;
	int num;
	char student_name[20];
 
	pHead = pHead->next;
	system("title 学生成绩统计系统-查找");//4-将标题栏命名为“学生成绩统计系统”
	bum = scanMenu();
	if (bum == 1)
	{
		printf("请输入学生的学号：");
		scanf("%d", &num);
		while (pHead)
		{
			if (pHead->one.num == num)
			{
				if (count == 0)
				{
					printf("\n\t\t\t已经查到！\n");
					printf("\n\  ┏━━━━━━┳━━━━━━━━┳━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━┓");
					printf("\n  ┃ 学号 ┃ 姓 名  ┃性别┃概  率┃离  散┃c  ++ ┃平均分┃总  分┃名次┃\n");
					count = 1;
				}
				printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
				printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", pHead->one.num,
					pHead->name, pHead->one.sex, pHead->one.prob_score, pHead->one.disc_score,
					pHead->one.cpp_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
				break;
			}
			pHead = pHead->next;
		}
		if (pHead == NULL)
		{
			printf("\n\t\t\t没有该学生记录！\n");
		}
		else
		{
			printf("  ┗━━━━━━┻━━━━━━━━┻━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━┛\n");
		}
	}
	else
	{
		if (bum == 2)
		{
			printf("请输入学生姓名：");
			scanf("%s", student_name);
			while (pHead)
			{
				if (strcmp(student_name, pHead->name) == 0)
				{
					if (count == 0)
					{
						printf("\n\t\t\t已经查到！\n");
						printf("\n\  ┏━━━━━━┳━━━━━━━━┳━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━┓");
						printf("\n  ┃ 学号 ┃ 姓 名  ┃性别┃概  率┃离  散┃c  ++ ┃平均分┃总  分┃名次┃\n");
						count = 1;
					}
					printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", pHead->one.num,
						pHead->name, pHead->one.sex, pHead->one.prob_score, pHead->one.disc_score,
						pHead->one.cpp_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
				}
				pHead = pHead->next;
			}
			if (count == 0)
			{
				printf("\n\t\t\t没有该学生记录！");
			}
			else
			{
				printf("  ┗━━━━━━┻━━━━━━━━┻━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━┛\n");
			}
		}
		else
		{
			if (bum == 3)
			{
				return;
			}
			else
			{
				findStudentInfo(pHead);
			}
		}
 
	}
	getch();
}
/*================================================
== 函数名：void menu()
== 功  能：菜单显示 
== 参  数：无 
== 返回值：无 
=================================================*/
void menu()
{
	system("CLS");//清屏
	printf("\n\n\n\t\t\t\t┌──────────────────────────────────┐\n");
	printf("\t\t\t\t│         学生成绩统计系统         │\n");
	printf("\t\t\t\t├──────────────────────────────────┤\n");
	printf("\t\t\t\t│         1   增加学生记录         │\n");
	printf("\t\t\t\t├──────────────────────────────────┤\n");
	printf("\t\t\t\t│         2   删除学生记录         │\n");
	printf("\t\t\t\t├──────────────────────────────────┤\n");
	printf("\t\t\t\t│         3   修改学生记录         │\n");
	printf("\t\t\t\t├──────────────────────────────────┤\n");
	printf("\t\t\t\t│         4   查找学生信息         │\n");
	printf("\t\t\t\t├──────────────────────────────────┤\n");
	printf("\t\t\t\t│         5   统计学生成绩         │\n");
	printf("\t\t\t\t├──────────────────────────────────┤\n");
	printf("\t\t\t\t│         6   查看学生成绩         │\n");
	printf("\t\t\t\t├──────────────────────────────────┤\n");
	printf("\t\t\t\t│         7   修改登陆密码         │\n");
	printf("\t\t\t\t├──────────────────────────────────┤\n");
	printf("\t\t\t\t│         8      关于              │\n");
	printf("\t\t\t\t├──────────────────────────────────┤\n");
	printf("\t\t\t\t│         9    退出系统            │\n");
	printf("\t\t\t\t└──────────────────────────────────┘\n");
}
/*================================================
== 函数名：void sortList(Student *pHead)
== 功  能：数据排序 
== 参  数：链表头指针 
== 返回值：无 
=================================================*/
void sortList(Student *pHead)
{
	Student *p1, *p2;
	StudentDate dat;
	char stu_name[20];
	int bum, count = 0, rank;
 
	system("title 学生成绩统计系统-查看");//6-将标题栏命名为“学生成绩统计系统”
	bum = sortMenu();
	if (bum == 1)//按平均分高低排序
	{
		for (p1 = pHead->next; p1 != NULL; p1 = p1->next)
		{
			for (p2 = p1->next; p2 != NULL; p2 = p2->next)
			{
				if (p2->one.aver_score > p1->one.aver_score)
				{
					dat = p2->one;
					rank = p2->rank;
					strcpy(stu_name, p2->name);
					p2->one = p1->one;
					p2->rank = p1->rank;
					strcpy(p2->name, p1->name);
					p1->one = dat;
					p1->rank = rank;
					strcpy(p1->name, stu_name);
				}
			}
		}
	}
	else
	{
		if (bum == 2)//按学号高低排序
		{
			for (p1 = pHead->next; p1 != NULL; p1 = p1->next)
			{
				for (p2 = p1->next; p2 != NULL; p2 = p2->next)
				{
					if (p2->one.num < p1->one.num)
					{
						dat = p2->one;
						rank = p2->rank;
						strcpy(stu_name, p2->name);
						p2->one = p1->one;
						p2->rank = p1->rank;
						strcpy(p2->name, p1->name);
						p1->one = dat;
						p1->rank = rank;
						strcpy(p1->name, stu_name);
					}
				}
			}
		}
		else
		{
			if (bum == 3)
			{
				return;
			}
			else
			{
				sortList(pHead);
			}
		}
	}
	printList(pHead);
}
/*================================================
== 函数名：int sortMenu()
== 功  能：排序方式菜单显示和选择 
== 参  数：无 
== 返回值：排序方式对应整型数 
=================================================*/
int sortMenu()
{
	int bum;
 
	system("CLS");
	printf("\n\n\n");
	printf("\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t┃                       以什么方式查询 ？                  ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    1   按成绩的高低                      ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    2   按学号的升次                      ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                    3   返回主菜单                        ┃\n");
	printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("请按键选择：");
	bum = (int)(getch() - '0');
	system("CLS");
 
	return bum;
}
/*================================================
== 函数名：void printList(Student *pHead)
== 功  能：链表数据打印 
== 参  数：链表头指针 
== 返回值：无 
=================================================*/
void printList(Student *pHead)
{
	int count = 0;
	pHead = pHead->next;
	system("CLS");
	printf("\n\  ┏━━━━━━┳━━━━━━━━┳━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━┓");
	printf("\n  ┃ 学号 ┃ 姓 名  ┃性别┃概  率┃离  散┃c  ++ ┃平均分┃总  分┃名次┃\n");
	while (pHead)
	{
		printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
		printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", pHead->one.num,
			pHead->name, pHead->one.sex, pHead->one.prob_score, pHead->one.disc_score,
			pHead->one.cpp_score, pHead->one.aver_score, pHead->one.sum_score, pHead->rank);
		pHead = pHead->next;
		count++;
	}
	printf("  ┗━━━━━━┻━━━━━━━━┻━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━┛\n");
	printf("\t\t\t该班一共%d个人!", count);
	getch();
}
/*================================================
== 函数名：void statisStudentInfo(Student *pHead)
== 功  能：查看学生信息 
== 参  数：链表头指针 
== 返回值：无 
=================================================*/
void statisStudentInfo(Student *pHead)
{
	double aver_score[5] = { 0,0,0,0,0 };
	Student *p1 = pHead->next;
	int count = 0;
	int bad = 0, bum;
 
	system("title 学生成绩统计系统-统计");//将标题栏命名为“学生成绩统计系统”
	bum = statisMenu();
	if (bum == 1)
	{
		while (p1)
		{
			aver_score[0] = aver_score[0] + p1->one.prob_score;
			aver_score[1] = aver_score[1] + p1->one.disc_score;
			aver_score[4] = aver_score[4] + p1->one.cpp_score;
			p1 = p1->next;
			count++;
		}
		aver_score[0] = aver_score[0] / count;
		aver_score[1] = aver_score[1] / count;
		aver_score[4] = aver_score[4] / count;
		p1 = pHead->next;
		printf("\n\n  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
		printf("  ┃\t概率的平均分为:%.1f，没有达到达到平均分的学生有        ┃\n", aver_score[0]);
		printf("  ┣━━━━━━┳━━━━━━━━┳━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━┫\n");
		printf("  ┃ 学号 ┃ 姓 名  ┃性别┃概  率┃离  散┃  c++ ┃平均分┃总  分┃名次┃\n");
		printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
		while (p1)
		{
			if (p1->one.prob_score < aver_score[0])
			{
				if (bad == 0)
				{
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
		bad = 0;
		p1 = pHead->next;
		printf("  ┣━━━━━━┻━━━━━━━━┻━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━┫\n");
		printf("  ┃\t离散的平均分为:%.1f，没有达到达到平均分的学生有        ┃\n", aver_score[1]);
		printf("  ┣━━━━━━┳━━━━━━━━┳━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━┫\n");
		printf("  ┃ 学号 ┃ 姓 名  ┃性别┃概  率┃离  散┃  c++ ┃平均分┃总  分┃名次┃\n");
		printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
		while (p1)
		{
			if (p1->one.disc_score < aver_score[1])
			{
				if (bad == 0)
				{
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
 
		bad = 0;
		p1 = pHead->next;
		printf("  ┣━━━━━━┻━━━━━━━━┻━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━┫\n");
		printf("  ┃\tc++的平均分为:%.1f，没有达到达到平均分的学生有         ┃\n", aver_score[4]);
		printf("  ┣━━━━━━┳━━━━━━━━┳━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━┫\n");
		printf("  ┃ 学号 ┃ 姓 名  ┃性别┃概  率┃离  散┃  c++ ┃平均分┃总  分┃名次┃\n");
		printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
		while (p1)
		{
			if (p1->one.cpp_score < aver_score[4])
			{
				if (bad == 0)
				{
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				else
				{
					printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
					printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
						p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
						p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
				}
				bad = 1;
			}
			p1 = p1->next;
		}
		printf("  ┗━━━━━━┻━━━━━━━━┻━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━┛\n");
		printf("\t\t\t\t\t\t该班一共%d个人!", count);
	}
	else
	{
		if (bum == 2)
		{
			bad = 0;
			printf("\n\n  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
			printf("  ┃\t概率成绩大于90分或小于60的学生有                       ┃\n");
			printf("  ┣━━━━━━┳━━━━━━━━┳━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━┫\n");
			printf("  ┃ 学号 ┃ 姓 名  ┃性别┃概  率┃离  散┃  c++ ┃平均分┃总  分┃名次┃\n");
			printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.prob_score < 60 || p1->one.prob_score >= 90)
				{
					if (bad == 0)
					{
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  ┣━━━━━━┻━━━━━━━━┻━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━┫\n");
			printf("  ┃\t离散成绩大于90分或小于60的学生有                       ┃\n");
			printf("  ┣━━━━━━┳━━━━━━━━┳━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━┫\n");
			printf("  ┃ 学号 ┃ 姓 名  ┃性别┃概  率┃离  散┃  c++ ┃平均分┃总  分┃名次┃\n");
			printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.disc_score < 60 || p1->one.disc_score >= 90)
				{
					if (bad == 0)
					{
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			bad = 0;
			printf("  ┣━━━━━━┻━━━━━━━━┻━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━┫\n");
			printf("  ┃\tc++成绩大于90分或小于60的学生有                        ┃\n");
			printf("  ┣━━━━━━┳━━━━━━━━┳━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┳━━━━┫\n");
			printf("  ┃ 学号 ┃ 姓 名  ┃性别┃概  率┃离  散┃  c++ ┃平均分┃总  分┃名次┃\n");
			printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
			p1 = pHead->next;
			while (p1)
			{
				if (p1->one.cpp_score < 60 || p1->one.cpp_score >= 90)
				{
					if (bad == 0)
					{
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					else
					{
						printf("  ┣━━━━━━╋━━━━━━━━╋━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━╋━━━━┫\n");
						printf("  ┃ %-5d┃ %-6s ┃  %c ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃%5.1f ┃ %-3d┃\n", p1->one.num,
							p1->name, p1->one.sex, p1->one.prob_score, p1->one.disc_score,
							p1->one.cpp_score, p1->one.aver_score, p1->one.sum_score, p1->rank);
					}
					bad = 1;
				}
				p1 = p1->next;
			}
			printf("  ┗━━━━━━┻━━━━━━━━┻━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┻━━━━┛\n");
		}
		else
		{
			if (bum == 3)
			{
				return;
			}
			else
			{
				statisStudentInfo(pHead);
			}
		}
	}
	getch();
}
/*================================================
== 函数名：int statisMenu()
== 功  能：查看方式菜单和选择 
== 参  数：无 
== 返回值：方式对应整型数 
=================================================*/
int statisMenu()
{
	int bum;
 
	system("CLS");
	printf("\n\n\n");
	printf("\t\t┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	printf("\t\t┃                   以什么方式统计学生信息？               ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                      1   按平均分                        ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                      2   按是否合格                      ┃\n");
	printf("\t\t┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	printf("\t\t┃                      3   返回主菜单                      ┃\n");
	printf("\t\t┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	printf("请按键选择：");
	bum = (int)(getch() - '0');
	system("CLS");
 
	return bum;
}
/*================================================
== 函数名：void gotoxy(int x, int y)
== 功  能：光标移动到指定位置 
== 参  数：int x：列坐标 
           int y：行坐标 
== 返回值：无 
=================================================*/
void gotoxy(int x, int y)//x为列坐标,y为行坐标
{
	COORD pos = { x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}
