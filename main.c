#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <io.h>
#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

/*定义一个链表来存放学生信息*/
typedef struct student
{
    char stuNum[9];//学生学号
    char stuName[10];//学生姓名
    char stuSex[10];     //学生性别
    char phoneNum[12];//手机号码
    double mathScore;//数学分数
    double chinScore;//语文分数
    struct student *next;
}student;

typedef struct Node
{
    struct student stu;
    struct Node *next;
}Node;

typedef struct Node *LinkList; /* 定义LinkList */

Status InitList(LinkList *L)
{
    *L=(LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
    if(!(*L)) /* 存储分配失败 */
            return ERROR;
    (*L)->next=NULL; /* 指针域为空 */
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(LinkList L)
{
    if(L->next)
            return FALSE;
    else
            return TRUE;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{
	LinkList p,q;
	p=(*L)->next;           /*  p指向第一个结点 */
	while(p)                /*  没到表尾 */
	{
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=NULL;        /* 头结点指针域为空 */
	return OK;
}
/*初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数*/
int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next; /*p指向第一个结点*/
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}

/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 已测试可用*/
Status ListInsert(LinkList *L,int i,struct student e)
{
	int j,k;
	LinkList p,s;
	p = *L;
	j = 1;
	while (p && j < i)     /* 寻找第i个结点 */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;   /* 第 i 个元素不存在 */

	s = (LinkList)malloc(sizeof(Node));  /*  生成新结点(C语言标准函数) */
    strcpy(s->stu.stuNum,e.stuNum);
    strcpy(s->stu.stuName,e.stuName);
    strcpy(s->stu.stuSex,e.stuSex);
    s->stu.mathScore=e.mathScore;//插入数学成绩
	s->stu.chinScore=e.chinScore;//插入语文成绩
    strcpy(s->stu.phoneNum,e.phoneNum);
    s->next = p->next;     /* 将p的后继结点赋值给s的后继  */
	p->next = s;          /* 将s赋值给p的后继 */
	return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：xian删除L的第i个数据元素(hou根据学号删除学生的所有信息)，并用e返回其值，L的长度减1 */
Status ListDelete(LinkList *L,char *num)
{

	int i,j,k;
	LinkList p,q,r;
	p = *L;
	/*要找到学号为num的人是第几个元素，并把这个赋值给i*/
	r = *L;
	j = 1;
	i=0;
	while(r->next)
    {
        if(!strcmp(num,r->stu.stuNum))//判断两个字符串是否相等
          break;
        else
        {i++;
        r=r->next;}
    }
	while (p->next && j < i)/* 遍历寻找第i个元素 */
	{
        p = p->next;
        ++j;
	}
	if (!(p->next) || j > i)
	    return ERROR;           /* 第i个元素不存在 */
	q = p->next;
	p->next = q->next;			/* 将q的后继赋值给p的后继 */

   //strcpy(e.stuNum,q->stu.stuNum);
	//*e = q->data;               /* 将q结点中的数据给e */
	free(q);                    /* 让系统回收此结点，释放内存 */
	printf("删除成功！\n");
	return OK;
}
/*对某学生的信息进行修改，传入学生学号，返回修改后的学生信息
输入1表示需要修改此项，输入0表示不需要修改此项跳过，
先实现修改第i位同学的信息*/
Status ListAlter(LinkList L,char *num)
{
   // LinkList p=L;//->next;
    //LinkList r=L;//->next;
    int i,j,flag;
    double alMathScore,alChinScore;
    char alSex[10],alPhoneNum[12],decide[10];
    char yes[4]="yes\0";
    char no[3]="no\0";
    char null[1]="\0";
    flag=0;
    LinkList p=L->next;
	while(p)
    {

        if(!strcmp(num,p->stu.stuNum))//判断两个字符串是否相等
          {
            flag=1;
            printf("输入no表示跳过修改性别，输入yes表示需要修改性别\n");
            scanf("%s",decide);
            if(!strcmp(decide,yes))
            {
                printf("修改性别为：\n");
                scanf("%s",alSex);
                strcpy(p->stu.stuSex,alSex);
                printf("修改性别成功！\n");
            }
            strcpy(decide,null);

            printf("输入no表示跳过修改电话号码，输入yes表示需要修改电话号码\n");
            scanf("%s",decide);
            if(!strcmp(decide,yes))
            {
                printf("修改电话号码为：\n");
                scanf("%s",alPhoneNum);
                strcpy(p->stu.phoneNum,alPhoneNum);
                printf("修电话号码成功！\n");
            }
            strcpy(decide,null);
            printf("输入no表示跳过数学分数的修改，输入yes表示需要修改数学分数\n");
            scanf("%s",decide);
            if(!strcmp(decide,yes))
            {
                printf("数学分数修改为：\n");
                scanf("%lf",&alMathScore);
                p->stu.mathScore=alMathScore;
                printf("修改数学成绩成功！\n");
            }
            strcpy(decide,null);
            printf("输入no表示跳过语文分数的修改，输入yes表示需要修改语文分数\n");
            scanf("%s",decide);
            if(!strcmp(decide,yes))
            {
                printf("语文分数修改为：\n");
                scanf("%lf",&alChinScore);
                p->stu.chinScore=alChinScore;
                printf("修改语文成绩成功！\n");
            }


          }
        p=p->next;
    }
    if(flag==0)
        printf("该学生不在学生列表中！\n");

}


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出，已测试可用*/
Status ListTraverse(LinkList L)
{
    int k;
    LinkList p=L->next;
    while(p)
    {
        printf("学生学号：");printf("%s\n",p->stu.stuNum);
        printf("学生姓名：");printf("%s\n",p->stu.stuName);
        printf("学生性别：");printf("%s\n",p->stu.stuSex);
        printf("手机号码：");printf("%s\n",p->stu.phoneNum);
        printf("数学成绩：");printf("%.2lf\n",p->stu.mathScore);
        printf("语文成绩：");printf("%.2lf\n",p->stu.chinScore);
        printf("\n");
        p=p->next;
    }
    printf("\n");
    return OK;
}

/*查询某个符合学号这个条件的学生并打印查询结果*/
Status ListQueryNum(LinkList L,char *num)
{
    LinkList p=L->next;
    int flag=0;
    while(p)
    {

        if(!strcmp(num,p->stu.stuNum))//输出分数小于bScore大于mScore的学生信息
          {
            flag=1;
            printf("学生学号：");printf("%s\n",p->stu.stuNum);
            printf("学生姓名：");printf("%s\n",p->stu.stuName);
            printf("学生性别：");printf("%s\n",p->stu.stuSex);
            printf("联系方式：");printf("%s\n",p->stu.phoneNum);
            printf("数学成绩：");printf("%.2lf\n",p->stu.mathScore);
            printf("语文成绩：");printf("%.2lf\n",p->stu.chinScore);
            printf("\n");
          }
        p=p->next;
    }
    if(flag==0)
        printf("该学生不在学生列表中！\n");
}

/*查询某个符合性别这个条件的学生并打印查询结果*/
Status ListQuerySex(LinkList L,char *Sex)
{
    LinkList p=L->next;
    int flag=0;
	while(p)
    {

        if(!strcmp(Sex,p->stu.stuSex))//判断两个字符串是否相等
          {
            flag=1;
            printf("学生学号：");printf("%s\n",p->stu.stuNum);
            printf("学生姓名：");printf("%s\n",p->stu.stuName);
            printf("学生性别：");printf("%s\n",p->stu.stuSex);
            printf("联系方式：");printf("%s\n",p->stu.phoneNum);
            printf("数学成绩：");printf("%.2lf\n",p->stu.mathScore);
            printf("语文成绩：");printf("%.2lf\n",p->stu.chinScore);
            printf("\n");

          }
        p=p->next;
    }
    if(flag==0)
        printf("该学生不在学生列表中！\n");
}

 int ListQuerySexNum(LinkList L,char *Sex)
{
    LinkList p=L->next;
    int number=0;
	while(p)
    {

        if(!strcmp(Sex,p->stu.stuSex))//判断两个字符串是否相等
          {
            number++;
          }
        p=p->next;
    }
    return number;
}
/*查询数学分数在mathBotScore~mathUpScore,
语文分数在chinBotScore~chinUpScore的学生并打印其信息*/
Status ListQueryScore(LinkList L,double mathBotScore,double mathUpScore,double chinBotScore,double chinUpScore)
{
    LinkList p=L->next;
	while(p)
    {

        if(p->stu.mathScore>=mathBotScore&&p->stu.mathScore<=mathUpScore&&
          p->stu.chinScore>=chinBotScore&&p->stu.chinScore<=chinUpScore)//输出分数小于bScore大于mScore的学生信息
          {

            printf("学生学号：");printf("%s\n",p->stu.stuNum);
            printf("学生姓名：");printf("%s\n",p->stu.stuName);
            printf("学生性别：");printf("%s\n",p->stu.stuSex);
            printf("联系方式：");printf("%s\n",p->stu.phoneNum);
            printf("数学成绩：");printf("%.2lf\n",p->stu.mathScore);
            printf("语文成绩：");printf("%.2lf\n",p->stu.chinScore);
            printf("\n");

          }
        p=p->next;
    }
}
//统计分数人数
int ListQueryScoreNum(LinkList L,double mathBotScore,double mathUpScore,double chinBotScore,double chinUpScore)
{
    LinkList p=L->next;
    int number=0;
	while(p)
    {

        if(p->stu.mathScore>=mathBotScore&&p->stu.mathScore<=mathUpScore&&
          p->stu.chinScore>=chinBotScore&&p->stu.chinScore<=chinUpScore)//输出分数小于bScore大于mScore的学生信息
          {
                number++;
          }
        p=p->next;
    }
    return number;
}
/*电话号码查询*/
Status ListQueryPhone(LinkList L,char * phoNum)
{
    LinkList p=L->next;
    printf("符合条件的学生信息如下：\n");
    int flag=0;
    while(p)
    {

        if(!strcmp(phoNum,p->stu.phoneNum))//输出分数小于bScore大于mScore的学生信息
          {
            flag=1;
            printf("学生学号：");printf("%s\n",p->stu.stuNum);
            printf("学生姓名：");printf("%s\n",p->stu.stuName);
            printf("学生性别：");printf("%s\n",p->stu.stuSex);
            printf("联系方式：");printf("%s\n",p->stu.phoneNum);
            printf("数学成绩：");printf("%.2lf\n",p->stu.mathScore);
            printf("语文成绩：");printf("%.2lf\n",p->stu.chinScore);
            printf("\n");

          }
        p=p->next;
    }
    if(flag==0)
        printf("该学生不在学生列表中！\n");
}


/*数学分数从高到低排序*/
void MathSort(LinkList L)
{
   int i,length;
   struct student *p;
   struct student *pnew;
   struct student *pold;
   struct student *head;
   LinkList r;
   r=L->next;
   head=(struct student *)malloc(sizeof(struct student));
   strcpy(head->stuNum,r->stu.stuNum);
   strcpy(head->stuName,r->stu.stuName);
   strcpy(head->stuSex,r->stu.stuSex);
   strcpy(head->phoneNum,r->stu.phoneNum);
   head->mathScore=r->stu.mathScore;
   head->chinScore=r->stu.chinScore;
   head->next=NULL;
   r=r->next;


   length=ListLength(L);

   for(i=0;i<length-1;i++)
   {
        pnew=(struct student *)malloc(sizeof(struct student));

        strcpy(pnew->stuNum,r->stu.stuNum);
        strcpy(pnew->stuName,r->stu.stuName);
        strcpy(pnew->stuSex,r->stu.stuSex);
        strcpy(pnew->phoneNum,r->stu.phoneNum);
        pnew->mathScore=r->stu.mathScore;
        pnew->chinScore=r->stu.chinScore;
        p=head;
        /*这里曾经出现过bug*/
        if(pnew->mathScore>=head->mathScore){
            pnew->next=head;
            head=pnew;
           // printf("1");
        }
        else{
            while(p!=NULL&&pnew->mathScore<p->mathScore){
                pold=p;
                p=p->next;

            }
            pnew->next=p;
            pold->next=pnew;
        }
        r=r->next;

   }
        printf("将数学成绩排序后：\n");
        for(i=0;i<length;i++)
        {
            printf("学生学号：");printf("%s\n",head->stuNum);
            printf("学生姓名：");printf("%s\n",head->stuName);
            printf("学生性别：");printf("%s\n",head->stuSex);
            printf("联系方式：");printf("%s\n",head->phoneNum);
            printf("数学成绩：");printf("%.2lf\n",head->mathScore);
            printf("语文成绩：");printf("%.2lf\n",head->chinScore);
            printf("\n");
            head=head->next;
        }
        //print(head);
}
/*语文分数从高到低排序*/
void ChinSort(LinkList L)
{
   int i,length;
   struct student *p;
   struct student *pnew;
   struct student *pold;
   struct student *head;
   LinkList r;
   r=L->next;
   head=(struct student *)malloc(sizeof(struct student));
   strcpy(head->stuNum,r->stu.stuNum);
   strcpy(head->stuName,r->stu.stuName);
   strcpy(head->stuSex,r->stu.stuSex);
   strcpy(head->phoneNum,r->stu.phoneNum);
   head->mathScore=r->stu.mathScore;
   head->chinScore=r->stu.chinScore;
   head->next=NULL;
   r=r->next;


   length=ListLength(L);

   for(i=0;i<length-1;i++)
   {
        pnew=(struct student *)malloc(sizeof(struct student));

        strcpy(pnew->stuNum,r->stu.stuNum);
        strcpy(pnew->stuName,r->stu.stuName);
        strcpy(pnew->stuSex,r->stu.stuSex);
        strcpy(pnew->phoneNum,r->stu.phoneNum);
        pnew->mathScore=r->stu.mathScore;
        pnew->chinScore=r->stu.chinScore;
        p=head;
        /*这里曾经出现过bug*/
        if(pnew->chinScore>=head->chinScore){
            pnew->next=head;
            head=pnew;
           // printf("1");
        }
        else{
            while(p!=NULL&&pnew->chinScore<p->chinScore){
                pold=p;
                p=p->next;

            }
            pnew->next=p;
            pold->next=pnew;
        }
        r=r->next;

   }
        printf("将数学成绩排序后：\n");
        for(i=0;i<length;i++)
        {
            printf("学生学号：");printf("%s\n",head->stuNum);
            printf("学生姓名：");printf("%s\n",head->stuName);
            printf("学生性别：");printf("%s\n",head->stuSex);
            printf("联系方式：");printf("%s\n",head->phoneNum);
            printf("数学成绩：");printf("%.2lf\n",head->mathScore);
            printf("语文成绩：");printf("%.2lf\n",head->chinScore);
            printf("\n");
            head=head->next;
        }
}
/*将表内的数据写入excel表格*/
void writeExcel(LinkList L) {

	FILE *fp = NULL;
	int i,length;

    LinkList p;
    p=L->next;
    length=ListLength(L);
	fp = fopen("F:\\test.xls", "w");
        fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\n","学号","姓名","性别","联系方式","数学成绩","语文成绩");
        for (i = 0; i <length; i++) {
            fprintf(fp,"%s\t%s\t%s\t%s\t%.2lf\t%.2lf\n",p->stu.stuNum,p->stu.stuName,p->stu.stuSex,p->stu.phoneNum,p->stu.mathScore,p->stu.chinScore);
            p=p->next;
	}
	fclose(fp);

}
/*从excel表格里的数据导入链表*/
void readExcel(LinkList L)
{
    FILE *fp;

    int i,j ;
    struct student excelRead;
    /*char stuNum1[9];//学生学号
    char stuName1[10];//学生姓名
    char stuSex1[10];     //学生性别
    char phoneNum1[12];//手机号码
    double mathScore1;//数学分数
    double chinScore1;//语文分数*/
    fp=fopen("f://student.txt","r");
    for(j = 0 ;j < 34 ; j++)
    {
        fscanf(fp,"%s\t",excelRead.stuNum);
        fscanf(fp,"%s\t",excelRead.stuName);
        fscanf(fp,"%s\t",excelRead.stuSex);
        fscanf(fp,"%s\t",excelRead.phoneNum);
        fscanf(fp,"%lf\t",&excelRead.mathScore);
        fscanf(fp,"%lf\n",&excelRead.chinScore);
        ListInsert(&L,1,excelRead);
    }
}

int main(void)
{
    LinkList L;
    int i,j,choice1,choice2,choice3,Sum,sumMale,sumFemale;
    int failMathNum,mathNum6_7,mathNum7_8,mathNum8_9,mathNum9_10,mathNum10;
    int failChinNum,chinNum6_7,chinNum7_8,chinNum8_9,chinNum9_10,chinNum10;


    char Snum[9],Sname[10],Ssex[10],Sphone[12];
    double SmathL,SchinL,SmathB,SchinB,Smath,Schin;
    struct student putIn;
    char num[9]="17041201\0";
    char Sex[10]="女\0";
    char phone[12]="13777396230\0";

    struct student hsr={"17041202\0","韩世容\0","男\0","17857680092\0",96,88};
    struct student gqy={"17041201\0","高沁源\0","女\0","15987652918\0",99,95};
    //printf("mao\n");
    struct student amao={"17041203\0","毛忆宁\0","女\0","13777396230\0",90,100};
    struct student tian={"11111111\0","天才\0","男\0","11111111111\0",100,100};
    struct student *head;
    head=(struct student *)malloc(sizeof(struct student));

    i=InitList(&L);
   // i= ListInsert(&L,1,amao);
    //i= ListInsert(&L,1,hsr);
    //i= ListInsert(&L,1,gqy);
    //i=ListInsert(&L,1,tian);
    //i= ListTraverse(L);
    /*之前测试的痕迹*/
      //i=ListDelete(&L,num);
     //ListAlter(L,"17041202\0");
    //i=ListTraverse(L);
    //i=ListQueryNum(L,num);
    //i=ListQuerySex(L,Sex);
    //ListQueryPhone(L,phone);
    //i=ListQueryScore(L,87,96,85,89);
    //MathSort(L);
    readExcel(L);
    printf("欢迎来到学生管理系统！\n");
    while(1)
{

    printf("输入0退出操作，输入1进行学生信息的输入，输入2删除学生信息，输入3修改学生信息，输入4查询学生信息，输入5进行分数排序,显示学生统计信息请按6.....\n");
    scanf("%d",&choice1);
    //退出操作
    if(choice1==0)
        break;
    //输入学生信息功能
    if(choice1==1)
    {

        printf("请输入学生学号：\n");
        scanf("%s",Snum);
        strcpy(putIn.stuNum,Snum);

        printf("请输入学生姓名：\n");
        scanf("%s",Sname);
        strcpy(putIn.stuName,Sname);

        printf("请输入学生性别：\n");
        scanf("%s",Ssex);
        strcpy(putIn.stuSex,Ssex);

        printf("请输入学生手机号：\n");
        scanf("%s",Sphone);
        strcpy(putIn.phoneNum,Sphone);

        printf("请输入学生数学成绩：\n");
        scanf("%lf",&Smath);
        putIn.mathScore=Smath;

        printf("请输入学生语文成绩：\n");
        scanf("%lf",&Schin);
        putIn.chinScore=Schin;

        i= ListInsert(&L,1,putIn);
    }
    //删除功能
    if(choice1==2)
    {
        printf("请输入要删除学生信息的学号：\n");
        scanf("%s",Snum);
        i=ListDelete(&L,Snum);
        //printf("信息录入成功！\n");
    }
    //修改功能
    if(choice1==3)
    {
        printf("请输入要修改学生信息的学号：\n");
        scanf("%s",Snum);
        i=ListAlter(L,Snum);
    }
    //查询功能
    if(choice1==4)
    {
        printf("请输入要查询的类型：通过学号查询请按1，通过性别查询请按2，通过分数查询请按3，通过电话号码查询请按4，打印所有同学信息请按5...\n");
        scanf("%d",&choice2);
        switch(choice2)
        {
            case 1:printf("请输入学生学号：\n");scanf("%s",Snum);i=ListQueryNum(L,Snum);break;
            case 2:printf("请输入学生性别：\n");scanf("%s",Ssex);i=ListQuerySex(L,Ssex);break;
            case 3:printf("请依次输入学生分数：数学分数下限-上限，语文分数下限-上限\n");
                   scanf("%lf%lf%lf%lf",&SmathL,&SmathB,&SchinL,&SchinB);
                   i=ListQueryScore(L,SmathL,SmathB,SchinL,SchinB);break;
            case 4:printf("请输入要查询的电话号码：\n");scanf("%s",Sphone);i=ListQueryPhone(L,Sphone);break;
            case 5:printf("所有同学信息打印如下：\n");i=ListTraverse(L);break;
            default:printf("error!");
        }

    }
    //排序成绩功能
    if(choice1==5)
    {
        printf("输入1表示数学成绩从高到低排序，输入2表示语文成绩从高到底排序：\n");
        scanf("%d",&choice3);
        switch(choice3)
        {
            case 1:MathSort(L);break;
            case 2:ChinSort(L);break;
            defalut:printf("error");
        }
    }
    //统计功能
    if(choice1==6)
    {
        Sum=ListLength(L);
        printf("__________________________________________________________________________________________\n");
        printf("总体人数为：%d\n",Sum);

        sumMale=ListQuerySexNum(L,"男");
        sumFemale=Sum-sumMale;
        printf("男女比例为   男：女=%d :%d=%.2lf\n",sumMale,sumFemale,(double)sumMale/(double)sumFemale);

        printf("各区间分数百分比计算：\n");

        failMathNum=ListQueryScoreNum(L,0,59,0,100);
        printf("数学:\n不及格人数：%d/%d=%.2lf\n",failMathNum,Sum,(double)failMathNum/(double)Sum);
        mathNum6_7=ListQueryScoreNum(L,60,69,0,100);
        printf("数学分数在60到69之间的人数：%d/%d=%.2lf\n",mathNum6_7,Sum,(double)mathNum6_7/(double)Sum);
        mathNum7_8=ListQueryScoreNum(L,70,79,0,100);
        printf("数学分数在70到79之间的人数：%d/%d=%.2lf\n",mathNum7_8,Sum,(double)mathNum7_8/(double)Sum);
        mathNum8_9=ListQueryScoreNum(L,80,89,0,100);
        printf("数学分数在80到89之间的人数：%d/%d=%.2lf\n",mathNum8_9,Sum,(double)mathNum8_9/(double)Sum);
        mathNum9_10=ListQueryScoreNum(L,90,99,0,100);
        printf("数学分数在90到99之间的人数：%d/%d=%.2lf\n",mathNum9_10,Sum,(double)mathNum9_10/(double)Sum);
        mathNum10=ListQueryScoreNum(L,100,100,0,100);
        printf("数学分数为满分的人数为：%d/%d=%.2lf\n",mathNum10,Sum,(double)mathNum10/(double)Sum);

        failChinNum=ListQueryScoreNum(L,0,100,0,59);
        printf("语文:\n不及格人数：%d/%d=%.2lf\n",failChinNum,Sum,(double)failChinNum/(double)Sum);
        chinNum6_7=ListQueryScoreNum(L,0,100,60,69);
        printf("语文分数在60到69之间的人数：%d/%d=%.2lf\n",chinNum6_7,Sum,(double)chinNum6_7/(double)Sum);
        chinNum7_8=ListQueryScoreNum(L,0,100,70,79);
        printf("语文分数在70到79之间的人数：%d/%d=%.2lf\n",chinNum7_8,Sum,(double)chinNum7_8/(double)Sum);
        chinNum8_9=ListQueryScoreNum(L,0,100,80,89);
        printf("语文分数在80到89之间的人数：%d/%d=%.2lf\n",chinNum8_9,Sum,(double)chinNum8_9/(double)Sum);
        chinNum9_10=ListQueryScoreNum(L,0,100,90,99);
        printf("语文分数在90到99之间的人数：%d/%d=%.2lf\n",chinNum9_10,Sum,(double)chinNum9_10/(double)Sum);
        chinNum10=ListQueryScoreNum(L,0,100,100,100);
        printf("语文分数为满分的人数为：%d/%d=%.2lf\n",chinNum10,Sum,(double)chinNum10/(double)Sum);


    }
    if (choice1!=5&&choice1!=4&&choice1!=3&&choice1!=2&&choice1!=1&&choice1!=0&&choice1!=6)
        printf("Error!Please input correct number!\n");
}
   // scanf("%s",Snum);

    //i=ListQueryNum(L,num);
    //scanf("%s",Snum);
    //strcpy(num,Snum);
   //i=ListDelete(&L,num);
   //i=ListAlter(L,num);
   //i= ListTraverse(L);
    //MathSort(L);
    //ChinSort(L,head);
    //print(head);
     writeExcel(L);
    //ListTraverse(L);
    //ChinSort(L,head);
    printf("体验结束，感谢您的使用！\n");
    return 0;
}
