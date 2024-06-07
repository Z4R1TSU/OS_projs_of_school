#ifndef _4_1FS_H_
#define _4_1FS_H_

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <windows.h>

using namespace std;

// ����û�����
const int MAX_USERS = 10;
// ÿ���û���������10���ļ�
const int MAX_FILES_PER_USER = 10;
// ÿ���û�������ͬʱ��5���ļ�
const int MAX_OPEN_FILES_PER_USER = 5;

// �ļ�
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

// UFD �û��ļ�Ŀ¼
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
    map<string, User> mfd; // MFD �û��ļ�Ŀ¼
    vector<File*> afd; // AFD �����ļ�Ŀ¼

    // ��������
    bool isValidUsername(const string& username);
    bool isValidFilename(const string& filename);
    bool isFileExist(const string& username, const string& filename);
};

#endif // _4_1FS_H_