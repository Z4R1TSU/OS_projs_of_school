#include <iostream>
#include <queue>
#include <vector>
#include <windows.h>

using namespace std;

// ����һ�����̽ṹ��
struct Process {
    string id;            // ����ID
    int totTime;          // ����������CPUʱ��
    int remainTime;       // ����ʣ������CPUʱ��
    int level;            // ��ǰ�������ڷ������еĵȼ�
    // constructor
    Process(string id, int t) 
        : id(id), totTime(t)
        , remainTime(t)
        , level(0) 
    {}
};

// �༶�������е����㷨(Multi-Level Feedback Queue Scheduling)
void mlfq(vector<Process>& ps, vector<int>& ts) {
    vector<queue<Process>> q(ts.size());
    int cntTime = 0;

    // ���н����ȼ���һ������
    for (auto& p : ps) {
        q[0].push(p);
    }

    for (;;) {
        bool isAllEmpty = true;

        for (int i = 0; i < q.size(); i ++) {
            if (!q[i].empty()) {
                isAllEmpty = false;
                Process cur_proc = q[i].front();
                q[i].pop();

                int cur_t = ts[i];
                cout << "���ڴ������: " << cur_proc.id << " �� " << i + 1 << " ������ ʣ��ʱ��: " << cur_proc.remainTime << ", ʱ��Ƭ����: " << cur_t << endl;

                if (cur_proc.remainTime <= cur_t) {
                    cntTime += cur_proc.remainTime;
                    cout << "���� " << cur_proc.id << " ��� ������ʱ��: " << cntTime << endl;
                } else {
                    cntTime += cur_t;
                    cur_proc.remainTime -= cur_t;

                    if (i < q.size() - 1) {
                        q[i + 1].push(cur_proc);
                    } else {
                        // ����Ѿ������һ�����У��ᵽһ������ȥ
                        cout << "���� " << cur_proc.id << " �ڵ������ֵ������޷�����ʱ��ɣ������ᵽһ������" << endl;
                        q[0].push(cur_proc);
                    }
                }
            }
        }

        // ������ж��ж�Ϊ�գ������
        if (isAllEmpty) {
            break;
        }
    }
}

int main() {
    system("color F5");
    keybd_event(VK_F11,0,0,0); // �Զ�ȫ��
    keybd_event(VK_F11,0,KEYEVENTF_KEYUP,0); // ��F11ȡ��ȫ��

    cout << "=== �༶�������е����㷨 ===" << endl;
    cout << "����: 3122004669 ������  ��F11(ȡ��)ȫ��" << endl;
    cout << "=== ���벿�� ===" << endl;
    cout << "�������ܹ��м�������: ";

    int n;
    cin >> n;

    vector<Process> ps;
    for (int i = 1; i <= n; i ++) {
        string id;
        int totTime;
        cout << "������� " << i << " �����̵�ID����CPUʱ��: ";
        cin >> id >> totTime;
        ps.emplace_back(id, totTime);
    }

    cout << "�������ܹ���Ҫ��������: " << endl;
    int m;
    cin >> m;

    vector<int> timeSlices(m);
    for (int i = 0; i < m; i ++) {
        cout << "������� " << i + 1 << " �����е�ʱ��Ƭ����: ";
        cin >> timeSlices[i];
    }

    cout << endl;
    cout << "=== ��ʼ���� ===" << endl;
    mlfq(ps, timeSlices);

    system("pause");
}