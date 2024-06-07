#include "4_1fs.h"
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
    int n;
    FileSystem fs = FileSystem{};

    do {
        system("cls");
        cout << "             ----------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                      ��ӭʹ�á��ļ�ϵͳ��ģ��ϵͳ                                                            |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        �� 1. �½��ļ�              ��                                                       |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        �� 2. ɾ���ļ�              ��                                                       |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        �� 3. ���ļ�              ��                                                      |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        �� 4. �ر��ļ�              ��                                                       |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        �� 5. �����ļ�����           ��                                                       |\n";
        cout << "            |                                                                                                                                          |\n";
        cout << "            |                                                        �� 6. ׷���ļ�����           ��                                                       |\n";
        cout << "            |                                                                                                                                          |\n";
        cout << "            |                                                        �� 7. ��д�ļ�����           ��                                                       |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            |                                                        �� 8. �������ļ�             ��                                                     |\n";
        cout << "            |                                                                                                             Produced by 3122004669      |\n";
        cout << "            |                                                        �� 9. ��ӡ�����ļ�           ��                                                      |\n";
        cout << "            |                                                                                                                                         |\n";
        cout << "            ------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "��ѡ�� >> ";
        do {
            cin >> n;
            
            // ��������Ƿ�ʧ�ܻ������Ƿ񳬳���Χ
            if (cin.fail() || n < 0 || n > 9) {
                cin.clear(); // ���ʧ��״̬
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���Դ��е�ʣ������
                cout << "������������������Ϸ���ѡ��" << endl;
            } else {    
                break; // ����Ϸ�������ѭ��
            }
        } while (true);

        switch(n) {
            case 1: {
                std::string username, filename, content;
                cout << "�������û�����" << endl;
                cin >> username;
                cout << "�������ļ�����" << endl;
                cin >> filename;
                cout << "���������ݣ�" << endl;
                cin.ignore();
                std::getline(cin, content);
                if (fs.createFile(username, filename, content)) {
                    cout << "�ļ������ɹ���" << endl;
                } else {
                    cout << "�ļ�����ʧ�ܡ�" << endl;
                }
                system("pause");
                break;
            }
            case 2: {
                std::string username, filename;
                cout << "�������û�����" << endl;
                cin >> username;
                cout << "�������ļ�����" << endl;
                cin >> filename;
                if (fs.deleteFile(username, filename)) {
                    cout << "�ļ�ɾ���ɹ���" << endl;
                } else {
                    cout << "�ļ�ɾ��ʧ�ܡ�" << endl;
                }
                system("pause");
                break;
            }
            case 3: {
                std::string username, filename;
                cout << "�������û�����" << endl;
                cin >> username;
                cout << "�������ļ�����" << endl;
                cin >> filename;
                if (fs.openFile(username, filename)) {
                    cout << "�ļ��򿪳ɹ���" << endl;
                } else {
                    cout << "�ļ���ʧ�ܡ�" << endl;
                }
                system("pause");
                break;
            }
            case 4: {
                std::string username, filename;
                cout << "�������û�����" << endl;
                cin >> username;
                cout << "�������ļ�����" << endl;
                cin >> filename;
                if (fs.closeFile(username, filename)) {
                    cout << "�ļ��رճɹ���" << endl;
                } else {
                    cout << "�ļ��ر�ʧ�ܡ�" << endl;
                }
                system("pause");
                break;
            }
            case 5: {
                std::string username, filename;
                cout << "�������û�����" << endl;
                cin >> username;
                cout << "�������ļ�����" << endl;
                cin >> filename;
                if (fs.readFile(username, filename)) {

                } else {
                    cout << "��ȡ�ļ�����ʧ�ܡ�" << endl;
                }
                system("pause");
                break;
            }
            case 6: {
                std::string username, filename, content;
                cout << "�������û�����" << endl;
                cin >> username;
                cout << "�������ļ�����" << endl;
                cin >> filename;
                cout << "������Ҫ׷�ӵ����ݣ�" << endl;
                cin.ignore();
                std::getline(cin, content);
                if (fs.appendFile(username, filename, content)) {
                    cout << "�ļ�����׷�ӳɹ���" << endl;
                } else {
                    cout << "�ļ�����׷��ʧ�ܡ�" << endl;
                }
                system("pause");
                break;
            }
            case 7: {
                std::string username, filename, content;
                cout << "�������û�����" << endl;
                cin >> username;
                cout << "�������ļ�����" << endl;
                cin >> filename;
                cout << "������Ҫ��д�����ݣ�" << endl;
                cin.ignore();
                std::getline(cin, content);
                if (fs.overwriteFile(username, filename, content)) {
                    cout << "�ļ�������д�ɹ���" << endl;
                } else {
                    cout << "�ļ�������дʧ�ܡ�" << endl;
                }
                system("pause");
                break;
            }
            case 8: {
                std::string username, oldname, newname;
                cout << "�������û�����" << endl;
                cin >> username;
                cout << "��������ļ�����" << endl;
                cin >> oldname;
                cout << "���������ļ�����" << endl;
                cin >> newname;
                if (fs.renameFile(username, oldname, newname)) {
                    cout << "�ļ��������ɹ���" << endl;
                } else {
                    cout << "�ļ�������ʧ�ܡ�" << endl;
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
                cout << "����������δ������\n������ѡ��\n";
                system("pause");
                break;
            }
        }
    } while(1);

    return 0;
}