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
#include "addstuinfodialog.h"

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
    void on_add_Button_clicked();
    void on_checkBox_clicked(bool checked);
    void on_delete_Button_clicked();

    void slot_addInfo(CStuInfo &info);
    void slot_updateInfo(CStuInfo &info);


    void slot_itemChanged(QStandardItem *item);
    void slot_popMenu(const QPoint &pos);
    void slot_actupdate(bool checked = false);
    void slot_actdelete(bool checked = false);

private:
    void InitUI();
    void appendToModel(CStuInfo &stuInfo);
private:
    Ui::MainWindow *ui;
    CDataSourceSQLite *m_dataSource;
    QStandardItemModel *m_standardModel;
    AddStuInfoDialog *m_addDialog ;
    QMenu *m_menu; //菜单
    QAction *m_actdelete;
    QAction *m_actupdate;

};
#endif // MAINWINDOW_H
