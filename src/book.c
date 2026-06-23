#include "book.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Book* find_book_by_id(Book *books, int count, const char *book_id) {
    if (!books || !book_id) return NULL;
    
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].book_id, book_id) == 0) {
            return &books[i];
        }
    }
    return NULL;
}

int search_books_by_title(Book *books, int count, const char *title,
                         Book *results, int max_results) {
    if (!books || !title || !results) return 0;
    
    int found = 0;
    for (int i = 0; i < count && found < max_results; i++) {
        if (fuzzy_match(books[i].title, title)) {
            results[found] = books[i];
            found++;
        }
    }
    
    return found;
}

int add_book(Book *books, int *count, const char *title, const char *author,
             const char *isbn, const char *category, int total) {
    if (!books || !count || !title || !author || !isbn || !category) return -1;
    
    if (*count >= MAX_BOOKS) return -1;
    
    Book new_book;
    generate_unique_id("B", new_book.book_id);
    strcpy(new_book.title, title);
    strcpy(new_book.author, author);
    strcpy(new_book.isbn, isbn);
    strcpy(new_book.category, category);
    new_book.total = total;
    new_book.available = total;
    get_current_date(new_book.created_at);
    
    books[*count] = new_book;
    (*count)++;
    
    return save_books_to_file(books, *count);
}

int remove_book(Book *books, int *count, const char *book_id) {
    if (!books || !count || !book_id) return -1;
    
    int index = -1;
    for (int i = 0; i < *count; i++) {
        if (strcmp(books[i].book_id, book_id) == 0) {
            index = i;
            break;
        }
    }
    
    if (index == -1) return -1;
    
    for (int i = index; i < *count - 1; i++) {
        books[i] = books[i + 1];
    }
    (*count)--;
    
    return save_books_to_file(books, *count);
}

int update_book_inventory(Book *book, int delta) {
    if (!book) return -1;
    
    int new_available = book->available + delta;
    
    if (new_available < 0 || new_available > book->total) {
        return -1;
    }
    
    book->available = new_available;
    return 0;
}

int get_available_books(Book *books, int count) {
    int available = 0;
    for (int i = 0; i < count; i++) {
        available += books[i].available;
    }
    return available;
}

void list_all_books(Book *books, int count) {
    print_table_header("图书列表");
    printf("%-15s | %-30s | %-15s | %-8s | %-8s\n",
           "图书ID", "书名", "作者", "总数", "可用");
    print_separator();
    
    for (int i = 0; i < count; i++) {
        printf("%-15s | %-30s | %-15s | %-8d | %-8d\n",
               books[i].book_id,
               books[i].title,
               books[i].author,
               books[i].total,
               books[i].available);
    }
    
    print_separator();
    printf("总计: %d 本图书, 可用: %d 本\n",
           count, get_available_books(books, count));
}

void display_book_details(Book *book) {
    if (!book) return;
    
    print_separator();
    printf("图书详情\n");
    print_separator();
    printf("图书 ID: %s\n", book->book_id);
    printf("书名: %s\n", book->title);
    printf("作者: %s\n", book->author);
    printf("ISBN: %s\n", book->isbn);
    printf("分类: %s\n", book->category);
    printf("总数: %d 本\n", book->total);
    printf("可用: %d 本\n", book->available);
    printf("已借: %d 本\n", book->total - book->available);
    printf("创建时间: %s\n", book->created_at);
    print_separator();
}
