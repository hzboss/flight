#include "myorderwindow.h"
#include "ui_myorderwindow.h"
#include "ticketinfo.h"

MyOrderWindow::MyOrderWindow(User&user,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyOrderWindow)
{
    ui->setupUi(this);
    QWidget *contentWidget = ui->TicketShowArea->widget();
    if (!contentWidget) {
        // 如果没有内容窗口，则创建一个新的
        contentWidget = new QWidget(ui->TicketShowArea);
        ui->TicketShowArea->setWidget(contentWidget);
    }
    QLayout *existingLayout = contentWidget->layout();
    if (existingLayout) {
        while (QLayoutItem *item = existingLayout->takeAt(0)) {
            delete item->widget(); // 删除小部件
            delete item; // 删除布局项
        }
        delete existingLayout; // 删除布局
    }
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);
    std::vector<Ticket> tickets = user.getTickets();
    for(size_t i = 0;i < tickets.size();i++){
        Ticket ticket(tickets[i].getFid(),tickets[i].getSp(),tickets[i].getEp(),tickets[i].getSt(),tickets[i].getEt(),tickets[i].getSid(),user.getAccount());
        TicketInfo* ticketinfo = new TicketInfo(ticket,this);
        layout->addWidget(ticketinfo);
    }
    contentWidget->setLayout(layout);
    connect(ui->RefreshBtn,&QPushButton::clicked,[this,&user](){
        User curuser = User(user.getAccount());
        QWidget *contentWidget = ui->TicketShowArea->widget();
        if (!contentWidget) {
            // 如果没有内容窗口，则创建一个新的
            contentWidget = new QWidget(ui->TicketShowArea);
            ui->TicketShowArea->setWidget(contentWidget);
        }
        QLayout *existingLayout = contentWidget->layout();
        if (existingLayout) {
            while (QLayoutItem *item = existingLayout->takeAt(0)) {
                delete item->widget(); // 删除小部件
                delete item; // 删除布局项
            }
            delete existingLayout; // 删除布局
        }
        QVBoxLayout *layout = new QVBoxLayout(contentWidget);
        std::vector<Ticket> tickets = curuser.getTickets();
        for(size_t i = 0;i < tickets.size();i++){
            Ticket ticket(tickets[i].getFid(),tickets[i].getSp(),tickets[i].getEp(),tickets[i].getSt(),tickets[i].getEt(),tickets[i].getSid(),user.getAccount());
            TicketInfo* ticketinfo = new TicketInfo(ticket,this);
            layout->addWidget(ticketinfo);
        }
        contentWidget->setLayout(layout);
    });
}

MyOrderWindow::~MyOrderWindow()
{
    delete ui;
}
