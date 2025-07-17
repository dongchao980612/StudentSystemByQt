#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("学生信息管理系统");
    this->setMaximumSize(WIDTH, HEIGHT);
    this->setMinimumSize(WIDTH, HEIGHT);



    addCss();
    initUI();

}

MainWindow::~MainWindow()
{
    delete m_dataSource;
    delete ui;
}

void MainWindow::slot_itemChanged(QStandardItem *item)
{
    // 1. 只关心第 0 列的复选框
    if (item->column() != 0 || !item->isCheckable())
    {
        return;
    }

    // 2. 统计当前已勾选行数
    int checkedCount = 0;
    int totalCount   = m_standardModel->rowCount();
    for (int r = 0; r < totalCount; ++r)
    {
        if (m_standardModel->item(r, 0)->checkState() == Qt::Checked)
        {
            ++checkedCount;
        }
    }

    // 3. 更新全选按钮状态
    QCheckBox *checkAll = ui->checkBox;   // 你的全选框
    checkAll->blockSignals(true);         // 防止递归触发
    if (checkedCount == totalCount && totalCount > 0)
    {
        checkAll->setCheckState(Qt::Checked);
    }
    else if (checkedCount == 0)
    {
        checkAll->setCheckState(Qt::Unchecked);
    }
    else
    {
        checkAll->setCheckState(Qt::PartiallyChecked);
    }
    checkAll->blockSignals(false);
}

void MainWindow::slot_addInfo(CStuInfo &stuInfo)
{
    m_addStuInfoDlg->setMode(AddStuInfoDialog::AddMode);
    m_dataSource->add(stuInfo);
    appendToModel(stuInfo);
}

void MainWindow::slot_updateInfo(CStuInfo &stuInfo)
{
    m_dataSource->update(stuInfo);
    int row = ui->tableView->currentIndex().row();
    m_standardModel->setData(m_standardModel->item(row, ColName)->index(), stuInfo.name());
    m_standardModel->setData(m_standardModel->item(row, ColSex)->index(), stuInfo.sex());
    m_standardModel->setData(m_standardModel->item(row, ColPhone)->index(), stuInfo.phone());
    m_standardModel->setData(m_standardModel->item(row, ColCET4)->index(), stuInfo.cet4());
    m_standardModel->setData(m_standardModel->item(row, ColGPA)->index(), stuInfo.gpa());
    m_standardModel->setData(m_standardModel->item(row, ColOverall)->index(), stuInfo.overallScore());
}

void MainWindow::slot_customContextMenuRequested(const QPoint &pos)
{

    if(m_standardModel->itemFromIndex(ui->tableView->indexAt(pos)) != NULL)
    {
        m_menu->exec(QCursor::pos());
    }
}

void MainWindow::slot_actUpdate()
{
    int row = ui->tableView->currentIndex().row();
    if (row < 0)
    {
        return;
    }

    CStuInfo stu = stuFromRow(m_standardModel, row);   // 🔹一行搞定
    m_addStuInfoDlg->setMode(AddStuInfoDialog::EditMode);
    m_addStuInfoDlg->setStuInfo(stu);   // 你已有的回填接口
    m_addStuInfoDlg->exec();
}

void MainWindow::slot_actDelete()
{
    int row = ui->tableView->currentIndex().row();
    int id = m_standardModel->item(row)->text().toInt();
    m_dataSource->remove(id);
    m_standardModel->removeRow(row);
}

void MainWindow::initUI()
{
    // 对象实例化
    m_dataSource = new CDataSourceSQLite();
    m_standardModel = new QStandardItemModel(this);
    m_addStuInfoDlg = new AddStuInfoDialog(this);

    m_menu = new QMenu(this);

    m_actUpdate = new QAction("修改", m_menu);
    m_actDelete = new QAction("删除", m_menu);
    m_menu->addAction(m_actUpdate);
    m_menu->addAction(m_actDelete);


    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    // 槽函数连接
    connect(m_standardModel, &QStandardItemModel::itemChanged, this, &MainWindow::slot_itemChanged);
    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &MainWindow::slot_customContextMenuRequested);
    connect(m_addStuInfoDlg, &AddStuInfoDialog::sig_addInfo, this, &MainWindow::slot_addInfo);
    connect(m_addStuInfoDlg, &AddStuInfoDialog::sig_updateInfo, this, &MainWindow::slot_updateInfo);
    connect(m_actUpdate, &QAction::triggered, this, &MainWindow::slot_actUpdate);
    connect(m_actDelete, &QAction::triggered, this, &MainWindow::slot_actDelete);
    // 添加表头
    QStringList labels;
    labels << "学号" << "姓名" << "性别" << "手机号" << "cet4" << "gpa" << "综合成绩";
    m_standardModel->setHorizontalHeaderLabels(labels);


    // 查询数据
    QList<CStuInfo> stuInfoList = m_dataSource->list();


    // 将数据添加到模型
    for (const CStuInfo &stu : stuInfoList)
    {
        appendToModel(stu);
    }

    //  将模型添加到视图
    ui->tableView->setModel(m_standardModel);


}

void MainWindow::addCss()
{

    // 放在 MainWindow 构造函数里即可
    QString qss = R"(
    /* 1. 整体背景、网格线 */
    QTableView {
        border: none;
        background: #ffffff;
        gridline-color: #e0e0e0;
        alternate-background-color: #fafafa;   /* 偶数行 */
        selection-background-color: #1976d2;   /* 选中行背景 */
        selection-color: #ffffff;
        outline: 0;                            /* 去掉选中虚线框 */
    }

    /* 2. 表头 */
    QHeaderView::section {
        background: #ffffff;
        color: #424242;
        font: 600 9pt "Segoe UI";
        border: none;
        border-bottom: 1px solid #c0c0c0;
        padding: 4px;
    }

    /* 3. 滚动条 */
    QScrollBar:vertical, QScrollBar:horizontal {
        border: none;
        background: #f5f5f5;
        width: 8px;
        height: 8px;
    }
    QScrollBar::handle {
        background: #bdbdbd;
        border-radius: 4px;
    }
    QScrollBar::handle:hover {
        background: #9e9e9e;
    }
    QScrollBar::add-line, QScrollBar::sub-line {
        width: 0px;
        height: 0px;
    }
    )";

    ui->tableView->setStyleSheet(qss);

    /* 4. 让交替色、选中行生效 */
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    /* 5. 单元格垂直居中、列宽自适应内容 */
    ui->tableView->verticalHeader()->setVisible(false);      // 去掉行号
    ui->tableView->verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView->resizeColumnsToContents();                // 首次自适应
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许双击编辑

}


bool MainWindow::appendToModel(const CStuInfo &stuInfo)
{
    struct Column
    {
        int             role;      // 用于 setData 的 role
        QVariant        value;     // 真实数据（排序用）
        QString         text;      // 显示文本
    };

    // 按顺序定义每一列
    const Column cols[] =
    {
        { Qt::DisplayRole, stuInfo.id(),          QStringLiteral("%1").arg(stuInfo.id(), 4, 10, QLatin1Char('0')) },
        { Qt::DisplayRole, QVariant(),            stuInfo.name() },
        { Qt::DisplayRole, QVariant(),            stuInfo.sex() },
        { Qt::DisplayRole, QVariant(),            stuInfo.phone() },
        { Qt::DisplayRole, stuInfo.cet4(),        QString::number(stuInfo.cet4()) },
        { Qt::DisplayRole, stuInfo.gpa(),         QString::number(stuInfo.gpa()) },
        { Qt::DisplayRole, stuInfo.overallScore(), QString::number(stuInfo.overallScore()) }
    };
    constexpr int kColCount = sizeof(cols) / sizeof(cols[0]);

    QList<QStandardItem *> rowItems;
    rowItems.reserve(kColCount);

    for (int c = 0; c < kColCount; ++c)
    {
        auto *item = new QStandardItem;
        item->setData(cols[c].value,  Qt::EditRole);   // 原始数据，用于排序、编辑
        item->setData(cols[c].text,  Qt::DisplayRole); // 显示文本
        item->setTextAlignment(Qt::AlignCenter);

        if (c == 0)                         // 首列带复选框
        {
            item->setCheckable(true);
            item->setCheckState(Qt::Unchecked);
        }
        rowItems.append(item);
    }

    m_standardModel->appendRow(rowItems);
    return true;

}


void MainWindow::on_add_Button_clicked()
{

    m_addStuInfoDlg->exec();
}

void MainWindow::on_delete_Button_clicked()
{

    // 先统计要删除的行数
    int delCount = 0;
    for (int row = 0; row < m_standardModel->rowCount(); ++row)
    {
        if (m_standardModel->item(row, 0)->checkState() == Qt::Checked)
        {
            ++delCount;
        }
    }

    if (delCount == 0)
    {
        return;    // 没有选中就啥也不干
    }

    // 弹出确认框
    auto reply = QMessageBox::question(
                     this,
                     "确认删除",
                     QString("您已勾选 %1 条记录，确定要删除吗？").arg(delCount),
                     QMessageBox::Yes | QMessageBox::No,
                     QMessageBox::No);

    if (reply != QMessageBox::Yes)
    {
        return;
    }


    // 倒序遍历，删除行时索引不会错位
    for (int row = m_standardModel->rowCount() - 1; row >= 0; --row)
    {
        QStandardItem *checkItem = m_standardModel->item(row, 0);      // 第 0 列复选框
        if (checkItem && checkItem->checkState() == Qt::Checked)
        {
            int id = checkItem->text().toInt();                // 学号
            m_dataSource->remove(id);                          // 从数据库删除
            m_standardModel->removeRow(row);                           // 从视图删除
        }
    }
}

void MainWindow::on_checkBox_stateChanged(int state)
{
    const Qt::CheckState checkState =
        (state == Qt::Checked) ? Qt::Checked : Qt::Unchecked;

    // 遍历模型，同步复选框
    for (int row = 0; row < m_standardModel->rowCount(); ++row)
    {
        if (QStandardItem *item = m_standardModel->item(row, 0))
        {
            item->setCheckState(checkState);
        }
    }
}
static CStuInfo stuFromRow(const QStandardItemModel *m, int row)
{
    return CStuInfo(
               m->item(row, ColID)->text().toInt(),
               m->item(row, ColName)->text(),
               m->item(row, ColSex)->text(),
               m->item(row, ColPhone)->text(),
               m->item(row, ColCET4)->text().toInt(),
               m->item(row, ColGPA)->text().toDouble()
           );
}

void MainWindow::on_stress_Button_clicked()
{
    CStuInfo info;
    info.setName("Stress");
    info.setSex("M");
    info.setPhone("13800000000");
    info.setCet4(550);
    info.setGpa(3.5);
    info.setOverallScore(88.8);

    QElapsedTimer t;
    t.start();
    int len_of_test_data = 10000;
    for (int i = 1; i <= len_of_test_data; ++i)
    {
        info.setId(900000 + i);
        m_dataSource->add(info);
    }
    qDebug() << "插入"<<len_of_test_data<<"条数据耗时:" << t.elapsed() << "ms";
}
