#include "fs.h"

FileSystem::FileSystem()
    : root("/", nullptr)
    , bitmap(FS_SZ, false)
    , users()
    , cur_user()
    , is_login(false) {
    cout << "��ʼ���ļ�ϵͳ" << endl;
    cur_dir = &root;
}

FileSystem::~FileSystem() = default;

bool FileSystem::sign_up(const string& username, const string& password) {
    if (auto is_valid = is_valid_username(username); is_valid) {
        users[username] = password;
        cout << "ע��ɹ�" << endl;
        return true;
    } else {
        cout << "���û����Ѵ���" << endl;
        return false;
    }
}

bool FileSystem::login(const string& username, const string& password) {
    if (users.find(username) == users.end()) {
        cout << "���û�������" << endl;
        return false;
    } else if (users[username] != password) {
        cout << "�������" << endl;
        return false;
    } else {
        cur_user = username;
        is_login = true;
        cout << "�û�" << cur_user << "��¼�ɹ�" << endl;
        return true;
    }
}

bool FileSystem::create_file(const string& filename, const string& content) {
    if (!is_login) {
        cout << "δ��֤���û������ȵ�¼" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) != cur_dir->files.end()) {
        cout << "�ļ��Ѵ���" << endl;
        return false;
    }

    // �ҵ����еĴ��̿飬��Ҫ��֤�����Ҵ�С�㹻
    int size = content.length();
    auto free_space = find_free_space(size);
    if (free_space.empty()) {
        cout << "�����������޷��������ļ�" << endl;
        return false;
    } else {
        // ��Ǵ��̿�Ϊ��ʹ��
        for (auto block : free_space) {
            bitmap[block] = true;
        }
        // �����ļ�
        int start_addr = free_space.front();
        cur_dir->files[filename] = std::make_unique<File>(File{ filename, start_addr, size, content, false });
        cout << "����" << filename << "�ļ��ɹ�" << endl;
        return true;
    }
}

bool FileSystem::open_file(const string& filename) {
    if (!is_login) {
        cout << "δ��֤���û������ȵ�¼" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) == cur_dir->files.end()) {
        cout << "�ļ�" << filename << "����" << cur_dir->name << "Ŀ¼��" << endl;
        return false;
    }

    cur_dir->files[filename]->is_open = true;
    cout << "��" << filename << "�ļ��ɹ�" << endl;
    cout << "�ļ����ݣ�" << cur_dir->files[filename]->content << endl;
    return true;
}

bool FileSystem::close_file(const string& filename) {
    if (!is_login) {
        cout << "δ��֤���û������ȵ�¼" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) == cur_dir->files.end()) {
        cout << "�ļ�" << filename << "����" << cur_dir->name << "Ŀ¼��" << endl;
        return false;
    }

    cur_dir->files[filename]->is_open = false;
    cout << "�ر�" << filename << "�ļ��ɹ�" << endl;
    return true;
}

bool FileSystem::read_file(const string& filename) {
    if (!is_login) {
        cout << "δ��֤���û������ȵ�¼" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) == cur_dir->files.end()) {
        cout << "�ļ�" << filename << "����" << cur_dir->name << "Ŀ¼��" << endl;
        return false;
    }

    cout << "�ļ�" << filename << "�����ݣ�" << cur_dir->files[filename]->content << endl;
    return true;
}

bool FileSystem::write_file(const string& filename, const string& content) {
    if (!is_login) {
        cout << "δ��֤���û������ȵ�¼" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) == cur_dir->files.end()) {
        cout << "�ļ�" << filename << "����" << cur_dir->name << "Ŀ¼��" << endl;
        return false;
    }

    cur_dir->files[filename]->content = content;
    cout << "д��ɹ�" << endl;
    return true;
}

bool FileSystem::delete_file(const string& filename) {
    if (!is_login) {
        cout << "δ��֤���û������ȵ�¼" << endl;
        return false;
    }
    if (cur_dir->files.find(filename) == cur_dir->files.end()) {
        cout << "�ļ�" << filename << "����" << cur_dir->name << "Ŀ¼��" << endl;
        return false;
    }

    // �ͷŴ��̿ռ�
    auto file = cur_dir->files[filename].get();
    for (int i = file->start_addr; i < file->start_addr + file->size; i ++) {
        bitmap[i] = false;
    }
    // ɾ����ǰĿ¼���ļ�
    cur_dir->files.erase(filename);
    cout << "ɾ��" << filename << "�ļ��ɹ�" << endl;
    return true;
}

bool FileSystem::make_dir(const string& dirname) {
    if (!is_login) {
        cout << "δ��֤���û������ȵ�¼" << endl;
        return false;
    }
    if (cur_dir->dirs.find(dirname) != cur_dir->dirs.end()) {
        cout << "Ŀ¼�Ѵ���" << endl;
        return false;
    }

    cur_dir->dirs[dirname] = std::make_unique<Directory>(Directory{ dirname, cur_dir });
    cout << "����" << dirname << "Ŀ¼�ɹ�" << endl;
    return true;
}

bool FileSystem::change_dir(const string& dirname) {
    if (!is_login) {
        cout << "δ��֤���û������ȵ�¼" << endl;
        return false;
    }
    if (cur_dir->dirs.find(dirname) == cur_dir->dirs.end()) {
        cout << "��ǰĿ¼" << cur_dir->name << "�²�����" << dirname << "Ŀ¼" << endl;
        return false;
    }

    cur_dir = cur_dir->dirs[dirname].get();
    cout << "�л���" << dirname << "Ŀ¼�ɹ�" << endl;
    return true;
}

bool FileSystem::delete_dir(const string& dirname) {
    if (!is_login) {
        cout << "δ��֤���û������ȵ�¼" << endl;
        return false;
    }
    if (cur_dir->dirs.find(dirname) == cur_dir->dirs.end()) {
        cout << "��ǰĿ¼" << cur_dir->name << "�²�����" << dirname << "Ŀ¼" << endl;
        return false;
    }

    cur_dir->dirs.erase(dirname);
    cout << "ɾ��" << dirname << "Ŀ¼�ɹ�" << endl;
    return true;
}

bool FileSystem::list_dir() {
    if (!is_login) {
        cout << "δ��֤���û������ȵ�¼" << endl;
        return false;
    }
    
    cout << "��ǰĿ¼ \"" << cur_dir->name << "\" ������Ŀ¼: " << endl;
    for (const auto& [name, dir] : cur_dir->dirs) {
        cout << "  " << name << "/" << endl;
    }

    cout << "��ǰĿ¼ \"" << cur_dir->name << "\" �����ļ�: " << endl;
    for (const auto& [name, file] : cur_dir->files) {
        cout << "  " << name << endl;
    }
    return true;
}

bool FileSystem::logout() {
    if (!is_login) {
        cout << "δ��֤���û������ȵ�¼" << endl;
        return false;
    }

    cur_user.clear();
    is_login = false;
    cout << "�û�" << cur_user << "���˳�" << endl;
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
                // ����ҵ����㹻�Ŀ��п飬�ͷ���
                return res;
            }
        } else {
            // �����������
            res.clear();
        }
    }
    return res;
}
