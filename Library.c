#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)

typedef struct _MEMBER {
    char m_name[20];
    char m_tel[12];
    int m_birth;
 } Member;

typedef struct _BOOK {
    char b_title[50];
    char b_writer[50];
    char b_publish[20];
    char b_chkout;
} Book;

typedef struct _STATUS {
    Member s_member;
    Book s_book;
    int s_chkoutDate;
    int s_retDate;
    char s_isret;
} Status;


void showBookList();
void chkoutB();
void returnB();
void showStatus();
void updateStatus(int bidx, int midx);


Member mymem[100] = { { "ȫ�浿", "01012345678", 19990101 }, { "�̼���", "01013572468", 19950227 },
                        { "������", "01011223344", 19970314 }, { "�輼��", "01098765432", 20021009 },
                        { "�念��", "01011111111", 20000722 } , { 0, 0, 0 } };

Book mybook[100] = { { "Ʈ���� �ڸ��� 2022", "�賭��, ���ؿ� ��", "�̷���â", 0 }, { "�Ųٷ� �д� �����", "���ù�", "������", 1 },
                    { "�׳� ���� ����", "�۱濵", "�Ͻ���", 0 }, { "�޷���Ʈ �� ��ȭ�� 2", "�̹̿�", "���丮����", 0 },
                    { "4~7������ �߿��� �ñ�� �����ϴ�", "���Ӽ�", "ī�ÿ����", 0 }, { "�ֽ����� �����Ģ", "�ڿ���", "���ÿ�", 0 },
                    { "�޺��� �����ϰ� �λ��� ���ϴϱ��", "����", "�迵��", 0 }, { "�λ��� �����̴�", "�ſ���, �־��", "�������", 0 },
                    { "��, �̰߰� ����ϰ� ������ �ٷ���", "�ӵ巹 �ڽ�����", "�̷���â", 0 },
                    { "���� ��, ���迡�� �� ����� ������� �ص�", "��ġ�� �̻�Ű / �ǿ��� ��", "���", 0 }, { 0, 0, 0, 0} };

Status mystatus[50] = { {{"�̼���", "01013572468", 19950227 }, { "�׳� ���� ����", "�۱濵", "�Ͻ���", 1 }, 20211030, 20211103, 1}, 
                        {{"������", "01011223344", 19970314 }, { "�Ųٷ� �д� �����", "���ù�", "������", 1 }, 20211101, 0, 0},
                        {{0, 0, 0}, { 0, 0, 0, 0 }, 0, 0, 0}, };


int main()
{
    while (1) 
    {
        int input = 0;
        printf("�� ���� ���� �ý��� ��\n");
        printf("1. ���� ���� ��� ���\n");
        printf("2. �����ϱ�\n");
        printf("3. �ݳ��ϱ�\n");
        printf("4. ���� ��Ȳ ���\n");
        printf("5. ����\n\n");
        printf("-> ���Ͻô� �޴��� �����ϼ��� (���� �Է�) : ");

        scanf("%d", &input);

        switch (input)
        {
        case 1:
            showBookList();
            break;
        case 2:
            chkoutB();
            break;
        case 3:
            returnB();
            break;
        case 4:
            showStatus();
            break;
        case 5:
            printf("���α׷��� �����մϴ�.\n\n");
            exit(0);
        default:
            printf("�߸��� �Է��Դϴ�.\n\n");
            break;
        }
    }

}

void showBookList()
{
    for (int i = 0; i < 100; i++)
    {
        if (!mybook[i].b_title[0]) break;

        printf("- %s �� %s �� %s �� ", mybook[i].b_title, mybook[i].b_writer, mybook[i].b_publish);

        if (mybook[i].b_chkout)
            printf("������\n");
        else
            printf("����\n");
    }
    printf("\n\n");
}

void chkoutB() 
{
    char search[50] = { 0, };
    char name[20] = { 0, };
    int findlist[10] = { 0, };
    int findbook = 0;
    int idx = 0, num = 1;

    printf("������ ������ �˻��ϼ���. : ");
    getchar();
    fgets(search, sizeof(char) * 50, stdin);

    if (search[strlen(search) - 1] == '\n')
        search[strlen(search) - 1] = 0;

    printf("\n");

    for (int i = 0; i < 100; i++)
    {
        if (!mybook[i].b_title[0]) break;
        
        if (strstr(mybook[i].b_title, search)) {
            findlist[idx] = i;
            
            printf("%d. %s �� %s �� %s �� ", idx + 1, mybook[i].b_title, mybook[i].b_writer, mybook[i].b_publish);

            if (mybook[i].b_chkout)
                printf("������\n");
            else
                printf("����\n");

            idx++;
        }
    }

    while (1) {
        printf("\n ������ ������ ��ȣ�� �Է��ϼ���. : ");
        scanf("%d", &num);

        if (num > idx || mybook[findlist[num - 1]].b_chkout) {
            printf("������ �� ���� �����Դϴ�.\n");
            return;
        }
        else break;
    }
    findbook = findlist[num - 1];       // mybook�� �ε��� ����

    printf("\n");

    getchar();
    printf("������ �Է��ϼ���. : ");
    fgets(name, sizeof(char) * 20, stdin);

    if (name[strlen(name) - 1] == '\n')
        name[strlen(name) - 1] = 0;

    for (int i = 0; i < 100; i++)
    {
        if (!mymem[i].m_name[0]) {
            printf("�������� �ʴ� ȸ���Դϴ�.\n\n");
            break;
        }

        if (!strcmp(mymem[i].m_name, name)) {
            updateStatus(findbook, i);
            printf("������ �Ϸ�Ǿ����ϴ�.\n\n");
            break;
        }
    }
}

void returnB()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char name[20] = { 0, };
    int chkoutlist[10] = { 0, };
    int idx = 0, num = 1;

    getchar();
    printf("������ �Է��ϼ���. : ");
    fgets(name, sizeof(char) * 20, stdin);

    if (name[strlen(name) - 1] == '\n')
        name[strlen(name) - 1] = 0;

    for (int i = 0; i < 50; i++)
    {
        if (!mystatus[i].s_book.b_title[0] && !chkoutlist[0] && !chkoutlist[1]) {
            printf("�������� �������� �ʽ��ϴ�.\n\n");
            break;
        }

        if (!strcmp(mystatus[i].s_member.m_name, name) && !mystatus[i].s_isret) {
            chkoutlist[idx] = i;
            printf("%d. %s �� %s �� %s\n", idx + 1, mystatus[i].s_book.b_title,
                        mystatus[i].s_book.b_writer, mystatus[i].s_book.b_publish);
            idx++;
        }
    }

    while (1) {
        printf("\n �ݳ��� ������ ��ȣ�� �Է��ϼ���. : ");
        scanf("%d", &num);

        if (num > idx || mystatus[chkoutlist[num - 1]].s_isret)
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
        else break;
    }

    mystatus[chkoutlist[num - 1]].s_isret = 1;
    mystatus[chkoutlist[num - 1]].s_retDate = (tm.tm_year + 1900) * 10000 + (tm.tm_mon + 1) * 100 + tm.tm_mday;
    mystatus[chkoutlist[num - 1]].s_book.b_chkout = 0;

    for (int i = 0; i < 100; i++)
    {
        if (!mybook[i].b_title[0]) break;

        if (!strcmp(mybook[i].b_title, mystatus[chkoutlist[num - 1]].s_book.b_title)) {
            mybook[i].b_chkout = 0;
        }
    }
    printf("�ݳ��� �Ϸ�Ǿ����ϴ�.\n\n");
    //showStatus();
}

void showStatus()
{
    for (int i = 0; i < 100; i++)
    {
        if (!mystatus[i].s_chkoutDate) break;

        printf("- %s �� %s(%s) �� %d ", mystatus[i].s_book.b_title, mystatus[i].s_member.m_name,
                                        mystatus[i].s_member.m_tel, mystatus[i].s_chkoutDate);

        if (!mystatus[i].s_isret)
            printf("�� ������\n");
        else
            printf("�� %d\n", mystatus[i].s_retDate);
    }
    printf("\n\n");
}

void updateStatus(int bidx, int midx)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    Status* bp = mystatus;
    int date = 0;

    while (bp->s_chkoutDate)
        bp++;

    strcpy(bp->s_member.m_name, mymem[midx].m_name);
    strcpy(bp->s_member.m_tel, mymem[midx].m_tel);
    bp->s_member.m_birth = mymem[midx].m_birth;

    strcpy(bp->s_book.b_title, mybook[bidx].b_title);
    strcpy(bp->s_book.b_writer, mybook[bidx].b_writer);
    strcpy(bp->s_book.b_publish, mybook[bidx].b_publish);
    bp->s_book.b_chkout = 1;
    mybook[bidx].b_chkout = 1;

    bp->s_chkoutDate = (tm.tm_year + 1900) * 10000 + (tm.tm_mon + 1) * 100 + tm.tm_mday;
    //bp->s_retDate = 0;
    bp->s_isret = 0;

    //showStatus();
}