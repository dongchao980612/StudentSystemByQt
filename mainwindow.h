#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QMap>

#include <QMenu>
#include <QAction>

#include "cdatasourcesqlite.h"
#include "cstuinfo.h"
#include  "addstuinfodialog.h"

#define WIDTH 1100
#define HEIGHT 800

#define ID_COLUMN 0
#define NAME_COLUMN 1
#define SEX_COLUMN 2
#define PHONE_COLUMN 3
#define CET4_COLUMN 4
#define GPA_COLUMN 5
#define OVERALLSCORE_COLUMN 6


QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void  slot_addInfo(CStuInfo &stuInfo);
    void on_add_Button_clicked();

    void on_delete_Button_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    void initUI();
    void  addCss();
    bool appendToModel(const CStuInfo &stuInfo);
private:
    Ui::MainWindow *ui;


    CDataSourceSQLite *m_dataSource;  // 数据源
    QStandardItemModel *m_standardModel;  // 数据模型
    AddStuInfoDialog *m_addStuInfo;

};
#endif // MAINWINDOW_H
