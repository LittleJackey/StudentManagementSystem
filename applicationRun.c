//
// Created by LittleJackey on 2022/5/12.
//
#include "StudentManagementSystem.h"

bool login(void) {
    const char *password = "123456";  // 登录密码
    char pwd[17];
    for (int i = 0; i < 3; ++i) {
        printf("请输入管理员密码(剩余次数%d)：", 3 - i);
        restrictInput(17, pwd, 0);
        if (strcmp(password, pwd) == 0) {
            printf("登录成功！\n");
            return true;
        } else {
            printf("密码错误！");
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
    // 新建链表
    LinkList *head = (LinkList *) malloc(sizeof(LinkList));
    head->next = NULL;
    LinkList *ptemp = head;
    LinkList *pnode = head;
    printf("请选择功能(按8显示功能菜单)：");

    int choice;
    while ((choice = getChoice()) != 9) {
        // 判断用户的选择
        switch (choice) {
            case 1: // 录入学生信息
                setStudent(&ptemp);
                saveStudentData(&pnode);
                break;
            case 2: // 打印学生信息
                printAllStudent(getNumberOfStudents());
                break;
            case 3: // 排序学生信息
                sortOfStudent(getNumberOfStudents());
                break;
            case 4: // 统计学生人数
                statisticsStudentInformation();
                break;
            case 5: // 查找学生信息
                findStudent(getNumberOfStudents());
                break;
            case 6: // 修改学生信息
                alterStudent(getNumberOfStudents());
                break;
            case 7: // 删除学生信息
                dropStudent(getNumberOfStudents());
                break;
            case 8: // 显示功能菜单
                printFunctionMenu();
                break;
            default:
                printf("Program error!\n");
                break;
        }

        printf("\n请选择功能(按8显示功能菜单)：");
    }
    emptyTheList(&head);
}

void menu(void) {
    printf("*************************************************\n");
    printf("*\t  欢迎使用高校学生成绩管理系统\t\t*\n");
    printf("*\t\tBy Little Jackey\t\t*\n");
    printf("*************************************************\n");
    printf("*\t\t1.录入学生信息\t\t\t*\n");
    printf("*\t\t2.显示全部学生\t\t\t*\n");
    printf("*\t\t3.排序学生信息\t\t\t*\n");
    printf("*\t\t4.统计学生信息\t\t\t*\n");
    printf("*\t\t5.查找学生信息\t\t\t*\n");
    printf("*\t\t6.修改学生信息\t\t\t*\n");
    printf("*\t\t7.删除学生信息\t\t\t*\n");
    printf("*\t\t8.显示功能菜单\t\t\t*\n");
    printf("*\t\t9.退出管理系统\t\t\t*\n");
    printf("*************************************************\n");
}

void creatDat(void) {
    if (isFileExist() == -1) {
        FILE *fp;
        if ((fp = fopen(DATA_PATH, "ab")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }
        fclose(fp);
        printf("%s写入成功！\n", DATA_NAME);
    }
}

int getChoice(void) {
    char input[2];
    restrictInput(2, input, 1);

    int choice;

    char *end;
    choice = strtol(input, &end, 10);

    if (*end != '\0') {
        printf("请正确输入选项：");
        choice = getChoice();
    }

    if (choice == 0) {
        printf("请正确输入选项：");
        choice = getChoice();
    }

    return choice;
}

void restrictInput(int max, char result[], int mode) {
    int i = 0;
    unsigned char x;

    while ((x = getch()) != '\r') {
        if (x != '\b' && i >= 0 && i < max - 1)//因为要给字符串加结尾的\0,所以要留一个位（max-1）
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
    // 创建新节点
    LinkList *pnew = (LinkList *) malloc(sizeof(LinkList));

    // 输入学生信息
    printf("请输入学生学号：");
    pnew->stu.stuId = getStuId(0, 0);
    while (isIdExist(pnew->stu.stuId, getNumberOfStudents())) {
        printf("该学号已存在！请重新输入学号：");
        pnew->stu.stuId = getStuId(0, 0);
    }

    printf("请输入学生姓名：");
    getStuName(pnew->stu.stuName, 0);

    printf("请输入学生性别(键入 M(男)/ F(女)不区分大小写)：");
    getStuSex(pnew->stu.stuSex, 0);

    printf("请输入学生年龄(1~99)：");
    pnew->stu.stuAge = getStuAge(0);

    printf("请输入学生语文成绩(0~150, 不输入默认为0)：");
    pnew->stu.stuScore[0] = getStuScore(0, 150);

    printf("请输入学生数学成绩(0~150, 不输入默认为0)：");
    pnew->stu.stuScore[1] = getStuScore(0, 150);

    printf("请输入学生英语成绩(0~150, 不输入默认为0)：");
    pnew->stu.stuScore[2] = getStuScore(0, 150);

    // 计算总成绩
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
            printf("学号不合法！请重新输入学号：");
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
            printf("学号不合法！请重新输入学号：");
            id = getStuId(1, findIndex);
        }

        if (isAlterStuIdExist(id, findIndex)) {
            printf("该学号已存在！请重新输入学号：");
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
                printf("学号不合法！请重新输入学号：");
                id = getStuId(2, 0);
            }
        }
        return id;
    }
}

bool isIdExist(long long id, long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;
        Student data[numberOfStudent + 1];

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
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
            printf("姓名不能为空！请重新输入：");
            restrictInput(17, name, 1);
        }

        strcpy(stuName, name);
    } else {
        while (true) {
            if (name[0] == '\0') {
                break;
            } else {
                if (name[0] == ' ') {
                    printf("姓名不能为空！请重新输入：");
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
            printf("您输入的不是 M 或 F(不区分大小写)!\n请重新输入：");
            restrictInput(2, sex, 1);
        }

        if (sex[0] == 'M' || sex[0] == 'm') {
            strcpy(stuSex, "男");
        } else if (sex[0] == 'F' || sex[0] == 'f') {
            strcpy(stuSex, "女");
        }
    } else {
        if (sex[0] == '\0') {
            return;
        } else {
            while (sex[0] != 'M' && sex[0] != 'F' && sex[0] != 'm' && sex[0] != 'f') {
                printf("您输入的不是 M 或 F(不区分大小写)!\n请重新输入：");
                restrictInput(2, sex, 1);
            }

            if (sex[0] == 'M' || sex[0] == 'm') {
                strcpy(stuSex, "男");
            } else if (sex[0] == 'F' || sex[0] == 'f') {
                strcpy(stuSex, "女");
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
            printf("输入的年龄不合法！请重新输入：");
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
            printf("输入的年龄不合法！请重新输入：");
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
            printf("您输入的成绩不合法！请重新输入：");
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
            printf("您输入的成绩不合法！请重新输入：");
            score = getStuScore(1, upperLimit);
        }

        return score;
    }
}

void printAllStudent(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }

        if (getc(fp) == EOF) {
            printf("暂无学生信息！\n");
        } else {
            Student data[numberOfStudent];
            rewind(fp);
            fread(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            printf("所有学生信息如下：\n");
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
    printf("|%-19s", "学号");
    printf("|%-16s", "姓名");
    printf("|%-4s", "性别");
    printf("|%-4s", "年龄");
    printf("|%-6s", "语文");
    printf("|%-6s", "数学");
    printf("|%-6s", "英语");
    printf("|%-6s|\n", "总成绩");
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
        fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    }

    while (pnode != NULL) {
        fwrite(&(pnode->stu), sizeof(Student), 1, fp);
        *pstart = pnode;
        pnode = pnode->next;
    }
    fclose(fp);
    printf("保存成功！\n");
}

void sortOfStudent(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;
        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }

        if (getc(fp) == EOF) {
            printf("排序失败！暂无学生信息！\n");
        } else {
            printf("*************************************************\n");
            printf("*\t\t     排序方式\t\t\t*\n");
            printf("*************************************************\n");
            printf("*\tA.按学号升序        B.按学号降序\t*\n");
            printf("*\tC.按语文成绩升序    D.按语文成绩降序\t*\n");
            printf("*\tE.按数学成绩升序    F.按数学成绩降序\t*\n");
            printf("*\tG.按英语成绩升序    H.按英语成绩降序\t*\n");
            printf("*\tI.按总成绩升序      J.按总成绩降序\t*\n");
            printf("*************************************************\n");
            printf("*\t\t   q.取消排序\t\t\t*\n");
            printf("*************************************************\n");

            Student data[numberOfStudent + 1];
            rewind(fp);
            fread(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            Student temp;
            printf("请选择排序方式：");
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
                    printf("成功取消排序！\n");
                    return;
            }

            // 更新 "sutdent.dat"
            fp = fopen(DATA_PATH, "wb");
            fwrite(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            printf("排序完成！\n");
        }
    }
}

char getSortChoice(char upper) {
    char sortChoice[2];

    restrictInput(2, sortChoice, 1);

    while ((sortChoice[0] < 65 || sortChoice[0] > toupper(upper) && sortChoice[0] < 97 ||
            sortChoice[0] > tolower(upper)) &&
           (sortChoice[0] != 'q' && sortChoice[0] != 'Q')) {
        printf("请正确输入选项：");
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
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        long numberOfStudent = getNumberOfStudents();
        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }


        if (getc(fp) == EOF) {
            printf("暂无学生信息！\n");
        } else {
            Student data[numberOfStudent];
            rewind(fp);
            fread(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            float chineseScoreSum = 0;  // 语文成绩之和
            float mathScoreSum = 0;     // 数学成绩之和
            float englishScoreSum = 0;  // 英语成绩之和
            float totalScoreSum = 0;    // 总成绩之和

            float chineseScoreMax = data[0].stuScore[0];    // 语文成绩最高分
            float mathScoreMax = data[0].stuScore[1];       // 数学成绩最高分
            float englishScoreMax = data[0].stuScore[2];    // 英语成绩最高分
            float totalScoreMax = data[0].stuScore[3];      // 总成绩最高分

            float chineseScoreMin = data[0].stuScore[0];    // 语文成绩最低分
            float mathScoreMin = data[0].stuScore[1];       // 数学成绩最低分
            float englishScoreMin = data[0].stuScore[2];    // 英语成绩最低分
            float totalScoreMin = data[0].stuScore[3];      // 总成绩最低分
            for (int i = 0; i < numberOfStudent; ++i) {
                chineseScoreSum += data[i].stuScore[0];
                mathScoreSum += data[i].stuScore[1];
                englishScoreSum += data[i].stuScore[2];
                totalScoreSum += data[i].stuScore[3];

                // 找最高分和最低分
                chineseScoreMax = chineseScoreMax < data[i].stuScore[0] ? data[i].stuScore[0] : chineseScoreMax;
                chineseScoreMin = chineseScoreMin > data[i].stuScore[0] ? data[i].stuScore[0] : chineseScoreMin;

                mathScoreMax = mathScoreMax < data[i].stuScore[1] ? data[i].stuScore[1] : mathScoreMax;
                mathScoreMin = mathScoreMin > data[i].stuScore[1] ? data[i].stuScore[1] : mathScoreMin;

                englishScoreMax = englishScoreMax < data[i].stuScore[2] ? data[i].stuScore[2] : englishScoreMax;
                englishScoreMin = englishScoreMin > data[i].stuScore[2] ? data[i].stuScore[2] : englishScoreMin;

                totalScoreMax = totalScoreMax < data[i].stuScore[3] ? data[i].stuScore[3] : totalScoreMax;
                totalScoreMin = totalScoreMin > data[i].stuScore[3] ? data[i].stuScore[3] : totalScoreMin;
            }
            // 计算语文平均分
            float chineseAverage = chineseScoreSum / (float) numberOfStudent;
            // 计算数学平均分
            float mathAverage = mathScoreSum / (float) numberOfStudent;
            // 计算英语平均分
            float englishAverage = englishScoreSum / (float) numberOfStudent;
            // 计算总平均分
            float totalAverage = totalScoreSum / (float) numberOfStudent;

            // 表格显示平均成绩
            for (int i = 0; i < 52; i++) {
                if (i == 0 || i == 9 || i == 20 || i == 31 || i == 42 || i == 51) {
                    printf("+");
                } else {
                    printf("-");
                }
            }
            putchar('\n');
            printf("|%-8s", "学生人数");
            printf("|%-10s", "语文平均分");
            printf("|%-10s", "数学平均分");
            printf("|%-10s", "英语平均分");
            printf("|%-8s|\n", "总平均分");
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

            // 表格显示语文成绩最高分
            printf("+");
            for (int i = 0; i < 74; i++) {
                printf("-");
            }
            printf("+\n");
            printf("|                              ");
            printf("语文成绩最高者");
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
            printf("语文成绩最低者");
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

            // 表格显示数学成绩最高分
            printf("+");
            for (int i = 0; i < 74; i++) {
                printf("-");
            }
            printf("+\n");
            printf("|                              ");
            printf("数学成绩最高者");
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
            printf("数学成绩最低者");
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

            // 表格显示数学成绩最高分
            printf("+");
            for (int i = 0; i < 74; i++) {
                printf("-");
            }
            printf("+\n");
            printf("|                              ");
            printf("英语成绩最高者");
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
            printf("英语成绩最低者");
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

            // 表格显示总成绩最高分
            printf("+");
            for (int i = 0; i < 74; i++) {
                printf("-");
            }
            printf("+\n");
            printf("|                               ");
            printf("总成绩最高者");
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
            printf("总成绩最低者");
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
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    }
}

void findStudent(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;
        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }


        if (getc(fp) == EOF) {
            printf("查找失败！暂无学生信息！\n");
        } else {
            Student data[numberOfStudent];
            rewind(fp);
            fread(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);

            printf("*********************************\n");
            printf("*\t     查找方式\t\t*\n");
            printf("*********************************\n");
            printf("*\t    A.精确查找\t\t*\n");
            printf("*\t    B.模糊查找\t\t*\n");
            printf("*********************************\n");
            printf("*\t    q.取消查找\t\t*\n");
            printf("*********************************\n");

            printf("请选择要查找的方式：");
            char choice_1 = getSortChoice('B');
            choice_1 = tolower(choice_1);
            if (choice_1 == 'a') {
                printf("*************************************************\n");
                printf("*\t\t     精确查找\t\t\t*\n");
                printf("*************************************************\n");
                printf("*\tA.按学号查找        B.按姓名查找\t*\n");
                printf("*\tC.按语文成绩查找    D.按数学成绩查找\t*\n");
                printf("*\tE.按英语成绩查找    F.按总成绩查找\t*\n");
                printf("*************************************************\n");
                printf("*\t\t   q.取消查找\t\t\t*\n");
                printf("*************************************************\n");
                printf("请选择要查找的方式：");
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
                        printf("成功取消查找！\n");
                        break;
                }
            } else if (choice_1 == 'b') {
                printf("*************************************************\n");
                printf("*\t\t     模糊查找\t\t\t*\n");
                printf("*************************************************\n");
                printf("*\tA.按语文成绩查找    B.按数学成绩查找\t*\n");
                printf("*\tC.按英语成绩查找    D.按总成绩查找\t*\n");
                printf("*************************************************\n");
                printf("*\t\t   q.取消查找\t\t\t*\n");
                printf("*************************************************\n");
                printf("请选择要查找的方式：");
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
                        printf("成功取消查找！\n");
                        break;
                }
            } else {
                printf("成功取消查找！\n");
                return;
            }
        }
    }
}

void findById(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        printf("请输入要查找学生的学号：");
        long long id = getStuId(0, 0);

        Student data[numberOfStudent + 1];

        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
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
            printf("暂未查找到该生信息！\n");
        }
    }
}

void findByName(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        printf("请输入要查找学生的姓名：");
        char needFindName[17];
        getStuName(needFindName, 0);

        Student data[numberOfStudent + 1];

        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }

        rewind(fp);
        fread(data, sizeof(Student), numberOfStudent, fp);
        fclose(fp);

        bool hasFind = false;

        for (int i = 0, j = 0; i < numberOfStudent; i++) {
            if ((strcmp(needFindName, data[i].stuName)) == 0) {
                hasFind = true;
                while (j < 1) { // j用来控制只循环一次
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
            printf("暂未查找到该生信息！\n");
        }
    }
}

void findByScore(long numberOfStudent, short mode, short subject) {
    if (isFileExist() == -1) {
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        Student data[numberOfStudent + 1];
        FILE *fp;
        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
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
            printf("请输入要查找的语文成绩(0~150, 不输入默认为0)：");
            break;
        case 1:
            printf("请输入要查找的数学成绩(0~150, 不输入默认为0)：");
            break;
        case 2:
            printf("请输入要查找的英语成绩(0~150, 不输入默认为0)：");
            break;
        case 3:
            printf("请输入要查找的总成绩(0~450, 不输入默认为0)：");
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
        printf("无信息！\n");
    }
}

void fuzzySearchByScore(Student data[], long numberOfStudent, short subject) {
    float lowerLimitOfScore;
    float upperLimitOfScore;
    if (subject == 3) {
        printf("请输入成绩的下限(0~450, 不输入默认为0)：");
        lowerLimitOfScore = getLimitOfScore(1, 0, 450);  // 下限
        printf("请输入成绩的上限(%.f~450, 不输入默认为0)：", lowerLimitOfScore);
        upperLimitOfScore = getLimitOfScore(0, lowerLimitOfScore, 450);  // 上限
    } else {
        printf("请输入成绩的下限(0~150, 不输入默认为0)：");
        lowerLimitOfScore = getLimitOfScore(1, 0, 150);  // 下限
        printf("请输入成绩的上限(%.f~150, 不输入默认为0)：", lowerLimitOfScore);
        upperLimitOfScore = getLimitOfScore(0, lowerLimitOfScore, 150);  // 上限
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
        printf("无信息！\n");
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
            printf("您输入的成绩上限不合法！请重新输入(%.f~%.f, 不输入默认为0)：", lowerLimitOfExistence, upperLimitOfGet);
            upperLimitOfScore = getLimitOfScore(0, lowerLimitOfExistence, upperLimitOfGet);
        }

        return upperLimitOfScore;
    } else {
        char lowerLimit[7];
        restrictInput(7, lowerLimit, 1);

        char *end;
        float lowerLimitOfScore = strtof(lowerLimit, &end);

        if (*end != '\0' || lowerLimitOfScore < 0 || lowerLimitOfScore > upperLimitOfGet) {
            printf("您输入的成绩下限不合法！请重新输入(0~%.f, 不输入默认为0)：", upperLimitOfGet);
            lowerLimitOfScore = getLimitOfScore(1, 0, upperLimitOfGet);
        }

        return lowerLimitOfScore;
    }
}

void alterStudent(long numberOfStudent) {
    if (isFileExist() == -1) {
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }


        if (getc(fp) == EOF) {
            printf("暂无学生信息！\n");
            return;
        }

        printf("请输入要修改的学生的学号(输入q取消修改)：");
        long long id = getStuId(2, 0);
        if (id != -1) {
            while (!isIdExist(id, numberOfStudent)) {
                printf("该学号不存在！请重新输入：");
                id = getStuId(2, 0);
                if (id == -1) {
                    printf("成功取消修改！\n");
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

            printf("请确认是否修改(y/n)：");
            char YNChoice = getYNChoice();
            if (YNChoice == 'Y' || YNChoice == 'y') {

            } else {
                printf("成功取消修改！\n");\
                return;
            }

            printf("请修改该学生信息(直接按回车则不进行修改)！\n");
            printf("请输入修改后的学生学号：");
            long long newId = getStuId(1, findIndex);
            if (newId != -1) {
                data[findIndex].stuId = newId;
            }

            printf("请输入修改后的学生姓名：");
            getStuName(data[findIndex].stuName, 1);

            printf("请输入修改后的学生性别(键入 M(男)/ F(女)不区分大小写)：");
            getStuSex(data[findIndex].stuSex, 1);

            printf("请输入修改后的学生年龄(1~99)：");
            long newAge = getStuAge(1);
            if (newAge != -1) {
                data[findIndex].stuAge = newAge;
            }

            printf("请输入修改后的语文成绩：");
            float newChineseScore = getStuScore(1, 150);
            if (newChineseScore != -1) {
                data[findIndex].stuScore[0] = newChineseScore;
            }

            printf("请输入修改后的数学成绩：");
            float newMathScore = getStuScore(1, 150);
            if (newMathScore != -1) {
                data[findIndex].stuScore[1] = newMathScore;
            }

            printf("请输入修改后的英语成绩：");
            float newEnglishScore = getStuScore(1, 150);
            if (newEnglishScore != -1) {
                data[findIndex].stuScore[2] = newEnglishScore;
            }

            // 计算总成绩
            data[findIndex].stuScore[3] =
                    data[findIndex].stuScore[0] + data[findIndex].stuScore[1] + data[findIndex].stuScore[2];

            // 更新 "sutdent.dat"
            fp = fopen(DATA_PATH, "wb");
            fwrite(data, sizeof(Student), numberOfStudent, fp);
            fclose(fp);
            printf("修改成功！\n");
        } else {
            printf("成功取消修改！\n");
        }
    }
}

char getYNChoice(void) {
    char YNChoice[2];

    restrictInput(2, YNChoice, 1);

    while ((YNChoice[0] != 'y' && YNChoice[0] != 'Y') && (YNChoice[0] != 'n' && YNChoice[0] != 'N')) {
        printf("请正确输入选项(y/n)：");
        restrictInput(2, YNChoice, 1);
    }

    return YNChoice[0];
}

bool isAlterStuIdExist(long long id, int findIndex) {
    long numberOfStudent = getNumberOfStudents();
    if (isFileExist() == -1) {
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        FILE *fp;
        Student data[numberOfStudent + 1];

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
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
        fprintf(stdout, "错误警告：%s 文件不存在！\n", DATA_NAME);
        exit(EXIT_FAILURE);
    } else {
        Student data[numberOfStudent];
        FILE *fp;

        if ((fp = fopen(DATA_PATH, "rb")) == NULL) {
            fprintf(stdout, "错误警告：无法打开 %s 文件！\n", DATA_NAME);
            exit(EXIT_FAILURE);
        }


        if (getc(fp) == EOF) {
            printf("暂无学生信息！\n");
            return;
        }

        printf("请输入要删除的学生的学号(输入q取消删除)：");
        long long id = getStuId(2, 0);
        if (id != -1) {
            while (!isIdExist(id, numberOfStudent)) {
                printf("该学号不存在！请重新输入：");
                id = getStuId(2, 0);
                if (id == -1) {
                    printf("成功取消删除！\n");
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

            printf("请确认是否删除(y/n)：");
            char YNChoice = getYNChoice();
            if (YNChoice == 'Y' || YNChoice == 'y') {

            } else {
                printf("成功取消删除！\n");\
                return;
            }

            for (int i = findIndex; i < numberOfStudent - 1; ++i) {
                data[i] = data[i + 1];
            }

            // 更新 "sutdent.dat"
            fp = fopen(DATA_PATH, "wb");
            fwrite(data, sizeof(Student), numberOfStudent - 1, fp);
            fclose(fp);
            printf("删除成功！\n");
        } else {
            printf("成功取消删除！\n");
        }
    }
}

void printFunctionMenu(void) {
    printf("*************************************************\n"
           "*\t\t   功能菜单\t\t\t*\n"
           "*************************************************\n"
           "*    1.录入学生信息\t" "   2.显示全部学生\t*\n"
           "*    3.排序学生信息\t" "   4.统计学生信息\t*\n"
           "*    5.查找学生信息\t" "   6.修改学生信息\t*\n"
           "*    7.删除学生信息\t" "   8.显示功能菜单\t*\n"
           "*************************************************\n"
           "*    \t\t9.退出管理系统\t\t\t*\n"
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