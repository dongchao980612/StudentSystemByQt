#ifndef CDATASOURCESQLITE_H
#define CDATASOURCESQLITE_H

#include "idatasource.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QDebug>

#define EXEC_SUCCESS 0
#define EXEC_FAILURE -1


class CDataSourceSQLite: public IDataSource
{
public:
    CDataSourceSQLite(const QString &dbName = "studentInfo.db");
    ~CDataSourceSQLite();

    bool open() override;
    void close() override;
    bool isOpen() override;


    QList<CStuInfo> list() override;
    bool add(const CStuInfo &stu) override;
    bool update(const CStuInfo &stu) override;
    bool remove(int id) override;

    QString lastError() const override
    {
        return m_error ;
    }



private:
    void createTable();          // 建表
    QSqlDatabase m_db;
    QString      m_error;

};

#endif // CDATASOURCESQLITE_H
