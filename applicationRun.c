//
// Created by LittleJackey on 2022/5/12.
//
#include "StudentManagementSystem.h"

bool login(void) {
    const char *password = "123456";  // ��¼����
    char pwd[17];
    for (int i = 0; i < 3; ++i) {
        printf("���������Ա����(ʣ�����%d)��", 3 - i);
        restrictInput(17, pwd, 0);
        if (strcmp(password, pwd) == 0) {
            printf("��¼�ɹ���\n");
            return true;
        } else {
            printf("�������");
        }
    }
    return false;
}

void printWelcome(void) {
    char welcome[8][200] = {
            {"__/\\\\\\_______________________/\\\\\\___/\\\\\\\\\\\\\\\\\\\\\\\\\\\\____/\\\\\\__________________/\\\\\\\\\\\\\\\\\\_________/\\\\\\\\\\\\\\\\\\\\________/\\\\\\\\____________/\\\\\\\\_____/\\\\\\\\\\\\\\\\\\\\\\\\\\\\_"},
            {" _\\//\\\\\\_____________________/\\\\\\___\\/\\\\\\//////////____\\/\\\\\\_______________/\\\\\\////////_______/\\\\\\/////////\\\\\\_____\\/\\\\\\\\\\\\________/\\\\\\\\\\\\____\\/\\\\\\//////////__"},
            {"   _\\//\\\\\\________/\\\\\\_______/\\\\\\____\\/\\\\\\______________\\/\\\\\\_____________/\\\\\\/______________/\\\\\\/________\\///\\\\\\___\\/\\\\\\//\\\\\\____/\\\\\\//\\\\\\____\\/\\\\\\____________"},
            {"     _\\//\\\\\\_____/\\\\\\\\\\\\\\____/\\\\\\_____\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\___\\/\\\\\\____________\\/\\\\\\______________\\/\\\\\\___________\\/\\\\\\___\\/\\\\\\\\///\\\\\\/\\\\\\/_\\/\\\\\\____\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\_"},
            {"       _\\//\\\\\\___/\\\\\\_//\\\\\\__/\\\\\\______\\/\\\\\\//////////____\\/\\\\\\____________\\/\\\\\\______________\\/\\\\\\___________\\/\\\\\\___\\/\\\\\\__\\///\\\\\\/___\\/\\\\\\____\\/\\\\\\//////////__"},
            {"         _\\//\\\\\\_/\\\\\\__\\//\\\\\\/\\\\\\_______\\/\\\\\\______________\\/\\\\\\____________\\///\\\\\\____________\\///\\\\\\________/\\\\\\/____\\/\\\\\\____\\///_____\\/\\\\\\____\\/\\\\\\____________"},
            {"           _\\//\\\\\\\\\\/____\\//\\\\\\\\\\________\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\___\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\___\\///\\\\\\\\\\\\\\\\\\\\\\____\\///\\\\\\\\\\\\\\\\\\\\\\/______\\/\\\\\\_____________\\/\\\\\\____\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\_"},
            {"             _\\/////_______\\/////_________\\//////////////____\\//////////////______\\///////////_______\\///////////________\\///______________\\///_____\\//////////////__"},
    };
    for (int i = 0; i < 8; ++i) {
        printf("%s\n", welcome[i]);
    }
    putchar('\n');
}

void applicationRun(void) {
    creatDat();
    // �½�����
    LinkList *head = (LinkList *) malloc(sizeof(LinkList));
    head->next = NULL;
    LinkList *ptemp = head;
    LinkList *pnode = head;
    printf("��ѡ����(��8��ʾ���ܲ˵�)��");

    int choice;
    while ((choice = getChoice()) != 9) {
        // �ж��û���ѡ��
        switch (choice) {
            case 1: // ¼��ѧ����Ϣ
                setStudent(&ptemp);
                saveStudentData(&pnode);
                break;
            case 2: // ��ӡѧ����Ϣ
                printAllStudent(getNumberOfStudents());
                break;
            case 3: // ����ѧ����Ϣ
                sortOfStudent(getNumberOfStudents());
                break;
            case 4: // ͳ��ѧ������
                statisticsStudentInformation();
                break;
            case 5: // ����ѧ����Ϣ
                findStudent(getNumberOfStudents());
                break;
            case 6: // �޸�ѧ����Ϣ
                alterStudent(getNumberOfStudents());
                break;
            case 7: // ɾ��ѧ����Ϣ
                dropStudent(getNumberOfStudents());
                break;
            case 8: // ��ʾ���ܲ˵�
                printFunctionMenu();
                break;
            default:
                printf("Program error!\n");
                break;
        }

        printf("\n��ѡ����(��8��ʾ���ܲ˵�)��");
    }
    emptyTheList(&head);
}

void menu(void) {
    printf("*************************************************\n");
    printf("*\t  ��ӭʹ�ø�Уѧ���ɼ�����ϵͳ\t\t*\n");
    printf("*\t\tBy Little Jackey\t\t*\n");
    printf("*************************************************\n");
    printf("*\t\t1.¼��ѧ����Ϣ\t\t\t*\n");
    printf("*\t\t2.��ʾȫ��ѧ��\t\t\t*\n");
    printf("*\t\t3.����ѧ����Ϣ\t\t\t*\n");
    printf("*\t\t4.ͳ��ѧ����Ϣ\t\t\t*\n");
    printf("*\t\t5.����ѧ����Ϣ\t\t\t*\n");
    printf("*\t\t6.�޸�ѧ����Ϣ\t\t\t*\n");
    printf("*\t\t7.ɾ��ѧ����Ϣ\t\t\t*\n");
    printf("*\t\t8.��ʾ���ܲ˵�\t\t\t*\n");
    printf("*\t\t9.�˳�����ϵͳ\t\t\t*\n");
    printf("*************************************************\n");
}

void creatDat(void) {
    if (isFileExist() == -1) {
        FILE *fp;
        if ((fp = fopen(DATA_PATH, "ab")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }
        fclose(fp);
        printf("%sд��ɹ���\n", DATA_NAME);
    }
}

int getChoice(void) {
    char input[2];
    restrictInput(2, input, 1);

    int choice;

    char *end;
    choice = strtol(input, &end, 10);

    if (*end != '\0') {
        printf("����ȷ����ѡ�");
        choice = getChoice();
    }

    if (choice == 0) {
        printf("����ȷ����ѡ�");
        choice = getChoice();
    }

    return choice;
}

void restrictInput(int max, char result[], int mode) {
    int i = 0;
    unsigned char x;

    while ((x = getch()) != '\r') {
        if (x != '\b' && i >= 0 && i < max - 1)//��ΪҪ���ַ����ӽ�β��\0,����Ҫ��һ��λ��max-1��
        {
            result[i] = x;
            i++;
            if (mode) {
                printf("%c", x);
            } else {
                printf("*");
            }

        } else if (x == '\b' && i > 0) {
            i--;
            printf("\b \b");
        }
    }
    printf("\n");
    result[i] = '\0';
}

void setStudent(LinkList **ptemp) {
    // �����½ڵ�
    LinkList *pnew = (LinkList *) malloc(sizeof(LinkList));

    // ����ѧ����Ϣ
    printf("������ѧ��ѧ�ţ�");
    pnew->stu.stuId = getStuId(0, 0);
    while (isIdExist(pnew->stu.stuId, getNumberOfStudents())) {
        printf("��ѧ���Ѵ��ڣ�����������ѧ�ţ�");
        pnew->stu.stuId = getStuId(0, 0);
    }

    printf("������ѧ��������");
    getStuName(pnew->stu.stuName, 0);

    printf("������ѧ���Ա�(���� M(��)/ F(Ů)�����ִ�Сд)��");
    getStuSex(pnew->stu.stuSex, 0);

    printf("������ѧ������(1~99)��");
    pnew->stu.stuAge = getStuAge(0);

    printf("������ѧ�����ĳɼ�(0~150, ������Ĭ��Ϊ0)��");
    pnew->stu.stuScore[0] = getStuScore(0, 150);

    printf("������ѧ����ѧ�ɼ�(0~150, ������Ĭ��Ϊ0)��");
    pnew->stu.stuScore[1] = getStuScore(0, 150);

    printf("������ѧ��Ӣ��ɼ�(0~150, ������Ĭ��Ϊ0)��");
    pnew->stu.stuScore[2] = getStuScore(0, 150);

    // �����ܳɼ�
    pnew->stu.stuScore[3] = pnew->stu.stuScore[0] + pnew->stu.stuScore[1] + pnew->stu.stuScore[2];

    (*ptemp)->next = pnew;
    *ptemp = pnew;
    pnew->next = NULL;
}

long long getStuId(short mode, int findIndex) {
    long long id;
    char stuId[19];
    restrictInput(19, stuId, 1);

    if (mode == 0) {
        char *end;
        id = strtoll(stuId, &end, 10);

        if (*end != '\0' || id <= 0) {
            printf("ѧ�Ų��Ϸ�������������ѧ�ţ�");
            id = getStuId(0, 0);
        }

        return id;
    } else if (mode == 1) {
        if (stuId[0] == '\0') {
            return -1;
        }

        char *end;
        id = strtoll(stuId, &end, 10);

        if (*end != '\0' || id <= 0) {
            printf("ѧ�Ų��Ϸ�������������ѧ�ţ�");
            id = getStuId(1, findIndex);
        }

        if (isAlterStuIdExist(id, findIndex)) {
            printf("��ѧ���Ѵ��ڣ�����������ѧ�ţ�");
            id = getStuId(1, findIndex);
        }

        return id;
    } else {
        if (stuId[0] == 'q' || stuId[0] == 'Q') {
            return -1;
        } else {
            char *end;
            id = strtoll(stuId, &end, 10);

            if (*end != '\0' || id <= 0) {
                printf("ѧ�Ų��Ϸ�������������ѧ�ţ�");
                id = getStuId(2, 0);
            }
        }
        return id;
    }
}

bool isIdExist(long long id, long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;
        Student data[numberOfStudent + 1];

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }

        rewind(fp);
        fread(data, sizeof(Student), numberOfStudent, fp);
        fclose(fp);

        for (int i = 0; i < numberOfStudent; i++) {
            if (id == data[i].stuId) {
                return true;
            }
        }
    }

    return false;
}

void getStuName(char stuName[], short mode) {
    char name[17];
    restrictInput(17, name, 1);

    if (mode == 0) {
        while (name[0] == ' ' || name[0] == '\0') {
            printf("��������Ϊ�գ����������룺");
            restrictInput(17, name, 1);
        }

        strcpy(stuName, name);
    } else {
        while (true) {
            if (name[0] == '\0') {
                break;
            } else {
                if (name[0] == ' ') {
                    printf("��������Ϊ�գ����������룺");
                    restrictInput(17, name, 1);
                    continue;
                }

                strcpy(stuName, name);
                break;
            }
        }
    }
}

void getStuSex(char stuSex[], short mode) {
    char sex[2];
    restrictInput(2, sex, 1);

    if (mode == 0) {
        while (sex[0] != 'M' && sex[0] != 'F' && sex[0] != 'm' && sex[0] != 'f') {
            printf("������Ĳ��� M �� F(�����ִ�Сд)!\n���������룺");
            restrictInput(2, sex, 1);
        }

        if (sex[0] == 'M' || sex[0] == 'm') {
            strcpy(stuSex, "��");
        } else if (sex[0] == 'F' || sex[0] == 'f') {
            strcpy(stuSex, "Ů");
        }
    } else {
        if (sex[0] == '\0') {
            return;
        } else {
            while (sex[0] != 'M' && sex[0] != 'F' && sex[0] != 'm' && sex[0] != 'f') {
                printf("������Ĳ��� M �� F(�����ִ�Сд)!\n���������룺");
                restrictInput(2, sex, 1);
            }

            if (sex[0] == 'M' || sex[0] == 'm') {
                strcpy(stuSex, "��");
            } else if (sex[0] == 'F' || sex[0] == 'f') {
                strcpy(stuSex, "Ů");
            }
        }
    }
}

long getStuAge(short mode) {
    long age;
    char stuAge[3];
    restrictInput(3, stuAge, 1);

    if (mode == 0) {
        char *end;
        age = strtol(stuAge, &end, 10);

        if (*end != '\0' || age <= 0) {
            printf("��������䲻�Ϸ������������룺");
            age = getStuAge(0);
        }

        return age;
    } else {
        if (stuAge[0] == '\0') {
            return -1;
        }

        char *end;
        age = strtol(stuAge, &end, 10);

        if (*end != '\0' || age <= 0) {
            printf("��������䲻�Ϸ������������룺");
            age = getStuAge(1);
        }

        return age;
    }
}

float getStuScore(short mode, float upperLimit) {
    float score;
    char studentScore[7];

    restrictInput(7, studentScore, 1);

    if (mode == 0) {
        char *end;
        score = strtof(studentScore, &end);

        if (*end != '\0' || score < 0 || score > upperLimit) {
            printf("������ĳɼ����Ϸ������������룺");
            score = getStuScore(0, upperLimit);
        }

        return score;
    } else {
        if (studentScore[0] == '\0') {
            return -1;
        }

        char *end;
        score = strtof(studentScore, &end);

        if (*end != '\0' || score < 0 || score > upperLimit) {
            printf("������ĳɼ����Ϸ������������룺");
            score = getStuScore(1, upperLimit);
        }

        return score;
    }
}

void printAllStudent(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }

        if (getc(fp) == EOF) {
            printf("����ѧ����Ϣ��\n");
        } else {
            Student data[numberOfStudent];
            rewind(fp);
            fread(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            printf("����ѧ����Ϣ���£�\n");
            printTable_1();
            printTable_2();
            printTable_1();
            for (int i = 0; i < numberOfStudent; i++) {
                printTable_3(data[i]);
            }
            printTable_1();
        }
    }
}

void printTable_1(void) {
    for (int i = 0; i < 76; i++) {
        if (i == 0 || i == 20 || i == 37 || i == 42 || i == 47 || i == 54 || i == 61 || i == 68 || i == 75) {
            printf("+");
        } else {
            printf("-");
        }
    }
    putchar('\n');
}

void printTable_2(void) {
    printf("|%-19s", "ѧ��");
    printf("|%-16s", "����");
    printf("|%-4s", "�Ա�");
    printf("|%-4s", "����");
    printf("|%-6s", "����");
    printf("|%-6s", "��ѧ");
    printf("|%-6s", "Ӣ��");
    printf("|%-6s|\n", "�ܳɼ�");
}

void printTable_3(Student data) {
    printf("|%-19lld", data.stuId);
    printf("|%-16s", data.stuName);
    printf("|%-4s", data.stuSex);
    printf("|%-4ld", data.stuAge);
    printf("|%-6.2f", data.stuScore[0]);
    printf("|%-6.2f", data.stuScore[1]);
    printf("|%-6.2f", data.stuScore[2]);
    printf("|%-6.2f|\n", data.stuScore[3]);
}

void saveStudentData(LinkList **pstart) {
    FILE *fp;
    LinkList *pnode = (*pstart)->next;

    if ((fp = fopen(DATA_PATH, "ab")) == NULL) {
        fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
        exit(EXIT_FAILURE);
    }

    while (pnode != NULL) {
        fwrite(&(pnode->stu), sizeof(Student), 1, fp);
        *pstart = pnode;
        pnode = pnode->next;
    }
    fclose(fp);
    printf("����ɹ���\n");
}

void sortOfStudent(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;
        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }

        if (getc(fp) == EOF) {
            printf("����ʧ�ܣ�����ѧ����Ϣ��\n");
        } else {
            printf("*************************************************\n");
            printf("*\t\t     ����ʽ\t\t\t*\n");
            printf("*************************************************\n");
            printf("*\tA.��ѧ������        B.��ѧ�Ž���\t*\n");
            printf("*\tC.�����ĳɼ�����    D.�����ĳɼ�����\t*\n");
            printf("*\tE.����ѧ�ɼ�����    F.����ѧ�ɼ�����\t*\n");
            printf("*\tG.��Ӣ��ɼ�����    H.��Ӣ��ɼ�����\t*\n");
            printf("*\tI.���ܳɼ�����      J.���ܳɼ�����\t*\n");
            printf("*************************************************\n");
            printf("*\t\t   q.ȡ������\t\t\t*\n");
            printf("*************************************************\n");

            Student data[numberOfStudent + 1];
            rewind(fp);
            fread(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            Student temp;
            printf("��ѡ������ʽ��");
            char choice = getSortChoice('J');
            choice = tolower(choice);
            switch (choice) {
                case 'a':
                    for (int i = 0; i < numberOfStudent - 1; i++) {
                        for (int j = 0; j < numberOfStudent - 1 - i; j++) {
                            if (data[j].stuId > data[j + 1].stuId) {
                                temp = data[j];
                                data[j] = data[j + 1];
                                data[j + 1] = temp;
                            }
                        }
                    }
                    break;
                case 'b':
                    for (int i = 0; i < numberOfStudent - 1; i++) {
                        for (int j = 0; j < numberOfStudent - 1 - i; j++) {
                            if (data[j].stuId < data[j + 1].stuId) {
                                temp = data[j];
                                data[j] = data[j + 1];
                                data[j + 1] = temp;
                            }
                        }
                    }
                    break;
                case 'c':
                    sortByScore(data, 0, numberOfStudent, 0);
                    break;
                case 'd':
                    sortByScore(data, 1, numberOfStudent, 0);
                    break;
                case 'e':
                    sortByScore(data, 0, numberOfStudent, 1);
                    break;
                case 'f':
                    sortByScore(data, 1, numberOfStudent, 1);
                    break;
                case 'g':
                    sortByScore(data, 0, numberOfStudent, 2);
                    break;
                case 'h':
                    sortByScore(data, 1, numberOfStudent, 2);
                    break;
                case 'i':
                    sortByScore(data, 0, numberOfStudent, 3);
                    break;
                case 'j':
                    sortByScore(data, 1, numberOfStudent, 3);
                    break;
                default:
                    printf("�ɹ�ȡ������\n");
                    return;
            }

            // ���� "sutdent.dat"
            fp = fopen(DATA_PATH, "wb");
            fwrite(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            printf("������ɣ�\n");
        }
    }
}

char getSortChoice(char upper) {
    char sortChoice[2];

    restrictInput(2, sortChoice, 1);

    while ((sortChoice[0] < 65 || sortChoice[0] > toupper(upper) && sortChoice[0] < 97 ||
            sortChoice[0] > tolower(upper)) &&
           (sortChoice[0] != 'q' && sortChoice[0] != 'Q')) {
        printf("����ȷ����ѡ�");
        restrictInput(2, sortChoice, 1);
    }
    return sortChoice[0];
}

void sortByScore(Student data[], int way, long numberOfStudent, int subject) {
    if (way == 0) {
        for (int i = 0; i < numberOfStudent - 1; i++) {
            for (int j = 0; j < numberOfStudent - 1 - i; j++) {
                if (data[j].stuScore[subject] > data[j + 1].stuScore[subject]) {
                    Student temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    } else {
        for (int i = 0; i < numberOfStudent - 1; i++) {
            for (int j = 0; j < numberOfStudent - 1 - i; j++) {
                if (data[j].stuScore[subject] < data[j + 1].stuScore[subject]) {
                    Student temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                }
            }
        }
    }
}

void statisticsStudentInformation(void) {
    if (isFileExist() == -1) {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        long numberOfStudent = getNumberOfStudents();
        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }


        if (getc(fp) == EOF) {
            printf("����ѧ����Ϣ��\n");
        } else {
            Student data[numberOfStudent];
            rewind(fp);
            fread(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            float chineseScoreSum = 0;  // ���ĳɼ�֮��
            float mathScoreSum = 0;     // ��ѧ�ɼ�֮��
            float englishScoreSum = 0;  // Ӣ��ɼ�֮��
            float totalScoreSum = 0;    // �ܳɼ�֮��

            float chineseScoreMax = data[0].stuScore[0];    // ���ĳɼ���߷�
            float mathScoreMax = data[0].stuScore[1];       // ��ѧ�ɼ���߷�
            float englishScoreMax = data[0].stuScore[2];    // Ӣ��ɼ���߷�
            float totalScoreMax = data[0].stuScore[3];      // �ܳɼ���߷�

            float chineseScoreMin = data[0].stuScore[0];    // ���ĳɼ���ͷ�
            float mathScoreMin = data[0].stuScore[1];       // ��ѧ�ɼ���ͷ�
            float englishScoreMin = data[0].stuScore[2];    // Ӣ��ɼ���ͷ�
            float totalScoreMin = data[0].stuScore[3];      // �ܳɼ���ͷ�
            for (int i = 0; i < numberOfStudent; ++i) {
                chineseScoreSum += data[i].stuScore[0];
                mathScoreSum += data[i].stuScore[1];
                englishScoreSum += data[i].stuScore[2];
                totalScoreSum += data[i].stuScore[3];

                // ����߷ֺ���ͷ�
                chineseScoreMax = chineseScoreMax < data[i].stuScore[0] ? data[i].stuScore[0] : chineseScoreMax;
                chineseScoreMin = chineseScoreMin > data[i].stuScore[0] ? data[i].stuScore[0] : chineseScoreMin;

                mathScoreMax = mathScoreMax < data[i].stuScore[1] ? data[i].stuScore[1] : mathScoreMax;
                mathScoreMin = mathScoreMin > data[i].stuScore[1] ? data[i].stuScore[1] : mathScoreMin;

                englishScoreMax = englishScoreMax < data[i].stuScore[2] ? data[i].stuScore[2] : englishScoreMax;
                englishScoreMin = englishScoreMin > data[i].stuScore[2] ? data[i].stuScore[2] : englishScoreMin;

                totalScoreMax = totalScoreMax < data[i].stuScore[3] ? data[i].stuScore[3] : totalScoreMax;
                totalScoreMin = totalScoreMin > data[i].stuScore[3] ? data[i].stuScore[3] : totalScoreMin;
            }
            // ��������ƽ����
            float chineseAverage = chineseScoreSum / (float) numberOfStudent;
            // ������ѧƽ����
            float mathAverage = mathScoreSum / (float) numberOfStudent;
            // ����Ӣ��ƽ����
            float englishAverage = englishScoreSum / (float) numberOfStudent;
            // ������ƽ����
            float totalAverage = totalScoreSum / (float) numberOfStudent;

            // �����ʾƽ���ɼ�
            for (int i = 0; i < 52; i++) {
                if (i == 0 || i == 9 || i == 20 || i == 31 || i == 42 || i == 51) {
                    printf("+");
                } else {
                    printf("-");
                }
            }
            putchar('\n');
            printf("|%-8s", "ѧ������");
            printf("|%-10s", "����ƽ����");
            printf("|%-10s", "��ѧƽ����");
            printf("|%-10s", "Ӣ��ƽ����");
            printf("|%-8s|\n", "��ƽ����");
            for (int i = 0; i < 52; i++) {
                if (i == 0 || i == 9 || i == 20 || i == 31 || i == 42 || i == 51) {
                    printf("+");
                } else {
                    printf("-");
                }
            }
            putchar('\n');
            printf("|%-8ld", numberOfStudent);
            printf("|%-10.2f", chineseAverage);
            printf("|%-10.2f", mathAverage);
            printf("|%-10.2f", englishAverage);
            printf("|%-8.2f|\n", totalAverage);
            for (int i = 0; i < 52; i++) {
                if (i == 0 || i == 9 || i == 20 || i == 31 || i == 42 || i == 51) {
                    printf("+");
                } else {
                    printf("-");
                }
            }
            putchar('\n');
            putchar('\n');

            // �����ʾ���ĳɼ���߷�
            printf("+");
            for (int i = 0; i < 74; i++) {
                printf("-");
            }
            printf("+\n");
            printf("|                              ");
            printf("���ĳɼ������");
            printf("                              |\n");
            printTable_1();
            printTable_2();
            printTable_1();
            for (int i = 0; i < numberOfStudent; ++i) {
                if (data[i].stuScore[0] == chineseScoreMax) {
                    printTable_3(data[i]);
                }
            }
            printTable_1();
            printf("|                              ");
            printf("���ĳɼ������");
            printf("                              |\n");
            printTable_1();
            printTable_2();
            printTable_1();
            for (int i = 0; i < numberOfStudent; ++i) {
                if (data[i].stuScore[0] == chineseScoreMin) {
                    printTable_3(data[i]);
                }
            }
            printTable_1();
            putchar('\n');

            // �����ʾ��ѧ�ɼ���߷�
            printf("+");
            for (int i = 0; i < 74; i++) {
                printf("-");
            }
            printf("+\n");
            printf("|                              ");
            printf("��ѧ�ɼ������");
            printf("                              |\n");
            printTable_1();
            printTable_2();
            printTable_1();
            for (int i = 0; i < numberOfStudent; ++i) {
                if (data[i].stuScore[1] == mathScoreMax) {
                    printTable_3(data[i]);
                }
            }
            printTable_1();
            printf("|                              ");
            printf("��ѧ�ɼ������");
            printf("                              |\n");
            printTable_1();
            printTable_2();
            printTable_1();
            for (int i = 0; i < numberOfStudent; ++i) {
                if (data[i].stuScore[1] == mathScoreMin) {
                    printTable_3(data[i]);
                }
            }
            printTable_1();
            putchar('\n');

            // �����ʾ��ѧ�ɼ���߷�
            printf("+");
            for (int i = 0; i < 74; i++) {
                printf("-");
            }
            printf("+\n");
            printf("|                              ");
            printf("Ӣ��ɼ������");
            printf("                              |\n");
            printTable_1();
            printTable_2();
            printTable_1();
            for (int i = 0; i < numberOfStudent; ++i) {
                if (data[i].stuScore[2] == englishScoreMax) {
                    printTable_3(data[i]);
                }
            }
            printTable_1();
            printf("|                              ");
            printf("Ӣ��ɼ������");
            printf("                              |\n");
            printTable_1();
            printTable_2();
            printTable_1();
            for (int i = 0; i < numberOfStudent; ++i) {
                if (data[i].stuScore[2] == englishScoreMin) {
                    printTable_3(data[i]);
                }
            }
            printTable_1();
            putchar('\n');

            // �����ʾ�ܳɼ���߷�
            printf("+");
            for (int i = 0; i < 74; i++) {
                printf("-");
            }
            printf("+\n");
            printf("|                               ");
            printf("�ܳɼ������");
            printf("                               |\n");
            printTable_1();
            printTable_2();
            printTable_1();
            for (int i = 0; i < numberOfStudent; ++i) {
                if (data[i].stuScore[3] == totalScoreMax) {
                    printTable_3(data[i]);
                }
            }
            printTable_1();
            printf("|                               ");
            printf("�ܳɼ������");
            printf("                               |\n");
            printTable_1();
            printTable_2();
            printTable_1();
            for (int i = 0; i < numberOfStudent; ++i) {
                if (data[i].stuScore[3] == totalScoreMin) {
                    printTable_3(data[i]);
                }
            }
            printTable_1();
        }
    }
}

long getNumberOfStudents(void) {
    if (isFileExist() == 0) {
        struct stat buf;
        stat(DATA_PATH, &buf);

        return buf.st_size / sizeof(Student);
    } else {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    }
}

void findStudent(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;
        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }


        if (getc(fp) == EOF) {
            printf("����ʧ�ܣ�����ѧ����Ϣ��\n");
        } else {
            Student data[numberOfStudent];
            rewind(fp);
            fread(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            printf("*********************************\n");
            printf("*\t     ���ҷ�ʽ\t\t*\n");
            printf("*********************************\n");
            printf("*\t    A.��ȷ����\t\t*\n");
            printf("*\t    B.ģ������\t\t*\n");
            printf("*********************************\n");
            printf("*\t    q.ȡ������\t\t*\n");
            printf("*********************************\n");

            printf("��ѡ��Ҫ���ҵķ�ʽ��");
            char choice_1 = getSortChoice('B');
            choice_1 = tolower(choice_1);
            if (choice_1 == 'a') {
                printf("*************************************************\n");
                printf("*\t\t     ��ȷ����\t\t\t*\n");
                printf("*************************************************\n");
                printf("*\tA.��ѧ�Ų���        B.����������\t*\n");
                printf("*\tC.�����ĳɼ�����    D.����ѧ�ɼ�����\t*\n");
                printf("*\tE.��Ӣ��ɼ�����    F.���ܳɼ�����\t*\n");
                printf("*************************************************\n");
                printf("*\t\t   q.ȡ������\t\t\t*\n");
                printf("*************************************************\n");
                printf("��ѡ��Ҫ���ҵķ�ʽ��");
                char choice_2 = getSortChoice('F');
                choice_2 = tolower(choice_2);
                switch (choice_2) {
                    case 'a':
                        findById(numberOfStudent);
                        break;
                    case 'b':
                        findByName(numberOfStudent);
                        break;
                    case 'c':
                        findByScore(numberOfStudent, 0, 0);
                        break;
                    case 'd':
                        findByScore(numberOfStudent, 0, 1);
                        break;
                    case 'e':
                        findByScore(numberOfStudent, 0, 2);
                        break;
                    case 'f':
                        findByScore(numberOfStudent, 0, 3);
                        break;
                    default:
                        printf("�ɹ�ȡ�����ң�\n");
                        break;
                }
            } else if (choice_1 == 'b') {
                printf("*************************************************\n");
                printf("*\t\t     ģ������\t\t\t*\n");
                printf("*************************************************\n");
                printf("*\tA.�����ĳɼ�����    B.����ѧ�ɼ�����\t*\n");
                printf("*\tC.��Ӣ��ɼ�����    D.���ܳɼ�����\t*\n");
                printf("*************************************************\n");
                printf("*\t\t   q.ȡ������\t\t\t*\n");
                printf("*************************************************\n");
                printf("��ѡ��Ҫ���ҵķ�ʽ��");
                char choice_3 = getSortChoice('D');
                choice_3 = tolower(choice_3);
                switch (choice_3) {
                    case 'a':
                        findByScore(numberOfStudent, 1, 0);
                        break;
                    case 'b':
                        findByScore(numberOfStudent, 1, 1);
                        break;
                    case 'c':
                        findByScore(numberOfStudent, 1, 2);
                        break;
                    case 'd':
                        findByScore(numberOfStudent, 1, 3);
                        break;
                    default:
                        printf("�ɹ�ȡ�����ң�\n");
                        break;
                }
            } else {
                printf("�ɹ�ȡ�����ң�\n");
                return;
            }
        }
    }
}

void findById(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        printf("������Ҫ����ѧ����ѧ�ţ�");
        long long id = getStuId(0, 0);

        Student data[numberOfStudent + 1];

        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }

        rewind(fp);
        fread(data, sizeof(Student), numberOfStudent, fp);
        fclose(fp);

        bool hasFind = false;
        for (int i = 0; i < numberOfStudent; i++) {
            if (data[i].stuId == id) {
                hasFind = true;

                printTable_1();
                printTable_2();
                printTable_1();
                printTable_3(data[i]);
                printTable_1();
                break;
            }
        }

        if (!hasFind) {
            printf("��δ���ҵ�������Ϣ��\n");
        }
    }
}

void findByName(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        printf("������Ҫ����ѧ����������");
        char needFindName[17];
        getStuName(needFindName, 0);

        Student data[numberOfStudent + 1];

        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }

        rewind(fp);
        fread(data, sizeof(Student), numberOfStudent, fp);
        fclose(fp);

        bool hasFind = false;

        for (int i = 0, j = 0; i < numberOfStudent; i++) {
            if ((strcmp(needFindName, data[i].stuName)) == 0) {
                hasFind = true;
                while (j < 1) { // j��������ֻѭ��һ��
                    printTable_1();
                    printTable_2();
                    printTable_1();
                    j++;
                }
                printTable_3(data[i]);
            }
        }
        if (hasFind == true) {
            printTable_1();
        }

        if (!hasFind) {
            printf("��δ���ҵ�������Ϣ��\n");
        }
    }
}

void findByScore(long numberOfStudent, short mode, short subject) {
    if (isFileExist() == -1) {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        Student data[numberOfStudent + 1];
        FILE *fp;
        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }

        rewind(fp);
        fread(data, sizeof(Student), numberOfStudent, fp);
        fclose(fp);

        if (mode == 0) {
            exactSearchByScore(data, numberOfStudent, subject);
        } else {
            fuzzySearchByScore(data, numberOfStudent, subject);
        }
    }
}


void exactSearchByScore(Student data[], long numberOfStudent, short subject) {
    switch (subject) {
        case 0:
            printf("������Ҫ���ҵ����ĳɼ�(0~150, ������Ĭ��Ϊ0)��");
            break;
        case 1:
            printf("������Ҫ���ҵ���ѧ�ɼ�(0~150, ������Ĭ��Ϊ0)��");
            break;
        case 2:
            printf("������Ҫ���ҵ�Ӣ��ɼ�(0~150, ������Ĭ��Ϊ0)��");
            break;
        case 3:
            printf("������Ҫ���ҵ��ܳɼ�(0~450, ������Ĭ��Ϊ0)��");
            break;
        default:
            break;
    }
    float needFindScore;
    if (subject == 3) {
        needFindScore = getStuScore(0, 450);
    } else {
        needFindScore = getStuScore(0, 150);
    }

    bool hasFind = false;
    for (int i = 0, j = 0; i < numberOfStudent; i++) {
        if (needFindScore == data[i].stuScore[subject]) {
            hasFind = true;
            while (j < 1) {
                printTable_1();
                printTable_2();
                printTable_1();
                j++;
            }
            printTable_3(data[i]);
        }
    }
    if (hasFind == true) {
        printTable_1();
    }

    if (!hasFind) {
        printf("����Ϣ��\n");
    }
}

void fuzzySearchByScore(Student data[], long numberOfStudent, short subject) {
    float lowerLimitOfScore;
    float upperLimitOfScore;
    if (subject == 3) {
        printf("������ɼ�������(0~450, ������Ĭ��Ϊ0)��");
        lowerLimitOfScore = getLimitOfScore(1, 0, 450);  // ����
        printf("������ɼ�������(%.f~450, ������Ĭ��Ϊ0)��", lowerLimitOfScore);
        upperLimitOfScore = getLimitOfScore(0, lowerLimitOfScore, 450);  // ����
    } else {
        printf("������ɼ�������(0~150, ������Ĭ��Ϊ0)��");
        lowerLimitOfScore = getLimitOfScore(1, 0, 150);  // ����
        printf("������ɼ�������(%.f~150, ������Ĭ��Ϊ0)��", lowerLimitOfScore);
        upperLimitOfScore = getLimitOfScore(0, lowerLimitOfScore, 150);  // ����
    }

    bool hasFind = false;
    for (int i = 0, j = 0; i < numberOfStudent; i++) {
        if (lowerLimitOfScore <= data[i].stuScore[subject] && data[i].stuScore[subject] <= upperLimitOfScore) {
            hasFind = true;
            while (j < 1) {
                printTable_1();
                printTable_2();
                printTable_1();
                j++;
            }
            printTable_3(data[i]);
        }
    }
    if (hasFind == true) {
        printTable_1();
    }

    if (!hasFind) {
        printf("����Ϣ��\n");
    }
}

float getLimitOfScore(short mode, float lowerLimitOfExistence, float upperLimitOfGet) {
    if (mode == 0) {
        char upperLimit[7];
        restrictInput(7, upperLimit, 1);

        char *end;
        float upperLimitOfScore = strtof(upperLimit, &end);

        if (*end != '\0' || upperLimitOfScore < 0 || upperLimitOfScore > upperLimitOfGet ||
            upperLimitOfScore < lowerLimitOfExistence) {
            printf("������ĳɼ����޲��Ϸ�������������(%.f~%.f, ������Ĭ��Ϊ0)��", lowerLimitOfExistence, upperLimitOfGet);
            upperLimitOfScore = getLimitOfScore(0, lowerLimitOfExistence, upperLimitOfGet);
        }

        return upperLimitOfScore;
    } else {
        char lowerLimit[7];
        restrictInput(7, lowerLimit, 1);

        char *end;
        float lowerLimitOfScore = strtof(lowerLimit, &end);

        if (*end != '\0' || lowerLimitOfScore < 0 || lowerLimitOfScore > upperLimitOfGet) {
            printf("������ĳɼ����޲��Ϸ�������������(0~%.f, ������Ĭ��Ϊ0)��", upperLimitOfGet);
            lowerLimitOfScore = getLimitOfScore(1, 0, upperLimitOfGet);
        }

        return lowerLimitOfScore;
    }
}

void alterStudent(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }


        if (getc(fp) == EOF) {
            printf("����ѧ����Ϣ��\n");
            return;
        }

        printf("������Ҫ�޸ĵ�ѧ����ѧ��(����qȡ���޸�)��");
        long long id = getStuId(2, 0);
        if (id != -1) {
            while (!isIdExist(id, numberOfStudent)) {
                printf("��ѧ�Ų����ڣ����������룺");
                id = getStuId(2, 0);
                if (id == -1) {
                    printf("�ɹ�ȡ���޸ģ�\n");
                    return;
                }
            }

            Student data[numberOfStudent + 1];
            rewind(fp);
            fread(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            int findIndex = 0;
            for (int i = 0; i < numberOfStudent; i++) {
                if (data[i].stuId == id) {
                    findIndex = i;
                    printTable_1();
                    printTable_2();
                    printTable_1();
                    printTable_3(data[i]);
                    printTable_1();
                    break;
                }
            }

            printf("��ȷ���Ƿ��޸�(y/n)��");
            char YNChoice = getYNChoice();
            if (YNChoice == 'Y' || YNChoice == 'y') {

            } else {
                printf("�ɹ�ȡ���޸ģ�\n");\
                return;
            }

            printf("���޸ĸ�ѧ����Ϣ(ֱ�Ӱ��س��򲻽����޸�)��\n");
            printf("�������޸ĺ��ѧ��ѧ�ţ�");
            long long newId = getStuId(1, findIndex);
            if (newId != -1) {
                data[findIndex].stuId = newId;
            }

            printf("�������޸ĺ��ѧ��������");
            getStuName(data[findIndex].stuName, 1);

            printf("�������޸ĺ��ѧ���Ա�(���� M(��)/ F(Ů)�����ִ�Сд)��");
            getStuSex(data[findIndex].stuSex, 1);

            printf("�������޸ĺ��ѧ������(1~99)��");
            long newAge = getStuAge(1);
            if (newAge != -1) {
                data[findIndex].stuAge = newAge;
            }

            printf("�������޸ĺ�����ĳɼ���");
            float newChineseScore = getStuScore(1, 150);
            if (newChineseScore != -1) {
                data[findIndex].stuScore[0] = newChineseScore;
            }

            printf("�������޸ĺ����ѧ�ɼ���");
            float newMathScore = getStuScore(1, 150);
            if (newMathScore != -1) {
                data[findIndex].stuScore[1] = newMathScore;
            }

            printf("�������޸ĺ��Ӣ��ɼ���");
            float newEnglishScore = getStuScore(1, 150);
            if (newEnglishScore != -1) {
                data[findIndex].stuScore[2] = newEnglishScore;
            }

            // �����ܳɼ�
            data[findIndex].stuScore[3] =
                    data[findIndex].stuScore[0] + data[findIndex].stuScore[1] + data[findIndex].stuScore[2];

            // ���� "sutdent.dat"
            fp = fopen(DATA_PATH, "wb");
            fwrite(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);
            printf("�޸ĳɹ���\n");
        } else {
            printf("�ɹ�ȡ���޸ģ�\n");
        }
    }
}

char getYNChoice(void) {
    char YNChoice[2];

    restrictInput(2, YNChoice, 1);

    while ((YNChoice[0] != 'y' && YNChoice[0] != 'Y') && (YNChoice[0] != 'n' && YNChoice[0] != 'N')) {
        printf("����ȷ����ѡ��(y/n)��");
        restrictInput(2, YNChoice, 1);
    }

    return YNChoice[0];
}

bool isAlterStuIdExist(long long id, int findIndex) {
    long numberOfStudent = getNumberOfStudents();
    if (isFileExist() == -1) {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;
        Student data[numberOfStudent + 1];

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }

        rewind(fp);
        fread(data, sizeof(Student), numberOfStudent, fp);
        fclose(fp);

        for (int i = 0; i < numberOfStudent; i++) {
            if (id == data[i].stuId && i != findIndex) {
                return true;
            }
        }
    }

    return false;
}

void dropStudent(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "���󾯸棺%s �ļ������ڣ�\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        Student data[numberOfStudent];
        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "���󾯸棺�޷��� %s �ļ���\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }


        if (getc(fp) == EOF) {
            printf("����ѧ����Ϣ��\n");
            return;
        }

        printf("������Ҫɾ����ѧ����ѧ��(����qȡ��ɾ��)��");
        long long id = getStuId(2, 0);
        if (id != -1) {
            while (!isIdExist(id, numberOfStudent)) {
                printf("��ѧ�Ų����ڣ����������룺");
                id = getStuId(2, 0);
                if (id == -1) {
                    printf("�ɹ�ȡ��ɾ����\n");
                    return;
                }
            }

            rewind(fp);
            fread(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            int findIndex = 0;
            for (int i = 0; i < numberOfStudent; i++) {
                if (data[i].stuId == id) {
                    findIndex = i;
                    printTable_1();
                    printTable_2();
                    printTable_1();
                    printTable_3(data[i]);
                    printTable_1();
                    break;
                }
            }

            printf("��ȷ���Ƿ�ɾ��(y/n)��");
            char YNChoice = getYNChoice();
            if (YNChoice == 'Y' || YNChoice == 'y') {

            } else {
                printf("�ɹ�ȡ��ɾ����\n");\
                return;
            }

            for (int i = findIndex; i < numberOfStudent - 1; ++i) {
                data[i] = data[i + 1];
            }

            // ���� "sutdent.dat"
            fp = fopen(DATA_PATH, "wb");
            fwrite(data, sizeof(Student), numberOfStudent - 1, fp);
            fclose(fp);
            printf("ɾ���ɹ���\n");
        } else {
            printf("�ɹ�ȡ��ɾ����\n");
        }
    }
}

void printFunctionMenu(void) {
    printf("*************************************************\n"
           "*\t\t   ���ܲ˵�\t\t\t*\n"
           "*************************************************\n"
           "*    1.¼��ѧ����Ϣ\t" "   2.��ʾȫ��ѧ��\t*\n"
           "*    3.����ѧ����Ϣ\t" "   4.ͳ��ѧ����Ϣ\t*\n"
           "*    5.����ѧ����Ϣ\t" "   6.�޸�ѧ����Ϣ\t*\n"
           "*    7.ɾ��ѧ����Ϣ\t" "   8.��ʾ���ܲ˵�\t*\n"
           "*************************************************\n"
           "*    \t\t9.�˳�����ϵͳ\t\t\t*\n"
           "*************************************************\n"
    );
}

int isFileExist(void) {
    return (_access(DATA_PATH, 0));
}

void emptyTheList(LinkList **head) {
    LinkList *psave;

    while (*head != NULL) {
        psave = (*head)->next;
        free(*head);
        *head = psave;
    }
}

void bye(void) {
    system("CLS");
    printBye();
    system("PAUSE");
}

void printBye(void) {
    char b[8][120] = {
            {"__/\\\\\\\\\\\\\\\\\\\\\\\\\\________/\\\\\\____________/\\\\\\____/\\\\\\\\\\\\\\\\\\\\\\\\\\\\_"},
            {" _\\/\\\\\\/////////\\\\\\_____\\///\\\\\\________/\\\\\\/____\\/\\\\\\//////////__"},
            {"  _\\/\\\\\\_______\\/\\\\\\_______\\///\\\\\\____/\\\\\\/______\\/\\\\\\____________"},
            {"   _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\/__________\\///\\\\\\/\\\\\\/________\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\_"},
            {"    _\\/\\\\\\/////////\\\\\\___________\\///\\\\\\/__________\\/\\\\\\//////////__"},
            {"     _\\/\\\\\\_______\\/\\\\\\_____________\\/\\\\\\___________\\/\\\\\\____________"},
            {"      _\\/\\\\\\\\\\\\\\\\\\\\\\\\\\/______________\\/\\\\\\___________\\/\\\\\\\\\\\\\\\\\\\\\\\\\\\\_"},
            {"       _\\/////////////________________\\///____________\\//////////////__"},
    };
    for (int i = 0; i < 8; i++) {
        printf("%s\n", b[i]);
    }
    putchar('\n');
}