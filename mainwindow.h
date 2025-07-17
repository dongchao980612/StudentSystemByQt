#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QMap>

#include <QMenu>
#include <QAction>
#include  <QElapsedTimer>


#include "cdatasourcesqlite.h"
#include "cstuinfo.h"
#include  "addstuinfodialog.h"

#define WIDTH 1100
#define HEIGHT 800

enum Columns
{
    ColID, ColName, ColSex, ColPhone, ColCET4, ColGPA, ColOverall
};

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
    void slot_itemChanged(QStandardItem *item);
    void slot_addInfo(CStuInfo &stuInfo);
    void  slot_updateInfo(CStuInfo &stuInfo);

    void slot_customContextMenuRequested(const QPoint &pos);
    void  slot_actUpdate();
    void  slot_actDelete();


    void on_add_Button_clicked();

    void on_delete_Button_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_stress_Button_clicked();

private:
    void initUI();
    void  addCss();
    bool appendToModel(const CStuInfo &stuInfo);

private:
    Ui::MainWindow *ui;


    CDataSourceSQLite *m_dataSource;  // 数据源
    QStandardItemModel *m_standardModel;  // 数据模型
    AddStuInfoDialog *m_addStuInfoDlg;

    QMenu  *m_menu;
    QAction *m_actUpdate; // 修改菜单项
    QAction *m_actDelete; //删除菜单项

};

static CStuInfo stuFromRow(const QStandardItemModel *m, int row);
#endif // MAINWINDOW_H
