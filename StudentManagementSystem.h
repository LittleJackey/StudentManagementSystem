//
// Created by LittleJackey on 2022/5/12.
//

#ifndef STUMS_STUDENTMANAGEMENTSYSTEM_H
#define STUMS_STUDENTMANAGEMENTSYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <io.h>
#include <conio.h>
#include <windows.h>

#define DATA_PATH "./student.dat"
#define DATA_NAME "student.dat"

typedef struct Student {
    long long stuId;    // 学号
    char stuName[17];    // 名字
    char stuSex[3];    // 性别
    long stuAge;    // 年龄
    float stuScore[4];    // 语文、数学、英语和总成绩
} Student;

// 链表
typedef struct linklist {
    Student stu;
    struct linklist *next;
} LinkList;

bool login(void);

/**
 * 打印 welcome
 */
void printWelcome(void);

/**
 * 打印菜单
 */
void menu(void);

/**
 * 运行学生成绩管理系统
 */
void applicationRun(void);

/**
 * 如果"student.dat"不存在则创建，否则不创建
 */
void creatDat(void);

/**
 * 获取用户对于功能的选择
 * @return 单个字符用于存储用户的选择
 */
int getChoice(void);

/**
 * 限制用户输入的长度
 * @param max 最大长度
 * @param result 用户的输入
 * @param mode 0：隐藏用户输入，用于输入密码; 1：不隐藏
 */
void restrictInput(int max, char result[], int mode);

/**
 * 录入一个学生，存入链表当中
 * @param ptemp 指向一个节点的指针
 */
void setStudent(LinkList **ptemp);

/**
 * 获取用户输入的学生的学号
 * @param mode 0:用于录入学号
 *             1:用于修改之后的学号
 *             2:用于需要修改的学号
 * @param findIndex 找到的学生的下标
 * @return 学生的学号
 */
long long getStuId(short mode, int findIndex);

/**
 * 判断用户输入的学生学号是否存在于文件中
 * @param id 用户
 * @param numberOfStudent 学生总人数
 * @return 存在返回true，不存在返回false
 */
bool isIdExist(long long id, long numberOfStudent);

/**
 * 获取用户输入的学生的名字
 * @param stuName 存储学生名字的数组
 * @param mode 0:用于录入名字
 *             1:用于修改之后的名字
 */
void getStuName(char stuName[], short mode);

/**
 * 获取用户输入的学生的性别
 * @param stuSex 存储学生性别的数组
 * @param mode 0:用于录入
 *             1:用于修改
 */
void getStuSex(char stuSex[], short mode);

/**
 * 获取用户输入的学生的年龄
 * @param mode 0:用于录入
 *             1:用于修改
 * @return 学生的年龄
 */
long getStuAge(short mode);

/**
 * 获取用户输入的学生的成绩
 * @param mode 0:用于录入 1:用于修改
 * @param upperLimit 成绩的上限
 * @return 学生的成绩
 */
float getStuScore(short mode, float upperLimit);

/**
 * 打印所有学生的信息
 * @param numberOfStudent 学生总人数
 */
void printAllStudent(long numberOfStudent);

/**
 * 打印表格
 */
void printTable_1(void);

void printTable_2(void);

void printTable_3(Student data);

/**
 * 将链表内容保存进 "student.dat" 文件
 * @param pstart 指向当前链表已保存位置的指针
 */
void saveStudentData(LinkList **pstart);

/**
 * 按学号升序排列学生信息
 * @param numberOfStudent 学生的总人数
 */
void sortOfStudent(long numberOfStudent);

/**
 * 获取用户选择的排序选项
 * @return 用户的选择的排序选项
 */
char getSortChoice(char upper);

/**
 * 排序学生信息
 * @param data 储存学生信息的结构体数组
 * @param way 排序方式，0：升序，1：降序
 * @param numberOfStudent 学生人数
 * @param subject 科目，0：语文成绩，1：数学成绩，2：英语成绩，3：平均成绩，4：总成绩
 */
void sortByScore(Student data[], int way, long numberOfStudent, int subject);

/**
 * 统计学生信息
 */
void statisticsStudentInformation(void);

/**
 * 获取学生总人数
 * @return 学生总人数
 */
long getNumberOfStudents(void);

/**
 * 在文件中查找一个学生
 * @param numberOfStudent 学生总人数
 */
void findStudent(long numberOfStudent);

/**
 * 通过学号精确查找学生
 * @param numberOfStudent 学生总人数
 */
void findById(long numberOfStudent);

/**
 * 通过姓名精确查找学生
 * @param numberOfStudent 学生总人数
 */
void findByName(long numberOfStudent);

/**
 * 通过成绩查找一个学生
 * @param numberOfStudent 学生总人数
 * @param mode 0:精确查找 1:模糊查找
 * @param subject 0:语文成绩 1:数学成绩 2:英语成绩 3:总成绩
 */
void findByScore(long numberOfStudent, short mode, short subject);

/**
 * 通过分数精确查找学生
 * @param data 学生
 * @param numberOfStudent 学生总人数
 * @param subject 0:语文成绩 1:数学成绩 2:英语成绩 3:总成绩
 */
void exactSearchByScore(Student data[], long numberOfStudent, short subject);

/**
 * 通过分数模糊查找学生
 * @param data 学生
 * @param numberOfStudent 学生总人数
 * @param subject 0:语文成绩 1:数学成绩 2:英语成绩 3:总成绩
 */
void fuzzySearchByScore(Student data[], long numberOfStudent, short subject);

/**
 * 用于模糊搜索获取用户输入分数的上下限
 * @param mode 0:上限; 1:下限
 * @return 分数的上下限
 */
float getLimitOfScore(short mode, float lowerLimitOfExistence, float upperLimitOfGet);

/**
 * 从文件中修改一个学生的信息
 * @param numberOfStudent 学生总人数
 */
void alterStudent(long numberOfStudent);

/**
 * 请求用户确认操作(yes or no)
 * @return Y/y或N/n
 */
char getYNChoice(void);

/**
 * 判断用户输入修改之后的学生学号是否存在（不包括修改前的学号）
 * @param id 用户输入的修改之后的学生学号
 * @param findIndex 结构体数组的下标，指向存储要修改的学生的学号
 * @return 用户修改之后的学生学号
 */
bool isAlterStuIdExist(long long id, int findIndex);

/**
 * 从删除一个学生信息
 * @param numberOfStudent 学生总人数
 */
void dropStudent(long numberOfStudent);

/**
 * 打印功能菜单
 */
void printFunctionMenu(void);

/**
 * 判断文件 "student.dat" 是否存在
 * @return 存在返回0，不存在返回-1
 */
int isFileExist(void);

/**
 * 释放由 malloc() 分配的内存，设置链表指针为 NULL
 * @param head 头节点
 */
void emptyTheList(LinkList **head);

/**
 * 结束收尾函数
 */
void bye(void);

/**
 * 打印 BYE
 */
void printBye(void);


#endif // STUMS_STUDENTMANAGEMENTSYSTEM_H