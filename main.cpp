#include "mainwindow.h"

#include <QApplication>
#include <iostream>

#include "cdatasourcesqlite.h"
#include "cstuinfo.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
#if 0
    qDebug() << "Tesing CDataSourceSQLite..." << endl;
    //CDataSourceSQLite dataSource;
    qDebug() << "Tesing CDataSourceSQLite end..." << endl;
#endif

#if 0
    qDebug() << "Tesing CStuInfo..." << endl;
    CStuInfo stu;
    stu.setData(1, "zhangsan", "男", "151", 322, 434);
    std::cout << stu;
    qDebug() << "Tesing CStuInfo end..." << endl;
#endif

#if 0
    qDebug() << "Tesing seleteStuInfo..." << endl;
    CDataSourceSQLite dataSource;
    QList<CStuInfo> stu_info_list;
    dataSource.seleteStuInfo(stu_info_list);
    qDebug() << stu_info_list.at(0) << endl;
#endif

    return a.exec();
}
