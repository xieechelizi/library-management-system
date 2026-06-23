CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
TARGET = library_system
SRCS = src/main.c src/user.c src/book.c src/borrow.c src/reserve.c src/utils.c src/file.c
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "✓ 编译完成: $(TARGET)"

# 编译源文件生成目标文件
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 运行（Windows）
run-win: $(TARGET)
	./$(TARGET).exe

# 清理编译文件
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
	@echo "✓ 清理完成"

# 清理所有（包括生成的数据）
clean-all: clean
	rm -rf data/
	@echo "✓ 完全清理完成"

# 帮助信息
help:
	@echo "可用命令:"
	@echo "  make          - 编译程序"
	@echo "  make run      - 编译并运行（Linux/macOS）"
	@echo "  make run-win  - 编译并运行（Windows）"
	@echo "  make clean    - 清理编译文件"
	@echo "  make clean-all- 清理所有文件和数据"
	@echo "  make help     - 显示此帮助信息"

.PHONY: all run run-win clean clean-all help
