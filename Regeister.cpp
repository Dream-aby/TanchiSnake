#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <windows.h>

//定义宏常量
#define MAX_ID 11
#define MAX_PWD 20
#define MAX_NAME 15
#define MAX_SEX 5
#define MAX_PHONE 12
#include<conio.h>


//创建用户的结构体
typedef struct Users
{
 char id[MAX_ID];
 char pwd[MAX_PWD];
 char name[MAX_NAME];
 char sex[MAX_SEX];
 char phone[MAX_PHONE];
}Users;

 

//声明函数

//打印菜单
void menu();

//用户注册
void Register();

//登录
void Login();

//找回密码
void Reback();

//定位光标
void gotoxy();

//获取x的位置
int posx();

//获取y的位置
int posy();

//密码输入（含掩盖功能）
void Getpwd(char* pwd);

int main()//主函数 
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
   printf("退出成功!\n");
   break;
  default:
   printf("选择错误,请重新选择!\n");
   break;
  }
 } while (input!='0');
}

//打印菜单
void menu()
{
 printf("************************************\n");
 printf("************************************\n");
 printf("*****1.Register         2.Login*****\n");
 printf("*****3.Reback           0.exit *****\n");
 printf("************************************\n");
 printf("************************************\n");
}

//注册系统
void Register() {  
    Users a; // 用于接收用户输入的临时变量  
    FILE* pf;  
  
    printf("欢迎来到注册界面!\n");  
  
    // 尝试以二进制读模式打开文件  
    pf = fopen("users.dat", "rb");  
    if (!pf) {  
        // 如果文件不存在（ENOENT），则创建文件  
        if (errno == ENOENT) {  
            pf = fopen("users.dat", "wb");  
            if (!pf) {  
                printf("创建文件失败: %s\n", strerror(errno));  
                return;  
            }  
            // 如果文件创建成功，则可以直接写入，无需检查重复用户  
        } else {  
            // 其他错误  
            printf("打开文件失败: %s\n", strerror(errno));  
            return;  
        }  
    }  
  
    // 读取用户信息，检查是否重复  
    Users b;  
    while (fread(&b, sizeof(Users), 1, pf) == 1) {  
        printf("请输入您的账号>>");  
        scanf("%19s", a.id); // 使用%19s防止缓冲区溢出  
        if (strcmp(a.id, b.id) == 0) {  
            printf("此用户名已存在，请重新输入!\n");  
            fclose(pf);  
            return;  
        }  
    }  
  
    // 读取完毕，或者文件不存在（新文件）  
    if (!feof(pf)) {  
        // 如果不是EOF，则读取出错  
        printf("读取文件时出错\n");  
        fclose(pf);  
        return;  
    }  
    fclose(pf); // 关闭文件以释放资源  
  
    // 读取用户的其他信息  
    printf("请输入您的姓名>>");  
    scanf("%49s", a.name); // 使用%49s防止缓冲区溢出  
    printf("请输入您的性别>>");  
    scanf("%9s", a.sex); // 使用%9s防止缓冲区溢出  
    printf("请输入您的电话号码>>");  
    scanf("%19s", a.phone); // 使用%19s防止缓冲区溢出  
    printf("请输入您的密码>>");  
    Getpwd(a.pwd);  
    printf("\n请再次确认您的密码>>");  
    char tmp[20];  
    Getpwd(tmp);  
  
    // 验证两次密码是否匹配  
    do {  
        if (strcmp(a.pwd, tmp) == 0) {  
            // 打开文件以追加模式  
            pf = fopen("users.dat", "ab");  
            if (!pf) {  
                printf("打开文件失败以写入信息: %s\n", strerror(errno));  
                return;  
            }  
            fwrite(&a, sizeof(Users), 1, pf);  
            printf("\n账号注册成功,请登录!\n");  
            fclose(pf);  
            return;  
        } else {  
            printf("\n两次密码不匹配!请重新输入>>");  
            Getpwd(a.pwd);  
            printf("\n请再次确认>>");  
            Getpwd(tmp);  
        }  
    } while (1);  
} 
//登录系统
void Login()
{
 Users a, b;//同理，a是用来给用户输入的，b是用来是水的（从文件中读取到b中，用b和a匹配比较）

 FILE* pf = fopen("users.dat", "rb");//以只读的方式打开文件
 if (!pf)//如果读取失败
 {
  printf("%s\n", strerror(errno));//上面有讲过~
  return;
 }
 printf("欢迎来到登录界面!\n");
 //Sleep(1000);
  
 fread(&b, sizeof(Users), 1, pf);//先从文件中读取一个用户试试水
  
 printf("请输入账号>>");
 scanf("%s", a.id);
  
 while (1)
 {
  if (!strcmp(a.id, b.id))//在文件中找到了与用户输入相同的id
  {
   break;
  }
  else
  {
   if (!feof(pf))//没读到文件末尾，继续读取文件中的id到b中
   {
    fread(&b, sizeof(Users), 1, pf);//继续从文件中读取用户信息进b，直到在文件中找到一个和a的信息相同的
   }
   else//读到文件末尾了，没有找到与用户输入相同的账号
   {
    printf("此账号不存在!请重新输入!\n");
    Sleep(500);
    fclose(pf);
    pf = NULL;
    return;
   }
  }
 }
 do
 {
  printf("请输入密码>>");
  Getpwd(a.pwd);//获取密码，在下面会讲
  if (!strcmp(a.pwd, b.pwd))//输入的密码与文件中的相同
  {
   printf("\n登录成功!欢迎使用!\n");
   Sleep(500);
   fclose(pf);//用完当然要把文件关啦
   pf = NULL;//置空，避免野指针
   return;
  }
  else
  {
   printf("\n密码输入错误,请重新输入\n");
  }
 } while (strcmp(a.pwd, b.pwd));

}

//找回密码
void Reback()
{
 char tmp[20] = "";//密码匹配用的
 Users a, b;

 FILE* pf = fopen("users.dat", "rb+");//"rb+"是为了读和写以二进制打开文件的意思
  
 if (!pf)//老样子，先判断能不能顺利打开
 {
  printf("%s", strerror(errno));
  return;
 }
  
 fread(&b, sizeof(Users), 1, pf);//照样，读一个试试水
  
 printf("请输入您的账号>>");
 Sleep(800);
  
 scanf("%s", a.id);
  
 while (1)//在文件中找到与用户输入相同的id
 {
  if (!strcmp(a.id, b.id))//如果读取到了相同的id（在文件中找到了和用户输入一样的）
  {
   break;
  }
  else
  {
   if (!feof(pf))//没读到文件尾，继续读
   {
    fread(&b, sizeof(Users), 1, pf);
   }
   else
   {
    printf("您输入的账号不存在!请重新输入!\n");
    Sleep(500);
    fclose(pf);
    pf = NULL;
    break;
   }
  }
 }
  
 //下面是信息匹配验证
 do//匹配姓名
 {
  printf("请输入您的姓名>>");
  scanf("%s", a.name);
  if (!strcmp(a.name, b.name))
  {
   break;
  }
  else
  {
   printf("输入错误,请重新输入!\n");
  }
 } while (strcmp(a.name, b.name));
  
 do//匹配性别
 {
  printf("请输入您的性别>>");
  scanf("%s", a.sex);
  if (!strcmp(a.sex, b.sex))
  {
   break;
  }
  else
  {
   printf("输入错误,请重新输入!\n");
  }
 } while (strcmp(a.sex, b.sex));
 do//匹配电话号码
 {
  printf("请输入您的电话号码>>");
  scanf("%s", a.phone);
  if (!strcmp(a.phone, b.phone))
  {
   break;
  }
  else
  {
   printf("输入错误,请重新输入!\n");
  }
 } while (strcmp(a.phone, b.phone));
  
 //更改密码
 printf("验证成功!请修改您的密码!\n");
 printf("请输入您的密码>>");
 Getpwd(a.id);
 printf("请再次确认您的密码>>");
 Getpwd(tmp);
 if (!pf)
 {
  printf("%s", strerror(errno));
  return;
 }
 //将原来的密码覆盖掉
 do
 {
  if (!strcmp(a.pwd, tmp))//两次密码相等
  {
   fseek(pf,-((int)(sizeof(Users)-MAX_ID)), SEEK_CUR);//将文件流调回到要修改的密码的位置
   fprintf(pf, "%s", a.pwd);//覆盖原来的密码
   printf("密码修改成功,请登录!\n");
   Sleep(500);
   fclose(pf);
   pf = NULL;
   return;
  }
  else
  {
   printf("两次密码不匹配!请重新输入>>");
   scanf("%s", a.pwd);
   printf("请再次确认>>");
   scanf("%s", tmp);
  }
 } while (1);

}

//定位光标
void gotoxy(int x, int y)
{
 //更新光标位置
 COORD pos;
 HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);//GetStdHandle是一个Windows API函数。
 pos.X = x;
 pos.Y = y;
 SetConsoleCursorPosition(hOutput, pos);
}
//获取光标x坐标
int posx()
{
 CONSOLE_SCREEN_BUFFER_INFO ptr;
 GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ptr);
 return (ptr.dwCursorPosition.X);
}
//获取光标y坐标
int posy()
{
 CONSOLE_SCREEN_BUFFER_INFO ptr;
 GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ptr);
 return (ptr.dwCursorPosition.Y);
}

//输入密码
void Getpwd(char* pwd)
{
 int i = 0;
 int x, y;
 while (1)
 {
  pwd[i] = getch();//获取单个密码（字符）
  if (pwd[i] == VK_BACK && i >= 0)//如果输入的是回退键，VK_BACK是键盘的键值，ASCII码值为8
  {
   if (i > 0)//i>0说明有输入东西了，则回退前一格
   {
    i--;
    x = posx() - 1;//定位x并回退一格
    y = posy();//定位y
    gotoxy(x, y);//定位光标
    printf(" ");//将*用空格掩盖
    x = posx() - 1;//再次回退，下次输入时光标才会显示在正确的位置
    y = posy();//定位y
    gotoxy(x, y);
    continue;//然后跳过此次循环
   }
   else if (i == 0)//i==0说明没输入东西，直接跳过此次循环即可
   {
    continue;
   }
  }
  if (i >= 0 && pwd[i] != VK_RETURN && pwd[i] != VK_BACK)//输入东西了
  {
   x = posx();
   y = posy();
   gotoxy(x, y);
   printf("*");
  }
  if (i == 0 && pwd[i] == VK_RETURN)//如果没输入东西直接按回车，直接跳过此次循环，避免程序把回车当密码了
  {
   continue;
  }
  if (pwd[i] == VK_RETURN||i==MAX_PWD-2)//输入回车了或者到上限了
  {
   i++;
   pwd[i] = '\0';//结尾放'\0'
   break;
  }
  i++;
 }
}
