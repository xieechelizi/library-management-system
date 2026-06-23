#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* ==================== 时间工具函数实现 ==================== */

void get_current_date(char *date_str) {
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    strftime(date_str, 11, "%Y-%m-%d", timeinfo);
}

void get_current_datetime(char *datetime_str) {
    time_t now = time(NULL);
    struct tm *timeinfo = localtime(&now);
    strftime(datetime_str, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
}

int calculate_days_difference(const char *date1, const char *date2) {
    struct tm tm1 = {0}, tm2 = {0};
    
    sscanf(date1, "%d-%d-%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    sscanf(date2, "%d-%d-%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday);
    
    tm1.tm_year -= 1900;
    tm1.tm_mon -= 1;
    tm2.tm_year -= 1900;
    tm2.tm_mon -= 1;
    
    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);
    
    return (int)((t2 - t1) / (24 * 3600));
}

void add_days_to_date(const char *base_date, int days, char *result_date) {
    struct tm tm_result = {0};
    
    sscanf(base_date, "%d-%d-%d", 
           &tm_result.tm_year, &tm_result.tm_mon, &tm_result.tm_mday);
    
    tm_result.tm_year -= 1900;
    tm_result.tm_mon -= 1;
    
    time_t t = mktime(&tm_result);
    t += days * 24 * 3600;
    
    struct tm *new_tm = localtime(&t);
    strftime(result_date, 11, "%Y-%m-%d", new_tm);
}

int is_overdue(const char *due_date) {
    char current_date[11];
    get_current_date(current_date);
    return calculate_days_difference(due_date, current_date) < 0 ? 1 : 0;
}

/* ==================== 字符串工具函数实现 ==================== */

void trim_string(char *str) {
    if (!str) return;
    
    int len = strlen(str);
    int start = 0, end = len - 1;
    
    // 找到第一个非空白字符
    while (start < len && isspace(str[start])) {
        start++;
    }
    
    // 找到最后一个非空白字符
    while (end >= start && isspace(str[end])) {
        end--;
    }
    
    // 移动字符串
    if (start > 0) {
        memmove(str, str + start, end - start + 2);
    }
    
    str[end - start + 1] = '\0';
}

int fuzzy_match(const char *str, const char *pattern) {
    if (!str || !pattern) return 0;
    
    char str_lower[MAX_LINE_LEN];
    char pattern_lower[MAX_LINE_LEN];
    
    strcpy(str_lower, str);
    strcpy(pattern_lower, pattern);
    
    to_lowercase(str_lower);
    to_lowercase(pattern_lower);
    
    return strstr(str_lower, pattern_lower) != NULL ? 1 : 0;
}

void to_lowercase(char *str) {
    if (!str) return;
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

void to_uppercase(char *str) {
    if (!str) return;
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int split_string(const char *str, const char *delimiter, 
                 char parts[][MAX_LINE_LEN], int max_parts) {
    if (!str || !delimiter || max_parts <= 0) return 0;
    
    char temp[MAX_LINE_LEN];
    strcpy(temp, str);
    
    int count = 0;
    char *token = strtok(temp, delimiter);
    
    while (token && count < max_parts) {
        strcpy(parts[count], token);
        trim_string(parts[count]);
        token = strtok(NULL, delimiter);
        count++;
    }
    
    return count;
}

void generate_unique_id(const char *prefix, char *id) {
    time_t now = time(NULL);
    int random_num = rand() % 10000;
    sprintf(id, "%s%ld_%d", prefix, now, random_num);
}

/* ==================== 数据校验函数实现 ==================== */

int validate_openid(const char *openid) {
    if (!openid || strlen(openid) == 0 || strlen(openid) > MAX_OPENID_LEN) {
        return 0;
    }
    
    for (int i = 0; openid[i]; i++) {
        if (!isalnum(openid[i]) && openid[i] != '_') {
            return 0;
        }
    }
    
    return 1;
}

int validate_username(const char *username) {
    if (!username || strlen(username) < 3 || strlen(username) > MAX_USERNAME_LEN) {
        return 0;
    }
    
    if (!isalpha(username[0])) {
        return 0;
    }
    
    for (int i = 0; username[i]; i++) {
        if (!isalnum(username[i]) && username[i] != '_') {
            return 0;
        }
    }
    
    return 1;
}

int validate_password(const char *password) {
    if (!password || strlen(password) < 6 || strlen(password) > MAX_PASSWORD_LEN) {
        return 0;
    }
    return 1;
}

int validate_isbn(const char *isbn) {
    if (!isbn || strlen(isbn) == 0 || strlen(isbn) > MAX_ISBN_LEN) {
        return 0;
    }
    
    for (int i = 0; isbn[i]; i++) {
        if (!isdigit(isbn[i]) && isbn[i] != '-') {
            return 0;
        }
    }
    
    return 1;
}

/* ==================== UI 辅助函数实现 ==================== */

void clear_screen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_separator(void) {
    printf("═══════════════════════════════════════════════════════════════\n");
}

void print_table_header(const char *header) {
    printf("\n");
    print_separator();
    printf("  %s\n", header);
    print_separator();
}

void print_success(const char *message) {
    printf("\n✓ 成功: %s\n", message);
}

void print_error(const char *message) {
    printf("\n✗ 错误: %s\n", message);
}

void print_warning(const char *message) {
    printf("\n⚠ 警告: %s\n", message);
}

void print_info(const char *message) {
    printf("\nℹ 信息: %s\n", message);
}

void pause_screen(void) {
    printf("\n按 Enter 键继续...");
    getchar();
}
