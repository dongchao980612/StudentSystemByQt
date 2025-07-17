#ifndef ADDSTUINFODIALOG_H
#define ADDSTUINFODIALOG_H

#define DIALOG_WIDTH 300
#define DIALOG_HEIGHT 300


#include  <QDialog>
#include  <QMessageBox>
#include  <QRegExp>
#include  <QRegExpValidator>
#include  <QValidator>
#include  <QRegularExpression>
#include  <QLatin1Char>

#include  "cstuinfo.h"

namespace Ui
{
    class AddStuInfoDialog;
}

class AddStuInfoDialog : public QDialog
{
    Q_OBJECT

public:
    enum Mode { AddMode, EditMode };          // <-- 新增枚举

    explicit AddStuInfoDialog(QWidget *parent = nullptr);
    ~AddStuInfoDialog();
    void setStuInfo(CStuInfo &info);


    void setMode(Mode mode);                  // 设置模式
    Mode mode() const
    {
        return m_mode;    // 读取模式
    }

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();
signals:
    void sig_addInfo(CStuInfo &info);
    void sig_updateInfo(CStuInfo &info);
private:
    Ui::AddStuInfoDialog *ui;
    void initUI();
    void clearData();
    Mode  m_mode = AddMode;   // <-- 取代原来的 m_is_Update


};

#endif // ADDSTUINFODIALOG_H
