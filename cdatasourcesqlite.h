#ifndef CDATASOURCESQLITE_H
#define CDATASOURCESQLITE_H

#include "idatasource.h"

#include <QSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>

class CDataSourceSQLite : public IDataSource
{
public:
    CDataSourceSQLite();
    ~CDataSourceSQLite();
private:
    QSqlDatabase m_db; //数据库连接
};

#endif // CDATASOURCESQLITE_H
