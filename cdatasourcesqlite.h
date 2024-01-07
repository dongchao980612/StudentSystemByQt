#ifndef CDATASOURCESQLITE_H
#define CDATASOURCESQLITE_H

#include "idatasource.h"

#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

class CDataSourceSQLite : public IDataSource
{
public:
    CDataSourceSQLite();
    ~CDataSourceSQLite();
private:
    QSqlDatabase m_db; //数据库连接

    // IDataSource interface
public:
    virtual bool seleteStuInfo(QList<CStuInfo> &stuInfoList) override;
    virtual bool addStuInfo(CStuInfo &stuInfo) override;
    virtual bool updateStuInfo(CStuInfo &stuInfo) override;
    virtual bool deleteStuInfo(int id) override;
};

#endif // CDATASOURCESQLITE_H
