#ifndef _FS_H_
#define _FS_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>

const int FS_SZ = 1024 * 1024; // �ļ�ϵͳ��С����λ���ֽ�

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::map;

struct File {
    string name;
    int start_addr;
    int size;
    string content;
    bool is_open;

    File (string name, int start_addr, int size, string content, bool is_open)
        : name(name)
        , start_addr(start_addr)
        , size(size)
        , content(content)
        , is_open(is_open)
    {}
};

struct Directory {
    string name;
    map<string, std::unique_ptr<File>> files;
    map<string, std::unique_ptr<Directory>> dirs;
    Directory *parent; // ��������ָ�룬��ֹ����ָ��Ľ�������

    Directory (string name, Directory *parent)
        : name(name)
        , parent(parent)
    {}
};

class FileSystem {
public:
    FileSystem ();
    ~FileSystem ();

    bool sign_up(const string& username, const string& password);
    bool login(const string& username, const string& password);
    bool create_file(const string& filename, const string& content);
    bool open_file(const string& filename);
    bool close_file(const string& filename);
    bool read_file(const string& filename);
    bool write_file(const string& filename, const string& content);
    bool delete_file(const string& filename);
    bool make_dir(const string& dirname);
    bool change_dir(const string& dirname);
    bool delete_dir(const string& dirname);
    bool list_dir();
    bool print_working_dir();
    bool disk_usage();
    bool logout();

private:
    map<string, string> users;  // �û���������
    Directory root;             // ��Ŀ¼
    Directory *cur_dir;         // ��ǰĿ¼
    string cur_user;            // ��ǰ�û�
    bool is_login;              // �Ƿ��ѵ�¼
    
    bool is_valid_username(const string& username);

    // �洢��ģ��
    vector<bool> bitmap;       // false������У�true������ռ��
    vector<int> find_free_space(int size); // Ѱ�ҿ��д洢�ռ�
};

#endif // _FS_H_