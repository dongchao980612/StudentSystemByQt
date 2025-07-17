#include "cdatasourcesqlite.h"


CDataSourceSQLite::CDataSourceSQLite(const QString &dbName)
{

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbName);

}

CDataSourceSQLite::~CDataSourceSQLite()
{
    close();
}

bool CDataSourceSQLite::open()
{
    if (isOpen())
    {
        return true;
    }
    if (!m_db.open())
    {
        m_error = m_db.lastError().text() + " " + __FILE__ + " " + QString::number(__LINE__) ;
        return false;
    }
    createTable();
    return true;
}

void CDataSourceSQLite::close()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool CDataSourceSQLite::isOpen()
{
    return m_db.isOpen();
}

void CDataSourceSQLite::createTable()
{
    QSqlQuery q(m_db);
    if (!q.exec("CREATE TABLE IF NOT EXISTS tb_student ("
                "id INTEGER PRIMARY KEY,"
                "name TEXT,"
                "sex TEXT,"
                "phone TEXT,"
                "cet4 INTEGER,"
                "gpa REAL,"
                "overallScore REAL)"))
    {
        m_error = q.lastError().text() + " " + __FILE__ + " " + QString::number(__LINE__) ;
    }
}

QList<CStuInfo> CDataSourceSQLite::list()
{
    QList<CStuInfo> res;
    if (!open())
    {
        return res;
    }

    QSqlQuery q("SELECT * FROM tb_student", m_db);

    while (q.next())
    {
        res.append({q.value("id").toInt(),
                    q.value("name").toString(),
                    q.value("sex").toString(),
                    q.value("phone").toString(),
                    q.value("cet4").toInt(),
                    q.value("gpa").toDouble()});
    }
    return res;
}

bool CDataSourceSQLite::add(const CStuInfo &stu)
{
    if (!open())
    {
        return false;
    }


    QSqlQuery q(m_db);
    q.prepare("INSERT INTO tb_student(id,name,sex,phone,cet4,gpa,overallScore) "
              "VALUES (?,?,?,?,?,?,?)");
    q.addBindValue(stu.id());
    q.addBindValue(stu.name());
    q.addBindValue(stu.sex());
    q.addBindValue(stu.phone());
    q.addBindValue(stu.cet4());
    q.addBindValue(stu.gpa());
    q.addBindValue(stu.overallScore());

    if (!q.exec())
    {
        m_error = q.lastError().text() + " " + __FILE__ + " " + QString::number(__LINE__) ;
        return false;
    }
    return true;
}

bool CDataSourceSQLite::update(const CStuInfo &stu)
{
    if (!open())
    {
        return false;
    }
    QSqlQuery q(m_db);
    q.prepare("UPDATE tb_student SET name=?,sex=?,phone=?,cet4=?,gpa=?,overallScore=? "
              "WHERE id=?");
    q.addBindValue(stu.name());
    q.addBindValue(stu.sex());
    q.addBindValue(stu.phone());
    q.addBindValue(stu.cet4());
    q.addBindValue(stu.gpa());
    q.addBindValue(stu.overallScore());
    q.addBindValue(stu.id());
    if (!q.exec())
    {
        m_error = q.lastError().text() + " " + __FILE__ + " " + QString::number(__LINE__) ;
        return false;
    }
    return true;
}

bool CDataSourceSQLite::remove(int id)
{
    if (!open())
    {
        return false;
    }
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM tb_student WHERE id=?");
    q.addBindValue(id);
    if (!q.exec())
    {
        m_error = q.lastError().text() + " " + __FILE__ + " " + QString::number(__LINE__);
        return false;
    }
    return true;
}
