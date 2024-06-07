#include <iostream>
#include <queue>
#include <vector>
#include <windows.h>

using namespace std;

// 定义一个进程结构体
struct Process {
    string id;            // 进程ID
    int totTime;          // 进程所需总CPU时间
    int remainTime;       // 进程剩余所需CPU时间
    int level;            // 当前进程所在反馈队列的等级
    // constructor
    Process(string id, int t) 
        : id(id), totTime(t)
        , remainTime(t)
        , level(0) 
    {}
};

// 多级反馈队列调度算法(Multi-Level Feedback Queue Scheduling)
void mlfq(vector<Process>& ps, vector<int>& ts) {
    vector<queue<Process>> q(ts.size());
    int cntTime = 0;

    // 所有进程先加入一级队列
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
                cout << "正在处理进程: " << cur_proc.id << " 在 " << i + 1 << " 级队列 剩余时长: " << cur_proc.remainTime << ", 时间片长度: " << cur_t << endl;

                if (cur_proc.remainTime <= cur_t) {
                    cntTime += cur_proc.remainTime;
                    cout << "进程 " << cur_proc.id << " 完成 总运行时间: " << cntTime << endl;
                } else {
                    cntTime += cur_t;
                    cur_proc.remainTime -= cur_t;

                    if (i < q.size() - 1) {
                        q[i + 1].push(cur_proc);
                    } else {
                        // 如果已经在最后一个队列，提到一级队列去
                        cout << "进程 " << cur_proc.id << " 在单次整轮调度中无法被及时完成，将被提到一级队列" << endl;
                        q[0].push(cur_proc);
                    }
                }
            }
        }

        // 如果所有队列都为空，则结束
        if (isAllEmpty) {
            break;
        }
    }
}

int main() {
    system("color F5");
    keybd_event(VK_F11,0,0,0); // 自动全屏
    keybd_event(VK_F11,0,KEYEVENTF_KEYUP,0); // 按F11取消全屏

    cout << "=== 多级反馈队列调度算法 ===" << endl;
    cout << "作者: 3122004669 徐哲磊  按F11(取消)全屏" << endl;
    cout << "=== 输入部分 ===" << endl;
    cout << "请输入总共有几个进程: ";

    int n;
    cin >> n;

    vector<Process> ps;
    for (int i = 1; i <= n; i ++) {
        string id;
        int totTime;
        cout << "请输入第 " << i << " 个进程的ID和总CPU时间: ";
        cin >> id >> totTime;
        ps.emplace_back(id, totTime);
    }

    cout << "请输入总共需要几级队列: " << endl;
    int m;
    cin >> m;

    vector<int> timeSlices(m);
    for (int i = 0; i < m; i ++) {
        cout << "请输入第 " << i + 1 << " 级队列的时间片长度: ";
        cin >> timeSlices[i];
    }

    cout << endl;
    cout << "=== 开始调度 ===" << endl;
    mlfq(ps, timeSlices);

    system("pause");
}