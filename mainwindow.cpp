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

    m_dataSource = new CDataSourceSQLite();
    m_standardModel = new QStandardItemModel(this);

    addCss();
    initUI();




}

MainWindow::~MainWindow()
{
    delete m_dataSource;
    delete ui;
}

void MainWindow::initUI()
{

    // 添加表头
    QStringList labels;
    labels << "学号" << "姓名" << "性别" << "手机号" << "cet4" << "gpa" << "综合成绩";
    m_standardModel->setHorizontalHeaderLabels(labels);


    // 查询数据
    QList<CStuInfo> stuInfoList;

    bool ret = m_dataSource->seleteStuInfo(stuInfoList);
    if(ret)
    {
        qDebug() << "查询失败";
        return ;
    }

    // 将数据添加到模型
    for (int i = 0; i < stuInfoList.size(); i++)
    {
        appendToModel(stuInfoList[i]);
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


bool MainWindow::appendToModel(CStuInfo &stuInfo)
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

