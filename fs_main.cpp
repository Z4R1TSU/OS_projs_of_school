#include "fs.h"
#include <windows.h>
#include <limits> // 输入健壮性

using std::cout;
using std::cin;
using std::endl;

int main() {
    system("color F5");
    keybd_event(VK_F11,0,0,0); //自动全屏
    keybd_event(VK_F11,0,KEYEVENTF_KEYUP,0); //按F11取消全屏
    printf("\n\n\n\n\n");
    int n = 0;
    FileSystem fs = FileSystem{};

    do {
        system("cls");
        cout << "             --------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                      欢迎使用“文件系统”模拟系统                                                             |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 1. 注册账号              ◎                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 2. 登录账号              ◎                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 3. 登出账号              ◎                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 4. 创建文件              ◎                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 5. 打开文件              ◎                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 6. 关闭文件              ◎                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 7. 读取文件内容           ◎                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 8. 写入文件              ◎                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 9. 删除文件              ◎                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 10. 创建新目录             ◎                                                      |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 11. 打开目录              ◎                                                      |\n";
        cout << "            |                                                                                                             Produced by 3122004669        |\n";
        cout << "            |                                                        ◎ 12. 删除目录              ◎                                                      |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 13. 显示当前目录          ◎                                                      |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 14. 显示工作路径          ◎                                                      |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        ◎ 15. 显示磁盘占用          ◎                                                      |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            --------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "请选择 >> ";
        do {
            cin >> n;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "输入有误，请重新输入合法的选项" << endl;
            } else if (n < 0 || n > 15) {
                cout << "输入有误，请重新输入合法的选项" << endl;
            }
        } while (n < 0 || n > 15);

        switch(n) {
            case 1: {
                string username, password;
                cout << "请输入用户名：";
                cin >> username;
                cout << "请输入密码：";
                cin >> password;
                fs.sign_up(username, password);
                system("pause");
                break;
            }
            case 2: {
                string username, password;
                cout << "请输入用户名：";
                cin >> username;
                cout << "请输入密码：";
                cin >> password;
                fs.login(username, password);
                system("pause");
                break;
            }
            case 3: {
                fs.logout();
                system("pause");
                break;
            }
            case 4: {
                string filename, content;
                cout << "请输入文件名：";
                cin >> filename;
                cout << "请输入文件内容：";
                cin >> content;
                fs.create_file(filename, content);
                system("pause");
                break;
            }
            case 5: {
                string filename;
                cout << "请输入文件名：";
                cin >> filename;
                fs.open_file(filename);
                system("pause");
                break;
            }
            case 6: {
                string filename;
                cout << "请输入文件名：";
                cin >> filename;
                fs.close_file(filename);
                system("pause");
                break;
            }
            case 7: {
                string filename;
                cout << "请输入文件名：";
                cin >> filename;
                fs.read_file(filename);
                system("pause");
                break;
            }
            case 8: {
                string filename, content;
                cout << "请输入文件名：";
                cin >> filename;
                cout << "请输入文件内容：";
                cin >> content;
                fs.write_file(filename, content);
                system("pause");
                break;
            }
            case 9: {
                string filename;
                cout << "请输入文件名：";
                cin >> filename;
                fs.delete_file(filename);
                system("pause");
                break;
            }
            case 10: {
                string dirname;
                cout << "请输入目录名：";
                cin >> dirname;
                fs.make_dir(dirname);
                system("pause");
                break;
            }
            case 11: {
                string dirname;
                cout << "请输入目录名：";
                cin >> dirname;
                fs.change_dir(dirname);
                system("pause");
                break;
            }
            case 12: {
                string dirname;
                cout << "请输入目录名：";
                cin >> dirname;
                fs.delete_dir(dirname);
                system("pause");
                break;
            }
            case 13: {
                fs.list_dir();
                system("pause");
                break;
            }
            case 14: {
                fs.print_working_dir();
                system("pause");
                break;
            }
            case 15: {
                fs.disk_usage();
                system("pause");
                break;
            }
            default: {
                cout << "其他功能暂未开发！\n请重新选择\n";
                system("pause");
                break;
            }
        }
    } while(1);

    return 0;
}