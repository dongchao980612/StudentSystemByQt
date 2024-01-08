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

    m_menu = new QMenu(this);
    m_actdelete = new QAction("删除", this);
    m_actupdate = new QAction("更新", this);
    m_menu->addAction(m_actdelete);
    m_menu->addAction(m_actupdate);

    connect(m_actupdate, &QAction::triggered, this, &MainWindow::slot_actupdate);
    connect(m_actdelete, &QAction::triggered, this, &MainWindow::slot_actdelete);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &MainWindow::slot_popMenu);

    connect(m_addDialog, &AddStuInfoDialog::sig_addInfo, this, &MainWindow::slot_addInfo);
    connect(m_addDialog, &AddStuInfoDialog::sig_updateInfo, this, &MainWindow::slot_updateInfo);
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

void MainWindow::slot_updateInfo(CStuInfo &info)
{
    bool ret = m_dataSource->updateStuInfo(info);
    if(!ret)
    {
        QMessageBox::information(this, "提示", "修改数据失败");
        return;
    }
    else
    {
        int row = ui->tableView->currentIndex().row();
        m_standardModel->setData(m_standardModel->item(row, NAME_COLUMN)->index(), info.name());
        m_standardModel->setData(m_standardModel->item(row, SEX_COLUMN)->index(), info.sex());
        m_standardModel->setData(m_standardModel->item(row, PHONE_COLUMN)->index(), info.phone());
        m_standardModel->setData(m_standardModel->item(row, CET4_COLUMN)->index(), info.cet4());
        m_standardModel->setData(m_standardModel->item(row, GPA_COLUMN)->index(), info.gpa());
        m_standardModel->setData(m_standardModel->item(row, OVERALLSCORE_COLUMN)->index(), info.overallScore());
        QMessageBox::information(this, "提示", "修改数据成功");
        return;
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

void MainWindow::slot_popMenu(const QPoint &pos)
{
    if(m_standardModel->itemFromIndex(ui->tableView->indexAt(pos)) == NULL)
    {
        return ;
    }
    else
    {
        m_menu->exec(QCursor::pos());
    }

}

void MainWindow::slot_actupdate(bool checked)
{
    m_addDialog->setIsUpdateDLG(true);
    int row = ui->tableView->currentIndex().row();
    int ID = m_standardModel->item(row, ID_COLUMN)->text().toInt();
    QString Name = m_standardModel->item(row, NAME_COLUMN)->text();
    QString sex = m_standardModel->item(row, SEX_COLUMN)->text();
    QString phone = m_standardModel->item(row, PHONE_COLUMN)->text();
    int cet4 = m_standardModel->item(row, CET4_COLUMN)->text().toInt();
    double gpa = m_standardModel->item(row, GPA_COLUMN)->text().toDouble();
    m_addDialog->display(ID, Name, sex, phone, cet4, gpa);
    m_addDialog->show();
}

void MainWindow::slot_actdelete(bool checked)
{
    Q_UNUSED(checked)
    int row = ui->tableView->currentIndex().row();
    int ID = m_standardModel->item(row)->text().toInt();
    int res = QMessageBox::information(this, "提示", "是否确认删除", QMessageBox::Yes | QMessageBox::No);
    if(res == QMessageBox::No)
    {
        return;
    }
    {
        m_dataSource->deleteStuInfo(ID);
        m_standardModel->removeRow(row);
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

void MainWindow::on_delete_Button_clicked()
{

    QMap<int, QStandardItem *> delMaps;

    for (int row = 0; row < m_standardModel->rowCount(); row++)
    {
        QStandardItem *item = m_standardModel->item(row);
        if(item->checkState() == Qt::Checked)
        {
            delMaps.insert(row, item);
        }
    }

    if(delMaps.size() < 1)
    {
        return ;
    }

    int res = QMessageBox::information(this, "提示", "是否确认删除", QMessageBox::Yes | QMessageBox::No);

    if(res == QMessageBox::No)
    {
        return;
    }
    else
    {
        // 删除数据库中的数据
        QList<int> keyList = delMaps.keys();

        for (int key = keyList.size() - 1; key >= 0; key--)
        {
            bool ret = m_dataSource->deleteStuInfo(delMaps.value(keyList[key])->text().toInt());
            if(!ret)
            {
                QMessageBox::information(this, "提示", "删除失败");
                return ;
            }
            else
            {
                // 删除窗口中数据
                // m_standardModel->takeRow(key);
                // delete  delMaps.value(keyList[key]);
                m_standardModel->removeRow(keyList[key]);
            }
        }
    }

}
