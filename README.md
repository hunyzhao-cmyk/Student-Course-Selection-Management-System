# 学生选课信息管理系统

基于 MFC 和 OpenGauss 数据库的学生选课信息管理系统，通过 ODBC 连接实现对学生信息和选课记录的增删改查操作。

## 功能特性

### 用户认证
- **登录**：通过学号和密码登录，密码使用 OpenGauss `gs_decrypt` 函数（AES128）解密验证
- **注册**：新用户注册，密码使用 `gs_encrypt` 函数（AES128）加密存储
- 密码长度要求 8~16 位

### 学生信息管理
- **查看**：以列表形式展示所有学生信息（学号、姓名、性别、年龄、所在系）
- **添加**：录入新学生信息，包含数据校验（学号非空、性别只能为"男"或"女"）
- **修改**：选中学生后编辑其信息并更新到数据库
- **删除**：删除选中的学生记录，带二次确认提示

### 选课管理
- **选课**：为选中学生勾选课程（数学、英语、物理、化学、生物），自动检测重复选课
- **重置**：清空选中学生的所有选课记录，带二次确认提示

## 技术栈

| 组件 | 技术 |
|------|------|
| 开发框架 | MFC (Microsoft Foundation Classes) |
| IDE | Visual Studio 2022 |
| 数据库 | OpenGauss |
| 连接方式 | ODBC |
| 加密算法 | AES128（OpenGauss 内置 `gs_encrypt` / `gs_decrypt`） |

## 数据库设计

### student 表（学生信息）

| 列名 | 类型 | 说明 |
|------|------|------|
| sno | VARCHAR | 学号（主键） |
| sname | VARCHAR | 姓名 |
| ssex | VARCHAR | 性别 |
| sage | INTEGER | 年龄 |
| sdept | VARCHAR | 所在系 |

### course 表（课程信息）

| 列名 | 类型 | 说明 |
|------|------|------|
| cno | INTEGER | 课程编号（主键） |
| cname | VARCHAR | 课程名称 |

### sc 表（选课记录）

| 列名 | 类型 | 说明 |
|------|------|------|
| sno | VARCHAR | 学号（外键） |
| cno | INTEGER | 课程编号（外键，关联 course 表） |

### Userinformation 表（用户信息）

| 列名 | 类型 | 说明 |
|------|------|------|
| Uname | VARCHAR | 用户名/学号 |
| Upassword | VARCHAR | 密码（AES128 加密存储） |

## 环境配置

### 1. 数据库准备

确保 OpenGauss 数据库已启动，并创建上述三张表。

### 2. ODBC 数据源配置

在 Windows ODBC 数据源管理器中配置用户 DSN：
- 数据源名称：`my_opengauss`
- 驱动程序：OpenGauss ODBC Driver
- 按照实际数据库地址、端口、用户名和密码进行配置

### 3. 编译运行

1. 使用 Visual Studio 2022 打开 `Demo.sln`
2. 选择 `Debug | Win32` 或 `Debug | x64` 配置
3. 编译并运行

## 项目结构

```
├── Demo.sln                 # 解决方案文件
├── Demo.vcxproj             # 项目配置文件
├── Demo.cpp                 # 应用程序入口
├── Demo.h                   # 应用程序类头文件
├── DemoDlg.cpp              # 主对话框实现（学生管理 + 选课）
├── DemoDlg.h                # 主对话框头文件
├── LoginDlg.cpp             # 登录/注册对话框实现
├── LoginDlg.h               # 登录/注册对话框头文件
├── resource.h               # 资源 ID 定义
├── MyDemo.rc                # 资源脚本
├── pch.h / pch.cpp          # 预编译头文件
├── framework.h              # 框架头文件
└── res/
    ├── Demo.ico              # 应用程序图标
    └── MyDemo.rc2            # 额外资源定义
```

## 许可证

本项目仅供学习交流使用。
