#include "mainwindow.h"

#include <QApplication>
#include "cdatasourcesqlite.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    CDataSourceSQLite cds;

    return a.exec();
}
