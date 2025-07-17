#include "addstuinfodialog.h"
#include "ui_addstuinfodialog.h"

AddStuInfoDialog::AddStuInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStuInfoDialog)
{
    ui->setupUi(this);
    this->setMaximumSize(DIALOG_WIDTH, DIALOG_HEIGHT);
    this->setMinimumSize(DIALOG_WIDTH, DIALOG_HEIGHT);
     setWindowTitle(this->mode() == AddMode ? "添加学生" : "修改学生");

    initUI();
}

AddStuInfoDialog::~AddStuInfoDialog()
{
    delete ui;
}

void AddStuInfoDialog::setStuInfo(CStuInfo &info)
{
    ui->lineEdit_ID->setText(QString("%1").arg(info.id(), 4, 10, QLatin1Char('0')));
    ui->lineEdit_ID->setReadOnly(true); // 设置为不可编辑
    ui->lineEdit_Name->setText(info.name());
    ui->comboBox_Sex->setCurrentText(info.sex());
    ui->lineEdit_Phone->setText(info.phone());
    ui->spinBox_Cet4->setValue(info.cet4());
    ui->doubleSpinBox_Gpa->setValue(info.gpa());
}

void AddStuInfoDialog::on_pushButton_OK_clicked()
{
    // 判断信息的合法性

    int id = ui->lineEdit_ID->text().toUInt();
    QString phone = ui->lineEdit_Phone->text();
    QString name = ui->lineEdit_Name->text();
    QString sex = ui->comboBox_Sex->currentText();
    int cet4 = ui->spinBox_Cet4->value();
    double gpa = ui->doubleSpinBox_Gpa->value();
    CStuInfo info(id, name, sex, phone, cet4, gpa);


    /* 方案 B：保持你原来两个信号（与枚举共存） */
    if (m_mode == EditMode)
    {
        emit sig_updateInfo(info);
    }
    else
    {
        emit sig_addInfo(info);
    }

    accept();




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
void AddStuInfoDialog::initUI()
{
    // 学号
    ui->lineEdit_ID->setPlaceholderText("请输入4位数学号");
    QRegExp reID("^[0-9]{4}$"); // 四位数
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
    // QRegExp rePhone("^1([358][0-9]|4[579]|66|7[0135678]|9[89])[0-9]{8}$");
    // ui->lineEdit_Phone->setValidator(new QRegExpValidator(rePhone, this));

    // 四级成绩
    ui->spinBox_Cet4->setRange(0, 750);

    // 平均成绩
    ui->doubleSpinBox_Gpa->setRange(0.0, 4.0);


    // 美化细节：一键清空
    for (auto le :
            {
                ui->lineEdit_ID, ui->lineEdit_Name, ui->lineEdit_Phone
            })
        le->setClearButtonEnabled(true);

}


void AddStuInfoDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}



void AddStuInfoDialog::setMode(AddStuInfoDialog::Mode mode)
{

    m_mode = mode;
    setWindowTitle(mode == AddMode ? "添加学生" : "修改学生");
    if (mode == AddMode)
    {
        clearData();
    }

}

