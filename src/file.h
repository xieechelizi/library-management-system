#ifndef FILE_H
#define FILE_H

#include "utils.h"

/* ==================== 文件初始化 ==================== */

/**
 * 初始化数据目录和文件
 */
void init_data_directory(void);

/**
 * 检查数据文件是否存在
 * @return 1 表示存在，0 表示不存在
 */
int check_data_files_exist(void);

/* ==================== 用户数据持久化 ==================== */

/**
 * 从文件读取所有用户
 * @param users 用户数组
 * @param count 用户数量指针
 * @return 成功返回 0，失败返回 -1
 */
int load_users_from_file(User *users, int *count);

/**
 * 将用户保存到文件
 * @param users 用户数组
 * @param count 用户数量
 * @return 成功返回 0，失败返回 -1
 */
int save_users_to_file(const User *users, int count);

/**
 * 添加新用户到文件
 * @param user 用户指针
 * @return 成功返回 0，失败返回 -1
 */
int append_user_to_file(const User *user);

/* ==================== 图书数据持久化 ==================== */

/**
 * 从文件读取所有图书
 * @param books 图书数组
 * @param count 图书数量指针
 * @return 成功返回 0，失败返回 -1
 */
int load_books_from_file(Book *books, int *count);

/**
 * 将图书保存到文件
 * @param books 图书数组
 * @param count 图书数量
 * @return 成功返回 0，失败返回 -1
 */
int save_books_to_file(const Book *books, int count);

/**
 * 添加新图书到文件
 * @param book 图书指针
 * @return 成功返回 0，失败返回 -1
 */
int append_book_to_file(const Book *book);

/* ==================== 图书分类数据持久化 ==================== */

/**
 * 从文件读取所有图书分类
 * @param categories 分类数组
 * @param count 分类数量指针
 * @return 成功返回 0，失败返回 -1
 */
int load_categories_from_file(Category *categories, int *count);

/**
 * 将图书分类保存到文件
 * @param categories 分类数组
 * @param count 分类数量
 * @return 成功返回 0，失败返回 -1
 */
int save_categories_to_file(const Category *categories, int count);

/* ==================== 借阅记录数据持久化 ==================== */

/**
 * 从文件读取所有借阅记录
 * @param records 借阅记录数组
 * @param count 记录数量指针
 * @return 成功返回 0，失败返回 -1
 */
int load_borrow_records_from_file(BorrowRecord *records, int *count);

/**
 * 将借阅记录保存到文件
 * @param records 借阅记录数组
 * @param count 记录数量
 * @return 成功返回 0，失败返回 -1
 */
int save_borrow_records_to_file(const BorrowRecord *records, int count);

/**
 * 添加新借阅记录到文件
 * @param record 借阅记录指针
 * @return 成功返回 0，失败返回 -1
 */
int append_borrow_record_to_file(const BorrowRecord *record);

/* ==================== 预约记录数据持久化 ==================== */

/**
 * 从文件读取所有预约记录
 * @param records 预约记录数组
 * @param count 记录数量指针
 * @return 成功返回 0，失败返回 -1
 */
int load_reserve_records_from_file(ReserveRecord *records, int *count);

/**
 * 将预约记录保存到文件
 * @param records 预约记录数组
 * @param count 记录数量
 * @return 成功返回 0，失败返回 -1
 */
int save_reserve_records_to_file(const ReserveRecord *records, int count);

/**
 * 添加新预约记录到文件
 * @param record 预约记录指针
 * @return 成功返回 0，失败返回 -1
 */
int append_reserve_record_to_file(const ReserveRecord *record);

#endif // FILE_H
