// 声明：该程序为学生信息管理程序,需要管理员账号才能操作。
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include <io.h>

// 学生信息结构体
typedef struct Node {
    int ID;// 学号
    char Name[50];// 姓名
    char Sex[10];// 性别
    char Province[20];// 省
    int Province_ID;// 省的数字
    int Town_ID;//市的数字
    char Town[20];// 市
    char born[20];//出生日期
    char poli[20];//政治面貌
    char phone[20];//手机电话
    char mail[40];//电子邮件
    struct Node* next;// 指针域
} node;

// 管理员结构体
typedef struct User {
    char Name[50];
    char password[50];
    struct User* next;
} user;

node list;// 链表
node list_sheng;// 链表
node list_shi;// 链表
user list_user;

//读取行数
int num, num1;

// 读取文件
int Read_FILE(node* L, node* L1, node* L2);

// 保存文件
int Write_FILE(node* L, node* L1, node* L2);

int Save_FILE_student_information(node* L);

int Save_FILE_student_address_sheng(node* L);

int Save_FILE_student_address_shi(node* L);

int Write_user(user *L);

// 主菜单界面
void welcome();

// 登陆页面
void set_password();
// 添加用户信息
void Set_User(char name[],char password[],user *L);
//读取管理员信息
int Read_FILE_user(user* L);
// 增加学生信息
void Add(node* L, node e);// 功能
void Add_Printf();// 界面

// 删除学生信息
void Delete_Printf(node* L);// 界面
void Delete(node* s);// 功能

// 修改学生信息
void Fix(node* L);

// 查询学生信息
void Search_Printf(node* L);// 界面
node* Search_id(int id, node* L);// 按学号进行查找
user* verification(char name[], char password[], user* L); // 按照性别进行查找
node* Search_province(char Province[], node* L);// 按照省份进行查询
node* Search_town(char Town[], node* L); // 按照市区进行查询
node* Search_poli(char poli[], node* L); // 按照政治面貌进行查询
node* Search_phone(char phone[], node* L); // 按照电话号码进行查询
node* Search_mail(char mail[], node* L);// 按照邮箱进行查询

// 退出管理系统
void goodbye();


void welcome() {
    //    system("cls");
    printf("--------------------------------------------------------------- \n");
    printf("|                       学生信息管理系统                       | \n");
    printf("|                    1 ---- 增加学生信息                      | \n");
    printf("|                    2 ---- 删除学生信息                      | \n");
    printf("|                    3 ---- 修改学生信息                      | \n");
    printf("|                    4 ---- 查询学生信息                      | \n");
    printf("|                    5 ---- 排序学生信息                      | \n");
    printf("|                    6 ---- 展示所有学生信息                   | \n");
    printf("|                    0 ---- 退出管理系统                      | \n");
    printf("----------------------------------------------------------------\n");

    printf("请选择想要实现的功能（数字）：");
}
void set_password() {
    int i = 1;
    char choose;
    char name[50];
    char password[50];
    char choose1;
    char name1[50];
    char password1[50];
    printf("------------------------------------------- \n");
    printf("|           欢迎进入学生信息管理系统            |\n");
    printf("------------------------------------------- \n");
    printf("是否拥有账户？（Y）or（N）\n");
    scanf("%c", &choose);
    getchar();
    if (choose == 'Y'){
        printf("请输入用户名：\n");
        scanf("%s", name);
        printf("请输入密码：\n");
        scanf("%s", password);
        while (i == 1){
            if (verification(name, password, &list_user) == NULL){
                printf("用户名或密码错误,请重新输入：\n");
                printf("请输入用户名：\n");
                scanf("%s", name);
                printf("请输入密码：\n");
                scanf("%s", password);
            }
            else {
                break;
            }
        }
    }
    else{
        printf("是否注册？Y or N\n");
        scanf("%c", &choose1);
        if (choose1 == 'Y'){
            printf("请输入用户名：\n");
            scanf("%s", name1);
            printf("请输入密码：\n");
            scanf("%s", password1);
            getchar();
            Set_User(name1, password1, &list_user);
            set_password();
        } else {
            printf("再见！！！");
            goodbye();
        }
    }
}
// 将省和市按照优化的方式进行处理
int Write_FILE(node* L, node* L1, node* L2) {
    node* l = L->next;
    node* t;
    //    if (L1->next)
    while (l != NULL) {
        node* s;
        t = L1;
        while (t->next != NULL) {
            if (strcmp(l->Province, t->Province) == 0) {
                l->Province_ID = t->ID;
                break;
            }
            t = t->next;
        }
        if (strcmp(l->Province, t->Province) == 0) {
            l->Province_ID = t->ID;
        }
        else if (t->next == NULL) {
            s = (node*)malloc(sizeof(node));
            strcpy(s->Province, l->Province);
            s->ID = num + 1;
            num += 1;
            l->Province_ID = s->ID;
            // 尾插法
            t->next = s;
            t = s;
            t->next = NULL;
        }
        l = l->next;
    }
    l = L->next;
    while (l != NULL) {
        node* s;
        t = L2;
        while (t->next != NULL) {
            if (strcmp(l->Town, t->Town) == 0) {
                l->Town_ID = t->ID;
                break;
            }
            t = t->next;
        }
        if (strcmp(l->Town, t->Town) == 0) {
            l->Town_ID = t->ID;
        }
        else if (t->next == NULL) {
            s = (node*)malloc(sizeof(node));
            strcpy(s->Town, l->Town);
            s->ID = num1 + 1;
            num1 += 1;
            l->Town_ID = s->ID;
            // 尾插法
            t->next = s;
            t = s;
            t->next = NULL;
        }
        l = l->next;
    }
    Save_FILE_student_information(&list);
    Save_FILE_student_address_sheng(&list_sheng);
    Save_FILE_student_address_shi(&list_shi);
    return 1;
}
// 读取文件 （管理员）
int Read_FILE_user(user* L) {
    FILE* pfRead;
    user st;
    user *s;
    user *t = L;
    if (_access("user.txt", 0) == -1) {
        pfRead = fopen("user.txt", "wb");
        fclose(pfRead);
        pfRead = fopen("user.txt", "rb");
    }
    else {
        pfRead = fopen("user.txt", "rb");
    }
    while (fscanf(pfRead, "%s %s[^\n]", st.Name, st.password) != EOF) {
        s = (user *) malloc(sizeof(node));
        *s = st;

        // 尾插法
        t->next = s;
        t = s;
        t->next = NULL;
        fgetc(pfRead);
    }
    fclose(pfRead);

    return 1;
}
void Set_User(char name[],char password[],user *L) {
    user st;
    user *p = L;
    strcpy(st.Name, name);
    strcpy(st.password, password);
    user *s = (user*)malloc(sizeof(node));
    *s = st;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = s;
    p = s;
    p->next = NULL;
}
// 读取文件（学生）
int Read_FILE(node* L, node* L1, node* L2) {
    FILE* pfRead;
    FILE* pfRead1;
    FILE* pfRead2;
    node st;
    node* s;
    node* t = L;
    node* t1 = L1;
    if (_access("student_information.txt", 0) == -1) {
        pfRead = fopen("student_information.txt", "wb");
        fclose(pfRead);
        pfRead = fopen("student_information.txt", "rb");
    }
    else pfRead = fopen("student_information.txt", "rb");

    if (_access("student_address_sheng.txt", 0) == -1) {
        pfRead1 = fopen("student_address_sheng.txt", "wb");
        fclose(pfRead1);
        pfRead1 = fopen("student_address_sheng.txt", "rb");
    }
    else pfRead1 = fopen("student_address_sheng.txt", "rb");

    if (_access("student_address_shi.txt", 0) == -1) {
        pfRead2 = fopen("student_address_shi.txt", "wb");
        fclose(pfRead2);
        pfRead2 = fopen("student_address_shi.txt", "rb");
    }
    else pfRead2 = fopen("student_address_shi.txt", "rb");

    while (fscanf(pfRead1, "%d %s[^\n]", &st.ID, st.Province) != EOF) {
        num += 1;
        s = (node*)malloc(sizeof(node));

        *s = st;

        // 尾插法
        t1->next = s;
        t1 = s;
        t1->next = NULL;
        fgetc(pfRead1);
    }
    node* t2 = L2;
    while (fscanf(pfRead2, "%d %s[^\n]", &st.ID, st.Town) != EOF) {
        num1 += 1;
        s = (node*)malloc(sizeof(node));

        *s = st;

        // 尾插法
        t2->next = s;
        t2 = s;
        t2->next = NULL;
        fgetc(pfRead2);
    }
    node* st1, * st2;
    while (fscanf(pfRead, "%d %s %s %d %d %s %s %s %s[^\n]", &st.ID, st.Name, st.Sex, &st.Province_ID, &st.Town_ID, st.born, st.poli, st.phone, st.mail) != EOF) {
        s = (node*)malloc(sizeof(node));
        st1 = Search_id(st.Province_ID, &list_sheng);
        strcpy(st.Province, st1->Province);
        st2 = Search_id(st.Town_ID, &list_shi);
        strcpy(st.Town, st2->Town);
        *s = st;

        // 尾插法
        t->next = s;
        t = s;
        t->next = NULL;
        fgetc(pfRead);
    }
    fclose(pfRead);
    fclose(pfRead1);
    fclose(pfRead2);
    return 1;
}

// 保存文件
int Save_FILE_student_information(node* L) {
    FILE* pfWrite = fopen("student_information.txt", "wb");
    if (pfWrite == NULL) {
        return 0;
    }

    node* p = L->next;

    while (p != NULL) {
        fprintf(pfWrite, "%d %s %s %d %d %s %s %s %s\n", p->ID, p->Name, p->Sex, p->Province_ID, p->Town_ID, p->born, p->poli, p->phone, p->mail);
        p = p->next;
    }
    fclose(pfWrite);
    return 1;
}
//保存文件
int Write_user(user *L) {
    FILE *pfWrite = fopen("user.txt", "wb");
    if (pfWrite == NULL) {
        return 0;
    }

    user *p = L->next;

    while (p != NULL) {
        fprintf(pfWrite, "%s %s\n", p->Name, p->password);
        p = p->next;
    }
    fclose(pfWrite);
    return 1;
}
int Save_FILE_student_address_sheng(node* L) {
    FILE* pfWrite = fopen("student_address_sheng.txt", "wb");
    if (pfWrite == NULL) {
        return 0;
    }

    node* p = L->next;

    while (p != NULL) {
        fprintf(pfWrite, "%d %s\n", p->ID, p->Province);
        p = p->next;
    }
    fclose(pfWrite);
    return 1;
}

int Save_FILE_student_address_shi(node* L) {
    FILE* pfWrite = fopen("student_address_shi.txt", "wb");
    if (pfWrite == NULL) {
        return 0;
    }

    node* p = L->next;

    while (p != NULL) {
        fprintf(pfWrite, "%d %s\n", p->ID, p->Town);
        p = p->next;
    }
    fclose(pfWrite);
    return 1;
}


// 增加学生信息
void Add_Printf() {
    node st;
    printf("请输入新增学生的相关信息：\n");
    printf("学号：");
    scanf("%d", &st.ID);
    printf("姓名：");
    scanf("%s", st.Name);
    printf("性别：");
    scanf("%s", st.Sex);
    printf("家庭住址（省）：");
    scanf("%s", st.Province);
    printf("家庭住址（市）：");
    scanf("%s", st.Town);
    printf("出生日期（请按照：年-月-日 的形式输入）");
    scanf("%s", st.born);
    printf("政治面貌：");
    scanf("%s", st.poli);
    printf("输入联系电话：");
    scanf("%s", st.phone);
    printf("输入个人邮箱：");
    scanf("%s", st.mail);

    Add(&list, st);
}

void Add(node* L, node e) {
    // 尾插法
    node* p = L;
    node* s = (node*)malloc(sizeof(node));
    *s = e;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = s;
    p = s;
    p->next = NULL;
}

// 删除学生信息
void Delete_Printf(node* L) {
    int id;

    node* p;

    printf("请输入要删除的学生的学号：");
    scanf("%d", &id);
    node* st = Search_id(id, L);
    p = st;

    if (st == NULL) {
        printf("查无此人！\n");
        return;
    }

    st = st->next;
    printf("________________________________________________________________\n");
    printf("|学号\t|姓名\t|性别\t|家庭住址: 省|市：\t |出生日期\t|政治面貌    |联系电话\t |电子邮件\n");
    printf("________________________________________________________________\n");
    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
    printf("________________________________________________________________\n");

    Delete(p);

}

void Delete(node* s) {
    node* t = s->next;

    s->next = t->next;
    t->next = NULL;

    free(t);
}

// 修改学生信息
void Fix(node* L) {
    system("cls");
    int id;
    printf("请输入要修改的学生的学号：");
    scanf("%d", &id);
    node* st = Search_id(id, L);

    if (st == NULL) {
        printf("查无此人！\n");
        return;
    }


    int choice = 0;
    while (1) {
        system("cls");

        // 输出一次所要修改的学生成绩
        printf("________________________________________________________________\n");
        printf("|学号\t|姓名\t|性别\t|家庭住址: 省|市：\t |出生日期\t|政治面貌    |联系电话\t |电子邮件\n");
        printf("________________________________________________________________\n");
        printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
        printf("________________________________________________________________\n");

        printf("修改姓名 ---- 1\n");
        printf("修改性别 ---- 2\n");
        printf("修改家庭住址（省） ---- 3\n");
        printf("修改家庭住址（市） ---- 4\n");
        printf("修改出生日期 ---- 5\n");
        printf("修改政治面貌 ---- 6\n");
        printf("修改联系电话 ---- 7\n");
        printf("修改电子邮件 ---- 8\n");

        printf("请输入要修改的信息：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入姓名：");
                scanf("%s", st->Name);
                break;
            case 2:
                printf("请输入性别：");
                scanf("%s", st->Sex);
                break;
            case 3:
                printf("请输入家庭住址（省）：");
                scanf("%s", st->Province);
                break;
            case 4:
                printf("请输入家庭住址（市）：");
                scanf("%s", st->Town);
                break;
            case 5:
                printf("请输入出生日期：");
                scanf("%s", st->born);
                break;
            case 6:
                printf("请输入政治面貌：");
                scanf("%s", st->poli);
                break;
            case 7:
                printf("请输入联系电话：");
                scanf("%s", st->phone);
                break;
            case 8:
                printf("请输入个人邮箱：");
                scanf("%s", st->mail);
                break;
        }
        printf("是否继续修改该学生信息？（Yes：1 / No：0）：");
        scanf("%d", &choice);
        if (choice == 0) {
            break;
        }
    }

    // 修改完成后该学生的信息
    printf("________________________________________________________________\n");
    printf("|学号\t|姓名\t|性别\t|家庭住址: 省|市：\t |出生日期\t|政治面貌    |联系电话\t |电子邮件\n");
    printf("________________________________________________________________\n");
    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
    printf("________________________________________________________________\n");

}

// 查询学生信息
void Search_Printf(node* L) {

    int choice = 0;
    printf("按照学号查询 ---- 1\n");
    printf("按照姓名查询 ---- 2\n");
    printf("按照性别查询 ---- 3\n");
    printf("按照家庭住址（省）查询 ---- 4\n");
    printf("按照家庭住址（市）查询 ---- 5\n");
    printf("按照政治面貌查询 ---- 6\n");
    printf("按照电话号码查询 ---- 7\n");
    printf("按照个人邮箱查询 ---- 8\n");
    printf("请输入查询方式：");
    scanf("%d", &choice);

    int id;
    char name[50];
    char sex[10];
    char Province[20];
    char Town[20];
    char poli[20];
    char phone[20];
    char mail[30];
    node* st;
    switch (choice) {
        case 1:{
            printf("请输入要查询的学号：");
            scanf("%d", &id);
            st = Search_id(id, L);

            if (st == NULL) {
                printf("查无此人！\n");
            }
            else {
                printf("________________________________________________________________\n");
                printf("|学号\t|姓名\t|性别\t|家庭住址: 省|市：\t |出生日期\t|政治面貌    |联系电话\t |电子邮件\n");
                printf("________________________________________________________________\n");
                printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                printf("________________________________________________________________\n");
            }
            break;
        }
        case 2:{
            int g = 0;
            printf("请输入要查询的姓名：");
            scanf("%s", name);
            st = L->next;
            while (st != NULL) {
                if (strcmp(name, st->Name) == 0) {
                    g = 1;
                    printf("________________________________________________________________\n");
                    printf("|学号\t|姓名\t|性别\t|家庭住址: 省|市：\t |出生日期\t|政治面貌    |联系电话\t |电子邮件\n");
                    printf("________________________________________________________________\n");
                    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                    printf("________________________________________________________________\n");
                }
                st = st->next;
            }
            if (g == 0){
                printf("没有任何数据！");
            }

            break;
        }
        case 3:{
            int g = 0;
            printf("请输入要查询的性别: ");
            scanf("%s", sex);
            st = L->next;
            while (st != NULL) {
                if (strcmp(sex, st->Sex) == 0) {
                    g = 1;
                    printf("________________________________________________________________\n");
                    printf("|学号\t|姓名\t|性别\t|家庭住址: 省|市：\t |出生日期\t|政治面貌    |联系电话\t |电子邮件\n");
                    printf("________________________________________________________________\n");
                    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                    printf("________________________________________________________________\n");
                }
                st = st->next;
            }
            if (g == 0){
                printf("没有任何数据！");
            }

            break;
        }
        case 4:{
            int g = 0;
            printf("请输入要查询的省份: ");
            scanf("%s", Province);
            st = L->next;
            while (st != NULL) {
                if (strcmp(Province, st->Province) == 0) {
                    g = 1;
                    printf("________________________________________________________________\n");
                    printf("|学号\t|姓名\t|性别\t|家庭住址: 省|市：\t |出生日期\t|政治面貌    |联系电话\t |电子邮件\n");
                    printf("________________________________________________________________\n");
                    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                    printf("________________________________________________________________\n");
                }
                st = st->next;
            }
            if (g == 0){
                printf("没有任何数据！");
            }

            break;
        }
        case 5:{
            int g = 0;
            printf("请输入要查询的市: ");
            scanf("%s", Town);
            st = L->next;
            while (st != NULL) {
                if (strcmp(Town, st->Town) == 0) {
                    g = 1;
                    printf("________________________________________________________________\n");
                    printf("|学号\t|姓名\t|性别\t|家庭住址: 省|市：\t |出生日期\t|政治面貌    |联系电话\t |电子邮件\n");
                    printf("________________________________________________________________\n");
                    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                    printf("________________________________________________________________\n");
                }
                st = st->next;
            }
            if (g == 0){
                printf("没有任何数据！");
            }

            break;
        }
        case 6:{
            int g = 0;
            printf("请输入要查询的政治面貌: ");
            scanf("%s", poli);
            st = L->next;
            while (st != NULL) {
                if (strcmp(poli, st->poli) == 0) {
                    g = 1;
                    printf("________________________________________________________________\n");
                    printf("|学号\t|姓名\t|性别\t|家庭住址: 省|市：\t |出生日期\t|政治面貌    |联系电话\t |电子邮件\n");
                    printf("________________________________________________________________\n");
                    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                    printf("________________________________________________________________\n");
                }
                st = st->next;
            }
            if (g == 0){
                printf("没有任何数据！");
            }

            break;
        }
        case 7:{
            printf("请输入要查询的电话号码: ");
            scanf("%s", phone);
            st = Search_phone(phone, L);

            if (st == NULL) {
                printf("查无此人！\n");
            }
            else {
                printf("________________________________________________________________\n");
                printf("|学号\t|姓名\t|性别\t|家庭住址: 省|市：\t |出生日期\t|政治面貌    |联系电话\t |电子邮件\n");
                printf("________________________________________________________________\n");
                printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                printf("________________________________________________________________\n");
            }
            break;
        }
        case 8:{
            printf("请输入要查询的个人邮箱: ");
            scanf("%s", mail);
            st = Search_mail(mail, L);

            if (st == NULL) {
                printf("查无此人！\n");
            }
            else {
                printf("________________________________________________________________\n");
                printf("|学号\t|姓名\t|性别\t|家庭住址: 省|市：\t |出生日期\t|政治面貌    |联系电话\t |电子邮件\n");
                printf("________________________________________________________________\n");
                printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                printf("________________________________________________________________\n");
            }
            break;
        }
    }
}

// 按学号进行查找
node* Search_id(int id, node* L) {
    node* p = L->next;

    while (p != NULL) {
        if (p->ID == id) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// 按姓名进行查找
user* verification(char name[], char password[], user* L) {
    user* p = L->next;

    while (p != NULL) {
        if ((strcmp(name, p->Name) == 0) && (strcmp(password, p->password) == 0)) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
// 按照性别进行查找
node* Search_sex(char sex[], node* L) {
    node *p = L->next;

    while (p != NULL) {
        if (strcmp(sex, p->Sex) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
// 按照省份进行查询
node* Search_province(char Province[], node* L) {
    node *p = L->next;

    while (p != NULL) {
        if (strcmp(Province, p->Province) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
// 按照市区进行查询
node* Search_town(char Town[], node* L) {
    node *p = L->next;

    while (p != NULL) {
        if (strcmp(Town, p->Town) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
// 按照政治面貌进行查询
node* Search_poli(char poli[], node* L) {
    node *p = L->next;

    while (p != NULL) {
        if (strcmp(poli, p->poli) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
// 按照电话号码进行查询
node* Search_phone(char phone[], node* L) {
    node *p = L->next;

    while (p != NULL) {
        if (strcmp(phone, p->phone) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
// 按照电话号码进行查询
node* Search_mail(char mail[], node* L) {
    node *p = L->next;

    while (p != NULL) {
        if (strcmp(mail, p->mail) == 0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
//管理员权限
void print(node* L) {
    node* p = L->next;
    while (p != NULL) {
        printf("%d %s %s %s %s %s %s %s %s\n", p->ID, p->Name, p->Sex, p->Province, p->Town, p->born, p->poli, p->phone, p->mail);
        p = p->next;
    }
}

// 退出管理系统
void goodbye() {
    Write_FILE(&list, &list_sheng, &list_shi);
    Write_user(&list_user);
    printf("欢迎下次使用学生信息管理系统！");
    exit(0);// 结束程序
}
// 学号从大到小
bool cmp_big_ID(node e1, node e2)
{
    return e1.ID > e2.ID;
}

// 学号从小到大
bool cmp_small_ID(node e1, node e2)
{
    return e1.ID < e2.ID;
}
void Sort(node* L)
{
    int choice = 0;
    printf("按照学号从大到小排序 ---- 1\n");
    printf("按照学号从小到大排序 ---- 2\n");
    printf("请选择排序方式：");
    scanf("%d", &choice);

    int flag = 0;
    for (node* p = L->next; p != NULL; p = p->next)
    {
        for (node* q = p; q != NULL; q = q->next)
        {
            switch (choice)
            {
                case 1:
                    if (!cmp_big_ID(*p, *q))
                    {
                        flag = 1;
                    }
                    break;
                case 2:
                    if (!cmp_small_ID(*p, *q))
                    {
                        flag = 1;
                    }
                    break;
            }
            if (flag == 1)
            {
                // 交换数据域
                node t = *p;
                *p = *q;
                *q = t;
                // 处理指针域
                t.next = p->next;
                p->next = q->next;
                q->next = t.next;
                flag = 0;
            }
        }
    }
}


int main() {
    int choice = 0;
    Read_FILE(&list, &list_sheng, &list_shi);
    Read_FILE_user(&list_user);
    while (true) {
        set_password();
        welcome();
        scanf("%d", &choice);
        switch (choice) {
            case 1:// 增加学生信息
                Add_Printf();
                break;
            case 2:// 删除学生信息
                Delete_Printf(&list);
                break;
            case 3:// 修改学生信息
                Fix(&list);
                break;
            case 4:// 查询学生信息
                Search_Printf(&list);
                break;
            case 5:
                Sort(&list);
                break;
            case 6:
                print(&list);
                break;
            case 0:// 退出管理系统
                goodbye();
                break;
        }
        printf("是否需要继续操作？（Yes：1 / No：0)：");
        scanf("%d", &choice);
        getchar();
        if (choice == 0) {
            goodbye();
            break;
        }
    }
    return 0;
}
