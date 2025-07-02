#include "userhomepage.h"
#include "ui_userhomepage.h"
#include "flight.h"
#include "userflightinfo.h"
#include <QTime>

UserHomePage::UserHomePage(User& user,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserHomePage)
{
    ui->setupUi(this);
    connect(ui->ReverseBtn,&QPushButton::clicked,[this](){
        QString start = ui->StartPointLine->text();
        QString end = ui->EndPointLine->text();
        ui->StartPointLine->setText(end);
        ui->EndPointLine->setText(start);
    });
    QTimer *timer;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &UserHomePage::updateTime);
    timer->start(1000);
    updateTime();

    connect(ui->SeekBtn,&QPushButton::clicked,[this,&user](){
        // 显示给定编号航班信息
        QString id = ui->SeekLine->text();
        Flight target = Flight::Seekres(id);
        QWidget *contentWidget = ui->UserShowFlightArea->widget();
        if (!contentWidget) {
            contentWidget = new QWidget();
            ui->UserShowFlightArea->setWidget(contentWidget);
        }
        QLayout *existingLayout = contentWidget->layout();
        if (existingLayout) {
            while (QLayoutItem *item = existingLayout->takeAt(0)) {
                delete item->widget(); // 删除小部件（如果它存在）
                delete item; // 删除布局项
            }
            delete existingLayout; // 删除旧布局
        }
        if(target.getFlightid()=="null"){
            return;
        }
        QVBoxLayout *layout = new QVBoxLayout(contentWidget);
        UserFlightInfo* flight = new UserFlightInfo(target,user,this);
        layout->addWidget(flight);
    });
    connect(ui->FilterBtn, &QPushButton::clicked, [this, &user](){
        QString start = ui->StartPointLine->text();
        QString end = ui->EndPointLine->text();
        std::vector<Flight> targets = Flight::Filtres(start, end);
        QWidget *contentWidget = ui->UserShowFlightArea->widget();
        if (!contentWidget) {
            contentWidget = new QWidget();
            ui->UserShowFlightArea->setWidget(contentWidget);
        }
        QLayout *existingLayout = contentWidget->layout();
        if (existingLayout) {
            while (QLayoutItem *item = existingLayout->takeAt(0)) {
                delete item->widget(); // 删除小部件（如果它存在）
                delete item; // 删除布局项
            }
            delete existingLayout; // 删除旧布局
        }

        // 为内容窗口创建新的QVBoxLayout
        QVBoxLayout *layout = new QVBoxLayout(contentWidget);

        // 遍历过滤后的航班信息，为每个航班创建UserFlightInfo小部件，并将其添加到布局中
        for (size_t i = 0; i < targets.size(); ++i) {
            UserFlightInfo *flight = new UserFlightInfo(targets[i], user, this);
            layout->addWidget(flight);
        }
    });
}

void UserHomePage::updateTime()
{
    QTime currentTime = QTime::currentTime();
    QString timeText = currentTime.toString("HH:mm:ss");
    ui->TimeLabel->setText(QString("<font color='black'>%1</font>").arg(timeText));
}

UserHomePage::~UserHomePage()
{
    delete ui;
}
