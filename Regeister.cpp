#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <windows.h>

//����곣��
#define MAX_ID 11
#define MAX_PWD 20
#define MAX_NAME 15
#define MAX_SEX 5
#define MAX_PHONE 12
#include<conio.h>


//�����û��Ľṹ��
typedef struct Users
{
 char id[MAX_ID];
 char pwd[MAX_PWD];
 char name[MAX_NAME];
 char sex[MAX_SEX];
 char phone[MAX_PHONE];
}Users;

 

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

int main()//������ ��ע���ںţ�C�������������������ȡ300G�������
{
 char input;
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
  
    // ��ȡ�û���Ϣ������Ƿ��ظ�  
    Users b;  
    while (fread(&b, sizeof(Users), 1, pf) == 1) {  
        printf("�����������˺�>>");  
        scanf("%19s", a.id); // ʹ��%19s��ֹ���������  
        if (strcmp(a.id, b.id) == 0) {  
            printf("���û����Ѵ��ڣ�����������!\n");  
            fclose(pf);  
            return;  
        }  
    }  
  
    // ��ȡ��ϣ������ļ������ڣ����ļ���  
    if (!feof(pf)) {  
        // �������EOF�����ȡ����  
        printf("��ȡ�ļ�ʱ����\n");  
        fclose(pf);  
        return;  
    }  
    fclose(pf); // �ر��ļ����ͷ���Դ  
  
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
 Users a, b;//ͬ��a���������û�����ģ�b��������ˮ�ģ����ļ��ж�ȡ��b�У���b��aƥ��Ƚϣ�

 FILE* pf = fopen("users.dat", "rb");//��ֻ���ķ�ʽ���ļ�
 if (!pf)//�����ȡʧ��
 {
  printf("%s\n", strerror(errno));//�����н���~
  return;
 }
 printf("��ӭ����̰������Ϸ��¼����!\n");
 //Sleep(1000);
  
 fread(&b, sizeof(Users), 1, pf);//�ȴ��ļ��ж�ȡһ���û�����ˮ
  
 printf("�������˺�>>");
 scanf("%s", a.id);
  
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
