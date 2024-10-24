#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include <iostream>
using namespace std;
#define MAXSIZE 10000   //���Ա�������ܳ��� 


//ѧ����Ϣ�Ķ��壺
typedef int Status;
typedef struct
{
    char no[8];   //8λѧ��
    char name[20]; //����
    int rank;     //�ɼ�
}Student;

//˳���Ķ��壺
typedef  struct
{
    Student* elem;     //ָ������Ԫ�صĻ���ַ
    int  length;       //���Ա�ĵ�ǰ���� 
}SqList;


//��ʼ��˳���
Status InitList(SqList& L)
{
    L.elem = new Student[MAXSIZE];
    if (!L.elem)
    {
        printf("˳����ʼ��ʧ�ܣ�\n");
        return 0;
    }
    L.length = 0;
    printf("˳����ʼ���ɹ���\n");
    return 1;
}

// �ڵ�i��λ���ϲ����µ�Ԫ�أ�ֵΪe������ʹԭ���ĵ�i��Ԫ�������һ��Ԫ�ص�
//������μ�1������ɹ�����1������Ϊ0
Status Insert(SqList& L, int i, Student e)
{
    if ((i < 1) || (i > L.length + 2))   //iֵ���Ϸ�
    {
        printf("iֵ���Ϸ���\n");
        return 0;
    }
    if (L.length == MAXSIZE)   //��ǰ�洢�ռ�����
    {
        printf("��ǰ�洢�ռ�������\n");
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

//��ʾ��Ϣ
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
// ����i��Ԫ�ش��ڣ�ɾ��������ֵ����eָ��Ŀռ�, ��������1; ��i�Ƿ�����ɾ��ʧ�ܣ�����0��
{
    if ((i < 1) || (i > L.length + 1))
    {
        printf("iֵ���Ϸ�");
        return 0;
    }
    for (int j = i; j <= L.length; j++)
        L.elem[j - 1] = L.elem[j];
    return 1;
}

void Output(Student* e)//���Ԫ��
{
    printf("ѧ��:%s\n����:%s\n�ɼ�:%d\n\n", e->no, e->name, e->rank);
}

//�˴�Ϊֱ�Ӳ������򡣶���������
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

//�˴�Ϊ�۰�������򡣶���������
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

//��������ѧ�ţ�
int Patition(SqList L, int low, int high)
{
    L.elem[0] = L.elem[low];                //�õ�һ����¼�������¼
    char* pivotkey = L.elem[low].no;      //�����¼�ؼ���
    while (low < high)
    {              //�ӱ���������м�ɨ��
        while (low < high && L.elem[high].no >= pivotkey)
            --high;
        L.elem[low] = L.elem[high];         //��������С�ļ�¼�ƶ����Ͷ�
        while (low < high && L.elem[low].no <= pivotkey)
            ++low;
        L.elem[high] = L.elem[low];         //���������ļ�¼�ƶ����߶�
    }
    L.elem[low] = L.elem[0];                //�����¼��λ
    return low;                       //��������λ��
}

void QSort(SqList L, int low, int high)
{
    //�Ա�L�е�������L.r[low...high]����������
    if (low < high) {
        int pivotloc = Patition(L, low, high); //һ��Ϊ��
        QSort(L, low, pivotloc - 1);           //�Ե��ӱ�ݹ�����
        QSort(L, pivotloc + 1, high);          //�Ը��ӱ�ݹ�����
    }
}
void QuickSort(SqList L)
{
    //�Ա�L����������
    QSort(L, 1, L.length);
}


int main()
{
    //��ʼ������
    SqList L;
    int i, n, choose;
    Student st, nt, e;
    InitList(L);

    //��������
    printf("������Ҫ¼��ѧ��������:");
    scanf_s("%d", &n);
    for (i = 1; i < n + 1; i++)
    {
        printf("��%d��ѧ��:\n", i + 1);
        printf("������Ҫ¼��ѧ����ѧ��:");
        scanf_s("%s", st.no, 8);
        printf("������Ҫ¼��ѧ��������:");
        scanf_s("%s", st.name, 20);
        printf("������Ҫ¼��ѧ���ĳɼ�:");
        scanf_s("%d", &st.rank);
        if (Insert(L, i, st))
            printf("Success!\n");
        else
            printf("Flase!\n");
    }
    L.length = n;


    printf("\n�ѳɹ�д����Ϣ����ѡ����Ҫ���еĲ�����\n");
    printf("1.��ʾ����ѧ����Ϣ\n");
    printf("2.�����������в���\n");
    printf("3.��ʾָ����λ��ѧ����Ϣ\n");
    printf("4.��ָ��λ�ò���ѧ����Ϣ\n");
    printf("5.ɾ��ָ��λ�õ�ѧ����¼\n");
    printf("6.ͳ��ѧ������\n");
    printf("7.����ֱ�Ӳ�����������۰����������������������\n");
    printf("8.���ÿ���������ѧ�Ž�������\n");
    printf("0.�˳�\n\n");
    while (1)
    {
        printf("��ѡ��Ҫ���еĲ�����");
        scanf("%d", &choose);
        if (choose == 0) break;
        switch (choose)
        {
        case 1://��ʾѧ����Ϣ
            for (int i = 1; i < L.length + 1; i++)
            {
                e = GetElem(L, i, nt);
                Output(&e);
            }
            break;

        case 2://���������������� 
            n = 1;
            while (n)
            {
                printf("������Ҫ���ҵ�ѧ������:");
                scanf_s("%s", st.name, 20);
                if (find(L, i, st) != 0)
                    Output(&L.elem[find(L, i, st)]);
                else
                    printf("not found! \n");
                printf("�����Ƿ���Ҫ���ң�1/0:");
                scanf_s("%d", &n);
            }
            break;

        case 3://����λ�ò���
            n = 1;
            while (n)
            {
                int sus;
                printf("������Ҫ���ҵ�λ��:");
                scanf_s("%d", &sus);
                e = GetElem(L, sus - 1, nt);
                Output(&e);
                printf("�����Ƿ���Ҫ���ң�1/0:");
                scanf_s("%d", &n);
            }
            break;

        case 4://������λ�ò�����Ϣ
            printf("�Ƿ���Ҫ������Ϣ��1/0:");
            scanf_s("%d", &n);
            while (n)
            {
                printf("������Ҫ¼��ѧ����λ��:");
                scanf_s("%d", &i);
                printf("������Ҫ¼��ѧ����ѧ��:");
                scanf_s("%s", st.no, 8);
                printf("������Ҫ¼��ѧ��������:");
                scanf_s("%s", st.name, 20);
                printf("������Ҫ¼��ѧ���ĳɼ�:");
                scanf_s("%d", &st.rank);
                if (Insert(L, i - 1, st))printf("success!");
                else printf("false!");
                printf("�����Ƿ���Ҫ���룿1/0:");
                scanf_s("%d", &n);
            }
            printf("�Ƿ���ʾ������Ϣ��1/0:");
            scanf_s("%d", &n);
            if (n)
                for (int i = 1; i < L.length + 1; i++)
                {
                    e = GetElem(L, i, nt);
                    Output(&e);
                }
            break;

        case 5://������λ��ɾ����Ϣ
            printf("�Ƿ���Ҫɾ����Ϣ��1/0:");
            scanf_s("%d", &n);
            while (n)
            {
                printf("��������Ҫɾ����λ��:");
                scanf_s("%d", &n);
                if (Remove(L, n, st))
                {
                    printf("success! \n");
                    L.length--;
                }
                else
                    printf("false! \n");
                printf("�����Ƿ���Ҫɾ����1/0:");
                scanf_s("%d", &n);
            }
            printf("�Ƿ���ʾ������Ϣ��1/0:");
            scanf_s("%d", &n);
            if (n)
                for (int i = 1; i < L.length + 1; i++)
                {
                    e = GetElem(L, i, nt);
                    Output(&e);
                }
            break;

        case 6://ͳ��
            printf("��¼���ѧ������Ϊ:%d\n", L.length);
            break;

        case 7://����������������
            printf("������Ҫ��������ķ�ʽ:\n1.ֱ�Ӳ���\n2.�۰����\n");
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
            printf("��ѧ�Ž��п�������Ϊ\n");
            for (int i = 1; i < L.length + 1; i++)
            {
                e = GetElem(L, i, nt);
                Output(&e);
            }
            break;
        }

    }
}