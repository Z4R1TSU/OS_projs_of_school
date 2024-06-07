#include <iostream>
#include <queue>
#include <vector>
#include <windows.h>

using namespace std;

// 定义一个进程结构体
struct Process {
    string id;      // 进程ID
    int time;       // CPU所需时间
    // constructor
    Process(string id, int time) : id(id), time(time) {}
};

// 轮转法调度算法
void roundRobin(vector<Process>& ps, int t) {
    queue<Process> q;

    for (Process& p : ps) {
        q.push(p);
    }

    while (!q.empty()) {
        Process cur_proc = q.front();
        q.pop();

        cout << "正在处理进程: " << cur_proc.id << " 需要时长: " << cur_proc.time << endl;

        if (cur_proc.time <= t) {
            // 如果当前进程可在一个时间片内完成
            cout << "进程 " << cur_proc.id << " 可以在一个时间片内完成." << endl;
        } else {
            // 如果当前进程不能在一个时间片内完成，则减去时间片后重新放入队列末尾
            cout << "进程 " << cur_proc.id << " 无法在一个时间片内完成." << endl;
            cout << "进程 " << cur_proc.id << " 本来需要运行时间 " << cur_proc.time << " 还剩下 " << cur_proc.time - t << endl;
            cur_proc.time -= t;
            q.push(cur_proc);
        }
    }
}

int main() {
    system("color F5");
    keybd_event(VK_F11,0,0,0); // 自动全屏
    keybd_event(VK_F11,0,KEYEVENTF_KEYUP,0); // 按F11取消全屏

    cout << "=== 时间片轮转调度算法 ===" << endl;
    cout << "作者: 3122004669 徐哲磊  按F11(取消)全屏" << endl;
    cout << "=== 输入部分 ===" << endl;
    cout << "请输入总共有几个程序: " << endl;

    int n;
    cin >> n;

    cout << "请依次输入每个程序的ID和需要的CPU时间: " << endl;

    vector<Process> ps;
    for (int i = 1; i <= n;  i ++) {
        string id;
        int time;
        cout << "请输入第 " << i << " 个程序的ID和需要的CPU时间: " << endl;
        cin >> id >> time;
        ps.emplace_back(id, time);
    }

    cout << "请输入时间片长度: " << endl;

    int t;
    cin >> t;

    cout << endl;
    cout << "=== 开始调度 ===" << endl;
    roundRobin(ps, t);

    system("pause");
}