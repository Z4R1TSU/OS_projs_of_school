#include <iostream>
#include <queue>
#include <vector>
#include <windows.h>

using namespace std;

struct Process {
    string id;       // 进程ID
    int startTime;   // 到达时间
    int periodTime;  // 服务时间
    
    Process(string id, int s, int p)
        : id(id)
        , startTime(s)
        , periodTime(p) 
    {}
};

// 先来先服务调度程序
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

        cout << "进程ID: " << cur_p.id << "\n"
             << "等待时间: " << curTime - cur_p.startTime << "\n"
             << "开始时间: " << curTime << "\n"
             << "结束时间: " << curTime + cur_p.periodTime << "\n\n";

        curTime += cur_p.periodTime;
        totTime += curTime - cur_p.startTime;
    }

    cout << "所有进程平均等待时间: " << (double)totTime / ps.size() << endl;
}

int main() {
    system("color F5");
    keybd_event(VK_F11,0,0,0); // 自动全屏
    keybd_event(VK_F11,0,KEYEVENTF_KEYUP,0); // 按F11取消全屏

    cout << "=== 先来先服务调度算法测试程序 ===" << endl;
    cout << "作者: 3122004669 徐哲磊  按F11(取消)全屏" << endl;
    cout << "=== 输入部分 ===" << endl;
    cout << "请输入总共有几个进程: ";

    int n;
    cin >> n;

    vector<Process> ps;
    for (int i = 1; i <= n; i ++) {
        string id;
        int startTime, totTime;
        cout << "请输入第 " << i << " 个进程的ID及其开始和服务时间: ";
        cin >> id >> startTime >> totTime;
        ps.emplace_back(id, startTime, totTime);
    }
    
    cout << endl;
    cout << "=== 开始调度 ===" << endl;

    fcfs(ps);
    
    system("pause");
}