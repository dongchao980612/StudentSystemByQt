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

    bool display(int id, QString name, QString sex, QString phone, int cet4, double gpa);
    bool isUpdateDLG() const;
    void setIsUpdateDLG(bool isUpdateDLG);

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

signals:
    void sig_addInfo(CStuInfo &info);
    void sig_updateInfo(CStuInfo &info);
private:
    void InitUI();
    void clearData();
private:
    Ui::AddStuInfoDialog *ui;
    bool m_isUpdateDLG;// 是否修改窗口
};
Q_DECLARE_METATYPE(CStuInfo)
#endif // ADDSTUINFODIALOG_H
