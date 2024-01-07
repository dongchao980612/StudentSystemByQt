# QT实现学生管理系统

使用Qt+SQLite搭建学生管理系统，功能包括学生信息的增删改查。

## 主界面

- **QTableView**：显示学生信息，包括ID、姓名、性别、手机号、CET4、GPA、综合成绩
- **QPushButton**：添加和删除信息
- **QCheckBox**：全选学生信息

## 创建数据库

```sql
create table if not exist tb_student(
    id int primary key not null,
    name varchar(50),
    sex varchar(2),
    phone varchar(11),
    cet4 int,gpa real,
    overallScore real
);
```

