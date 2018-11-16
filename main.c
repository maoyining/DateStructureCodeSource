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

#define MAXSIZE 20 /* �洢�ռ��ʼ������ */

typedef int Status;/* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */
typedef int ElemType;/* ElemType���͸���ʵ������������������Ϊint */

/*����һ�����������ѧ����Ϣ*/
typedef struct student
{
    char stuNum[9];//ѧ��ѧ��
    char stuName[10];//ѧ������
    char stuSex[10];     //ѧ���Ա�
    char phoneNum[12];//�ֻ�����
    double mathScore;//��ѧ����
    double chinScore;//���ķ���
    struct student *next;
}student;

typedef struct Node
{
    struct student stu;
    struct Node *next;
}Node;

typedef struct Node *LinkList; /* ����LinkList */

Status InitList(LinkList *L)
{
    *L=(LinkList)malloc(sizeof(Node)); /* ����ͷ���,��ʹLָ���ͷ��� */
    if(!(*L)) /* �洢����ʧ�� */
            return ERROR;
    (*L)->next=NULL; /* ָ����Ϊ�� */
    return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
Status ListEmpty(LinkList L)
{
    if(L->next)
            return FALSE;
    else
            return TRUE;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
Status ClearList(LinkList *L)
{
	LinkList p,q;
	p=(*L)->next;           /*  pָ���һ����� */
	while(p)                /*  û����β */
	{
		q=p->next;
		free(p);
		p=q;
	}
	(*L)->next=NULL;        /* ͷ���ָ����Ϊ�� */
	return OK;
}
/*��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ���*/
int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next; /*pָ���һ�����*/
    while(p)
    {
        i++;
        p=p->next;
    }
    return i;
}

/* ��ʼ������˳�����Ա�L�Ѵ���,1��i��ListLength(L)�� */
/* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 �Ѳ��Կ���*/
Status ListInsert(LinkList *L,int i,struct student e)
{
	int j,k;
	LinkList p,s;
	p = *L;
	j = 1;
	while (p && j < i)     /* Ѱ�ҵ�i����� */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return ERROR;   /* �� i ��Ԫ�ز����� */

	s = (LinkList)malloc(sizeof(Node));  /*  �����½��(C���Ա�׼����) */
    strcpy(s->stu.stuNum,e.stuNum);
    strcpy(s->stu.stuName,e.stuName);
    strcpy(s->stu.stuSex,e.stuSex);
    s->stu.mathScore=e.mathScore;//������ѧ�ɼ�
	s->stu.chinScore=e.chinScore;//�������ĳɼ�
    strcpy(s->stu.phoneNum,e.phoneNum);
    s->next = p->next;     /* ��p�ĺ�̽�㸳ֵ��s�ĺ��  */
	p->next = s;          /* ��s��ֵ��p�ĺ�� */
	return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* ���������xianɾ��L�ĵ�i������Ԫ��(hou����ѧ��ɾ��ѧ����������Ϣ)������e������ֵ��L�ĳ��ȼ�1 */
Status ListDelete(LinkList *L,char *num)
{

	int i,j,k;
	LinkList p,q,r;
	p = *L;
	/*Ҫ�ҵ�ѧ��Ϊnum�����ǵڼ���Ԫ�أ����������ֵ��i*/
	r = *L;
	j = 1;
	i=0;
	while(r->next)
    {
        if(!strcmp(num,r->stu.stuNum))//�ж������ַ����Ƿ����
          break;
        else
        {i++;
        r=r->next;}
    }
	while (p->next && j < i)/* ����Ѱ�ҵ�i��Ԫ�� */
	{
        p = p->next;
        ++j;
	}
	if (!(p->next) || j > i)
	    return ERROR;           /* ��i��Ԫ�ز����� */
	q = p->next;
	p->next = q->next;			/* ��q�ĺ�̸�ֵ��p�ĺ�� */

   //strcpy(e.stuNum,q->stu.stuNum);
	//*e = q->data;               /* ��q����е����ݸ�e */
	free(q);                    /* ��ϵͳ���մ˽�㣬�ͷ��ڴ� */
	printf("ɾ���ɹ���\n");
	return OK;
}
/*��ĳѧ������Ϣ�����޸ģ�����ѧ��ѧ�ţ������޸ĺ��ѧ����Ϣ
����1��ʾ��Ҫ�޸Ĵ������0��ʾ����Ҫ�޸Ĵ���������
��ʵ���޸ĵ�iλͬѧ����Ϣ*/
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

        if(!strcmp(num,p->stu.stuNum))//�ж������ַ����Ƿ����
          {
            flag=1;
            printf("����no��ʾ�����޸��Ա�����yes��ʾ��Ҫ�޸��Ա�\n");
            scanf("%s",decide);
            if(!strcmp(decide,yes))
            {
                printf("�޸��Ա�Ϊ��\n");
                scanf("%s",alSex);
                strcpy(p->stu.stuSex,alSex);
                printf("�޸��Ա�ɹ���\n");
            }
            strcpy(decide,null);

            printf("����no��ʾ�����޸ĵ绰���룬����yes��ʾ��Ҫ�޸ĵ绰����\n");
            scanf("%s",decide);
            if(!strcmp(decide,yes))
            {
                printf("�޸ĵ绰����Ϊ��\n");
                scanf("%s",alPhoneNum);
                strcpy(p->stu.phoneNum,alPhoneNum);
                printf("�޵绰����ɹ���\n");
            }
            strcpy(decide,null);
            printf("����no��ʾ������ѧ�������޸ģ�����yes��ʾ��Ҫ�޸���ѧ����\n");
            scanf("%s",decide);
            if(!strcmp(decide,yes))
            {
                printf("��ѧ�����޸�Ϊ��\n");
                scanf("%lf",&alMathScore);
                p->stu.mathScore=alMathScore;
                printf("�޸���ѧ�ɼ��ɹ���\n");
            }
            strcpy(decide,null);
            printf("����no��ʾ�������ķ������޸ģ�����yes��ʾ��Ҫ�޸����ķ���\n");
            scanf("%s",decide);
            if(!strcmp(decide,yes))
            {
                printf("���ķ����޸�Ϊ��\n");
                scanf("%lf",&alChinScore);
                p->stu.chinScore=alChinScore;
                printf("�޸����ĳɼ��ɹ���\n");
            }


          }
        p=p->next;
    }
    if(flag==0)
        printf("��ѧ������ѧ���б��У�\n");

}


/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* ������������ζ�L��ÿ������Ԫ��������Ѳ��Կ���*/
Status ListTraverse(LinkList L)
{
    int k;
    LinkList p=L->next;
    while(p)
    {
        printf("ѧ��ѧ�ţ�");printf("%s\n",p->stu.stuNum);
        printf("ѧ��������");printf("%s\n",p->stu.stuName);
        printf("ѧ���Ա�");printf("%s\n",p->stu.stuSex);
        printf("�ֻ����룺");printf("%s\n",p->stu.phoneNum);
        printf("��ѧ�ɼ���");printf("%.2lf\n",p->stu.mathScore);
        printf("���ĳɼ���");printf("%.2lf\n",p->stu.chinScore);
        printf("\n");
        p=p->next;
    }
    printf("\n");
    return OK;
}

/*��ѯĳ������ѧ�����������ѧ������ӡ��ѯ���*/
Status ListQueryNum(LinkList L,char *num)
{
    LinkList p=L->next;
    int flag=0;
    while(p)
    {

        if(!strcmp(num,p->stu.stuNum))//�������С��bScore����mScore��ѧ����Ϣ
          {
            flag=1;
            printf("ѧ��ѧ�ţ�");printf("%s\n",p->stu.stuNum);
            printf("ѧ��������");printf("%s\n",p->stu.stuName);
            printf("ѧ���Ա�");printf("%s\n",p->stu.stuSex);
            printf("��ϵ��ʽ��");printf("%s\n",p->stu.phoneNum);
            printf("��ѧ�ɼ���");printf("%.2lf\n",p->stu.mathScore);
            printf("���ĳɼ���");printf("%.2lf\n",p->stu.chinScore);
            printf("\n");
          }
        p=p->next;
    }
    if(flag==0)
        printf("��ѧ������ѧ���б��У�\n");
}

/*��ѯĳ�������Ա����������ѧ������ӡ��ѯ���*/
Status ListQuerySex(LinkList L,char *Sex)
{
    LinkList p=L->next;
    int flag=0;
	while(p)
    {

        if(!strcmp(Sex,p->stu.stuSex))//�ж������ַ����Ƿ����
          {
            flag=1;
            printf("ѧ��ѧ�ţ�");printf("%s\n",p->stu.stuNum);
            printf("ѧ��������");printf("%s\n",p->stu.stuName);
            printf("ѧ���Ա�");printf("%s\n",p->stu.stuSex);
            printf("��ϵ��ʽ��");printf("%s\n",p->stu.phoneNum);
            printf("��ѧ�ɼ���");printf("%.2lf\n",p->stu.mathScore);
            printf("���ĳɼ���");printf("%.2lf\n",p->stu.chinScore);
            printf("\n");

          }
        p=p->next;
    }
    if(flag==0)
        printf("��ѧ������ѧ���б��У�\n");
}

 int ListQuerySexNum(LinkList L,char *Sex)
{
    LinkList p=L->next;
    int number=0;
	while(p)
    {

        if(!strcmp(Sex,p->stu.stuSex))//�ж������ַ����Ƿ����
          {
            number++;
          }
        p=p->next;
    }
    return number;
}
/*��ѯ��ѧ������mathBotScore~mathUpScore,
���ķ�����chinBotScore~chinUpScore��ѧ������ӡ����Ϣ*/
Status ListQueryScore(LinkList L,double mathBotScore,double mathUpScore,double chinBotScore,double chinUpScore)
{
    LinkList p=L->next;
	while(p)
    {

        if(p->stu.mathScore>=mathBotScore&&p->stu.mathScore<=mathUpScore&&
          p->stu.chinScore>=chinBotScore&&p->stu.chinScore<=chinUpScore)//�������С��bScore����mScore��ѧ����Ϣ
          {

            printf("ѧ��ѧ�ţ�");printf("%s\n",p->stu.stuNum);
            printf("ѧ��������");printf("%s\n",p->stu.stuName);
            printf("ѧ���Ա�");printf("%s\n",p->stu.stuSex);
            printf("��ϵ��ʽ��");printf("%s\n",p->stu.phoneNum);
            printf("��ѧ�ɼ���");printf("%.2lf\n",p->stu.mathScore);
            printf("���ĳɼ���");printf("%.2lf\n",p->stu.chinScore);
            printf("\n");

          }
        p=p->next;
    }
}
//ͳ�Ʒ�������
int ListQueryScoreNum(LinkList L,double mathBotScore,double mathUpScore,double chinBotScore,double chinUpScore)
{
    LinkList p=L->next;
    int number=0;
	while(p)
    {

        if(p->stu.mathScore>=mathBotScore&&p->stu.mathScore<=mathUpScore&&
          p->stu.chinScore>=chinBotScore&&p->stu.chinScore<=chinUpScore)//�������С��bScore����mScore��ѧ����Ϣ
          {
                number++;
          }
        p=p->next;
    }
    return number;
}
/*�绰�����ѯ*/
Status ListQueryPhone(LinkList L,char * phoNum)
{
    LinkList p=L->next;
    printf("����������ѧ����Ϣ���£�\n");
    int flag=0;
    while(p)
    {

        if(!strcmp(phoNum,p->stu.phoneNum))//�������С��bScore����mScore��ѧ����Ϣ
          {
            flag=1;
            printf("ѧ��ѧ�ţ�");printf("%s\n",p->stu.stuNum);
            printf("ѧ��������");printf("%s\n",p->stu.stuName);
            printf("ѧ���Ա�");printf("%s\n",p->stu.stuSex);
            printf("��ϵ��ʽ��");printf("%s\n",p->stu.phoneNum);
            printf("��ѧ�ɼ���");printf("%.2lf\n",p->stu.mathScore);
            printf("���ĳɼ���");printf("%.2lf\n",p->stu.chinScore);
            printf("\n");

          }
        p=p->next;
    }
    if(flag==0)
        printf("��ѧ������ѧ���б��У�\n");
}


/*��ѧ�����Ӹߵ�������*/
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
        /*�����������ֹ�bug*/
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
        printf("����ѧ�ɼ������\n");
        for(i=0;i<length;i++)
        {
            printf("ѧ��ѧ�ţ�");printf("%s\n",head->stuNum);
            printf("ѧ��������");printf("%s\n",head->stuName);
            printf("ѧ���Ա�");printf("%s\n",head->stuSex);
            printf("��ϵ��ʽ��");printf("%s\n",head->phoneNum);
            printf("��ѧ�ɼ���");printf("%.2lf\n",head->mathScore);
            printf("���ĳɼ���");printf("%.2lf\n",head->chinScore);
            printf("\n");
            head=head->next;
        }
        //print(head);
}
/*���ķ����Ӹߵ�������*/
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
        /*�����������ֹ�bug*/
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
        printf("����ѧ�ɼ������\n");
        for(i=0;i<length;i++)
        {
            printf("ѧ��ѧ�ţ�");printf("%s\n",head->stuNum);
            printf("ѧ��������");printf("%s\n",head->stuName);
            printf("ѧ���Ա�");printf("%s\n",head->stuSex);
            printf("��ϵ��ʽ��");printf("%s\n",head->phoneNum);
            printf("��ѧ�ɼ���");printf("%.2lf\n",head->mathScore);
            printf("���ĳɼ���");printf("%.2lf\n",head->chinScore);
            printf("\n");
            head=head->next;
        }
}
/*�����ڵ�����д��excel���*/
void writeExcel(LinkList L) {

	FILE *fp = NULL;
	int i,length;

    LinkList p;
    p=L->next;
    length=ListLength(L);
	fp = fopen("F:\\test.xls", "w");
        fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%s\n","ѧ��","����","�Ա�","��ϵ��ʽ","��ѧ�ɼ�","���ĳɼ�");
        for (i = 0; i <length; i++) {
            fprintf(fp,"%s\t%s\t%s\t%s\t%.2lf\t%.2lf\n",p->stu.stuNum,p->stu.stuName,p->stu.stuSex,p->stu.phoneNum,p->stu.mathScore,p->stu.chinScore);
            p=p->next;
	}
	fclose(fp);

}
/*��excel���������ݵ�������*/
void readExcel(LinkList L)
{
    FILE *fp;

    int i,j ;
    struct student excelRead;
    /*char stuNum1[9];//ѧ��ѧ��
    char stuName1[10];//ѧ������
    char stuSex1[10];     //ѧ���Ա�
    char phoneNum1[12];//�ֻ�����
    double mathScore1;//��ѧ����
    double chinScore1;//���ķ���*/
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
    char Sex[10]="Ů\0";
    char phone[12]="13777396230\0";

    struct student hsr={"17041202\0","������\0","��\0","17857680092\0",96,88};
    struct student gqy={"17041201\0","����Դ\0","Ů\0","15987652918\0",99,95};
    //printf("mao\n");
    struct student amao={"17041203\0","ë����\0","Ů\0","13777396230\0",90,100};
    struct student tian={"11111111\0","���\0","��\0","11111111111\0",100,100};
    struct student *head;
    head=(struct student *)malloc(sizeof(struct student));

    i=InitList(&L);
   // i= ListInsert(&L,1,amao);
    //i= ListInsert(&L,1,hsr);
    //i= ListInsert(&L,1,gqy);
    //i=ListInsert(&L,1,tian);
    //i= ListTraverse(L);
    /*֮ǰ���Եĺۼ�*/
      //i=ListDelete(&L,num);
     //ListAlter(L,"17041202\0");
    //i=ListTraverse(L);
    //i=ListQueryNum(L,num);
    //i=ListQuerySex(L,Sex);
    //ListQueryPhone(L,phone);
    //i=ListQueryScore(L,87,96,85,89);
    //MathSort(L);
    readExcel(L);
    printf("��ӭ����ѧ������ϵͳ��\n");
    while(1)
{

    printf("����0�˳�����������1����ѧ����Ϣ�����룬����2ɾ��ѧ����Ϣ������3�޸�ѧ����Ϣ������4��ѯѧ����Ϣ������5���з�������,��ʾѧ��ͳ����Ϣ�밴6.....\n");
    scanf("%d",&choice1);
    //�˳�����
    if(choice1==0)
        break;
    //����ѧ����Ϣ����
    if(choice1==1)
    {

        printf("������ѧ��ѧ�ţ�\n");
        scanf("%s",Snum);
        strcpy(putIn.stuNum,Snum);

        printf("������ѧ��������\n");
        scanf("%s",Sname);
        strcpy(putIn.stuName,Sname);

        printf("������ѧ���Ա�\n");
        scanf("%s",Ssex);
        strcpy(putIn.stuSex,Ssex);

        printf("������ѧ���ֻ��ţ�\n");
        scanf("%s",Sphone);
        strcpy(putIn.phoneNum,Sphone);

        printf("������ѧ����ѧ�ɼ���\n");
        scanf("%lf",&Smath);
        putIn.mathScore=Smath;

        printf("������ѧ�����ĳɼ���\n");
        scanf("%lf",&Schin);
        putIn.chinScore=Schin;

        i= ListInsert(&L,1,putIn);
    }
    //ɾ������
    if(choice1==2)
    {
        printf("������Ҫɾ��ѧ����Ϣ��ѧ�ţ�\n");
        scanf("%s",Snum);
        i=ListDelete(&L,Snum);
        //printf("��Ϣ¼��ɹ���\n");
    }
    //�޸Ĺ���
    if(choice1==3)
    {
        printf("������Ҫ�޸�ѧ����Ϣ��ѧ�ţ�\n");
        scanf("%s",Snum);
        i=ListAlter(L,Snum);
    }
    //��ѯ����
    if(choice1==4)
    {
        printf("������Ҫ��ѯ�����ͣ�ͨ��ѧ�Ų�ѯ�밴1��ͨ���Ա��ѯ�밴2��ͨ��������ѯ�밴3��ͨ���绰�����ѯ�밴4����ӡ����ͬѧ��Ϣ�밴5...\n");
        scanf("%d",&choice2);
        switch(choice2)
        {
            case 1:printf("������ѧ��ѧ�ţ�\n");scanf("%s",Snum);i=ListQueryNum(L,Snum);break;
            case 2:printf("������ѧ���Ա�\n");scanf("%s",Ssex);i=ListQuerySex(L,Ssex);break;
            case 3:printf("����������ѧ����������ѧ��������-���ޣ����ķ�������-����\n");
                   scanf("%lf%lf%lf%lf",&SmathL,&SmathB,&SchinL,&SchinB);
                   i=ListQueryScore(L,SmathL,SmathB,SchinL,SchinB);break;
            case 4:printf("������Ҫ��ѯ�ĵ绰���룺\n");scanf("%s",Sphone);i=ListQueryPhone(L,Sphone);break;
            case 5:printf("����ͬѧ��Ϣ��ӡ���£�\n");i=ListTraverse(L);break;
            default:printf("error!");
        }

    }
    //����ɼ�����
    if(choice1==5)
    {
        printf("����1��ʾ��ѧ�ɼ��Ӹߵ�����������2��ʾ���ĳɼ��Ӹߵ�������\n");
        scanf("%d",&choice3);
        switch(choice3)
        {
            case 1:MathSort(L);break;
            case 2:ChinSort(L);break;
            defalut:printf("error");
        }
    }
    //ͳ�ƹ���
    if(choice1==6)
    {
        Sum=ListLength(L);
        printf("__________________________________________________________________________________________\n");
        printf("��������Ϊ��%d\n",Sum);

        sumMale=ListQuerySexNum(L,"��");
        sumFemale=Sum-sumMale;
        printf("��Ů����Ϊ   �У�Ů=%d :%d=%.2lf\n",sumMale,sumFemale,(double)sumMale/(double)sumFemale);

        printf("����������ٷֱȼ��㣺\n");

        failMathNum=ListQueryScoreNum(L,0,59,0,100);
        printf("��ѧ:\n������������%d/%d=%.2lf\n",failMathNum,Sum,(double)failMathNum/(double)Sum);
        mathNum6_7=ListQueryScoreNum(L,60,69,0,100);
        printf("��ѧ������60��69֮���������%d/%d=%.2lf\n",mathNum6_7,Sum,(double)mathNum6_7/(double)Sum);
        mathNum7_8=ListQueryScoreNum(L,70,79,0,100);
        printf("��ѧ������70��79֮���������%d/%d=%.2lf\n",mathNum7_8,Sum,(double)mathNum7_8/(double)Sum);
        mathNum8_9=ListQueryScoreNum(L,80,89,0,100);
        printf("��ѧ������80��89֮���������%d/%d=%.2lf\n",mathNum8_9,Sum,(double)mathNum8_9/(double)Sum);
        mathNum9_10=ListQueryScoreNum(L,90,99,0,100);
        printf("��ѧ������90��99֮���������%d/%d=%.2lf\n",mathNum9_10,Sum,(double)mathNum9_10/(double)Sum);
        mathNum10=ListQueryScoreNum(L,100,100,0,100);
        printf("��ѧ����Ϊ���ֵ�����Ϊ��%d/%d=%.2lf\n",mathNum10,Sum,(double)mathNum10/(double)Sum);

        failChinNum=ListQueryScoreNum(L,0,100,0,59);
        printf("����:\n������������%d/%d=%.2lf\n",failChinNum,Sum,(double)failChinNum/(double)Sum);
        chinNum6_7=ListQueryScoreNum(L,0,100,60,69);
        printf("���ķ�����60��69֮���������%d/%d=%.2lf\n",chinNum6_7,Sum,(double)chinNum6_7/(double)Sum);
        chinNum7_8=ListQueryScoreNum(L,0,100,70,79);
        printf("���ķ�����70��79֮���������%d/%d=%.2lf\n",chinNum7_8,Sum,(double)chinNum7_8/(double)Sum);
        chinNum8_9=ListQueryScoreNum(L,0,100,80,89);
        printf("���ķ�����80��89֮���������%d/%d=%.2lf\n",chinNum8_9,Sum,(double)chinNum8_9/(double)Sum);
        chinNum9_10=ListQueryScoreNum(L,0,100,90,99);
        printf("���ķ�����90��99֮���������%d/%d=%.2lf\n",chinNum9_10,Sum,(double)chinNum9_10/(double)Sum);
        chinNum10=ListQueryScoreNum(L,0,100,100,100);
        printf("���ķ���Ϊ���ֵ�����Ϊ��%d/%d=%.2lf\n",chinNum10,Sum,(double)chinNum10/(double)Sum);


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
    printf("�����������л����ʹ�ã�\n");
    return 0;
}
