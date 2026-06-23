#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/* 数据文件路径定义 */
#define DATA_DIR "data"
#define USERS_FILE "data/users.txt"
#define BOOKS_FILE "data/books.txt"
#define CATEGORIES_FILE "data/categories.txt"
#define BORROW_RECORDS_FILE "data/borrow_records.txt"
#define RESERVE_RECORDS_FILE "data/reserve_records.txt"

/* ==================== 文件初始化 ==================== */

void init_data_directory(void) {
    // 创建数据目录
#ifdef _WIN32
    _mkdir(DATA_DIR);
#else
    mkdir(DATA_DIR, 0755);
#endif
    
    // 如果数据文件不存在，创建空文件或初始化数据
    FILE *fp = NULL;
    
    // 初始化用户文件
    fp = fopen(USERS_FILE, "a");
    if (fp) fclose(fp);
    
    // 初始化图书文件
    fp = fopen(BOOKS_FILE, "a");
    if (fp) fclose(fp);
    
    // 初始化分类文件
    fp = fopen(CATEGORIES_FILE, "a");
    if (fp) {
        // 写入默认分类
        fprintf(fp, "C001|计算机\n");
        fprintf(fp, "C002|文学\n");
        fprintf(fp, "C003|历史\n");
        fprintf(fp, "C004|科学\n");
        fprintf(fp, "C005|艺术\n");
        fclose(fp);
    }
    
    // 初始化借阅记录文件
    fp = fopen(BORROW_RECORDS_FILE, "a");
    if (fp) fclose(fp);
    
    // 初始化预约记录文件
    fp = fopen(RESERVE_RECORDS_FILE, "a");
    if (fp) fclose(fp);
}

int check_data_files_exist(void) {
    FILE *fp = fopen(USERS_FILE, "r");
    if (fp) {
        fclose(fp);
        return 1;
    }
    return 0;
}

/* ==================== 用户数据持久化 ==================== */

int load_users_from_file(User *users, int *count) {
    if (!users || !count) return -1;
    
    FILE *fp = fopen(USERS_FILE, "r");
    if (!fp) {
        *count = 0;
        return 0;
    }
    
    char line[MAX_LINE_LEN];
    *count = 0;
    
    while (fgets(line, sizeof(line), fp) && *count < MAX_USERS) {
        // 去除换行符
        line[strcspn(line, "\n")] = '\0';
        
        if (strlen(line) == 0) continue;
        
        // 解析行数据: openid|nickname|role|status|created_at|borrow_limit
        char parts[6][MAX_LINE_LEN];
        int parts_count = split_string(line, "|", parts, 6);
        
        if (parts_count >= 6) {
            strcpy(users[*count].openid, parts[0]);
            strcpy(users[*count].nickname, parts[1]);
            strcpy(users[*count].role, parts[2]);
            strcpy(users[*count].status, parts[3]);
            strcpy(users[*count].created_at, parts[4]);
            users[*count].borrow_limit = atoi(parts[5]);
            (*count)++;
        }
    }
    
    fclose(fp);
    return 0;
}

int save_users_to_file(const User *users, int count) {
    if (!users) return -1;
    
    FILE *fp = fopen(USERS_FILE, "w");
    if (!fp) return -1;
    
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s|%s|%s|%s|%s|%d\n",
                users[i].openid,
                users[i].nickname,
                users[i].role,
                users[i].status,
                users[i].created_at,
                users[i].borrow_limit);
    }
    
    fclose(fp);
    return 0;
}

int append_user_to_file(const User *user) {
    if (!user) return -1;
    
    FILE *fp = fopen(USERS_FILE, "a");
    if (!fp) return -1;
    
    fprintf(fp, "%s|%s|%s|%s|%s|%d\n",
            user->openid,
            user->nickname,
            user->role,
            user->status,
            user->created_at,
            user->borrow_limit);
    
    fclose(fp);
    return 0;
}

/* ==================== 图书数据持久化 ==================== */

int load_books_from_file(Book *books, int *count) {
    if (!books || !count) return -1;
    
    FILE *fp = fopen(BOOKS_FILE, "r");
    if (!fp) {
        *count = 0;
        return 0;
    }
    
    char line[MAX_LINE_LEN];
    *count = 0;
    
    while (fgets(line, sizeof(line), fp) && *count < MAX_BOOKS) {
        line[strcspn(line, "\n")] = '\0';
        
        if (strlen(line) == 0) continue;
        
        // 解析: book_id|title|author|isbn|category|total|available|created_at
        char parts[8][MAX_LINE_LEN];
        int parts_count = split_string(line, "|", parts, 8);
        
        if (parts_count >= 8) {
            strcpy(books[*count].book_id, parts[0]);
            strcpy(books[*count].title, parts[1]);
            strcpy(books[*count].author, parts[2]);
            strcpy(books[*count].isbn, parts[3]);
            strcpy(books[*count].category, parts[4]);
            books[*count].total = atoi(parts[5]);
            books[*count].available = atoi(parts[6]);
            strcpy(books[*count].created_at, parts[7]);
            (*count)++;
        }
    }
    
    fclose(fp);
    return 0;
}

int save_books_to_file(const Book *books, int count) {
    if (!books) return -1;
    
    FILE *fp = fopen(BOOKS_FILE, "w");
    if (!fp) return -1;
    
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s|%s|%s|%s|%s|%d|%d|%s\n",
                books[i].book_id,
                books[i].title,
                books[i].author,
                books[i].isbn,
                books[i].category,
                books[i].total,
                books[i].available,
                books[i].created_at);
    }
    
    fclose(fp);
    return 0;
}

int append_book_to_file(const Book *book) {
    if (!book) return -1;
    
    FILE *fp = fopen(BOOKS_FILE, "a");
    if (!fp) return -1;
    
    fprintf(fp, "%s|%s|%s|%s|%s|%d|%d|%s\n",
            book->book_id,
            book->title,
            book->author,
            book->isbn,
            book->category,
            book->total,
            book->available,
            book->created_at);
    
    fclose(fp);
    return 0;
}

/* ==================== 图书分类数据持久化 ==================== */

int load_categories_from_file(Category *categories, int *count) {
    if (!categories || !count) return -1;
    
    FILE *fp = fopen(CATEGORIES_FILE, "r");
    if (!fp) {
        *count = 0;
        return 0;
    }
    
    char line[MAX_LINE_LEN];
    *count = 0;
    
    while (fgets(line, sizeof(line), fp) && *count < 100) {
        line[strcspn(line, "\n")] = '\0';
        
        if (strlen(line) == 0) continue;
        
        char parts[2][MAX_LINE_LEN];
        int parts_count = split_string(line, "|", parts, 2);
        
        if (parts_count >= 2) {
            strcpy(categories[*count].category_id, parts[0]);
            strcpy(categories[*count].category_name, parts[1]);
            (*count)++;
        }
    }
    
    fclose(fp);
    return 0;
}

int save_categories_to_file(const Category *categories, int count) {
    if (!categories) return -1;
    
    FILE *fp = fopen(CATEGORIES_FILE, "w");
    if (!fp) return -1;
    
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s|%s\n",
                categories[i].category_id,
                categories[i].category_name);
    }
    
    fclose(fp);
    return 0;
}

/* ==================== 借阅记录数据持久化 ==================== */

int load_borrow_records_from_file(BorrowRecord *records, int *count) {
    if (!records || !count) return -1;
    
    FILE *fp = fopen(BORROW_RECORDS_FILE, "r");
    if (!fp) {
        *count = 0;
        return 0;
    }
    
    char line[MAX_LINE_LEN];
    *count = 0;
    
    while (fgets(line, sizeof(line), fp) && *count < MAX_BORROW_RECORDS) {
        line[strcspn(line, "\n")] = '\0';
        
        if (strlen(line) == 0) continue;
        
        char parts[8][MAX_LINE_LEN];
        int parts_count = split_string(line, "|", parts, 8);
        
        if (parts_count >= 8) {
            strcpy(records[*count].record_id, parts[0]);
            strcpy(records[*count].openid, parts[1]);
            strcpy(records[*count].book_id, parts[2]);
            strcpy(records[*count].borrow_date, parts[3]);
            strcpy(records[*count].due_date, parts[4]);
            strcpy(records[*count].return_date, parts[5]);
            strcpy(records[*count].status, parts[6]);
            (*count)++;
        }
    }
    
    fclose(fp);
    return 0;
}

int save_borrow_records_to_file(const BorrowRecord *records, int count) {
    if (!records) return -1;
    
    FILE *fp = fopen(BORROW_RECORDS_FILE, "w");
    if (!fp) return -1;
    
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s|%s|%s|%s|%s|%s|%s\n",
                records[i].record_id,
                records[i].openid,
                records[i].book_id,
                records[i].borrow_date,
                records[i].due_date,
                records[i].return_date,
                records[i].status);
    }
    
    fclose(fp);
    return 0;
}

int append_borrow_record_to_file(const BorrowRecord *record) {
    if (!record) return -1;
    
    FILE *fp = fopen(BORROW_RECORDS_FILE, "a");
    if (!fp) return -1;
    
    fprintf(fp, "%s|%s|%s|%s|%s|%s|%s\n",
            record->record_id,
            record->openid,
            record->book_id,
            record->borrow_date,
            record->due_date,
            record->return_date,
            record->status);
    
    fclose(fp);
    return 0;
}

/* ==================== 预约记录数据持久化 ==================== */

int load_reserve_records_from_file(ReserveRecord *records, int *count) {
    if (!records || !count) return -1;
    
    FILE *fp = fopen(RESERVE_RECORDS_FILE, "r");
    if (!fp) {
        *count = 0;
        return 0;
    }
    
    char line[MAX_LINE_LEN];
    *count = 0;
    
    while (fgets(line, sizeof(line), fp) && *count < MAX_RESERVE_RECORDS) {
        line[strcspn(line, "\n")] = '\0';
        
        if (strlen(line) == 0) continue;
        
        char parts[7][MAX_LINE_LEN];
        int parts_count = split_string(line, "|", parts, 7);
        
        if (parts_count >= 7) {
            strcpy(records[*count].reserve_id, parts[0]);
            strcpy(records[*count].openid, parts[1]);
            strcpy(records[*count].book_id, parts[2]);
            strcpy(records[*count].reserve_date, parts[3]);
            strcpy(records[*count].expire_date, parts[4]);
            strcpy(records[*count].status, parts[5]);
            records[*count].position = atoi(parts[6]);
            (*count)++;
        }
    }
    
    fclose(fp);
    return 0;
}

int save_reserve_records_to_file(const ReserveRecord *records, int count) {
    if (!records) return -1;
    
    FILE *fp = fopen(RESERVE_RECORDS_FILE, "w");
    if (!fp) return -1;
    
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s|%s|%s|%s|%s|%s|%d\n",
                records[i].reserve_id,
                records[i].openid,
                records[i].book_id,
                records[i].reserve_date,
                records[i].expire_date,
                records[i].status,
                records[i].position);
    }
    
    fclose(fp);
    return 0;
}

int append_reserve_record_to_file(const ReserveRecord *record) {
    if (!record) return -1;
    
    FILE *fp = fopen(RESERVE_RECORDS_FILE, "a");
    if (!fp) return -1;
    
    fprintf(fp, "%s|%s|%s|%s|%s|%s|%d\n",
            record->reserve_id,
            record->openid,
            record->book_id,
            record->reserve_date,
            record->expire_date,
            record->status,
            record->position);
    
    fclose(fp);
    return 0;
}
