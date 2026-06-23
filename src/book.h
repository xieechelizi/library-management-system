#ifndef BOOK_H
#define BOOK_H

#include "utils.h"

/* ==================== 图书管理功能 ==================== */

/**
 * 根据图书 ID 查找图书
 * @param books 图书数组
 * @param count 图书数量
 * @param book_id 图书 ID
 * @return 图书指针，不存在返回 NULL
 */
Book* find_book_by_id(Book *books, int count, const char *book_id);

/**
 * 根据标题模糊搜索图书
 * @param books 图书数组
 * @param count 图书数量
 * @param title 搜索关键词
 * @param results 搜索结果数组
 * @param max_results 最大结果数
 * @return 实际找到的图书数
 */
int search_books_by_title(Book *books, int count, const char *title,
                         Book *results, int max_results);

/**
 * 添加新图书
 * @param books 图书数组
 * @param count 图书数量指针
 * @param title 图书标题
 * @param author 作者
 * @param isbn ISBN
 * @param category 分类
 * @param total 总数
 * @return 成功返回 0，失败返回 -1
 */
int add_book(Book *books, int *count, const char *title, const char *author,
             const char *isbn, const char *category, int total);

/**
 * 下架图书
 * @param books 图书数组
 * @param count 图书数量指针
 * @param book_id 要下架的图书 ID
 * @return 成功返回 0，失败返回 -1
 */
int remove_book(Book *books, int *count, const char *book_id);

/**
 * 更新图书库存
 * @param book 图书指针
 * @param delta 变化数（正数表示增加，负数表示减少）
 * @return 成功返回 0，失败返回 -1（库存不足）
 */
int update_book_inventory(Book *book, int delta);

/**
 * 获取可用图书总数
 * @param books 图书数组
 * @param count 图书数量
 * @return 可用图书总数
 */
int get_available_books(Book *books, int count);

/**
 * 列出所有图书
 * @param books 图书数组
 * @param count 图书数量
 */
void list_all_books(Book *books, int count);

/**
 * 显示图书详情
 * @param book 图书指针
 */
void display_book_details(Book *book);

#endif // BOOK_H
