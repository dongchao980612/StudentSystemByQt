#include "cdatasourcesqlite.h"

CDataSourceSQLite::CDataSourceSQLite()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("./StuInfo.db");
    if(!m_db.open())
    {
        qDebug() << "database open error...";
        return;
    }
    else
    {
        qDebug() << "database open OK...";
    }

    QSqlQuery query;
    QString sql = QString("create table if not exists tb_student"
                          "(id int primary key not null,"
                          " name varchar(50),sex varchar(2),"
                          "phone varchar(11),"
                          "cet4 int,gpa real,"
                          "overallScore real);");
    if(!query.exec(sql))
    {
        qDebug() << sql;
        qDebug() << "exec sql error...";
        return;
    }
    else
    {
        qDebug() << "exec sql OK...";
    }
    m_db.close();
}
CDataSourceSQLite::~CDataSourceSQLite()
{
    qDebug() << "~CDataSourceSQLite...";
}
