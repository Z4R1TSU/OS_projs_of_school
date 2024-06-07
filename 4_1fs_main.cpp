#include "4_1fs.h"
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
    int n;
    FileSystem fs = FileSystem{};

    do {
        system("cls");
        cout << "             ----------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                      欢迎使用“文件系统”模拟系统                                                            |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        ◎ 1. 新建文件              ◎                                                       |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        ◎ 2. 删除文件              ◎                                                       |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        ◎ 3. 打开文件              ◎                                                      |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        ◎ 4. 关闭文件              ◎                                                       |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        ◎ 5. 读出文件内容           ◎                                                       |\n";
        cout << "            |                                                                                                                                          |\n";
        cout << "            |                                                        ◎ 6. 追加文件内容           ◎                                                       |\n";
        cout << "            |                                                                                                                                          |\n";
        cout << "            |                                                        ◎ 7. 重写文件内容           ◎                                                       |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        ◎ 8. 重命名文件             ◎                                                     |\n";
        cout << "            |                                                                                                             Produced by 3122004669      |\n";
        cout << "            |                                                        ◎ 9. 打印所有文件           ◎                                                      |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            ------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "请选择 >> ";
        do {
            cin >> n;
            
            // 检查输入是否失败或整数是否超出范围
            if (cin.fail() || n < 0 || n > 9) {
                cin.clear(); // 清除失败状态
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略此行的剩余输入
                cout << "输入有误，请重新输入合法的选项" << endl;
            } else {    
                break; // 输入合法，跳出循环
            }
        } while (true);

        switch(n) {
            case 1: {
                std::string username, filename, content;
                cout << "请输入用户名：" << endl;
                cin >> username;
                cout << "请输入文件名：" << endl;
                cin >> filename;
                cout << "请输入内容：" << endl;
                cin.ignore();
                std::getline(cin, content);
                if (fs.createFile(username, filename, content)) {
                    cout << "文件创建成功。" << endl;
                } else {
                    cout << "文件创建失败。" << endl;
                }
                system("pause");
                break;
            }
            case 2: {
                std::string username, filename;
                cout << "请输入用户名：" << endl;
                cin >> username;
                cout << "请输入文件名：" << endl;
                cin >> filename;
                if (fs.deleteFile(username, filename)) {
                    cout << "文件删除成功。" << endl;
                } else {
                    cout << "文件删除失败。" << endl;
                }
                system("pause");
                break;
            }
            case 3: {
                std::string username, filename;
                cout << "请输入用户名：" << endl;
                cin >> username;
                cout << "请输入文件名：" << endl;
                cin >> filename;
                if (fs.openFile(username, filename)) {
                    cout << "文件打开成功。" << endl;
                } else {
                    cout << "文件打开失败。" << endl;
                }
                system("pause");
                break;
            }
            case 4: {
                std::string username, filename;
                cout << "请输入用户名：" << endl;
                cin >> username;
                cout << "请输入文件名：" << endl;
                cin >> filename;
                if (fs.closeFile(username, filename)) {
                    cout << "文件关闭成功。" << endl;
                } else {
                    cout << "文件关闭失败。" << endl;
                }
                system("pause");
                break;
            }
            case 5: {
                std::string username, filename;
                cout << "请输入用户名：" << endl;
                cin >> username;
                cout << "请输入文件名：" << endl;
                cin >> filename;
                if (fs.readFile(username, filename)) {

                } else {
                    cout << "读取文件内容失败。" << endl;
                }
                system("pause");
                break;
            }
            case 6: {
                std::string username, filename, content;
                cout << "请输入用户名：" << endl;
                cin >> username;
                cout << "请输入文件名：" << endl;
                cin >> filename;
                cout << "请输入要追加的内容：" << endl;
                cin.ignore();
                std::getline(cin, content);
                if (fs.appendFile(username, filename, content)) {
                    cout << "文件内容追加成功。" << endl;
                } else {
                    cout << "文件内容追加失败。" << endl;
                }
                system("pause");
                break;
            }
            case 7: {
                std::string username, filename, content;
                cout << "请输入用户名：" << endl;
                cin >> username;
                cout << "请输入文件名：" << endl;
                cin >> filename;
                cout << "请输入要重写的内容：" << endl;
                cin.ignore();
                std::getline(cin, content);
                if (fs.overwriteFile(username, filename, content)) {
                    cout << "文件内容重写成功。" << endl;
                } else {
                    cout << "文件内容重写失败。" << endl;
                }
                system("pause");
                break;
            }
            case 8: {
                std::string username, oldname, newname;
                cout << "请输入用户名：" << endl;
                cin >> username;
                cout << "请输入旧文件名：" << endl;
                cin >> oldname;
                cout << "请输入新文件名：" << endl;
                cin >> newname;
                if (fs.renameFile(username, oldname, newname)) {
                    cout << "文件重命名成功。" << endl;
                } else {
                    cout << "文件重命名失败。" << endl;
                }
                system("pause");
                break;
            }
            case 9: {
                fs.printAllFiles();
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