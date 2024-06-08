#ifndef _FS_H_
#define _FS_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>

const int FS_SZ = 1024 * 1024; // 文件系统大小，单位：字节

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
    Directory *parent; // 这里用裸指针，防止智能指针的交叉引用

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
    map<string, string> users;  // 用户名和密码
    Directory root;             // 根目录
    Directory *cur_dir;         // 当前目录
    string cur_user;            // 当前用户
    bool is_login;              // 是否已登录
    
    bool is_valid_username(const string& username);

    // 存储器模块
    vector<bool> bitmap;       // false代表空闲，true代表已占用
    vector<int> find_free_space(int size); // 寻找空闲存储空间
};

#endif // _FS_H_