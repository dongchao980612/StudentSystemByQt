#include "addstuinfodialog.h"
#include "ui_addstuinfodialog.h"

AddStuInfoDialog::AddStuInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStuInfoDialog)
{
    ui->setupUi(this);
    this->setMaximumSize(250, 300);
    this->setMinimumSize(250, 300);
    this->setWindowTitle("添加/修改学生信息");

    this->InitUI();
}

AddStuInfoDialog::~AddStuInfoDialog()
{
    delete ui;
}

bool AddStuInfoDialog::display(int id, QString name, QString sex, QString phone, int cet4, double gpa)
{
    ui->lineEdit_ID->setText(QString("%1").arg(id, 4, 10, QLatin1Char('0')));
    ui->lineEdit_ID->setReadOnly(true);
    ui->lineEdit_Name->setText(name);
    ui->comboBox_Sex->setCurrentText(sex);
    ui->lineEdit_Phone->setText(phone);
    ui->spinBox_Cet4->setValue(cet4);
    ui->doubleSpinBox_Gpa->setValue(gpa);
}

void AddStuInfoDialog::on_pushButton_OK_clicked()
{
    // 判断信息的合法性
    int IdLen = ui->lineEdit_ID->text().length();
    int Id ;
    if(IdLen != 4)
    {
        QMessageBox::information(this, "提示", "输入学号不正确");
        return;
    }
    else
    {
        Id = ui->lineEdit_ID->text().toUInt();
    }

    int PhoneLen = ui->lineEdit_Phone->text().length();
    QString Phone;
    if(PhoneLen != 11)
    {
        QMessageBox::information(this, "提示", "输入手机号不正确");
        return;
    }
    else
    {
        Phone = ui->lineEdit_Phone->text();
    }
    QString Name = ui->lineEdit_Name->text();
    QString Sex = ui->comboBox_Sex->currentText();

    int Cet4 = ui->spinBox_Cet4->value();
    double Gpa = ui->doubleSpinBox_Gpa->value();


    CStuInfo info(Id, Name, Sex, Phone, Cet4, Gpa);

    if(m_isUpdateDLG)
    {
        sig_updateInfo(info);
    }
    else
    {
        emit sig_addInfo(info);
        this->clearData();
    }



}

void AddStuInfoDialog::InitUI()
{
    // 学号
    ui->lineEdit_ID->setPlaceholderText("请输入4位数学号");
    QRegExp reID("^[0-9]{4}$");
    ui->lineEdit_ID->setValidator(new QRegExpValidator(reID, this));

    //姓名
    ui->lineEdit_Name->setPlaceholderText("请输入姓名");
    QRegExp reName("^[a-zA-Z\\u4e00-\u9fa5]{1,}$");
    ui->lineEdit_Name->setValidator(new QRegExpValidator(reName, this));

    // 性别
    QStringList texts;
    texts << "男" << "女";
    ui->comboBox_Sex->addItems(texts);

    // 手机号
    ui->lineEdit_Phone->setPlaceholderText("请输入11位数手机号");
    QRegExp rePhone("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    ui->lineEdit_Phone->setValidator(new QRegExpValidator(rePhone, this));

    // 四级成绩
    ui->spinBox_Cet4->setRange(0, 750);

    // 平均成绩
    ui->doubleSpinBox_Gpa->setRange(0.0, 4.0);
}

void AddStuInfoDialog::clearData()
{
    ui->lineEdit_ID->clear();
    ui->lineEdit_ID->setPlaceholderText("请输入4位数学号");

    ui->lineEdit_Name->clear();
    ui->lineEdit_Name->setPlaceholderText("请输入姓名");

    ui->lineEdit_Phone->clear();
    ui->lineEdit_Phone->setPlaceholderText("请输入11位数手机号");

    ui->spinBox_Cet4->setValue(0);
    ui->doubleSpinBox_Gpa->setValue(0);

}

bool AddStuInfoDialog::isUpdateDLG() const
{
    return m_isUpdateDLG;
}

void AddStuInfoDialog::setIsUpdateDLG(bool isUpdateDLG)
{
    m_isUpdateDLG = isUpdateDLG;
}

void AddStuInfoDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}
