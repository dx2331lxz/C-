// �������ó���Ϊѧ����Ϣ�������,��Ҫ����Ա�˺Ų��ܲ�����
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>
#include <io.h>

// ѧ����Ϣ�ṹ��
typedef struct Node {
    int ID;// ѧ��
    char Name[50];// ����
    char Sex[10];// �Ա�
    char Province[20];// ʡ
    int Province_ID;// ʡ������
    int Town_ID;//�е�����
    char Town[20];// ��
    char born[20];//��������
    char poli[20];//������ò
    char phone[20];//�ֻ��绰
    char mail[40];//�����ʼ�
    struct Node* next;// ָ����
} node;

// ����Ա�ṹ��
typedef struct User {
    char Name[50];
    char password[50];
    struct User* next;
} user;

node list;// ����
node list_sheng;// ����
node list_shi;// ����
user list_user;

//��ȡ����
int num, num1;

// ��ȡ�ļ�
int Read_FILE(node* L, node* L1, node* L2);

// �����ļ�
int Write_FILE(node* L, node* L1, node* L2);

int Save_FILE_student_information(node* L);

int Save_FILE_student_address_sheng(node* L);

int Save_FILE_student_address_shi(node* L);

int Write_user(user *L);

// ���˵�����
void welcome();

// ��½ҳ��
void set_password();
// ����û���Ϣ
void Set_User(char name[],char password[],user *L);
//��ȡ����Ա��Ϣ
int Read_FILE_user(user* L);
// ����ѧ����Ϣ
void Add(node* L, node e);// ����
void Add_Printf();// ����

// ɾ��ѧ����Ϣ
void Delete_Printf(node* L);// ����
void Delete(node* s);// ����

// �޸�ѧ����Ϣ
void Fix(node* L);

// ��ѯѧ����Ϣ
void Search_Printf(node* L);// ����
node* Search_id(int id, node* L);// ��ѧ�Ž��в���
user* verification(char name[], char password[], user* L); // �����Ա���в���
node* Search_province(char Province[], node* L);// ����ʡ�ݽ��в�ѯ
node* Search_town(char Town[], node* L); // �����������в�ѯ
node* Search_poli(char poli[], node* L); // ����������ò���в�ѯ
node* Search_phone(char phone[], node* L); // ���յ绰������в�ѯ
node* Search_mail(char mail[], node* L);// ����������в�ѯ

// �˳�����ϵͳ
void goodbye();


void welcome() {
    //    system("cls");
    printf("--------------------------------------------------------------- \n");
    printf("|                       ѧ����Ϣ����ϵͳ                       | \n");
    printf("|                    1 ---- ����ѧ����Ϣ                      | \n");
    printf("|                    2 ---- ɾ��ѧ����Ϣ                      | \n");
    printf("|                    3 ---- �޸�ѧ����Ϣ                      | \n");
    printf("|                    4 ---- ��ѯѧ����Ϣ                      | \n");
    printf("|                    5 ---- ����ѧ����Ϣ                      | \n");
    printf("|                    6 ---- չʾ����ѧ����Ϣ                   | \n");
    printf("|                    0 ---- �˳�����ϵͳ                      | \n");
    printf("----------------------------------------------------------------\n");

    printf("��ѡ����Ҫʵ�ֵĹ��ܣ����֣���");
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
    printf("|           ��ӭ����ѧ����Ϣ����ϵͳ            |\n");
    printf("------------------------------------------- \n");
    printf("�Ƿ�ӵ���˻�����Y��or��N��\n");
    scanf("%c", &choose);
    getchar();
    if (choose == 'Y'){
        printf("�������û�����\n");
        scanf("%s", name);
        printf("���������룺\n");
        scanf("%s", password);
        while (i == 1){
            if (verification(name, password, &list_user) == NULL){
                printf("�û������������,���������룺\n");
                printf("�������û�����\n");
                scanf("%s", name);
                printf("���������룺\n");
                scanf("%s", password);
            }
            else {
                break;
            }
        }
    }
    else{
        printf("�Ƿ�ע�᣿Y or N\n");
        scanf("%c", &choose1);
        if (choose1 == 'Y'){
            printf("�������û�����\n");
            scanf("%s", name1);
            printf("���������룺\n");
            scanf("%s", password1);
            getchar();
            Set_User(name1, password1, &list_user);
            set_password();
        } else {
            printf("�ټ�������");
            goodbye();
        }
    }
}
// ��ʡ���а����Ż��ķ�ʽ���д���
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
            // β�巨
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
            // β�巨
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
// ��ȡ�ļ� ������Ա��
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

        // β�巨
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
// ��ȡ�ļ���ѧ����
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

        // β�巨
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

        // β�巨
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

        // β�巨
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

// �����ļ�
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
//�����ļ�
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


// ����ѧ����Ϣ
void Add_Printf() {
    node st;
    printf("����������ѧ���������Ϣ��\n");
    printf("ѧ�ţ�");
    scanf("%d", &st.ID);
    printf("������");
    scanf("%s", st.Name);
    printf("�Ա�");
    scanf("%s", st.Sex);
    printf("��ͥסַ��ʡ����");
    scanf("%s", st.Province);
    printf("��ͥסַ���У���");
    scanf("%s", st.Town);
    printf("�������ڣ��밴�գ���-��-�� ����ʽ���룩");
    scanf("%s", st.born);
    printf("������ò��");
    scanf("%s", st.poli);
    printf("������ϵ�绰��");
    scanf("%s", st.phone);
    printf("����������䣺");
    scanf("%s", st.mail);

    Add(&list, st);
}

void Add(node* L, node e) {
    // β�巨
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

// ɾ��ѧ����Ϣ
void Delete_Printf(node* L) {
    int id;

    node* p;

    printf("������Ҫɾ����ѧ����ѧ�ţ�");
    scanf("%d", &id);
    node* st = Search_id(id, L);
    p = st;

    if (st == NULL) {
        printf("���޴��ˣ�\n");
        return;
    }

    st = st->next;
    printf("________________________________________________________________\n");
    printf("|ѧ��\t|����\t|�Ա�\t|��ͥסַ: ʡ|�У�\t |��������\t|������ò    |��ϵ�绰\t |�����ʼ�\n");
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

// �޸�ѧ����Ϣ
void Fix(node* L) {
    system("cls");
    int id;
    printf("������Ҫ�޸ĵ�ѧ����ѧ�ţ�");
    scanf("%d", &id);
    node* st = Search_id(id, L);

    if (st == NULL) {
        printf("���޴��ˣ�\n");
        return;
    }


    int choice = 0;
    while (1) {
        system("cls");

        // ���һ����Ҫ�޸ĵ�ѧ���ɼ�
        printf("________________________________________________________________\n");
        printf("|ѧ��\t|����\t|�Ա�\t|��ͥסַ: ʡ|�У�\t |��������\t|������ò    |��ϵ�绰\t |�����ʼ�\n");
        printf("________________________________________________________________\n");
        printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
        printf("________________________________________________________________\n");

        printf("�޸����� ---- 1\n");
        printf("�޸��Ա� ---- 2\n");
        printf("�޸ļ�ͥסַ��ʡ�� ---- 3\n");
        printf("�޸ļ�ͥסַ���У� ---- 4\n");
        printf("�޸ĳ������� ---- 5\n");
        printf("�޸�������ò ---- 6\n");
        printf("�޸���ϵ�绰 ---- 7\n");
        printf("�޸ĵ����ʼ� ---- 8\n");

        printf("������Ҫ�޸ĵ���Ϣ��");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("������������");
                scanf("%s", st->Name);
                break;
            case 2:
                printf("�������Ա�");
                scanf("%s", st->Sex);
                break;
            case 3:
                printf("�������ͥסַ��ʡ����");
                scanf("%s", st->Province);
                break;
            case 4:
                printf("�������ͥסַ���У���");
                scanf("%s", st->Town);
                break;
            case 5:
                printf("������������ڣ�");
                scanf("%s", st->born);
                break;
            case 6:
                printf("������������ò��");
                scanf("%s", st->poli);
                break;
            case 7:
                printf("��������ϵ�绰��");
                scanf("%s", st->phone);
                break;
            case 8:
                printf("������������䣺");
                scanf("%s", st->mail);
                break;
        }
        printf("�Ƿ�����޸ĸ�ѧ����Ϣ����Yes��1 / No��0����");
        scanf("%d", &choice);
        if (choice == 0) {
            break;
        }
    }

    // �޸���ɺ��ѧ������Ϣ
    printf("________________________________________________________________\n");
    printf("|ѧ��\t|����\t|�Ա�\t|��ͥסַ: ʡ|�У�\t |��������\t|������ò    |��ϵ�绰\t |�����ʼ�\n");
    printf("________________________________________________________________\n");
    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
    printf("________________________________________________________________\n");

}

// ��ѯѧ����Ϣ
void Search_Printf(node* L) {

    int choice = 0;
    printf("����ѧ�Ų�ѯ ---- 1\n");
    printf("����������ѯ ---- 2\n");
    printf("�����Ա��ѯ ---- 3\n");
    printf("���ռ�ͥסַ��ʡ����ѯ ---- 4\n");
    printf("���ռ�ͥסַ���У���ѯ ---- 5\n");
    printf("����������ò��ѯ ---- 6\n");
    printf("���յ绰�����ѯ ---- 7\n");
    printf("���ո��������ѯ ---- 8\n");
    printf("�������ѯ��ʽ��");
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
            printf("������Ҫ��ѯ��ѧ�ţ�");
            scanf("%d", &id);
            st = Search_id(id, L);

            if (st == NULL) {
                printf("���޴��ˣ�\n");
            }
            else {
                printf("________________________________________________________________\n");
                printf("|ѧ��\t|����\t|�Ա�\t|��ͥסַ: ʡ|�У�\t |��������\t|������ò    |��ϵ�绰\t |�����ʼ�\n");
                printf("________________________________________________________________\n");
                printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                printf("________________________________________________________________\n");
            }
            break;
        }
        case 2:{
            int g = 0;
            printf("������Ҫ��ѯ��������");
            scanf("%s", name);
            st = L->next;
            while (st != NULL) {
                if (strcmp(name, st->Name) == 0) {
                    g = 1;
                    printf("________________________________________________________________\n");
                    printf("|ѧ��\t|����\t|�Ա�\t|��ͥסַ: ʡ|�У�\t |��������\t|������ò    |��ϵ�绰\t |�����ʼ�\n");
                    printf("________________________________________________________________\n");
                    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                    printf("________________________________________________________________\n");
                }
                st = st->next;
            }
            if (g == 0){
                printf("û���κ����ݣ�");
            }

            break;
        }
        case 3:{
            int g = 0;
            printf("������Ҫ��ѯ���Ա�: ");
            scanf("%s", sex);
            st = L->next;
            while (st != NULL) {
                if (strcmp(sex, st->Sex) == 0) {
                    g = 1;
                    printf("________________________________________________________________\n");
                    printf("|ѧ��\t|����\t|�Ա�\t|��ͥסַ: ʡ|�У�\t |��������\t|������ò    |��ϵ�绰\t |�����ʼ�\n");
                    printf("________________________________________________________________\n");
                    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                    printf("________________________________________________________________\n");
                }
                st = st->next;
            }
            if (g == 0){
                printf("û���κ����ݣ�");
            }

            break;
        }
        case 4:{
            int g = 0;
            printf("������Ҫ��ѯ��ʡ��: ");
            scanf("%s", Province);
            st = L->next;
            while (st != NULL) {
                if (strcmp(Province, st->Province) == 0) {
                    g = 1;
                    printf("________________________________________________________________\n");
                    printf("|ѧ��\t|����\t|�Ա�\t|��ͥסַ: ʡ|�У�\t |��������\t|������ò    |��ϵ�绰\t |�����ʼ�\n");
                    printf("________________________________________________________________\n");
                    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                    printf("________________________________________________________________\n");
                }
                st = st->next;
            }
            if (g == 0){
                printf("û���κ����ݣ�");
            }

            break;
        }
        case 5:{
            int g = 0;
            printf("������Ҫ��ѯ����: ");
            scanf("%s", Town);
            st = L->next;
            while (st != NULL) {
                if (strcmp(Town, st->Town) == 0) {
                    g = 1;
                    printf("________________________________________________________________\n");
                    printf("|ѧ��\t|����\t|�Ա�\t|��ͥסַ: ʡ|�У�\t |��������\t|������ò    |��ϵ�绰\t |�����ʼ�\n");
                    printf("________________________________________________________________\n");
                    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                    printf("________________________________________________________________\n");
                }
                st = st->next;
            }
            if (g == 0){
                printf("û���κ����ݣ�");
            }

            break;
        }
        case 6:{
            int g = 0;
            printf("������Ҫ��ѯ��������ò: ");
            scanf("%s", poli);
            st = L->next;
            while (st != NULL) {
                if (strcmp(poli, st->poli) == 0) {
                    g = 1;
                    printf("________________________________________________________________\n");
                    printf("|ѧ��\t|����\t|�Ա�\t|��ͥסַ: ʡ|�У�\t |��������\t|������ò    |��ϵ�绰\t |�����ʼ�\n");
                    printf("________________________________________________________________\n");
                    printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                    printf("________________________________________________________________\n");
                }
                st = st->next;
            }
            if (g == 0){
                printf("û���κ����ݣ�");
            }

            break;
        }
        case 7:{
            printf("������Ҫ��ѯ�ĵ绰����: ");
            scanf("%s", phone);
            st = Search_phone(phone, L);

            if (st == NULL) {
                printf("���޴��ˣ�\n");
            }
            else {
                printf("________________________________________________________________\n");
                printf("|ѧ��\t|����\t|�Ա�\t|��ͥסַ: ʡ|�У�\t |��������\t|������ò    |��ϵ�绰\t |�����ʼ�\n");
                printf("________________________________________________________________\n");
                printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                printf("________________________________________________________________\n");
            }
            break;
        }
        case 8:{
            printf("������Ҫ��ѯ�ĸ�������: ");
            scanf("%s", mail);
            st = Search_mail(mail, L);

            if (st == NULL) {
                printf("���޴��ˣ�\n");
            }
            else {
                printf("________________________________________________________________\n");
                printf("|ѧ��\t|����\t|�Ա�\t|��ͥסַ: ʡ|�У�\t |��������\t|������ò    |��ϵ�绰\t |�����ʼ�\n");
                printf("________________________________________________________________\n");
                printf("|%d     |%s    |%s     |%s\t  |%s\t|%s   |%s\t|%s |%s\n", st->ID, st->Name, st->Sex, st->Province, st->Town, st->born, st->poli, st->phone, st->mail);
                printf("________________________________________________________________\n");
            }
            break;
        }
    }
}

// ��ѧ�Ž��в���
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

// ���������в���
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
// �����Ա���в���
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
// ����ʡ�ݽ��в�ѯ
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
// �����������в�ѯ
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
// ����������ò���в�ѯ
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
// ���յ绰������в�ѯ
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
// ���յ绰������в�ѯ
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
//����ԱȨ��
void print(node* L) {
    node* p = L->next;
    while (p != NULL) {
        printf("%d %s %s %s %s %s %s %s %s\n", p->ID, p->Name, p->Sex, p->Province, p->Town, p->born, p->poli, p->phone, p->mail);
        p = p->next;
    }
}

// �˳�����ϵͳ
void goodbye() {
    Write_FILE(&list, &list_sheng, &list_shi);
    Write_user(&list_user);
    printf("��ӭ�´�ʹ��ѧ����Ϣ����ϵͳ��");
    exit(0);// ��������
}
// ѧ�ŴӴ�С
bool cmp_big_ID(node e1, node e2)
{
    return e1.ID > e2.ID;
}

// ѧ�Ŵ�С����
bool cmp_small_ID(node e1, node e2)
{
    return e1.ID < e2.ID;
}
void Sort(node* L)
{
    int choice = 0;
    printf("����ѧ�ŴӴ�С���� ---- 1\n");
    printf("����ѧ�Ŵ�С�������� ---- 2\n");
    printf("��ѡ������ʽ��");
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
                // ����������
                node t = *p;
                *p = *q;
                *q = t;
                // ����ָ����
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
            case 1:// ����ѧ����Ϣ
                Add_Printf();
                break;
            case 2:// ɾ��ѧ����Ϣ
                Delete_Printf(&list);
                break;
            case 3:// �޸�ѧ����Ϣ
                Fix(&list);
                break;
            case 4:// ��ѯѧ����Ϣ
                Search_Printf(&list);
                break;
            case 5:
                Sort(&list);
                break;
            case 6:
                print(&list);
                break;
            case 0:// �˳�����ϵͳ
                goodbye();
                break;
        }
        printf("�Ƿ���Ҫ������������Yes��1 / No��0)��");
        scanf("%d", &choice);
        getchar();
        if (choice == 0) {
            goodbye();
            break;
        }
    }
    return 0;
}
