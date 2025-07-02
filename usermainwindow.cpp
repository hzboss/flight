#include "usermainwindow.h"
#include "ui_usermainwindow.h"
#include <QStackedWidget>
#include <QToolBar>
#include "myorderwindow.h"
#include "userhomepage.h"
#include <QMessageBox>

UserMainWindow::UserMainWindow(User &user, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("用户主界面");
    QIcon icon = QIcon(":/photosources/mainwindow.jpg");
    this->setWindowIcon(icon);

    // 创建QStackedWidget并设置到中央部件
    QStackedWidget *stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // 创建首页和我的订单页面
    UserHomePage *homePage = new UserHomePage(user, this);
    MyOrderWindow *myOrdersPage = new MyOrderWindow(user, this);

    // 将页面添加到堆栈中
    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(myOrdersPage);

    // 创建工具栏并添加动作
    QToolBar *toolBar = addToolBar("MainToolbar");
    //toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // 可选：设置工具按钮的样式
    QAction *homeAction = toolBar->addAction("首页");
    QAction *myOrdersAction = toolBar->addAction("我的订单");

    // 添加切换账户和退出系统按钮
    QAction *switchAccountAction = toolBar->addAction("切换账户");
    QAction *exitAction = toolBar->addAction("退出系统");

    // 将切换账户和退出系统按钮移动到工具栏右侧（使用addWidget添加分隔符和动作）
    QWidget *spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    toolBar->addWidget(spacer);
    toolBar->addAction(switchAccountAction);
    toolBar->addAction(exitAction);

    // 为工具栏设置样式表
    QString toolBarStyleSheet = R"(
QToolBar {
            background-color: #4A90E2;
            border: 1px solid #377BD8;
            padding: 5px;
            font-size: 14px;
            spacing: 10px;
        }

        QToolBar::handle {
            width: 5px;
            background: #377BD8;
        }

        QToolBar::separator {
            width: 2px;
            margin: 3px 4px;
            background: #377BD8;
        }

        QToolButton {
            background-color: transparent;
            border: none;
            padding: 5px;
            color: white;
        }

        QToolButton:hover {
            background-color: #5DADE2;
        }

        QToolButton:checked {
            background-color: #377BD8;
        }

        QAction {
            color: white;
        }
    )";
    toolBar->setStyleSheet(toolBarStyleSheet);

    // 连接动作到槽
    connect(homeAction, &QAction::triggered, [stackedWidget]() {
        stackedWidget->setCurrentIndex(0); // 切换到首页
    });
    connect(myOrdersAction, &QAction::triggered, [stackedWidget]() {
        stackedWidget->setCurrentIndex(1); // 切换到我的订单
    });
    connect(switchAccountAction, &QAction::triggered, this, &UserMainWindow::onSwitchAccount);
    connect(exitAction, &QAction::triggered, this, &UserMainWindow::onExit);

    stackedWidget->setCurrentIndex(0); // 默认显示首页

    std::vector<Ticket> tickets = user.getTickets();
    int judge = 0;
    QString waittofly;
    for(size_t i = 0;i < tickets.size();i++){
        qint64 secondsDifference = tickets[i].getSt().secsTo(QDateTime::currentDateTime());
        if(secondsDifference <= 12*3600){
            judge = 1;
            waittofly+=tickets[i].getFid();
            waittofly+=" ";
        }
    }
    if(judge == 1){
        QMessageBox::information(this,"提醒","您购买的的航班号为 "+waittofly+"的航班将于12小时内起飞，请注意时间");
    }
}

// 槽函数：处理切换账户逻辑
void UserMainWindow::onSwitchAccount() {
    this->close();
    UserLogin *usl = new UserLogin();
    usl->exec();
}

// 槽函数：处理退出系统逻辑
void UserMainWindow::onExit() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "退出系统",
                                  "你确定要退出系统吗?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        this->close();
    }
}

UserMainWindow::~UserMainWindow()
{
    delete ui;
}
