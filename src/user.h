#ifndef USER_H
#define USER_H

#include "utils.h"

/* ==================== 用户管理功能 ==================== */

/**
 * 根据 OpenID 查找用户
 * @param users 用户数组
 * @param count 用户数量
 * @param openid 要查找的 OpenID
 * @return 用户指针，不存在返回 NULL
 */
User* find_user_by_openid(User *users, int count, const char *openid);

/**
 * 注册新用户（读者自动注册）
 * @param users 用户数组
 * @param count 用户数量指针
 * @param openid OpenID
 * @param nickname 昵称
 * @return 成功返回 0，失败返回 -1
 */
int register_reader(User *users, int *count, const char *openid, const char *nickname);

/**
 * 冻结用户账号
 * @param users 用户数组
 * @param count 用户数量
 * @param openid 要冻结的用户 OpenID
 * @return 成功返回 0，失败返回 -1
 */
int freeze_user(User *users, int count, const char *openid);

/**
 * 解冻用户账号
 * @param users 用户数组
 * @param count 用户数量
 * @param openid 要解冻的用户 OpenID
 * @return 成功返回 0，失败返回 -1
 */
int unfreeze_user(User *users, int count, const char *openid);

/**
 * 列出所有读者
 * @param users 用户数组
 * @param count 用户数量
 */
void list_all_readers(User *users, int count);

#endif // USER_H
