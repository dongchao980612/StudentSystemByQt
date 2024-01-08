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
                          "name varchar(50),"
                          "sex varchar(2),"
                          "phone varchar(11),"
                          "cet4 int,"
                          "gpa real,"
                          "overallScore real);");
    if(!query.exec(sql))
    {
        qDebug() << sql;
        qDebug() << "exec create sql error...";
        return;
    }
    else
    {
        qDebug() << "exec create sql OK...";
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
        qDebug() << "database open error...";
        return false;
    }
    else
    {
        QSqlQuery query;
        QString sql = "select * from tb_student";
        if(!query.exec(sql))
        {
            qDebug() << sql;
            qDebug() << "exec select sql error...";
            return false;
        }
        else
        {
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
            return true;
        }
    }
}

bool CDataSourceSQLite::addStuInfo(CStuInfo &stuInfo)
{
    if(!m_db.open())
    {
        qDebug() << "database open error...";
        return false;
    }
    else
    {

        int Id = stuInfo.id();
        QString Name = stuInfo.name();
        QString Sex = stuInfo.sex();
        QString Phone = stuInfo.phone();
        int Cet4 = stuInfo.cet4();
        double Gpa = stuInfo.gpa();
        double OverallScore = stuInfo.overallScore();

        QSqlQuery query;
        QString sql = QString("insert into tb_student(id,name,sex,phone,cet4,gpa,overallScore) values(%1,'%2','%3','%4',%5,%6,%7)").arg(Id).arg(Name).arg(Sex).arg(Phone).arg(Cet4).arg(Gpa).arg(OverallScore);
        if(!query.exec(sql))
        {
            qDebug() << "lastError" << query.lastError().text();
            qDebug() << sql;
            qDebug() << "exec insert sql error...";
            return false;
        }
        else
        {
            m_db.close();
            return true ;
        }
    }
}

bool CDataSourceSQLite::updateStuInfo(CStuInfo &stuInfo)
{
    qDebug() << __FUNCTION__;
    if(!m_db.open())
    {
        qDebug() << "database open error...";
        return false;
    }
    else
    {

        int Id = stuInfo.id();
        QString Name = stuInfo.name();
        QString Sex = stuInfo.sex();
        QString Phone = stuInfo.phone();
        int Cet4 = stuInfo.cet4();
        double Gpa = stuInfo.gpa();
        double OverallScore = stuInfo.overallScore();

        QSqlQuery query;
        QString sql = QString("update tb_student set name='%2',sex='%3',phone='%4',cet4=%5,gpa=%6,overallScore=%7 where id=%1").arg(Id).arg(Name).arg(Sex).arg(Phone).arg(Cet4).arg(Gpa).arg(OverallScore);
        if(!query.exec(sql))
        {
            qDebug() << "lastError" << query.lastError().text();
            qDebug() << sql;
            qDebug() << "exec insert sql error...";
            return false;
        }
        else
        {
            m_db.close();
            return true ;
        }
    }
    return true ;
}

bool CDataSourceSQLite::deleteStuInfo(int id)
{
    if(!m_db.open())
    {
        qDebug() << "database open error...";
        return false;
    }
    else
    {
        QSqlQuery query;
        QString sql = QString("delete from tb_student where id= %1").arg(id);
        if(!query.exec(sql))
        {
            qDebug() << "lastError" << query.lastError().text();
            qDebug() << sql;
            qDebug() << "exec insert sql error...";
            return false;
        }
        else
        {
            m_db.close();
            return true ;
        }
    }
}

