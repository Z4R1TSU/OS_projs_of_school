#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <windows.h>
#include <ctime>
#include <cstdlib>

using namespace std;

const int TOT_ADDR_SIZE = 20;       // 生成的总的指令地址数
const int MEMORY_SIZE = 64;         // 物理内存页数
const int PAGE_SIZE = 4;            // 页面大小
const int ADDR_SPACE = 256;         // 地址空间大小

// 生成随机的指令地址
vector<int> randomGenerateAddress() {
    vector<int> addrs;
    addrs.reserve(TOT_ADDR_SIZE);
    
    srand(time(0));
    for (int i = 0; i < TOT_ADDR_SIZE; i ++) {
        int random_val = rand() % 100;
        if (random_val < 50) {
            // 50％的指令是顺序执行的
            addrs.push_back(i % ADDR_SPACE);
        } else if (random_val < 75) {
            // 25％的指令均匀地散布在前地址部分
            addrs.push_back(rand() % (ADDR_SPACE / 2));
        } else {
            // 25％的地址是均匀地散布在后地址部分
            addrs.push_back(rand() % (ADDR_SPACE / 2) + ADDR_SPACE / 2);
        }
    }
    return addrs;
}

void print_pgtbl(const vector<int>& pgtbl) {
    cout << "Page table的内容为: " << endl;
    for (int i = 0; i < pgtbl.size(); i ++) {
        if (pgtbl[i] != -1) {
            cout << pgtbl[i] << " ";
        } else {
            cout << ".";
        }
    }
    cout << endl;
}

// 用FIFO进行进行页面请求与管理(页面淘汰算法)
void fifo(vector<int>& addrs) {
    // 初始化页表
    int pgnum = ADDR_SPACE / PAGE_SIZE;
    vector<int> pgtbl(pgnum, -1);
    // FIFO -> queue
    queue<int> q;
    int pgf_cnt = 0;
    
    for (const auto& addr : addrs) {
        int pgidx = floor(addr / PAGE_SIZE);
        bool page_fault = true;

        // 检查页面是否已经在物理内存中
        for (int i = 0; i < MEMORY_SIZE; i ++) {
            if (pgtbl[i] == pgidx) {
                page_fault = false;
            }
        }

        if (page_fault) {
            pgf_cnt ++;

            // 如果内存已满，使用FIFO进行页面替换
            if (q.size() == MEMORY_SIZE) {
                int rm_pg_num = q.front();
                q.pop();
                for (int i = 0; i < MEMORY_SIZE; i ++) {
                    if (pgtbl[i] == rm_pg_num) {
                        pgtbl[i] = -1;
                        break;
                    }
                }
                cout << "内存已满，替换第 " << rm_pg_num << " 页" << endl;
            }

            // 更新页表和FIFO队列
            for (int i = 0; i < MEMORY_SIZE; i ++) {
                if (pgtbl[i] == -1) {
                    pgtbl[i] = pgidx;
                    q.push(pgidx);
                    cout << "第 " << i << " 位被修改为 " << pgidx << endl;
                    break;
                }
            }
        } else {
            cout << "第 " << pgidx << " 页已经在内存当中" << endl;
        }

        print_pgtbl(pgtbl);
    }

    cout << "总Page Faults出现 " << pgf_cnt << " 次" << endl;
}

int main() {
    // system("color F5");
    keybd_event(VK_F11,0,0,0); // 自动全屏
    keybd_event(VK_F11,0,KEYEVENTF_KEYUP,0); // 按F11取消全屏

    cout << "=== 请求页式存储管理算法测试程序 ===" << endl;
    cout << "作者: 3122004669 徐哲磊  按F11(取消)全屏" << endl;
    cout << "Page Table无效内容用.表示" << endl;

    cout << "物理内存页数: " << MEMORY_SIZE << endl
         << "页面大小: " << PAGE_SIZE << endl
         << "地址空间大小: " << ADDR_SPACE << endl;

    vector<int> addrs = randomGenerateAddress();

    // 输出生成的随机指令地址流
    cout << "输出生成的随机指令地址流: ";
    for (const auto& addr: addrs) {
        cout << addr << " ";
    }
    cout << endl;

    fifo(addrs);

    system("pause");
}