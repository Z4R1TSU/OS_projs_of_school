#include "fs.h"

FileSystem::FileSystem()
    : root("/", nullptr)
    , bitmap(FS_SZ, false)
    , users()
    , cur_user()
    , is_login(false) {
    cout << "初始化文件系统" << endl;
    cur_dir = &root;
}

FileSystem::~FileSystem() = default;

bool FileSystem::sign_up(const string& username, const string& password) {
    if (auto is_valid = is_valid_username(username); is_valid) {
        users[username] = password;
        cout << "注册成功" << endl;
        return true;
    } else {
        cout << "该用户名已存在" << endl;
        return false;
    }
}

bool FileSystem::login(const string& username, const string& password) {
    if (users.find(username) == users.end()) {
        cout << "该用户不存在" << endl;
        return false;
    } else if (users[username] != password) {
        cout << "密码错误" << endl;
        return false;
    } else {
        cur_user = username;
        is_login = true;
        cout << "用户" << cur_user << "登录成功" << endl;
        return true;
    }
}

bool FileSystem::create_file(const string& filename, const string& content) {
    if (!is_login) {
        cout << "未认证的用户，请先登录" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) != cur_dir->files.end()) {
        cout << "文件已存在" << endl;
        return false;
    }

    // 找到空闲的磁盘块，需要保证连续且大小足够
    int size = content.length();
    auto free_space = find_free_space(size);
    if (free_space.empty()) {
        cout << "磁盘已满，无法创建该文件" << endl;
        return false;
    } else {
        // 标记磁盘块为已使用
        for (auto block : free_space) {
            bitmap[block] = true;
        }
        // 创建文件
        int start_addr = free_space.front();
        cur_dir->files[filename] = std::make_unique<File>(File{ filename, start_addr, size, content, false });
        cout << "创建" << filename << "文件成功" << endl;
        return true;
    }
}

bool FileSystem::open_file(const string& filename) {
    if (!is_login) {
        cout << "未认证的用户，请先登录" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) == cur_dir->files.end()) {
        cout << "文件" << filename << "不在" << cur_dir->name << "目录下" << endl;
        return false;
    }

    cur_dir->files[filename]->is_open = true;
    cout << "打开" << filename << "文件成功" << endl;
    cout << "文件内容：" << cur_dir->files[filename]->content << endl;
    return true;
}

bool FileSystem::close_file(const string& filename) {
    if (!is_login) {
        cout << "未认证的用户，请先登录" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) == cur_dir->files.end()) {
        cout << "文件" << filename << "不在" << cur_dir->name << "目录下" << endl;
        return false;
    }

    cur_dir->files[filename]->is_open = false;
    cout << "关闭" << filename << "文件成功" << endl;
    return true;
}

bool FileSystem::read_file(const string& filename) {
    if (!is_login) {
        cout << "未认证的用户，请先登录" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) == cur_dir->files.end()) {
        cout << "文件" << filename << "不在" << cur_dir->name << "目录下" << endl;
        return false;
    }

    cout << "文件" << filename << "的内容：" << cur_dir->files[filename]->content << endl;
    return true;
}

bool FileSystem::write_file(const string& filename, const string& content) {
    if (!is_login) {
        cout << "未认证的用户，请先登录" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) == cur_dir->files.end()) {
        cout << "文件" << filename << "不在" << cur_dir->name << "目录下" << endl;
        return false;
    }

    cur_dir->files[filename]->content = content;
    cout << "写入成功" << endl;
    return true;
}

bool FileSystem::delete_file(const string& filename) {
    if (!is_login) {
        cout << "未认证的用户，请先登录" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) == cur_dir->files.end()) {
        cout << "文件" << filename << "不在" << cur_dir->name << "目录下" << endl;
        return false;
    }

    // 释放磁盘空间
    auto file = cur_dir->files[filename].get();
    for (int i = file->start_addr; i < file->start_addr + file->size; i ++) {
        bitmap[i] = false;
    }
    // 删除当前目录下文件
    cur_dir->files.erase(filename);
    cout << "删除" << filename << "文件成功" << endl;
    return true;
}

bool FileSystem::make_dir(const string& dirname) {
    if (!is_login) {
        cout << "未认证的用户，请先登录" << endl;
        return false;
    }
    if (cur_dir->dirs.find(dirname) != cur_dir->dirs.end()) {
        cout << "目录已存在" << endl;
        return false;
    }

    cur_dir->dirs[dirname] = std::make_unique<Directory>(Directory{ dirname, cur_dir });
    cout << "创建" << dirname << "目录成功" << endl;
    return true;
}

bool FileSystem::change_dir(const string& dirname) {
    if (!is_login) {
        cout << "未认证的用户，请先登录" << endl;
        return false;
    }
    if (cur_dir->dirs.find(dirname) == cur_dir->dirs.end()) {
        cout << "当前目录" << cur_dir->name << "下不存在" << dirname << "目录" << endl;
        return false;
    }

    cur_dir = cur_dir->dirs[dirname].get();
    cout << "切换到" << dirname << "目录成功" << endl;
    return true;
}

bool FileSystem::delete_dir(const string& dirname) {
    if (!is_login) {
        cout << "未认证的用户，请先登录" << endl;
        return false;
    }
    if (cur_dir->dirs.find(dirname) == cur_dir->dirs.end()) {
        cout << "当前目录" << cur_dir->name << "下不存在" << dirname << "目录" << endl;
        return false;
    }

    cur_dir->dirs.erase(dirname);
    cout << "删除" << dirname << "目录成功" << endl;
    return true;
}

bool FileSystem::list_dir() {
    if (!is_login) {
        cout << "未认证的用户，请先登录" << endl;
        return false;
    }
    
    cout << "当前目录 \"" << cur_dir->name << "\" 存在子目录: " << endl;
    for (const auto& [name, dir] : cur_dir->dirs) {
        cout << "  " << name << "/" << endl;
    }

    cout << "当前目录 \"" << cur_dir->name << "\" 存在文件: " << endl;
    for (const auto& [name, file] : cur_dir->files) {
        cout << "  " << name << endl;
    }
    return true;
}

bool FileSystem::logout() {
    if (!is_login) {
        cout << "未认证的用户，请先登录" << endl;
        return false;
    }

    cur_user.clear();
    is_login = false;
    cout << "用户" << cur_user << "已退出" << endl;
    return true;
}


bool FileSystem::is_valid_username(const string& username) {
    if (users.find(username) == users.end()) {
        return true;
    }
    return false;
}

vector<int> FileSystem::find_free_space(int size) {
    vector<int> res;
    for (int i = 0; i < FS_SZ; i ++) {
        if (!bitmap[i]) {
            res.push_back(i);
            if (res.size() == size) {
                // 如果找到了足够的空闲块，就返回
                return res;
            }
        } else {
            // 不连续则清空
            res.clear();
        }
    }
    return res;
}
