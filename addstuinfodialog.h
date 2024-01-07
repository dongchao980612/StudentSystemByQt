#ifndef ADDSTUINFODIALOG_H
#define ADDSTUINFODIALOG_H

#include <QDialog>
#include <QRegExp>
#include <QDebug>
#include <QMessageBox>
#include "cstuinfo.h"
namespace Ui
{
    class AddStuInfoDialog;
}

class AddStuInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStuInfoDialog(QWidget *parent = nullptr);
    ~AddStuInfoDialog();

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

signals:
    void sig_addInfo(CStuInfo &info);
private:
    void InitUI();
    void clearData();
private:
    Ui::AddStuInfoDialog *ui;
};
Q_DECLARE_METATYPE(CStuInfo)
#endif // ADDSTUINFODIALOG_H
