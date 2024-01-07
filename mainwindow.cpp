#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("学生管理系统");
    this->setMaximumSize(800, 500);
    this->setMinimumSize(800, 500);

    m_dataSource = new CDataSourceSQLite();
    m_addDialog = new AddStuInfoDialog(this);

    connect(m_addDialog, &AddStuInfoDialog::sig_addInfo, this, &MainWindow::slot_addInfo);
    this->InitUI();
}

MainWindow::~MainWindow()
{
    delete  m_dataSource;
    delete ui;
}

void MainWindow::InitUI()
{
    m_standardModel = new QStandardItemModel(this);

    connect(m_standardModel, &QStandardItemModel::itemChanged, this, &MainWindow::slot_itemChanged);

    // 查询数据
    QList<CStuInfo> stuInfoList;
    bool ret = m_dataSource->seleteStuInfo(stuInfoList);
    if(!ret)
    {
        QMessageBox::information(this, "提示", "查询失败");
        return ;
    }
    else
    {
        for (int i = 0; i < stuInfoList.size(); i++)
        {
            appendToModel(stuInfoList[i]);
        }

        // 添加表头
        QStringList labels;
        labels << "学号" << "姓名" << "性别" << "手机号" << "cet4" << "gpa" << "综合成绩";
        m_standardModel->setHorizontalHeaderLabels(labels);
        ui->tableView->verticalHeader()->setVisible(false);
        // ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许双击编辑
        ui->tableView->setModel(m_standardModel);
    }

}

void MainWindow::appendToModel(CStuInfo &stuInfo)
{

    QStandardItem *itemId = new QStandardItem(QString("%1").arg(stuInfo.id(), 4, 10, QLatin1Char('0')));
    itemId->setCheckable(true);
    itemId->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QStandardItem *itemName = new QStandardItem(stuInfo.name());
    itemName->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QStandardItem *itemSex = new QStandardItem(stuInfo.sex());
    itemSex->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QStandardItem *itemPhone = new QStandardItem(stuInfo.phone());
    itemPhone->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QStandardItem *itemCet4 = new QStandardItem(QString::number(stuInfo.cet4()));
    itemCet4->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QStandardItem *itemGpa = new QStandardItem(QString::number(stuInfo.gpa()));
    itemGpa->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QStandardItem *itemOverallScore = new QStandardItem(QString::number(stuInfo.overallScore()));
    itemOverallScore->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


    QList<QStandardItem *> rowItem;
    rowItem.append(itemId);
    rowItem.append(itemName);
    rowItem.append(itemSex);
    rowItem.append(itemPhone);
    rowItem.append(itemCet4);
    rowItem.append(itemGpa);
    rowItem.append(itemOverallScore);

    m_standardModel->appendRow(rowItem);
}


void MainWindow::on_add_Button_clicked()
{
    m_addDialog->show();
}

void MainWindow::slot_addInfo(CStuInfo &info)
{

    bool ret = m_dataSource->addStuInfo(info);
    if(!ret)
    {
        QMessageBox::information(this, "提示", "添加数据失败");
        return;
    }
    else
    {
        appendToModel(info);
    }
}

void MainWindow::slot_itemChanged(QStandardItem *item)
{
    if(m_standardModel->indexFromItem(item).column() > 0)
    {
        return ;
    }
    else
    {
        for (int row = 0; row < m_standardModel->rowCount(); row++)
        {
            if(m_standardModel->item(row)->checkState() != Qt::Checked)
            {
                ui->checkBox->setChecked(false);
                return;
            }
            else
            {
                ui->checkBox->setChecked(true);
                return;
            }
        }
    }
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    for (int row = 0; row < m_standardModel->rowCount(); row++)
    {
        if(checked)
        {
            m_standardModel->item(row)->setCheckState(Qt::Checked);
        }
        else
        {
            m_standardModel->item(row)->setCheckState(Qt::Unchecked);
        }
    }
}
