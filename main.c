#include "StudentManagementSystem.h"

int main(void)
{
    // ��¼��֤
    printWelcome();
    if (!login()) {
        system("CLS"); // ����
        printf("��¼ʧ�ܣ������Ѻľ���\n\n");
        printBye();
        system("PAUSE");
        return 0;
    }
    Sleep(300);
    system("CLS"); // ����

    menu(); // ��ӡ�˵�
    applicationRun(); // ����ϵͳ

    bye(); // ��ӡ�ټ�

    return 0;
}
