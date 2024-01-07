#ifndef IDATASOURCE_H
#define IDATASOURCE_H
#include <QList>

#include "cstuinfo.h"

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

#endif // IDATASOURCE_H
