#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMessageBox>
#include "cdatasourcesqlite.h"
#include "addstuinfodialog.h"

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
    void slot_addInfo(CStuInfo &info);
    void slot_itemChanged(QStandardItem *item);
    void on_checkBox_clicked(bool checked);

private:
    void InitUI();
    void appendToModel(CStuInfo &stuInfo);
private:
    Ui::MainWindow *ui;
    CDataSourceSQLite *m_dataSource;
    QStandardItemModel *m_standardModel;
    AddStuInfoDialog *m_addDialog ;
};
#endif // MAINWINDOW_H
