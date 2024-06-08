#include "4_1fs.h"

FileSystem::FileSystem() {
    cout << "��ʼ���ļ�ϵͳ" << endl;
}

FileSystem::~FileSystem() {
    cout << "�����ļ�ϵͳ" << endl;
}

bool FileSystem::createFile(const string& username, const string& filename, const string& content) {
    if (!isValidUsername(username) || mfd[username].files.size() >= MAX_FILES_PER_USER) {
        cout << "�û�" << username << "�򿪵��ļ�������������" << endl;
        return false;
    }
    mfd[username].files[filename] = { filename, content, false };
    cout << "�û�" << username << "����" << filename << "�ļ��ɹ�" << endl;
    return true;
}

bool FileSystem::deleteFile(const string& username, const string& filename) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        if (auto isClosed = closeFile(username, filename); !isClosed) {
            cout << "�û�" << username << "�ر�" << filename << "�ļ�ʧ�ܣ��޷�����ɾ��" << endl;
            return false;
        }
        mfd[username].files.erase(filename);
        return true;
    } else {
        cout << "�û�" << username << "������" << filename << "�ļ�" << endl;
        return false;
    }
}

bool FileSystem::openFile(const string& username, const string& filename) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        if (mfd[username].files[filename].is_open) {
            cout << "�ļ�" << filename << "�ѱ���" << endl;
            return false;
        } else {
            mfd[username].files[filename].is_open = true;
            cout << "�û�" << username << "��" << filename << "�ļ��ɹ�" << endl;
            cout << "�ļ�����Ϊ��";
            cout << mfd[username].files[filename].content << endl;
            return true;
        }
    } else {
        cout << "�û�" << username << "������" << filename << "�ļ�" << endl;
        return false;
    }
}

bool FileSystem::closeFile(const string& username, const string& filename) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        if (mfd[username].files[filename].is_open) {
            mfd[username].files[filename].is_open = false;
            cout << "�û�" << username << "�ɹ��ر�" << filename << "�ļ�" << endl;
            return true;
        } else {
            cout << "�ļ�" << filename << "�ѱ��ر�" << endl;
            return true;
        }
    } else {
        cout << "�û�" << username << "������" << filename << "�ļ�" << endl;
        return false;
    }
}

bool FileSystem::readFile(const string& username, const string& filename) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        string_view content = mfd[username].files[filename].content;
        cout << "�ļ�" << filename << "������Ϊ��" << content << endl;
        return true;
    } else {
        cout << "�û�" << username << "������" << filename << "�ļ�" << endl;
        return false;
    }
}

bool FileSystem::appendFile(const string& username, const string& filename, const string& content) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        mfd[username].files[filename].content += content;
        cout << "�û�" << username << "׷�����ݵ�" << filename << "�ļ��ɹ�" << endl;
        return true;
    } else {
        cout << "�û�" << username << "������" << filename << "�ļ�" << endl;
        return false;
    }
}

bool FileSystem::overwriteFile(const string& username, const string& filename, const string& content) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        mfd[username].files[filename].content = content;
        cout << "�û�" << username << "��д���ݵ�" << filename << "�ļ��ɹ�" << endl;
        return true;
    } else {
        cout << "�û�" << username << "������" << filename << "�ļ�" << endl;
        return false;
    }
}

bool FileSystem::renameFile(const string& username, const string& oldname, const string& newname) {
    if (auto isFound = isFileExist(username, oldname); isFound) {
        if (isValidFilename(newname)) {
            mfd[username].files[newname] = mfd[username].files[oldname];
            mfd[username].files.erase(oldname);
            mfd[username].files[newname].name = newname;
            cout << "�û�" << username << "��������" << oldname << "��Ϊ������" << newname << "�ɹ�" << endl;
            return true;
        } else {
            cout << "������" << newname << "�����������" << endl;
            return false;
        }
    } else {
        cout << "�û�" << username << "������" << oldname << "�ļ�" << endl;
        return false;
    }
}

void FileSystem::printAllFiles() {
    for (const auto& user : mfd) {
        cout << "�û�" << user.first << "ӵ�������ļ���" << endl;
        for (const auto& file : user.second.files) {
            cout << "  " << file.second.name  << " �ļ����� " << (file.second.is_open ? "��" : "�ر�") << " ״̬" << endl;
        }
    }
}  

bool FileSystem::isValidFilename(const string& filename) {
    for (const auto& fn : mfd) {
        if (fn.first == filename) {
            cout << "���ļ��������������" << endl;
            return false;
        }
    }
    return true;
}

bool FileSystem::isValidUsername(const string& username) {
    for (const auto& un : mfd) {
        if (un.second.name == username) {
            cout << "���û��������������" << endl;
            return false;
        }
    }
    return true;
}

bool FileSystem::isFileExist(const string& username, const string& filename) {
    auto userIt = mfd.find(username);
    if (userIt != mfd.end()) {
        auto fileIt = userIt->second.files.find(filename);
        if (fileIt != userIt->second.files.end()) {
            return true;
        }
    }
    return false;
}
