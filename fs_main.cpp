#include "fs.h"
#include <windows.h>
#include <limits> // ���뽡׳��

using std::cout;
using std::cin;
using std::endl;

int main() {
    system("color F5");
    keybd_event(VK_F11,0,0,0); //�Զ�ȫ��
    keybd_event(VK_F11,0,KEYEVENTF_KEYUP,0); //��F11ȡ��ȫ��
    printf("\n\n\n\n\n");
    int n = 0;
    FileSystem fs = FileSystem{};

    do {
        system("cls");
        cout << "             --------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                      ��ӭʹ�á��ļ�ϵͳ��ģ��ϵͳ                                                             |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 1. ע���˺�              ��                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 2. ��¼�˺�              ��                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 3. �ǳ��˺�              ��                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 4. �����ļ�              ��                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 5. ���ļ�              ��                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 6. �ر��ļ�              ��                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 7. ��ȡ�ļ�����           ��                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 8. д���ļ�              ��                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 9. ɾ���ļ�              ��                                                       |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 10. ������Ŀ¼             ��                                                      |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 11. ��Ŀ¼              ��                                                      |\n";
        cout << "            |                                                                                                             Produced by 3122004669        |\n";
        cout << "            |                                                        �� 12. ɾ��Ŀ¼              ��                                                      |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 13. ��ʾ��ǰĿ¼          ��                                                      |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 14. ��ʾ����·��          ��                                                      |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            |                                                        �� 15. ��ʾ����ռ��          ��                                                      |\n";
        cout << "            |                                                                                                                                           |\n";
        cout << "            --------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "��ѡ�� >> ";
        do {
            cin >> n;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "������������������Ϸ���ѡ��" << endl;
            } else if (n < 0 || n > 15) {
                cout << "������������������Ϸ���ѡ��" << endl;
            }
        } while (n < 0 || n > 15);

        switch(n) {
            case 1: {
                string username, password;
                cout << "�������û�����";
                cin >> username;
                cout << "���������룺";
                cin >> password;
                fs.sign_up(username, password);
                system("pause");
                break;
            }
            case 2: {
                string username, password;
                cout << "�������û�����";
                cin >> username;
                cout << "���������룺";
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
                cout << "�������ļ�����";
                cin >> filename;
                cout << "�������ļ����ݣ�";
                cin >> content;
                fs.create_file(filename, content);
                system("pause");
                break;
            }
            case 5: {
                string filename;
                cout << "�������ļ�����";
                cin >> filename;
                fs.open_file(filename);
                system("pause");
                break;
            }
            case 6: {
                string filename;
                cout << "�������ļ�����";
                cin >> filename;
                fs.close_file(filename);
                system("pause");
                break;
            }
            case 7: {
                string filename;
                cout << "�������ļ�����";
                cin >> filename;
                fs.read_file(filename);
                system("pause");
                break;
            }
            case 8: {
                string filename, content;
                cout << "�������ļ�����";
                cin >> filename;
                cout << "�������ļ����ݣ�";
                cin >> content;
                fs.write_file(filename, content);
                system("pause");
                break;
            }
            case 9: {
                string filename;
                cout << "�������ļ�����";
                cin >> filename;
                fs.delete_file(filename);
                system("pause");
                break;
            }
            case 10: {
                string dirname;
                cout << "������Ŀ¼����";
                cin >> dirname;
                fs.make_dir(dirname);
                system("pause");
                break;
            }
            case 11: {
                string dirname;
                cout << "������Ŀ¼����";
                cin >> dirname;
                fs.change_dir(dirname);
                system("pause");
                break;
            }
            case 12: {
                string dirname;
                cout << "������Ŀ¼����";
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
                cout << "����������δ������\n������ѡ��\n";
                system("pause");
                break;
            }
        }
    } while(1);

    return 0;
}