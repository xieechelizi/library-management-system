#include "user.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

User* find_user_by_openid(User *users, int count, const char *openid) {
    if (!users || !openid) return NULL;
    
    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].openid, openid) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

int register_reader(User *users, int *count, const char *openid, const char *nickname) {
    if (!users || !count || !openid || !nickname) return -1;
    
    // 检查用户数是否已满
    if (*count >= MAX_USERS) {
        return -1;
    }
    
    // 检查 OpenID 是否已存在
    if (find_user_by_openid(users, *count, openid)) {
        return -1;
    }
    
    // 创建新用户
    User new_user;
    strcpy(new_user.openid, openid);
    strcpy(new_user.nickname, nickname);
    strcpy(new_user.role, ROLE_READER);
    strcpy(new_user.status, STATUS_ACTIVE);
    get_current_datetime(new_user.created_at);
    new_user.borrow_limit = MAX_BORROW_COUNT;
    
    // 添加到数组
    users[*count] = new_user;
    (*count)++;
    
    // 保存到文件
    if (save_users_to_file(users, *count) == 0) {
        return 0;
    }
    
    return -1;
}

int freeze_user(User *users, int count, const char *openid) {
    if (!users || !openid) return -1;
    
    User *user = find_user_by_openid(users, count, openid);
    if (!user) return -1;
    
    strcpy(user->status, STATUS_FROZEN);
    return save_users_to_file(users, count);
}

int unfreeze_user(User *users, int count, const char *openid) {
    if (!users || !openid) return -1;
    
    User *user = find_user_by_openid(users, count, openid);
    if (!user) return -1;
    
    strcpy(user->status, STATUS_ACTIVE);
    return save_users_to_file(users, count);
}

void list_all_readers(User *users, int count) {
    print_table_header("所有读者账户");
    printf("%-15s | %-20s | %-10s | %-10s\n", "OpenID", "昵称", "状态", "借阅上限");
    print_separator();
    
    int reader_count = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].role, ROLE_READER) == 0) {
            printf("%-15s | %-20s | %-10s | %-10d\n",
                   users[i].openid,
                   users[i].nickname,
                   users[i].status,
                   users[i].borrow_limit);
            reader_count++;
        }
    }
    
    print_separator();
    printf("总计: %d 个读者\n", reader_count);
}
