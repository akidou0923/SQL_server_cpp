#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include <iostream>
using namespace std;
#define MAXSIZE 10000   //线性表的最大可能长度 


//学生信息的定义：
typedef int Status;
typedef struct
{
    char no[8];   //8位学号
    char name[20]; //姓名
    int rank;     //成绩
}Student;

//顺序表的定义：
typedef  struct
{
    Student* elem;     //指向数据元素的基地址
    int  length;       //线性表的当前长度 
}SqList;


//初始化顺序表
Status InitList(SqList& L)
{
    L.elem = new Student[MAXSIZE];
    if (!L.elem)
    {
        printf("顺序表初始化失败！\n");
        return 0;
    }
    L.length = 0;
    printf("顺序表初始化成功！\n");
    return 1;
}

// 在第i个位置上插入新的元素（值为e），并使原来的第i个元素至最后一个元素的
//序号依次加1。插入成功返回1，否则为0
Status Insert(SqList& L, int i, Student e)
{
    if ((i < 1) || (i > L.length + 2))   //i值不合法
    {
        printf("i值不合法！\n");
        return 0;
    }
    if (L.length == MAXSIZE)   //当前存储空间已满
    {
        printf("当前存储空间已满！\n");
        return 0;
    }
    for (int j = L.length; j >= i; j--)
    {
        L.elem[j + 1] = L.elem[j];
    }
    L.elem[i] = e;
    ++L.length;
    return 1;
}

//显示信息
Student GetElem(SqList L, int i, Student& e)
{
    return L.elem[i];
}

Status find(SqList L, int i, Student e)
{
    for (i = 1; i < L.length; i++)
        if (strcmp(L.elem[i].name, e.name) == 0)return i;
    return 0;
}

Status Remove(SqList L, int i, Student e)
// 若第i个元素存在，删除并将其值放入e指向的空间, 函数返回1; 若i非法，则删除失败，返回0。
{
    if ((i < 1) || (i > L.length + 1))
    {
        printf("i值不合法");
        return 0;
    }
    for (int j = i; j <= L.length; j++)
        L.elem[j - 1] = L.elem[j];
    return 1;
}

void Output(Student* e)//输出元素
{
    printf("学号:%s\n姓名:%s\n成绩:%d\n\n", e->no, e->name, e->rank);
}

//此处为直接插入排序。对姓名排序
void InsertSort(SqList L)
{
    for (int i = 2; i <= L.length; i++)
        if (strcmp(L.elem[i].name, L.elem[i - 1].name) < 0)
        {
            L.elem[0] = L.elem[i];
            L.elem[i] = L.elem[i - 1];
            int j;
            for (j = i - 2; strcmp(L.elem[0].name, L.elem[j].name) < 0; j--)
                L.elem[j + 1] = L.elem[j];
            L.elem[j + 1] = L.elem[0];
        }
}

//此处为折半插入排序。对姓名排序
void BInsertSort(SqList L)
{
    for (int i = 2; i <= L.length; i++)
    {
        L.elem[0] = L.elem[i];
        int low = 1, high = i - 1;
        while (low <= high)
        {
            int m = (low + high) / 2;
            if (strcmp(L.elem[0].name, L.elem[m].name) < 0) high = m - 1;
            else low = m + 1;
        }
        for (int j = i - 1; j >= high + 1; --j) L.elem[j + 1] = L.elem[j];
        L.elem[high + 1] = L.elem[0];
    }
}

//快速排序（学号）
int Patition(SqList L, int low, int high)
{
    L.elem[0] = L.elem[low];                //用第一个记录作枢轴记录
    char* pivotkey = L.elem[low].no;      //枢轴记录关键字
    while (low < high)
    {              //从表的两端向中间扫描
        while (low < high && L.elem[high].no >= pivotkey)
            --high;
        L.elem[low] = L.elem[high];         //将比枢轴小的记录移动到低端
        while (low < high && L.elem[low].no <= pivotkey)
            ++low;
        L.elem[high] = L.elem[low];         //将比枢轴大的记录移动到高端
    }
    L.elem[low] = L.elem[0];                //枢轴记录到位
    return low;                       //返回枢轴位置
}

void QSort(SqList L, int low, int high)
{
    //对表L中的子序列L.r[low...high]做快速排序
    if (low < high) {
        int pivotloc = Patition(L, low, high); //一分为二
        QSort(L, low, pivotloc - 1);           //对低子表递归排序
        QSort(L, pivotloc + 1, high);          //对高子表递归排序
    }
}
void QuickSort(SqList L)
{
    //对表L做快速排序
    QSort(L, 1, L.length);
}


int main()
{
    //初始化链表
    SqList L;
    int i, n, choose;
    Student st, nt, e;
    InitList(L);

    //插入数据
    printf("请输入要录入学生的人数:");
    scanf_s("%d", &n);
    for (i = 1; i < n + 1; i++)
    {
        printf("第%d个学生:\n", i + 1);
        printf("请输入要录入学生的学号:");
        scanf_s("%s", st.no, 8);
        printf("请输入要录入学生的姓名:");
        scanf_s("%s", st.name, 20);
        printf("请输入要录入学生的成绩:");
        scanf_s("%d", &st.rank);
        if (Insert(L, i, st))
            printf("Success!\n");
        else
            printf("Flase!\n");
    }
    L.length = n;


    printf("\n已成功写入信息，请选择需要进行的操作：\n");
    printf("1.显示所有学生信息\n");
    printf("2.根据姓名进行查找\n");
    printf("3.显示指定的位置学生信息\n");
    printf("4.在指定位置插入学生信息\n");
    printf("5.删除指定位置的学生记录\n");
    printf("6.统计学生人数\n");
    printf("7.利用直接插入排序或者折半插入排序按照姓名进行排序\n");
    printf("8.利用快速排序按照学号进行排序\n");
    printf("0.退出\n\n");
    while (1)
    {
        printf("请选择要进行的操作：");
        scanf("%d", &choose);
        if (choose == 0) break;
        switch (choose)
        {
        case 1://显示学生信息
            for (int i = 1; i < L.length + 1; i++)
            {
                e = GetElem(L, i, nt);
                Output(&e);
            }
            break;

        case 2://根据姓名查找数据 
            n = 1;
            while (n)
            {
                printf("请输入要查找的学生姓名:");
                scanf_s("%s", st.name, 20);
                if (find(L, i, st) != 0)
                    Output(&L.elem[find(L, i, st)]);
                else
                    printf("not found! \n");
                printf("请问是否还需要查找？1/0:");
                scanf_s("%d", &n);
            }
            break;

        case 3://根据位置查找
            n = 1;
            while (n)
            {
                int sus;
                printf("请输入要查找的位置:");
                scanf_s("%d", &sus);
                e = GetElem(L, sus - 1, nt);
                Output(&e);
                printf("请问是否还需要查找？1/0:");
                scanf_s("%d", &n);
            }
            break;

        case 4://在任意位置插入信息
            printf("是否需要插入信息？1/0:");
            scanf_s("%d", &n);
            while (n)
            {
                printf("请输入要录入学生的位置:");
                scanf_s("%d", &i);
                printf("请输入要录入学生的学号:");
                scanf_s("%s", st.no, 8);
                printf("请输入要录入学生的姓名:");
                scanf_s("%s", st.name, 20);
                printf("请输入要录入学生的成绩:");
                scanf_s("%d", &st.rank);
                if (Insert(L, i - 1, st))printf("success!");
                else printf("false!");
                printf("请问是否还需要插入？1/0:");
                scanf_s("%d", &n);
            }
            printf("是否显示所有信息？1/0:");
            scanf_s("%d", &n);
            if (n)
                for (int i = 1; i < L.length + 1; i++)
                {
                    e = GetElem(L, i, nt);
                    Output(&e);
                }
            break;

        case 5://在任意位置删除信息
            printf("是否需要删除信息？1/0:");
            scanf_s("%d", &n);
            while (n)
            {
                printf("请输入需要删除的位置:");
                scanf_s("%d", &n);
                if (Remove(L, n, st))
                {
                    printf("success! \n");
                    L.length--;
                }
                else
                    printf("false! \n");
                printf("请问是否还需要删除？1/0:");
                scanf_s("%d", &n);
            }
            printf("是否显示所有信息？1/0:");
            scanf_s("%d", &n);
            if (n)
                for (int i = 1; i < L.length + 1; i++)
                {
                    e = GetElem(L, i, nt);
                    Output(&e);
                }
            break;

        case 6://统计
            printf("已录入的学生个数为:%d\n", L.length);
            break;

        case 7://按照姓名进行排序
            printf("请输入要进行排序的方式:\n1.直接插入\n2.折半插入\n");
            scanf_s("%d", &n);
            if (n == 1)
            {
                InsertSort(L);
                for (int i = 1; i < L.length + 1; i++)
                {
                    e = GetElem(L, i, nt);
                    Output(&e);
                }
            }
            else
            {
                BInsertSort(L);
                for (int i = 1; i < L.length + 1; i++)
                {
                    e = GetElem(L, i, nt);
                    Output(&e);
                }
            }                            
            break;
        case 8:QuickSort(L);
            printf("按学号进行快速排序为\n");
            for (int i = 1; i < L.length + 1; i++)
            {
                e = GetElem(L, i, nt);
                Output(&e);
            }
            break;
        }

    }
}