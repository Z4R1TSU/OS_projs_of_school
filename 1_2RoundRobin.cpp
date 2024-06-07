#include <iostream>
#include <queue>
#include <vector>
#include <windows.h>

using namespace std;

// ����һ�����̽ṹ��
struct Process {
    string id;      // ����ID
    int time;       // CPU����ʱ��
    // constructor
    Process(string id, int time) : id(id), time(time) {}
};

// ��ת�������㷨
void roundRobin(vector<Process>& ps, int t) {
    queue<Process> q;

    for (Process& p : ps) {
        q.push(p);
    }

    while (!q.empty()) {
        Process cur_proc = q.front();
        q.pop();

        cout << "���ڴ������: " << cur_proc.id << " ��Ҫʱ��: " << cur_proc.time << endl;

        if (cur_proc.time <= t) {
            // �����ǰ���̿���һ��ʱ��Ƭ�����
            cout << "���� " << cur_proc.id << " ������һ��ʱ��Ƭ�����." << endl;
        } else {
            // �����ǰ���̲�����һ��ʱ��Ƭ����ɣ����ȥʱ��Ƭ�����·������ĩβ
            cout << "���� " << cur_proc.id << " �޷���һ��ʱ��Ƭ�����." << endl;
            cout << "���� " << cur_proc.id << " ������Ҫ����ʱ�� " << cur_proc.time << " ��ʣ�� " << cur_proc.time - t << endl;
            cur_proc.time -= t;
            q.push(cur_proc);
        }
    }
}

int main() {
    system("color F5");
    keybd_event(VK_F11,0,0,0); // �Զ�ȫ��
    keybd_event(VK_F11,0,KEYEVENTF_KEYUP,0); // ��F11ȡ��ȫ��

    cout << "=== ʱ��Ƭ��ת�����㷨 ===" << endl;
    cout << "����: 3122004669 ������  ��F11(ȡ��)ȫ��" << endl;
    cout << "=== ���벿�� ===" << endl;
    cout << "�������ܹ��м�������: " << endl;

    int n;
    cin >> n;

    cout << "����������ÿ�������ID����Ҫ��CPUʱ��: " << endl;

    vector<Process> ps;
    for (int i = 1; i <= n;  i ++) {
        string id;
        int time;
        cout << "������� " << i << " �������ID����Ҫ��CPUʱ��: " << endl;
        cin >> id >> time;
        ps.emplace_back(id, time);
    }

    cout << "������ʱ��Ƭ����: " << endl;

    int t;
    cin >> t;

    cout << endl;
    cout << "=== ��ʼ���� ===" << endl;
    roundRobin(ps, t);

    system("pause");
}