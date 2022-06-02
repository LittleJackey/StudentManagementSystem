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
    long long stuId;    // ѧ��
    char stuName[17];    // ����
    char stuSex[3];    // �Ա�
    long stuAge;    // ����
    float stuScore[4];    // ���ġ���ѧ��Ӣ����ܳɼ�
} Student;

// ����
typedef struct linklist {
    Student stu;
    struct linklist *next;
} LinkList;

bool login(void);

/**
 * ��ӡ welcome
 */
void printWelcome(void);

/**
 * ��ӡ�˵�
 */
void menu(void);

/**
 * ����ѧ���ɼ�����ϵͳ
 */
void applicationRun(void);

/**
 * ���"student.dat"�������򴴽������򲻴���
 */
void creatDat(void);

/**
 * ��ȡ�û����ڹ��ܵ�ѡ��
 * @return �����ַ����ڴ洢�û���ѡ��
 */
int getChoice(void);

/**
 * �����û�����ĳ���
 * @param max ��󳤶�
 * @param result �û�������
 * @param mode 0�������û����룬������������; 1��������
 */
void restrictInput(int max, char result[], int mode);

/**
 * ¼��һ��ѧ��������������
 * @param ptemp ָ��һ���ڵ��ָ��
 */
void setStudent(LinkList **ptemp);

/**
 * ��ȡ�û������ѧ����ѧ��
 * @param mode 0:����¼��ѧ��
 *             1:�����޸�֮���ѧ��
 *             2:������Ҫ�޸ĵ�ѧ��
 * @param findIndex �ҵ���ѧ�����±�
 * @return ѧ����ѧ��
 */
long long getStuId(short mode, int findIndex);

/**
 * �ж��û������ѧ��ѧ���Ƿ�������ļ���
 * @param id �û�
 * @param numberOfStudent ѧ��������
 * @return ���ڷ���true�������ڷ���false
 */
bool isIdExist(long long id, long numberOfStudent);

/**
 * ��ȡ�û������ѧ��������
 * @param stuName �洢ѧ�����ֵ�����
 * @param mode 0:����¼������
 *             1:�����޸�֮�������
 */
void getStuName(char stuName[], short mode);

/**
 * ��ȡ�û������ѧ�����Ա�
 * @param stuSex �洢ѧ���Ա������
 * @param mode 0:����¼��
 *             1:�����޸�
 */
void getStuSex(char stuSex[], short mode);

/**
 * ��ȡ�û������ѧ��������
 * @param mode 0:����¼��
 *             1:�����޸�
 * @return ѧ��������
 */
long getStuAge(short mode);

/**
 * ��ȡ�û������ѧ���ĳɼ�
 * @param mode 0:����¼�� 1:�����޸�
 * @param upperLimit �ɼ�������
 * @return ѧ���ĳɼ�
 */
float getStuScore(short mode, float upperLimit);

/**
 * ��ӡ����ѧ������Ϣ
 * @param numberOfStudent ѧ��������
 */
void printAllStudent(long numberOfStudent);

/**
 * ��ӡ���
 */
void printTable_1(void);

void printTable_2(void);

void printTable_3(Student data);

/**
 * ���������ݱ���� "student.dat" �ļ�
 * @param pstart ָ��ǰ�����ѱ���λ�õ�ָ��
 */
void saveStudentData(LinkList **pstart);

/**
 * ��ѧ����������ѧ����Ϣ
 * @param numberOfStudent ѧ����������
 */
void sortOfStudent(long numberOfStudent);

/**
 * ��ȡ�û�ѡ�������ѡ��
 * @return �û���ѡ�������ѡ��
 */
char getSortChoice(char upper);

/**
 * ����ѧ����Ϣ
 * @param data ����ѧ����Ϣ�Ľṹ������
 * @param way ����ʽ��0������1������
 * @param numberOfStudent ѧ������
 * @param subject ��Ŀ��0�����ĳɼ���1����ѧ�ɼ���2��Ӣ��ɼ���3��ƽ���ɼ���4���ܳɼ�
 */
void sortByScore(Student data[], int way, long numberOfStudent, int subject);

/**
 * ͳ��ѧ����Ϣ
 */
void statisticsStudentInformation(void);

/**
 * ��ȡѧ��������
 * @return ѧ��������
 */
long getNumberOfStudents(void);

/**
 * ���ļ��в���һ��ѧ��
 * @param numberOfStudent ѧ��������
 */
void findStudent(long numberOfStudent);

/**
 * ͨ��ѧ�ž�ȷ����ѧ��
 * @param numberOfStudent ѧ��������
 */
void findById(long numberOfStudent);

/**
 * ͨ��������ȷ����ѧ��
 * @param numberOfStudent ѧ��������
 */
void findByName(long numberOfStudent);

/**
 * ͨ���ɼ�����һ��ѧ��
 * @param numberOfStudent ѧ��������
 * @param mode 0:��ȷ���� 1:ģ������
 * @param subject 0:���ĳɼ� 1:��ѧ�ɼ� 2:Ӣ��ɼ� 3:�ܳɼ�
 */
void findByScore(long numberOfStudent, short mode, short subject);

/**
 * ͨ��������ȷ����ѧ��
 * @param data ѧ��
 * @param numberOfStudent ѧ��������
 * @param subject 0:���ĳɼ� 1:��ѧ�ɼ� 2:Ӣ��ɼ� 3:�ܳɼ�
 */
void exactSearchByScore(Student data[], long numberOfStudent, short subject);

/**
 * ͨ������ģ������ѧ��
 * @param data ѧ��
 * @param numberOfStudent ѧ��������
 * @param subject 0:���ĳɼ� 1:��ѧ�ɼ� 2:Ӣ��ɼ� 3:�ܳɼ�
 */
void fuzzySearchByScore(Student data[], long numberOfStudent, short subject);

/**
 * ����ģ��������ȡ�û����������������
 * @param mode 0:����; 1:����
 * @return ������������
 */
float getLimitOfScore(short mode, float lowerLimitOfExistence, float upperLimitOfGet);

/**
 * ���ļ����޸�һ��ѧ������Ϣ
 * @param numberOfStudent ѧ��������
 */
void alterStudent(long numberOfStudent);

/**
 * �����û�ȷ�ϲ���(yes or no)
 * @return Y/y��N/n
 */
char getYNChoice(void);

/**
 * �ж��û������޸�֮���ѧ��ѧ���Ƿ���ڣ��������޸�ǰ��ѧ�ţ�
 * @param id �û�������޸�֮���ѧ��ѧ��
 * @param findIndex �ṹ��������±ָ꣬��洢Ҫ�޸ĵ�ѧ����ѧ��
 * @return �û��޸�֮���ѧ��ѧ��
 */
bool isAlterStuIdExist(long long id, int findIndex);

/**
 * ��ɾ��һ��ѧ����Ϣ
 * @param numberOfStudent ѧ��������
 */
void dropStudent(long numberOfStudent);

/**
 * ��ӡ���ܲ˵�
 */
void printFunctionMenu(void);

/**
 * �ж��ļ� "student.dat" �Ƿ����
 * @return ���ڷ���0�������ڷ���-1
 */
int isFileExist(void);

/**
 * �ͷ��� malloc() ������ڴ棬��������ָ��Ϊ NULL
 * @param head ͷ�ڵ�
 */
void emptyTheList(LinkList **head);

/**
 * ������β����
 */
void bye(void);

/**
 * ��ӡ BYE
 */
void printBye(void);


#endif // STUMS_STUDENTMANAGEMENTSYSTEM_H