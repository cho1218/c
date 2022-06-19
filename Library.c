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


Member mymem[100] = { { "홍길동", "01012345678", 19990101 }, { "이순신", "01013572468", 19950227 },
                        { "강감찬", "01011223344", 19970314 }, { "김세종", "01098765432", 20021009 },
                        { "장영실", "01011111111", 20000722 } , { 0, 0, 0 } };

Book mybook[100] = { { "트렌드 코리아 2022", "김난도, 이준영 외", "미래의창", 0 }, { "거꾸로 읽는 세계사", "유시민", "돌베개", 1 },
                    { "그냥 하지 말라", "송길영", "북스톤", 0 }, { "달러구트 꿈 백화점 2", "이미예", "팩토리나인", 0 },
                    { "4~7세보다 중요한 시기는 없습니다", "이임숙", "카시오페아", 0 }, { "주식투자 절대원칙", "박영옥", "센시오", 0 },
                    { "햇빛은 찬란하고 인생은 귀하니까요", "장명숙", "김영사", 0 }, { "인생은 실전이다", "신영준, 주언규", "상상스퀘어", 0 },
                    { "돈, 뜨겁게 사랑하고 차갑게 다루어라", "앙드레 코스톨라니", "미래의창", 0 },
                    { "오늘 밤, 세계에서 이 사랑이 사라진다 해도", "이치조 미사키 / 권영주 역", "모모", 0 }, { 0, 0, 0, 0} };

Status mystatus[50] = { {{"이순신", "01013572468", 19950227 }, { "그냥 하지 말라", "송길영", "북스톤", 1 }, 20211030, 20211103, 1}, 
                        {{"강감찬", "01011223344", 19970314 }, { "거꾸로 읽는 세계사", "유시민", "돌베개", 1 }, 20211101, 0, 0},
                        {{0, 0, 0}, { 0, 0, 0, 0 }, 0, 0, 0}, };


int main()
{
    while (1) 
    {
        int input = 0;
        printf("♥ 도서 관리 시스템 ♥\n");
        printf("1. 보유 도서 목록 출력\n");
        printf("2. 대출하기\n");
        printf("3. 반납하기\n");
        printf("4. 대출 현황 출력\n");
        printf("5. 종료\n\n");
        printf("-> 원하시는 메뉴를 선택하세요 (숫자 입력) : ");

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
            printf("프로그램을 종료합니다.\n\n");
            exit(0);
        default:
            printf("잘못된 입력입니다.\n\n");
            break;
        }
    }

}

void showBookList()
{
    for (int i = 0; i < 100; i++)
    {
        if (!mybook[i].b_title[0]) break;

        printf("- %s ● %s ● %s ● ", mybook[i].b_title, mybook[i].b_writer, mybook[i].b_publish);

        if (mybook[i].b_chkout)
            printf("대출중\n");
        else
            printf("보유\n");
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

    printf("대출할 도서를 검색하세요. : ");
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
            
            printf("%d. %s ● %s ● %s ● ", idx + 1, mybook[i].b_title, mybook[i].b_writer, mybook[i].b_publish);

            if (mybook[i].b_chkout)
                printf("대출중\n");
            else
                printf("보유\n");

            idx++;
        }
    }

    while (1) {
        printf("\n 대출할 도서의 번호를 입력하세요. : ");
        scanf("%d", &num);

        if (num > idx || mybook[findlist[num - 1]].b_chkout) {
            printf("대출할 수 없는 도서입니다.\n");
            return;
        }
        else break;
    }
    findbook = findlist[num - 1];       // mybook의 인덱스 저장

    printf("\n");

    getchar();
    printf("성함을 입력하세요. : ");
    fgets(name, sizeof(char) * 20, stdin);

    if (name[strlen(name) - 1] == '\n')
        name[strlen(name) - 1] = 0;

    for (int i = 0; i < 100; i++)
    {
        if (!mymem[i].m_name[0]) {
            printf("존재하지 않는 회원입니다.\n\n");
            break;
        }

        if (!strcmp(mymem[i].m_name, name)) {
            updateStatus(findbook, i);
            printf("대출이 완료되었습니다.\n\n");
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
    printf("성함을 입력하세요. : ");
    fgets(name, sizeof(char) * 20, stdin);

    if (name[strlen(name) - 1] == '\n')
        name[strlen(name) - 1] = 0;

    for (int i = 0; i < 50; i++)
    {
        if (!mystatus[i].s_book.b_title[0] && !chkoutlist[0] && !chkoutlist[1]) {
            printf("대출목록이 존재하지 않습니다.\n\n");
            break;
        }

        if (!strcmp(mystatus[i].s_member.m_name, name) && !mystatus[i].s_isret) {
            chkoutlist[idx] = i;
            printf("%d. %s ● %s ● %s\n", idx + 1, mystatus[i].s_book.b_title,
                        mystatus[i].s_book.b_writer, mystatus[i].s_book.b_publish);
            idx++;
        }
    }

    while (1) {
        printf("\n 반납할 도서의 번호를 입력하세요. : ");
        scanf("%d", &num);

        if (num > idx || mystatus[chkoutlist[num - 1]].s_isret)
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
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
    printf("반납이 완료되었습니다.\n\n");
    //showStatus();
}

void showStatus()
{
    for (int i = 0; i < 100; i++)
    {
        if (!mystatus[i].s_chkoutDate) break;

        printf("- %s ● %s(%s) ● %d ", mystatus[i].s_book.b_title, mystatus[i].s_member.m_name,
                                        mystatus[i].s_member.m_tel, mystatus[i].s_chkoutDate);

        if (!mystatus[i].s_isret)
            printf("● 대출중\n");
        else
            printf("● %d\n", mystatus[i].s_retDate);
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