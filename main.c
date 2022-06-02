#include "StudentManagementSystem.h"

int main(void)
{
    // 登录验证
    printWelcome();
    if (!login()) {
        system("CLS"); // 清屏
        printf("登录失败！机会已耗尽。\n\n");
        printBye();
        system("PAUSE");
        return 0;
    }
    Sleep(300);
    system("CLS"); // 清屏

    menu(); // 打印菜单
    applicationRun(); // 运行系统

    bye(); // 打印再见

    return 0;
}
