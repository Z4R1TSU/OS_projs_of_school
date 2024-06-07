#ifndef _4_1FS_H_
#define _4_1FS_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <windows.h>

using namespace std;

// 最大用户数量
const int MAX_USERS = 10;
// 每个用户最多可以有10个文件
const int MAX_FILES_PER_USER = 10;
// 每个用户最多可以同时打开5个文件
const int MAX_OPEN_FILES_PER_USER = 5;

// 文件
struct File {
    string name;
    string content;
    bool is_open;

    File (string name = "", string content = "", bool is_open = false)
        : name(name)
        , content(content)
        , is_open(is_open)
    {}

    File (const File& other) 
        : name(other.name)
        , content(other.content)
        , is_open(other.is_open)
    {}

    File& operator= (const File& other) {
        if (this != &other) {
            this->name = other.name;
            this->content = other.content;
            this->is_open = other.is_open;
        }
        return *this;
    }
};

// UFD 用户文件目录
struct User {
    string name;
    map<string, File> files;
};

class FileSystem {
public:
    FileSystem();
    ~FileSystem();

    bool createFile(const string& username, const string& filename, const string& content = "");
    bool deleteFile(const string& username, const string& filename);
    bool openFile(const string& username, const string& filename);
    bool closeFile(const string& username, const string& filename);
    bool readFile(const string& username, const string& filename);
    bool appendFile(const string& username, const string& filename, const string& content);
    bool overwriteFile(const string& username, const string& filename, const string& content);
    bool renameFile(const string& username, const string& oldname, const string& newname);
    void printAllFiles();

private:
    map<string, User> mfd; // MFD 用户文件目录
    vector<File*> afd; // AFD 可用文件目录

    // 辅助函数
    bool isValidUsername(const string& username);
    bool isValidFilename(const string& filename);
    bool isFileExist(const string& username, const string& filename);
};

#endif // _4_1FS_H_