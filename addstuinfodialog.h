#ifndef ADDSTUINFODIALOG_H
#define ADDSTUINFODIALOG_H

#define WIDTH 300
#define HEIGHT 300


#include <QDialog>
#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include  <QValidator>
#include <QRegularExpression>

#include  "cstuinfo.h"

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
    Ui::AddStuInfoDialog *ui;
    void initUI();
    void clearData();
};

#endif // ADDSTUINFODIALOG_H
