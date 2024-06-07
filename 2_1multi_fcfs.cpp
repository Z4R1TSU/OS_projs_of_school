#include <iostream>
#include <queue>
#include <vector>
#include <windows.h>

using namespace std;

struct Process {
    string id;       // ����ID
    int startTime;   // ����ʱ��
    int periodTime;  // ����ʱ��
    
    Process(string id, int s, int p)
        : id(id)
        , startTime(s)
        , periodTime(p) 
    {}
};

// �����ȷ�����ȳ���
void fcfs(const vector<Process>& ps) {
    queue<Process> q;
    for (const auto& p : ps) {
        q.push(p);
    }

    int curTime = 0;
    int totTime = 0;
    
    while (!q.empty()) {
        Process cur_p = q.front();
        q.pop();
        
        while (curTime < cur_p.startTime) {
            curTime ++;
        }

        cout << "����ID: " << cur_p.id << "\n"
             << "�ȴ�ʱ��: " << curTime - cur_p.startTime << "\n"
             << "��ʼʱ��: " << curTime << "\n"
             << "����ʱ��: " << curTime + cur_p.periodTime << "\n\n";

        curTime += cur_p.periodTime;
        totTime += curTime - cur_p.startTime;
    }

    cout << "���н���ƽ���ȴ�ʱ��: " << (double)totTime / ps.size() << endl;
}

int main() {
    system("color F5");
    keybd_event(VK_F11,0,0,0); // �Զ�ȫ��
    keybd_event(VK_F11,0,KEYEVENTF_KEYUP,0); // ��F11ȡ��ȫ��

    cout << "=== �����ȷ�������㷨���Գ��� ===" << endl;
    cout << "����: 3122004669 ������  ��F11(ȡ��)ȫ��" << endl;
    cout << "=== ���벿�� ===" << endl;
    cout << "�������ܹ��м�������: ";

    int n;
    cin >> n;

    vector<Process> ps;
    for (int i = 1; i <= n; i ++) {
        string id;
        int startTime, totTime;
        cout << "������� " << i << " �����̵�ID���俪ʼ�ͷ���ʱ��: ";
        cin >> id >> startTime >> totTime;
        ps.emplace_back(id, startTime, totTime);
    }
    
    cout << endl;
    cout << "=== ��ʼ���� ===" << endl;

    fcfs(ps);
    
    system("pause");
}