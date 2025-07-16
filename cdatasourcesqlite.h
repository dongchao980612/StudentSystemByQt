#ifndef CDATASOURCESQLITE_H
#define CDATASOURCESQLITE_H

#include "idatasource.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QDebug>

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

#endif // CDATASOURCESQLITE_H
