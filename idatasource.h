#ifndef IDATASOURCE_H
#define IDATASOURCE_H

#include <QList>

#include "cstuinfo.h"

class IDataSource
{
public:
    IDataSource();
    virtual ~IDataSource() = 0;

    virtual bool open()   = 0;
    virtual void close()  = 0;
    virtual bool isOpen() = 0;



    virtual QList<CStuInfo> list()                       = 0;
    virtual bool add(const CStuInfo &stu)                = 0;
    virtual bool update(const CStuInfo &stu)             = 0;
    virtual bool remove(int id)                          = 0;

    /* 如需分页/过滤，可再扩展 */
    virtual QString lastError() const
    {
        return {};
    }
};

#endif // IDATASOURCE_H
