#include "4_1fs.h"

FileSystem::FileSystem() {
    cout << "初始化文件系统" << endl;
}

FileSystem::~FileSystem() {
    cout << "销毁文件系统" << endl;
}

bool FileSystem::createFile(const string& username, const string& filename, const string& content) {
    if (!isValidUsername(username) || mfd[username].files.size() >= MAX_FILES_PER_USER) {
        cout << "用户" << username << "打开的文件数量超过限制" << endl;
        return false;
    }
    mfd[username].files[filename] = { filename, content, false };
    cout << "用户" << username << "创建" << filename << "文件成功" << endl;
    return true;
}

bool FileSystem::deleteFile(const string& username, const string& filename) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        if (auto isClosed = closeFile(username, filename); !isClosed) {
            cout << "用户" << username << "关闭" << filename << "文件失败，无法进行删除" << endl;
            return false;
        }
        mfd[username].files.erase(filename);
        return true;
    } else {
        cout << "用户" << username << "不存在" << filename << "文件" << endl;
        return false;
    }
}

bool FileSystem::openFile(const string& username, const string& filename) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        if (mfd[username].files[filename].is_open) {
            cout << "文件" << filename << "已被打开" << endl;
            return false;
        } else {
            mfd[username].files[filename].is_open = true;
            cout << "用户" << username << "打开" << filename << "文件成功" << endl;
            cout << "文件内容为：";
            cout << mfd[username].files[filename].content << endl;
            return true;
        }
    } else {
        cout << "用户" << username << "不存在" << filename << "文件" << endl;
        return false;
    }
}

bool FileSystem::closeFile(const string& username, const string& filename) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        if (mfd[username].files[filename].is_open) {
            mfd[username].files[filename].is_open = false;
            cout << "用户" << username << "成功关闭" << filename << "文件" << endl;
            return true;
        } else {
            cout << "文件" << filename << "已被关闭" << endl;
            return true;
        }
    } else {
        cout << "用户" << username << "不存在" << filename << "文件" << endl;
        return false;
    }
}

bool FileSystem::readFile(const string& username, const string& filename) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        string_view content = mfd[username].files[filename].content;
        cout << "文件" << filename << "的内容为：" << content << endl;
        return true;
    } else {
        cout << "用户" << username << "不存在" << filename << "文件" << endl;
        return false;
    }
}

bool FileSystem::appendFile(const string& username, const string& filename, const string& content) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        mfd[username].files[filename].content += content;
        cout << "用户" << username << "追加内容到" << filename << "文件成功" << endl;
        return true;
    } else {
        cout << "用户" << username << "不存在" << filename << "文件" << endl;
        return false;
    }
}

bool FileSystem::overwriteFile(const string& username, const string& filename, const string& content) {
    if (auto isFound = isFileExist(username, filename); isFound) {
        mfd[username].files[filename].content = content;
        cout << "用户" << username << "覆写内容到" << filename << "文件成功" << endl;
        return true;
    } else {
        cout << "用户" << username << "不存在" << filename << "文件" << endl;
        return false;
    }
}

bool FileSystem::renameFile(const string& username, const string& oldname, const string& newname) {
    if (auto isFound = isFileExist(username, oldname); isFound) {
        if (isValidFilename(newname)) {
            mfd[username].files[newname] = mfd[username].files[oldname];
            mfd[username].files.erase(oldname);
            mfd[username].files[newname].name = newname;
            cout << "用户" << username << "将旧名字" << oldname << "改为新名字" << newname << "成功" << endl;
            return true;
        } else {
            cout << "新名字" << newname << "存在重名情况" << endl;
            return false;
        }
    } else {
        cout << "用户" << username << "不存在" << oldname << "文件" << endl;
        return false;
    }
}

void FileSystem::printAllFiles() {
    for (const auto& user : mfd) {
        cout << "用户" << user.first << "拥有如下文件：" << endl;
        for (const auto& file : user.second.files) {
            cout << "  " << file.second.name  << " 文件处于 " << (file.second.is_open ? "打开" : "关闭") << " 状态" << endl;
        }
    }
}  

bool FileSystem::isValidFilename(const string& filename) {
    for (const auto& fn : mfd) {
        if (fn.first == filename) {
            cout << "该文件名存在重名情况" << endl;
            return false;
        }
    }
    return true;
}

bool FileSystem::isValidUsername(const string& username) {
    for (const auto& un : mfd) {
        if (un.second.name == username) {
            cout << "该用户名存在重名情况" << endl;
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
