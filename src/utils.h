#ifndef UTILS_H
#define UTILS_H

#include <time.h>

/* ==================== 常量定义 ==================== */
#define MAX_USERS 800
#define MAX_BOOKS 2000
#define MAX_BORROW_RECORDS 10000
#define MAX_RESERVE_RECORDS 5000

#define MAX_OPENID_LEN 50
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_NICKNAME_LEN 100
#define MAX_TITLE_LEN 200
#define MAX_AUTHOR_LEN 100
#define MAX_ISBN_LEN 20
#define MAX_CATEGORY_LEN 50
#define MAX_BOOK_ID_LEN 20
#define MAX_RECORD_ID_LEN 20
#define MAX_LINE_LEN 1024

/* 业务规则参数 */
#define MAX_BORROW_DAYS 30          // 借阅期限（天数）
#define MAX_BORROW_COUNT 5          // 单用户最大借阅数
#define RESERVE_EXPIRE_DAYS 7       // 预约过期时间（天数）
#define MAX_RESERVE_POS 100         // 最大排队位置

/* 用户角色 */
#define ROLE_READER "reader"
#define ROLE_ADMIN "admin"

/* 用户状态 */
#define STATUS_ACTIVE "active"
#define STATUS_FROZEN "frozen"

/* 图书状态 */
#define BOOK_STATUS_AVAILABLE "available"
#define BOOK_STATUS_UNAVAILABLE "unavailable"

/* 借阅记录状态 */
#define BORROW_STATUS_BORROWING "borrowing"
#define BORROW_STATUS_RETURNED "returned"
#define BORROW_STATUS_OVERDUE "overdue"

/* 预约记录状态 */
#define RESERVE_STATUS_WAITING "waiting"
#define RESERVE_STATUS_READY "ready"
#define RESERVE_STATUS_EXPIRED "expired"
#define RESERVE_STATUS_PICKED "picked"

/* ==================== 数据结构 ==================== */

/* 用户结构体 */
typedef struct {
    char openid[MAX_OPENID_LEN];
    char nickname[MAX_NICKNAME_LEN];
    char role[20];              // "reader" 或 "admin"
    char status[20];            // "active" 或 "frozen"
    char created_at[20];        // YYYY-MM-DD HH:MM:SS
    int borrow_limit;           // 最大借阅数限制
} User;

/* 图书分类结构体 */
typedef struct {
    char category_id[20];
    char category_name[MAX_CATEGORY_LEN];
} Category;

/* 图书结构体 */
typedef struct {
    char book_id[MAX_BOOK_ID_LEN];
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    char isbn[MAX_ISBN_LEN];
    char category[MAX_CATEGORY_LEN];
    int total;                  // 总数
    int available;              // 可用数
    char created_at[20];
} Book;

/* 借阅记录结构体 */
typedef struct {
    char record_id[MAX_RECORD_ID_LEN];
    char openid[MAX_OPENID_LEN];
    char book_id[MAX_BOOK_ID_LEN];
    char borrow_date[20];       // YYYY-MM-DD
    char due_date[20];
    char return_date[20];       // 空表示未归还
    char status[20];            // borrowing / returned / overdue
} BorrowRecord;

/* 预约记录结构体 */
typedef struct {
    char reserve_id[MAX_RECORD_ID_LEN];
    char openid[MAX_OPENID_LEN];
    char book_id[MAX_BOOK_ID_LEN];
    char reserve_date[20];
    char expire_date[20];
    char status[20];            // waiting / ready / expired / picked
    int position;               // 排队位置
} ReserveRecord;

/* ==================== 时间工具函数 ==================== */

/**
 * 获取当前日期字符串 (YYYY-MM-DD)
 * @param date_str 输出缓冲区，长度至少为 11
 */
void get_current_date(char *date_str);

/**
 * 获取当前日期时间字符串 (YYYY-MM-DD HH:MM:SS)
 * @param datetime_str 输出缓冲区，长度至少为 20
 */
void get_current_datetime(char *datetime_str);

/**
 * 计算两个日期之间的天数差
 * @param date1 日期字符串格式: YYYY-MM-DD
 * @param date2 日期字符串格式: YYYY-MM-DD
 * @return 天数差（负数表示 date1 在 date2 之前）
 */
int calculate_days_difference(const char *date1, const char *date2);

/**
 * 在给定日期上添加天数
 * @param base_date 基准日期 (YYYY-MM-DD)
 * @param days 要添加的天数
 * @param result_date 结果缓冲区
 */
void add_days_to_date(const char *base_date, int days, char *result_date);

/**
 * 检查日期是否已逾期
 * @param due_date 截止日期 (YYYY-MM-DD)
 * @return 1 表示已逾期，0 表示未逾期
 */
int is_overdue(const char *due_date);

/* ==================== 字符串工具函数 ==================== */

/**
 * 去除字符串两端空白
 * @param str 输入/输出字符串
 */
void trim_string(char *str);

/**
 * 字符串模糊匹配
 * @param str 原字符串
 * @param pattern 匹配模式
 * @return 1 表示匹配，0 表示不匹配
 */
int fuzzy_match(const char *str, const char *pattern);

/**
 * 将字符串转换为小写
 * @param str 输入/输出字符串
 */
void to_lowercase(char *str);

/**
 * 将字符串转换为大写
 * @param str 输入/输出字符串
 */
void to_uppercase(char *str);

/**
 * 分割字符串（使用指定分隔符）
 * @param str 输入字符串
 * @param delimiter 分隔符
 * @param parts 输出数组（存储分割后的部分）
 * @param max_parts 最大分割数
 * @return 实际分割后的部分数
 */
int split_string(const char *str, const char *delimiter, char parts[][MAX_LINE_LEN], int max_parts);

/**
 * 生成唯一 ID（基于时间戳和随机数）
 * @param prefix 前缀
 * @param id 输出缓冲区
 */
void generate_unique_id(const char *prefix, char *id);

/* ==================== 数据校验函数 ==================== */

/**
 * 验证 OpenID 格式
 * @param openid OpenID 字符串
 * @return 1 表示有效，0 表示无效
 */
int validate_openid(const char *openid);

/**
 * 验证用户名格式
 * @param username 用户名
 * @return 1 表示有效，0 表示无效
 */
int validate_username(const char *username);

/**
 * 验证密码强度
 * @param password 密码
 * @return 1 表示有效，0 表示无���
 */
int validate_password(const char *password);

/**
 * 验证 ISBN 格式
 * @param isbn ISBN
 * @return 1 表示有效，0 表示无效
 */
int validate_isbn(const char *isbn);

/* ==================== UI 辅助函数 ==================== */

/**
 * 清屏
 */
void clear_screen(void);

/**
 * 打印菜单分隔线
 */
void print_separator(void);

/**
 * 打印表头
 */
void print_table_header(const char *header);

/**
 * 打印成功消息
 */
void print_success(const char *message);

/**
 * 打印错误消息
 */
void print_error(const char *message);

/**
 * 打印警告消息
 */
void print_warning(const char *message);

/**
 * 打印信息消息
 */
void print_info(const char *message);

/**
 * 暂停程序（等待用户按 Enter）
 */
void pause_screen(void);

#endif // UTILS_H
