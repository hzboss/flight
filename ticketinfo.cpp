#include "ticketinfo.h"
#include "ui_ticketinfo.h"
#include "user.h"
#include "flight.h"
#include <QMessageBox>

TicketInfo::TicketInfo(Ticket& ticket,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TicketInfo)
{
    ui->setupUi(this);
    QImage image = QImage(":/photosources/ft1.jpeg");
    QSize labelSize = ui->label_8->size();
    QPixmap scaledPixmap = QPixmap::fromImage(image).scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_8->setPixmap(scaledPixmap);
    ui->StartPoint->setText(ticket.getSp());
    ui->EndPoint->setText(ticket.getEp());
    ui->FlightId->setText(ticket.getFid());
    ui->StartTime->setDateTime(ticket.getSt());
    ui->EndTime->setDateTime(ticket.getEt());
    QString useraccount = ticket.getOAcc();
    if(ticket.getSt() < QDateTime::currentDateTime()){
        ui->RefundTicketBtn->setEnabled(false);
        ui->StateLabel->setText("订单已结束");
        ui->StateLabel->setStyleSheet("color: gray;");
    }else{
        ui->StateLabel->setText("待起飞");
        ui->StateLabel->setStyleSheet("color: blue;");
    }
    qint64 secondsDifference = ticket.getSt().secsTo(ticket.getEt());
    double hoursDifference = secondsDifference / 3600.0;
    ui->FlyTime->setText(QString::number(hoursDifference, 'f', 2));
    // 对传来的Seatid进行处理后写入SeatIdLine
    int sid = ticket.getSid();
    QString seatid;
    if(sid % 6 == 1){
        seatid = QString::number(sid / 6) + "A";
    }else if(sid % 6 == 2){
        seatid = QString::number(sid / 6) + "B";
    }else if(sid % 6 == 3){
        seatid = QString::number(sid / 6) + "C";
    }else if(sid % 6 == 4){
        seatid = QString::number(sid / 6) + "D";
    }else if(sid % 6 == 5){
        seatid = QString::number(sid / 6) + "E";
    }else if(sid % 6 == 0){
        seatid = QString::number(sid / 6) + "F";
    }
    ui->SeatIdLine->setText(seatid);
    connect(ui->RefundTicketBtn,&QPushButton::clicked,[this,useraccount](){
        QString flightid = ui->FlightId->text();
        Flight flight = Flight::Seekres(flightid);
        flight.deletePassenger(useraccount);
        User* user = new User(useraccount);
        user->RefundTicket(flightid);  //这里因为创建了临时flight对象，所以可以进行deletePassenger函数。
        //注意：因为flight是临时变量，所以其实对他的乘客pop和push没有意义，只需在数据库里进行删除添加，所以已经全部注释掉了，也避免的因为push和pop带来的访问空对象的问题
        QMessageBox::information(nullptr, "提示", "退票成功");
    });
}

TicketInfo::~TicketInfo()
{
    delete ui;
}
