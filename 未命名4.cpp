#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>
#include <string.h>
#include <errno.h>
#include<bits/stdc++.h>
#include<conio.h>
#define U 1
#define D 2
#define L 3 
#define R 4       //�ߵ�״̬��U���� ��D���£�L:�� R����
//����곣��
#define MAX_ID 11
#define MAX_PWD 20
#define MAX_NAME 15
#define MAX_SEX 5
#define MAX_PHONE 12
using namespace std;
//����ȫ�ֱ���name������ʾ������Ϸ�е��û�
char Username[MAX_NAME] ;
//�����û��Ľṹ��
typedef struct Users
{
 char id[MAX_ID];
 char pwd[MAX_PWD];
 char name[MAX_NAME];
 char sex[MAX_SEX];
 char phone[MAX_PHONE];
}Users;

//��־�ṹ�� 
 struct UserGameLog {
    string  username;
    string  password;
    time_t start_time;
    time_t end_time; 
    int score;
} ;
 UserGameLog logs[10];

typedef struct SNAKE //�����һ���ڵ�
{
    int x;
    int y;
    struct SNAKE* next;
}snake;

//ȫ�ֱ���//
int score = 0, add = 10;//�ܵ÷���ÿ�γ�ʳ��÷֡�
int status, sleeptime = 200;//ÿ�����е�ʱ����
snake* head, * food;//��ͷָ�룬ʳ��ָ��
snake* q;//�����ߵ�ʱ���õ���ָ��
int endgamestatus = 0; //��Ϸ�����������1��ײ��ǽ��2��ҧ���Լ���3�������˳���Ϸ��

//����ȫ������//
void Pos();
void creatMap();
void initsnake();
int biteself();
void createfood();
//void cantcrosswall();
//void snakemove();
void cantcrosswall(UserGameLog *s,int k);
void snakemove(UserGameLog *s,int k);
void pause();
void gamecircle(UserGameLog *s,int k);
//void gamecircle();
void welcometogame();
//void endgame();
void endgame(UserGameLog *s,int k);
void gamestart();
//��������

//��ӡ�˵�
void menu();

//�û�ע��
void Register();

//��¼
void Login();

//�һ�����
void Reback();

//��λ���
void gotoxy();

//��ȡx��λ��
int posx();
//��ȡy��λ��
int posy();
//�������루���ڸǹ��ܣ�
void Getpwd(char* pwd);


void Pos(int x, int y)//���ù��λ��
{
    COORD pos;
    HANDLE hOutput;
    pos.X = x;
    pos.Y = y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, pos);
}

void creatMap()//������ͼ
{
    int i;
    for (i = 0; i < 58; i += 2)//��ӡ���±߿�
    {
        Pos(i, 0);
        printf("��");
        Pos(i, 26);
        printf("��");
    }
    for (i = 1; i < 26; i++)//��ӡ���ұ߿�
    {
        Pos(0, i);
        printf("��");
        Pos(56, i);
        printf("��");
    }
}

void initsnake()//��ʼ������
{
    snake* tail;
    int i;
    tail = (snake*)malloc(sizeof(snake));//����β��ʼ��ͷ�巨����x,y�趨��ʼ��λ��//
    tail->x = 24;
    tail->y = 5;
    tail->next = NULL;
    for (i = 1; i <= 4; i++)
    {
        head = (snake*)malloc(sizeof(snake));
        head->next = tail;
        head->x = 24 + 2 * i;
        head->y = 5;
        tail = head;
    }
    while (tail != NULL)//��ͷ��Ϊ���������
    {
        Pos(tail->x, tail->y);
        printf("��");
        tail = tail->next;
    }
}

int biteself()//�ж��Ƿ�ҧ�����Լ�
{
    snake* self;
    self = head->next;
    while (self != NULL)
    {
        if (self->x == head->x && self->y == head->y)
        {
            return 1;
        }
        self = self->next;
    }
    return 0;
}

void createfood()
{
    snake* food_1;
    srand((unsigned)time(NULL));
    food_1 = (snake*)malloc(sizeof(snake));
    do
    {
        food_1->x = rand() % 52 + 2;
        food_1->y = rand() % 24 + 1;
        q = head;
        while (q != NULL)
        {
            if (q->x == food_1->x && q->y == food_1->y) // �ж������Ƿ���ʳ���غ�
            {
                food_1->x = rand() % 52 + 2;
                food_1->y = rand() % 24 + 1;
                q = head; // ���¼��ʳ��λ��
            }
            else
            {
                q = q->next;
            }
        }
    } while ((food_1->x % 2) != 0); // ��֤��Ϊż����ʹ��ʳ��������ͷ����

    Pos(food_1->x, food_1->y);
    food = food_1;
    printf("��");
}
void cantcrosswall( UserGameLog *s,int k)//���ܴ�ǽ
{
    if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
    {
        endgamestatus = 1;
        endgame(s,k);
    }
}


void saveUserGameLogsToFile(UserGameLog logs[], int size) {
    ofstream file("GameLog.txt", ios::out | ios::app); // ʹ�����ģʽ���ļ�������ļ��������򴴽�

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }
        for (int i = 0; i <= size; i++) {
        file << "Username: " << logs[i].username << endl;
        file << "Password: " << logs[i].password << endl;
        file << "Start Time: " << ctime(&logs[i].start_time);
        file << "End Time: " << ctime(&logs[i].end_time);
        file << "Score: " << logs[i].score << endl;
        file << endl;
    }

    file.close();
}




void snakemove( UserGameLog *s,int k)//��ǰ��,��U,��D,��L,��R
{
    snake* nexthead;
    cantcrosswall(s,k);

    nexthead = (snake*)malloc(sizeof(snake));
    if (status == U)
    {
        nexthead->x = head->x;
        nexthead->y = head->y - 1;
        if (nexthead->x == food->x && nexthead->y == food->y)//�����һ����ʳ��//
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("��");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
        else                                               //���û��ʳ��//
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q->next->next != NULL)
            {
                Pos(q->x, q->y);
                printf("��");
                q = q->next;
            }
            Pos(q->next->x, q->next->y);
            printf("  ");
            free(q->next);
            q->next = NULL;
        }
    }
    if (status == D)
    {
        nexthead->x = head->x;
        nexthead->y = head->y + 1;
        if (nexthead->x == food->x && nexthead->y == food->y)  //��ʳ��
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("��");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
        else                               //û��ʳ��
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q->next->next != NULL)
            {
                Pos(q->x, q->y);
                printf("��");
                q = q->next;
            }
            Pos(q->next->x, q->next->y);
            printf("  ");
            free(q->next);
            q->next = NULL;
        }
    }
    if (status == L)
    {
        nexthead->x = head->x - 2;
        nexthead->y = head->y;
        if (nexthead->x == food->x && nexthead->y == food->y)//��ʳ��
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("��");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
        else                                //û��ʳ��
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q->next->next != NULL)
            {
                Pos(q->x, q->y);
                printf("��");
                q = q->next;
            }
            Pos(q->next->x, q->next->y);
            printf("  ");
            free(q->next);
            q->next = NULL;
        }
    }
    if (status == R)
    {
        nexthead->x = head->x + 2;
        nexthead->y = head->y;
        if (nexthead->x == food->x && nexthead->y == food->y)//��ʳ��
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q != NULL)
            {
                Pos(q->x, q->y);
                printf("��");
                q = q->next;
            }
            score = score + add;
            createfood();
        }
        else                                         //û��ʳ��
        {
            nexthead->next = head;
            head = nexthead;
            q = head;
            while (q->next->next != NULL)
            {
                Pos(q->x, q->y);
                printf("��");
                q = q->next;
            }
            Pos(q->next->x, q->next->y);
            printf("  ");
            free(q->next);
            q->next = NULL;
        }
    }
    if (biteself() == 1)       //�ж��Ƿ��ҧ���Լ�
    {
        endgamestatus = 2;
        endgame(s,k);
    }
}


void pause()//��ͣ
{
    while (1)
    {
        Sleep(300);
        if (GetAsyncKeyState(VK_SPACE))
        {
            break;
        }

    }
}
void gamecircle(UserGameLog *s,int k)//������Ϸ        
{
	Pos(64, 5);
	printf("%s������Ϸ��",Username); 

    Pos(64, 15);
    printf("���ܴ�ǽ������ҧ���Լ�\n");
    Pos(64, 16);
    printf("�á�.��.��.���ֱ�����ߵ��ƶ�.");
    Pos(64, 17);
    printf("F1 Ϊ���٣�F2 Ϊ����\n");
    Pos(64, 18);
    printf("ESC ���˳���Ϸ.space����ͣ��Ϸ.");
    Pos(64, 20);
    status = R;
    while (1)
    {
        Pos(64, 10);
        printf("�÷֣�%d  ", score);
        Pos(64, 11);
        printf("ÿ��ʳ��÷֣�%d��", add);
        if (GetAsyncKeyState(VK_UP) && status != D)
        {
            status = U;
        }
        else if (GetAsyncKeyState(VK_DOWN) && status != U)
        {
            status = D;
        }
        else if (GetAsyncKeyState(VK_LEFT) && status != R)
        {
            status = L;
        }
        else if (GetAsyncKeyState(VK_RIGHT) && status != L)
        {
            status = R;
        }
        else if (GetAsyncKeyState(VK_SPACE))
        {
            pause();
        }
        else if (GetAsyncKeyState(VK_ESCAPE))
        {
            endgamestatus = 3;
            break;
        }
        else if (GetAsyncKeyState(VK_F1))
        {
            if (sleeptime >= 50)
            {
                sleeptime = sleeptime - 30;
                add = add + 2;
                if (sleeptime == 320)
                {
                    add = 2;//��ֹ����1֮���ټӻ����д�
                }
            }
        }
        else if (GetAsyncKeyState(VK_F2))
        {
            if (sleeptime < 350)
            {
                sleeptime = sleeptime + 30;
                add = add - 2;
                if (sleeptime == 350)
                {
                    add = 1;  //��֤��ͷ�Ϊ1
                }
            }
        }
        Sleep(sleeptime);
        snakemove( s,k);
    }
}

void welcometogame()//��ʼ����
{
	
    Pos(40, 12);
    printf("��ӭ����̰ʳ����Ϸ��");
    Pos(40, 25);
    system("pause");
    system("cls");
    Pos(25, 12);
    printf("�á�.��.��.���ֱ�����ߵ��ƶ��� F1 Ϊ���٣�2 Ϊ����\n");
    Pos(25, 13);
    printf("���ٽ��ܵõ����ߵķ�����\n");
    system("pause");
    system("cls");
}

void endgame(UserGameLog *s,int k)//������Ϸ
{

    system("cls");
    Pos(24, 12);
    if (endgamestatus == 1)
    {
        printf("�Բ�����ײ��ǽ�ˡ���Ϸ����!");
    }
    else if (endgamestatus == 2)
    {
        printf("�Բ�����ҧ���Լ��ˡ���Ϸ����!");
    }
    else if (endgamestatus == 3)
    {
        printf("���Ѿ���������Ϸ��");
    }
    Pos(24, 13);
    printf("���ĵ÷���%d\n", score);
    s[k].score=score;
    s[k].end_time=time(NULL);
   saveUserGameLogsToFile(s,k);
    exit(0);
}

void gamestart()//��Ϸ��ʼ��
{
    system("mode con cols=100 lines=30");
    welcometogame();
    creatMap();
    initsnake();
    createfood();
}

//��ӡ�˵�
void menu()
{
 printf("************************************\n");
 printf("************************************\n");
 printf("*****1.Register         2.Login*****\n");
 printf("*****3.Reback           0.exit *****\n");
 printf("************************************\n");
 printf("************************************\n");
}

//ע��ϵͳ
void Register() {  
    Users a; // ���ڽ����û��������ʱ����  
    FILE* pf;  
  
    printf("��ӭ����ע�����!\n");  
  
    // �����Զ����ƶ�ģʽ���ļ�  
    pf = fopen("users.dat", "rb");  
    if (!pf) {  
        // ����ļ������ڣ�ENOENT�����򴴽��ļ�  
        if (errno == ENOENT) {  
            pf = fopen("users.dat", "wb");  
            if (!pf) {  
                printf("�����ļ�ʧ��: %s\n", strerror(errno));  
                return;  
            }  
            // ����ļ������ɹ��������ֱ��д�룬�������ظ��û�  
        } else {  
            // ��������  
            printf("���ļ�ʧ��: %s\n", strerror(errno));  
            return;  
        }  
    }    
        printf("�����������˺�>>");  
        scanf("%19s", a.id); // ʹ��%19s��ֹ���������  

    // ��ȡ�û���������Ϣ  
    printf("��������������>>");  
    scanf("%49s", a.name); // ʹ��%49s��ֹ���������  
    printf("�����������Ա�>>");  
    scanf("%9s", a.sex); // ʹ��%9s��ֹ���������  
    printf("���������ĵ绰����>>");  
    scanf("%19s", a.phone); // ʹ��%19s��ֹ���������  
    printf("��������������>>");  
    Getpwd(a.pwd);  
    printf("\n���ٴ�ȷ����������>>");  
    char tmp[20];  
    Getpwd(tmp);  
  
    // ��֤���������Ƿ�ƥ��  
    do {  
        if (strcmp(a.pwd, tmp) == 0) {  
            // ���ļ���׷��ģʽ  
            pf = fopen("users.dat", "ab");  
            if (!pf) {  
                printf("���ļ�ʧ����д����Ϣ: %s\n", strerror(errno));  
                return;  
            }  
            fwrite(&a, sizeof(Users), 1, pf);  
            printf("\n�˺�ע��ɹ�,���¼!\n");  
            fclose(pf);  
            return;  
        } else {  
            printf("\n�������벻ƥ��!����������>>");  
            Getpwd(a.pwd);  
            printf("\n���ٴ�ȷ��>>");  
            Getpwd(tmp);  
        }  
    } while (1);  
} 
//��¼ϵͳ
void Login()
{
 Users a, b;//ͬ��a���������û�����ģ�b�Ǵ��ļ��ж�ȡ��b�У���b��aƥ��Ƚ�

 FILE* pf = fopen("users.dat", "rb");//��ֻ���ķ�ʽ���ļ�
 if (!pf)//�����ȡʧ��
 {
  printf("%s\n", strerror(errno));//�����н���~
  return;
 }
 printf("��ӭ������¼����!\n");
 //Sleep(1000);
  
 fread(&b, sizeof(Users), 1, pf);//�ȴ��ļ��ж�ȡһ���û�����ˮ
  
 printf("�������˺�>>");
 scanf("%s", a.id);
 //name=a.name;
 
  
 while (1)
 {
  if (!strcmp(a.id, b.id))//���ļ����ҵ������û�������ͬ��id
  {
   break;
  }
  else
  {
   if (!feof(pf))//û�����ļ�ĩβ��������ȡ�ļ��е�id��b��
   {
    fread(&b, sizeof(Users), 1, pf);//�������ļ��ж�ȡ�û���Ϣ��b��ֱ�����ļ����ҵ�һ����a����Ϣ��ͬ��
   }
   else//�����ļ�ĩβ�ˣ�û���ҵ����û�������ͬ���˺�
   {
    printf("���˺Ų�����!����������!\n");
    Sleep(500);
    fclose(pf);
    pf = NULL;
    return;
   }
  }
 }
 do
 {
  printf("����������>>");
  Getpwd(a.pwd);//��ȡ���룬������ὲ
  if (!strcmp(a.pwd, b.pwd))//������������ļ��е���ͬ
  {
   printf("\n��¼�ɹ�!��ӭʹ��!\n");
     
    strcpy(Username, b.name);
    logs[0].username=b.name;
    logs[0].password=b.pwd;
    //strcpy(logs[0].username, b.name);
    //strcpy(logs[0].password, b.pwd);
 printf("��������������%s\n",b.name);
   Sleep(500);
   fclose(pf);//���굱ȻҪ���ļ�����
   pf = NULL;//�ÿգ�����Ұָ��
   return;
  }
  else
  {
   printf("\n�����������,����������\n");
  }
 } while (strcmp(a.pwd, b.pwd));


}

//�һ�����
void Reback()
{
 char tmp[20] = "";//����ƥ���õ�
 Users a, b;

 FILE* pf = fopen("users.dat", "rb+");//"rb+"��Ϊ�˶���д�Զ����ƴ��ļ�����˼
  
 if (!pf)//�����ӣ����ж��ܲ���˳����
 {
  printf("%s", strerror(errno));
  return;
 }
  
 fread(&b, sizeof(Users), 1, pf);//��������һ������ˮ
  
 printf("�����������˺�>>");
 Sleep(800);
  
 scanf("%s", a.id);
  
 while (1)//���ļ����ҵ����û�������ͬ��id
 {
  if (!strcmp(a.id, b.id))//�����ȡ������ͬ��id�����ļ����ҵ��˺��û�����һ���ģ�
  {
   break;
  }
  else
  {
   if (!feof(pf))//û�����ļ�β��������
   {
    fread(&b, sizeof(Users), 1, pf);
   }
   else
   {
    printf("��������˺Ų�����!����������!\n");
    Sleep(500);
    fclose(pf);
    pf = NULL;
    break;
   }
  }
 }
  
 //��������Ϣƥ����֤
 do//ƥ������
 {
  printf("��������������>>");
  scanf("%s", a.name);
  if (!strcmp(a.name, b.name))
  {
   break;
  }
  else
  {
   printf("�������,����������!\n");
  }
 } while (strcmp(a.name, b.name));
  
 do//ƥ���Ա�
 {
  printf("�����������Ա�>>");
  scanf("%s", a.sex);
  if (!strcmp(a.sex, b.sex))
  {
   break;
  }
  else
  {
   printf("�������,����������!\n");
  }
 } while (strcmp(a.sex, b.sex));
 do//ƥ��绰����
 {
  printf("���������ĵ绰����>>");
  scanf("%s", a.phone);
  if (!strcmp(a.phone, b.phone))
  {
   break;
  }
  else
  {
   printf("�������,����������!\n");
  }
 } while (strcmp(a.phone, b.phone));
  
 //��������
 printf("��֤�ɹ�!���޸���������!\n");
 printf("��������������>>");
 Getpwd(a.id);
 printf("���ٴ�ȷ����������>>");
 Getpwd(tmp);
 if (!pf)
 {
  printf("%s", strerror(errno));
  return;
 }
 //��ԭ�������븲�ǵ�
 do
 {
  if (!strcmp(a.pwd, tmp))//�����������
  {
   fseek(pf,-((int)(sizeof(Users)-MAX_ID)), SEEK_CUR);//���ļ������ص�Ҫ�޸ĵ������λ��
   fprintf(pf, "%s", a.pwd);//����ԭ��������
   printf("�����޸ĳɹ�,���¼!\n");
   Sleep(500);
   fclose(pf);
   pf = NULL;
   return;
  }
  else
  {
   printf("�������벻ƥ��!����������>>");
   scanf("%s", a.pwd);
   printf("���ٴ�ȷ��>>");
   scanf("%s", tmp);
  }
 } while (1);

}

//��λ���
void gotoxy(int x, int y)
{
 //���¹��λ��
 COORD pos;
 HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//GetStdHandle��һ��Windows API������
 pos.X = x;
 pos.Y = y;
 SetConsoleCursorPosition(hOutput, pos);
}
//��ȡ���x����
int posx()
{
 CONSOLE_SCREEN_BUFFER_INFO ptr;
 GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ptr);
 return (ptr.dwCursorPosition.X);
}
//��ȡ���y����
int posy()
{
 CONSOLE_SCREEN_BUFFER_INFO ptr;
 GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ptr);
 return (ptr.dwCursorPosition.Y);
}

//��������
void Getpwd(char* pwd)
{
 int i = 0;
 int x, y;
 while (1)
 {
  pwd[i] = getch();//��ȡ�������루�ַ���
  if (pwd[i] == VK_BACK && i >= 0)//���������ǻ��˼���VK_BACK�Ǽ��̵ļ�ֵ��ASCII��ֵΪ8
  {
   if (i > 0)//i>0˵�������붫���ˣ������ǰһ��
   {
    i--;
    x = posx() - 1;//��λx������һ��
    y = posy();//��λy
    gotoxy(x, y);//��λ���
    printf(" ");//��*�ÿո��ڸ�
    x = posx() - 1;//�ٴλ��ˣ��´�����ʱ���Ż���ʾ����ȷ��λ��
    y = posy();//��λy
    gotoxy(x, y);
    continue;//Ȼ�������˴�ѭ��
   }
   else if (i == 0)//i==0˵��û���붫����ֱ�������˴�ѭ������
   {
    continue;
   }
  }
  if (i >= 0 && pwd[i] != VK_RETURN && pwd[i] != VK_BACK)//���붫����
  {
   x = posx();
   y = posy();
   gotoxy(x, y);
   printf("*");
  }
  if (i == 0 && pwd[i] == VK_RETURN)//���û���붫��ֱ�Ӱ��س���ֱ�������˴�ѭ�����������ѻس���������
  {
   continue;
  }
  if (pwd[i] == VK_RETURN||i==MAX_PWD-2)//����س��˻��ߵ�������
  {
   i++;
   pwd[i] = '\0';//��β��'\0'
   break;
  }
  i++;
 }
} 
int main()
{
	char input;
	
	logs[0].start_time = time(NULL);
 	do
 	{
  menu();
  setbuf(stdin, NULL);
  input = getchar();
  switch (input)
  {
  case '1':
   Register();
   break;
  case '2':
   Login();
   gamestart();
   gamecircle(logs,0);
    endgame(logs,0);
   break;
  case '3':
   Reback();
   break;
  case '0':
   printf("�˳��ɹ�!\n");
   break;
  default:
   printf("ѡ�����,������ѡ��!\n");
   break;
    }
 } while (input!='0');
	//�������̰���ߴ��� 
    /*gamestart();
    gamecircle();
    endgame();*/
    return 0;
}

