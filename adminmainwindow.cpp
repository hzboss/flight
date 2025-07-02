#include "adminmainwindow.h"
#include "ui_adminmainwindow.h"
#include <QPixmap>
#include "flight.h"
#include "adminflightinfo.h"
#include <QMessageBox>
#include <QTime>

AdminMainWindow::AdminMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AdminMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("管理员主界面");
    QIcon icon = QIcon(":/photosources/mainwindow.jpg");
    this->setWindowIcon(icon);

    connect(ui->ReverseBtn,&QPushButton::clicked,[this](){
        QString start = ui->StartPointLine->text();
        QString end = ui->EndPointLine->text();
        ui->StartPointLine->setText(end);
        ui->EndPointLine->setText(start);
    });
    QTimer *timer;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &AdminMainWindow::updateTime);
    timer->start(1000);
    updateTime();
    connect(ui->SeekBtn,&QPushButton::clicked,[this](){
        // 显示给定编号航班信息
        QString id = ui->SeekLine->text();
        Flight target = Flight::Seekres(id);
        // 获取 QScrollArea 的内容窗口
        QWidget *contentWidget = ui->AdminShowFlightArea->widget();
        if (!contentWidget) {
            // 如果没有内容窗口，则创建一个新的
            contentWidget = new QWidget(ui->AdminShowFlightArea);
            ui->AdminShowFlightArea->setWidget(contentWidget);
        }

        // 获取并删除现有的布局（如果存在）
        QLayout *existingLayout = contentWidget->layout();
        if (existingLayout) {
            while (QLayoutItem *item = existingLayout->takeAt(0)) {
                delete item->widget(); // 删除小部件
                delete item; // 删除布局项
            }
            delete existingLayout; // 删除布局
        }
        if(target.getFlightid()=="null"){
            return;
        }
        QVBoxLayout *layout = new QVBoxLayout(contentWidget);
        AdminFlightInfo* flight = new AdminFlightInfo(target,this);
        layout->addWidget(flight);
    });
    connect(ui->FilterBtn, &QPushButton::clicked, [this](){
        // 显示给定起点终点航班信息
        QString start = ui->StartPointLine->text();
        QString end = ui->EndPointLine->text();

        // 获取 QScrollArea 的内容窗口
        QWidget *contentWidget = ui->AdminShowFlightArea->widget();
        if (!contentWidget) {
            // 如果没有内容窗口，则创建一个新的
            contentWidget = new QWidget(ui->AdminShowFlightArea);
            ui->AdminShowFlightArea->setWidget(contentWidget);
        }

        // 获取并删除现有的布局（如果存在）
        QLayout *existingLayout = contentWidget->layout();
        if (existingLayout) {
            while (QLayoutItem *item = existingLayout->takeAt(0)) {
                delete item->widget(); // 删除小部件
                delete item; // 删除布局项
            }
            delete existingLayout; // 删除布局
        }

        // 获取过滤后的航班信息
        std::vector<Flight> targets = Flight::Filtres(start, end);

        // 创建新的 QVBoxLayout
        QVBoxLayout *layout = new QVBoxLayout(contentWidget);
        for (size_t i = 0; i < targets.size(); i++) {
            AdminFlightInfo *flight = new AdminFlightInfo(targets[i], this);
            layout->addWidget(flight);
        }
    });
    connect(ui->ExitBtn,&QPushButton::clicked,[this](){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "退出系统",
                                      "你确定要退出系统吗?",
                                      QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            this->close();
        }
    });
    connect(ui->AddFlightBtn,&QPushButton::clicked,this,&AdminMainWindow::AddFlightBtnClicked);
}

void AdminMainWindow::updateTime()
{
    QTime currentTime = QTime::currentTime();
    QString timeText = currentTime.toString("HH:mm:ss");
    ui->TimeLabel->setText(QString("<font color='black'>%1</font>").arg(timeText));
}

void AdminMainWindow::AddFlightBtnClicked(){
    AddFlightDialog *addflightdialog = new AddFlightDialog();
    addflightdialog->setModal(true); // 设置为模态窗口
    addflightdialog->exec(); // 显示窗口并阻止与其他窗口的交互
}

AdminMainWindow::~AdminMainWindow()
{
    delete ui;
}
