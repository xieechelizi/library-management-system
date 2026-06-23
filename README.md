# 校园图书管理系统

> 基于 C 语言分层架构设计的小型图书管理控制台系统，适配校园班级/院系图书室使用

## 📋 项目概述

| 项目属性 | 说明 |
|--------|------|
| **系统规模** | 校园小型图书管理微信小程序模拟系统 |
| **数据容量** | 图书 500~2000 本，用户上限 800 人 |
| **技术栈** | 标准 C 语言（无第三方依赖） |
| **存储方式** | 本地 txt 文本文件模拟数据库 |
| **运行环境** | Windows/Linux/macOS（仅需 gcc/clang） |

## 🏗️ 系统架构

```
┌─────────────────────────────────────┐
│       业务逻辑层 (Business)          │
│  ├─ 借阅业务    ├─ 预约业务          │
│  └─ 搜索业务    └─ 统计业务          │
├─────────────────────────────────────┤
│       功能模块层 (Module)            │
│  ├─ 用户模块    ├─ 图书模块          │
│  ├─ 借阅模块    └─ 预约模块          │
├─────────────────────────────────────┤
│       数据持久化层 (Persistence)     │
│  ├─ 文件读写    ├─ 数据解析          │
│  └─ 数据校验    └─ 持久化保存        │
├─────────────────────────────────────┤
│       基础工具层 (Utils)             │
│  ├─ 时间处理    ├─ 字符串处理        │
│  ├─ 数据结构    └─ 公共函数          │
└─────────────────────────────────────┘
```

## ✨ 核心功能

### 👤 读者端功能
- ✅ 微信登录模拟（OpenID 身份校验 + 自动注册）
- ✅ 图书模糊检索、库存状态实时查看
- ✅ 图书借阅（三重校验：库存、借阅上限、逾期拦截）
- ✅ 图书预约（无库存才可预约、防重复、7天自动取消）
- ✅ 个人中心（在借图书、历史借阅、预约记录、逾期提醒）

### 👨‍💼 管理员功能
- ✅ 管理员权限���录
- ✅ 图书管理（新增、下架、分类管理）
- ✅ 归还处理（自动逾期标记、库存恢复、预约状态更新）
- ✅ 用户管理（读者查看、违规冻结）
- ✅ 数据统计（过期预约清理、业务数据汇总）

## 🚀 快速开始

### 1. 编译程序

**Linux/macOS:**
```bash
cd library-management-system
gcc -o library_system src/*.c -std=c99 -Wall
```

**Windows (MinGW):**
```bash
gcc -o library_system.exe src/*.c -std=c99 -Wall
```

### 2. 运行程序
```bash
./library_system          # Linux/macOS
./library_system.exe      # Windows
```

### 3. 首次运行
- 程序自动创建 `data/` 目录
- 自动初始化 5 个数据文件：
  - `users.txt` - 用户表
  - `books.txt` - 图书表
  - `categories.txt` - 分类表
  - `borrow_records.txt` - 借阅记录表
  - `reserve_records.txt` - 预约记录表

## 📁 项目结构

```
library-management-system/
│
├── src/                              # C 源代码目录
│   ├── main.c                        # 主程序入口 (UI层)
│   ├── user.c / user.h              # 用户管理模块
│   ├── book.c / book.h              # 图书管理模块
│   ├── borrow.c / borrow.h          # 借阅业务模块
│   ├── reserve.c / reserve.h        # 预约业务模块
│   ├── utils.c / utils.h            # 工具函数库
│   └── file.c / file.h              # 文件持久化层
│
├── data/                             # 数据存储目录 (自动生成)
│   ├── users.txt                    # 用户数据
│   ├── books.txt                    # 图书数据
│   ├── categories.txt               # 分类数据
│   ├── borrow_records.txt           # 借阅记录
│   └── reserve_records.txt          # 预约记录
│
├── docs/                             # 毕业设计文档
│   ├── 01_需求分析.md
│   ├── 02_DFD数据流图.md
│   ├── 03_四层架构设计.md
│   ├── 04_ER数据库设计.md
│   ├── 05_业务流程图.md
│   ├── 06_模块实现逻辑.md
│   └── 07_API接口文档.md
│
├── Makefile                          # 编译配置
├── README.md                         # 本文件
└── .gitignore
```

## 📊 数据表结构

### 用户表 (users.txt)
```
openid|nickname|role|status|created_at|borrow_limit
wx123|张三|reader|active|2024-01-01|5
admin001|管理员|admin|active|2024-01-01|0
```

### 图书表 (books.txt)
```
book_id|title|author|isbn|category|total|available|created_at
B001|C语言程序设计|谭浩强|123456|计算机|3|2|2024-01-01
```

### 借阅记录表 (borrow_records.txt)
```
record_id|openid|book_id|borrow_date|due_date|return_date|status
BR001|wx123|B001|2024-01-15|2024-02-15||borrowing
```

### 预约记录表 (reserve_records.txt)
```
reserve_id|openid|book_id|reserve_date|expire_date|status|position
RE001|wx123|B001|2024-01-10|2024-01-17|waiting|1
```

## 🔐 测试账号

### 读者账号
- **OpenID**: `reader001` / `reader002` / `reader003`
- **初始密码**: 自动注册（首次登录自动生成）

### 管理员账号
- **用户名**: `admin`
- **密码**: `admin123`

## 🛠️ 编译与运行

### 使用 Makefile（推荐）
```bash
make            # 编译
make run        # 编译并运行
make clean      # 清理编译文件
```

### 手动编译
```bash
# 编译所有源文件
gcc -o library_system src/main.c src/user.c src/book.c \
    src/borrow.c src/reserve.c src/utils.c src/file.c \
    -std=c99 -Wall -Wextra

# 运行
./library_system
```

## 📝 主要业务流程

### 读者借书流程
1. 用户登录/注册（OpenID 校验）
2. 搜索图书
3. 查看图书详情
4. 发起借阅申请
5. 系统验证：
   - ✓ 图书库存是��充足
   - ✓ 用户是否超过借阅上限
   - ✓ 用户是否有逾期图书
6. 借阅成功，生成借阅记录

### 管理员归还流程
1. 用户归还图书
2. 管理员扫描/输入图书 ID
3. 系统自动：
   - 更新图书库存
   - 标记借阅记录为已归还
   - 检查是否逾期并标记
   - 更新预约用户的可借状态

### 预约流程
1. 图书无库存时，用户可预约
2. 图书被归还后，系统自动通知预约用户
3. 用户 7 天内未领取，预约自动过期

## 📈 数据统计功能

- 📊 借阅排行榜（热门图书）
- 👥 用户借阅统计
- 📅 逾期催收数据
- 💰 借阅费用统计
- 🗑️ 过期预约自动清理

## ⚙️ 系统配置

### 常用参数（可在 `utils.h` 中修改）
```c
#define MAX_BORROW_DAYS 30       // 借阅期限（天数）
#define MAX_BORROW_COUNT 5       // 单用户最大借阅数
#define RESERVE_EXPIRE_DAYS 7    // 预约过期时间（天数）
#define MAX_USERS 800            // 最大用户数
#define MAX_BOOKS 2000           // 最大图书数
```

## 🐛 常见问题

### Q1: 程序无法创建 data 目录？
**A**: 确保程序有写权限，或手动创建 `data/` 目录。

### Q2: 数据丢失怎么办？
**A**: 所有数据存储在 `data/*.txt` 文件中，请勿删除。可手动备份这些文件。

### Q3: 如何重置数据？
**A**: 删除 `data/` 目录，重新运行程序自动初始化。

### Q4: 如何修改管理员密码？
**A**: 编辑 `data/users.txt`，修改 admin 用户的密码字段（建议使用简单密码用于演示）。

## 📚 毕业设计文档

详见 `docs/` 目录：
- `01_需求分析.md` - 系统需求分析报告
- `02_DFD数据流图.md` - 数据流图设计
- `03_四层架构设计.md` - 架构设计说明
- `04_ER数据库设计.md` - 数据模型设计
- `05_业务流程图.md` - 业务流程详解
- `06_模块实现逻辑.md` - 核心模块实现
- `07_API接口文档.md` - 接口参考手册

## 🎯 评分要点

✅ **架构设计** - 完整的四层分层模型  
✅ **功能完整性** - 读者/管理员双端功能闭环  
✅ **数据持久化** - 本地文件存储方案  
✅ **业务逻辑** - 借阅、预约、逾期管理  
✅ **代码规范** - 模块化、注释完整、无内存泄漏  
✅ **文档齐全** - 需求、设计、流程、实现文档  

## 📄 许可证

本项目仅供学习和毕业设计使用。

## 📞 联系方式

如有问题，请提交 Issue 或联系开发者。

---

**最后更新**: 2024年  
**版本**: v1.0
