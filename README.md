# QT实现学生管理系统

使用QTableView+QStandardItemModel+SQLite搭建学生管理系统，功能包括学生信息的增删改查，以及弹出式菜单等功能。

## 主界面

- **QTableView**：显示学生信息，包括ID、姓名、性别、手机号、CET4、GPA、综合成绩
- **QPushButton**：**添加**和**删除**信息
- **QCheckBox**：全选学生信息

## 创建数据库

```sql
create table if not exist tb_student(
    id int primary key not null,
    name varchar(50),
    sex varchar(2),
    phone varchar(11),
    cet4 int,
    gpa real,
    overallScore real
);
```

#### 定义接口

- IDataSource

```c++
class IDataSource
{
public:
    IDataSource();
    virtual ~IDataSource() = 0;

    /**
      * @brief 查询所有学生信息
      * @param stuInfoList 学生信息列表
      * @return true-成功 false-失败
      */
    virtual bool seleteStuInfo(QList<CStuInfo> &stuInfoList) = 0;

    /**
      * @brief 添加学生信息
      * @param stuInfo 学生信息
      * @return true-成功 false-失败
      */
    virtual bool addStuInfo(CStuInfo &stuInfo) = 0;

    /**
      * @brief 修改学生信息
      * @param stuInfo 学生信息
      * @return true-成功 false-失败
      */
    virtual bool updateStuInfo(CStuInfo &stuInfo) = 0;

    /**
      * @brief 删除学生信息
      * @param id 学生ID
      * @return true-成功 false-失败
      */
    virtual bool deleteStuInfo(int id) = 0;
};
```

##### SQLite

- CDataSourceSQLite

```c++
// cdatasourcesqlite.h
class CDataSourceSQLite: public IDataSource
{
public:
    CDataSourceSQLite();
    ~CDataSourceSQLite();


    virtual bool seleteStuInfo(QList<CStuInfo> &stuInfoList) override;
    virtual bool addStuInfo(CStuInfo &stuInfo) override;
    virtual bool updateStuInfo(CStuInfo &stuInfo) override;
    virtual bool deleteStuInfo(int id) override;

private:
    QSqlDatabase m_db;
};
 
// main.cpp

int main(int argc, char *argv[])
{
    qDebug() << "Tesing CDataSourceSQLite..." << endl;
    CDataSourceSQLite dataSource;
    qDebug() << "Tesing CDataSourceSQLite end..." << endl;

}
```
##  f3. 测试
- CStuInfo
```c++
class CStuInfo
{
public:
    CStuInfo();
    CStuInfo(int id, QString name, QString sex, QString phone, int cet4, double gpa);

    bool  setData(int id, QString name, QString sex, QString phone, int cet4, double gpa);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString sex() const;
    void setSex(const QString &sex);

    QString phone() const;
    void setPhone(const QString &phone);

    int cet4() const;
    void setCet4(int cet4);

    double gpa() const;
    void setGpa(double gpa);

    double overallScore() const;
    void setOverallScore(double overallScore);

    friend QDebug operator<<(QDebug dbg, const CStuInfo &stu);
private:
    int m_id ; // 学生ID，4位
    QString m_name; // 姓名
    QString m_sex ; // 性别，男/女
    QString m_phone; // 手机号，11位
    int m_cet4 ; // 四级成绩，0-750
    double m_gpa;// 平均成绩，0-4
    double  m_overallScore; // 总成绩，100 = m_cet4 * 0.04 + m_gpa * 17.5
};
```