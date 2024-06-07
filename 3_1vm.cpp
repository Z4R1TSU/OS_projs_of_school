#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <windows.h>
#include <ctime>
#include <cstdlib>

using namespace std;

const int TOT_ADDR_SIZE = 20;       // ���ɵ��ܵ�ָ���ַ��
const int MEMORY_SIZE = 64;         // �����ڴ�ҳ��
const int PAGE_SIZE = 4;            // ҳ���С
const int ADDR_SPACE = 256;         // ��ַ�ռ��С

// ���������ָ���ַ
vector<int> randomGenerateAddress() {
    vector<int> addrs;
    addrs.reserve(TOT_ADDR_SIZE);
    
    srand(time(0));
    for (int i = 0; i < TOT_ADDR_SIZE; i ++) {
        int random_val = rand() % 100;
        if (random_val < 50) {
            // 50����ָ����˳��ִ�е�
            addrs.push_back(i % ADDR_SPACE);
        } else if (random_val < 75) {
            // 25����ָ����ȵ�ɢ����ǰ��ַ����
            addrs.push_back(rand() % (ADDR_SPACE / 2));
        } else {
            // 25���ĵ�ַ�Ǿ��ȵ�ɢ���ں��ַ����
            addrs.push_back(rand() % (ADDR_SPACE / 2) + ADDR_SPACE / 2);
        }
    }
    return addrs;
}

void print_pgtbl(const vector<int>& pgtbl) {
    cout << "Page table������Ϊ: " << endl;
    for (int i = 0; i < pgtbl.size(); i ++) {
        if (pgtbl[i] != -1) {
            cout << pgtbl[i] << " ";
        } else {
            cout << ".";
        }
    }
    cout << endl;
}

// ��FIFO���н���ҳ�����������(ҳ����̭�㷨)
void fifo(vector<int>& addrs) {
    // ��ʼ��ҳ��
    int pgnum = ADDR_SPACE / PAGE_SIZE;
    vector<int> pgtbl(pgnum, -1);
    // FIFO -> queue
    queue<int> q;
    int pgf_cnt = 0;
    
    for (const auto& addr : addrs) {
        int pgidx = floor(addr / PAGE_SIZE);
        bool page_fault = true;

        // ���ҳ���Ƿ��Ѿ��������ڴ���
        for (int i = 0; i < MEMORY_SIZE; i ++) {
            if (pgtbl[i] == pgidx) {
                page_fault = false;
            }
        }

        if (page_fault) {
            pgf_cnt ++;

            // ����ڴ�������ʹ��FIFO����ҳ���滻
            if (q.size() == MEMORY_SIZE) {
                int rm_pg_num = q.front();
                q.pop();
                for (int i = 0; i < MEMORY_SIZE; i ++) {
                    if (pgtbl[i] == rm_pg_num) {
                        pgtbl[i] = -1;
                        break;
                    }
                }
                cout << "�ڴ��������滻�� " << rm_pg_num << " ҳ" << endl;
            }

            // ����ҳ���FIFO����
            for (int i = 0; i < MEMORY_SIZE; i ++) {
                if (pgtbl[i] == -1) {
                    pgtbl[i] = pgidx;
                    q.push(pgidx);
                    cout << "�� " << i << " λ���޸�Ϊ " << pgidx << endl;
                    break;
                }
            }
        } else {
            cout << "�� " << pgidx << " ҳ�Ѿ����ڴ浱��" << endl;
        }

        print_pgtbl(pgtbl);
    }

    cout << "��Page Faults���� " << pgf_cnt << " ��" << endl;
}

int main() {
    // system("color F5");
    keybd_event(VK_F11,0,0,0); // �Զ�ȫ��
    keybd_event(VK_F11,0,KEYEVENTF_KEYUP,0); // ��F11ȡ��ȫ��

    cout << "=== ����ҳʽ�洢�����㷨���Գ��� ===" << endl;
    cout << "����: 3122004669 ������  ��F11(ȡ��)ȫ��" << endl;
    cout << "Page Table��Ч������.��ʾ" << endl;

    cout << "�����ڴ�ҳ��: " << MEMORY_SIZE << endl
         << "ҳ���С: " << PAGE_SIZE << endl
         << "��ַ�ռ��С: " << ADDR_SPACE << endl;

    vector<int> addrs = randomGenerateAddress();

    // ������ɵ����ָ���ַ��
    cout << "������ɵ����ָ���ַ��: ";
    for (const auto& addr: addrs) {
        cout << addr << " ";
    }
    cout << endl;

    fifo(addrs);

    system("pause");
}