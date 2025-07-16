#include "cdatasourcesqlite.h"


CDataSourceSQLite::CDataSourceSQLite()
{

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("studentInfo.db");
    if(!m_db.open())
    {
        qDebug() << "Failed to open database!";
        return;
    }

    QSqlQuery query;
    QString sql = QString("create table if not exists tb_student"
                          "(id int primary key not null,"
                          "name varchar(50),"
                          "sex varchar(2),"
                          "phone varchar(11),"
                          "cet4 int,"
                          "gpa real,"
                          "overallScore real);");

    if(!query.exec(sql))
    {
        qDebug() << query.lastError();
        qDebug() << "Exec create sql error...";
        return;
    }

    m_db.close();
}

CDataSourceSQLite::~CDataSourceSQLite()
{

}

bool CDataSourceSQLite::seleteStuInfo(QList<CStuInfo> &stuInfoList)
{

    if(!m_db.open())
    {
        qDebug() << "Open database  error...";
        return EXIT_FAILURE;
    }

    QSqlQuery query;
    QString sql = "select * from tb_student";
    if(!query.exec(sql))
    {
        qDebug() << "Failed to select sql error...";
        return EXIT_FAILURE;
    }

    while (query.next())
    {
        int Id = query.value("id").toInt();
        QString Name = query.value("name").toString();
        QString Sex = query.value("sex").toString();
        QString Phone = query.value("phone").toString();
        int Cet4 = query.value("cet4").toInt();
        double Gpa = query.value("gpa").toDouble();
        CStuInfo info(Id, Name, Sex, Phone, Cet4, Gpa);
        stuInfoList.append(info);
    }
    m_db.close();

    return EXIT_SUCCESS;


}

bool CDataSourceSQLite::addStuInfo(CStuInfo &stuInfo)
{
    return true;
}

bool CDataSourceSQLite::updateStuInfo(CStuInfo &stuInfo)
{
    return true;
}

bool CDataSourceSQLite::deleteStuInfo(int id)
{
    return true;
}
