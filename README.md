# DateStructureCodeSource
数据结构代码存储
## 数据结构大作业思路过程

> 悔恨万分的是之前的几个需求的实现的过程都忘记记录下来了，完全凭着感觉在做作业，汪汪汪。

### 第四个需求：修改学生信息
-  `ListAlter(L,2);` 先以i代替学号实现修改学生的性别（已实现）
这一步的具体实现方法：输入1表示需要修改，输入0 表示跳过选修。
-  下一步再通过输入学生学号来修改学生性别。
(刚刚想开始继续数据结构大作业，就听到了噩耗，金庸走了，桌上还放着先生的雪山飞狐，飞雪连天射白鹿，笑书神侠倚碧鸳，先生走好)
- 生命在不断地找bug中变得更加坚不可摧。汪汪汪。
### 第五个需求：将学生的信息按照某种方式排序
- 今天又改了一个bug哈哈哈，希望这真的是最后一个bug。
- 链表排序，思路来源于书上的链表的插入排序法。一开始我竟然想直接按照书上的对我的链表进行排序，后来的后来，我发现自己太年轻，于是先把书上的东西把两个函数改成了一个函=函数，放在了同一个main函数里面，嘻嘻嘻，然后终于可以了我的妈妈咪。书上代码修改如下：
```
#include<stdio.h>
#include<stdlib.h>
struct student
{
    char name[10];
    float score;
    struct student *next;
};
void print(struct student *head)
{
    struct student *p=head;
    while(p!=NULL)
    {
        printf("%s %1.f\n",p->name,p->score);
        p=p->next;
    }
}
int main()
{
    struct student *head;

    struct student *p,*pnew,*pold;
    pnew=(struct student *)malloc(sizeof(struct student));

    int i,n;
    printf("INPUT THE NUMBER:\n");
    scanf("%d",&n);
    printf("IN PUT NODES:\n");
    head=(struct student *)malloc(sizeof(struct student));
    scanf("%s%f",head->name,&head->score);
    head->next=NULL;
    for(i=0;i<n;i++)
    {
        pnew=(struct student *)malloc(sizeof(struct student));
        scanf("%s%f",pnew->name,&pnew->score);
        p=head;
        if(pnew->score>=head->score){
            pnew->next=head;
            head=pnew;
            //printf("1");
        }
        else{
            while(p!=NULL&&pnew->score<p->score){
                pold=p;
                p=p->next;
            }
            pnew->next=p;
            pold->next=pnew;
        }

    }
    print(head);
}
```
然后我把这段代码再迁移到这个大作业里面，值得注意的是，这里面有一个bug，那就是有一个地方的>应该改为>=
### 下面是测试的过程（CiJi）
#### 输入1进行学生信息的录入
还可以改进的地方：录入完学生的信息应该让其显示录入成功！
#### 输入3修改学生信息
- no和yes那里改一改
- 修改语文成功的时候后面加上一个\0
- 大物是什饿垃圾玩意儿啊
- 这个过程文档好潦草随性鸭，没有什么能够阻挡，我对自由的向往..........
