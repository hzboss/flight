#include "userflightinfo.h"
#include "ui_userflightinfo.h"
#include <QMessageBox>
#include <QTimer>

UserFlightInfo::UserFlightInfo(Flight& flight,User& user,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserFlightInfo)
{
    ui->setupUi(this);
    ui->FlightId->setText(flight.getFlightid());
    ui->StartPoint->setText(flight.getStartpoint());
    ui->EndPoint->setText(flight.getEndpoint());
    ui->StartTime->setDateTime(flight.getStarttime());
    ui->EndTime->setDateTime(flight.getEndtime());
    qint64 secondsDifference = flight.getStarttime().secsTo(flight.getEndtime());
    double hoursDifference = secondsDifference / 3600.0;
    ui->FlyTime->setText(QString::number(hoursDifference, 'f', 2));
    ui->PriceLine->setText(QString::number(flight.getPrice()));
    ui->RemainSeatsNum->setText(QString::number(flight.getNum()-flight.getPassengers().size()));
    int reseats = flight.getNum()-flight.getPassengers().size();
    QTimer *timer;
    QDateTime starttime = ui->StartTime->dateTime();
    QDateTime endtime = ui->EndTime->dateTime();
    if(reseats == 0){
        ui->BuyTicketBtn->setEnabled(false);
    }
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,[this,starttime,endtime,reseats](){
        QDateTime curtime = QDateTime::currentDateTime();
        if(curtime > starttime && curtime < endtime){
            ui->StateLabel->setText("飞行中");
            ui->StateLabel->setStyleSheet("color: green;");
        }else if(curtime < starttime){
            ui->StateLabel->setText("待起飞");
            ui->StateLabel->setStyleSheet("color: blue;");
        }else{
            ui->StateLabel->setText("暂不开放售票");
            ui->StateLabel->setStyleSheet("color: gray;");
        }
        if(ui->StateLabel->text() != "待起飞"){
            ui->BuyTicketBtn->setEnabled(false);
        }
        if(reseats == 0){
            ui->StateLabel->setText("售罄");
            ui->StateLabel->setStyleSheet("color: gray;");
        }

    });
    timer->start(1000);
    QImage image = QImage(":/photosources/ft1.jpeg");
    QSize labelSize = ui->ImageLabel->size();
    QPixmap scaledPixmap = QPixmap::fromImage(image).scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->ImageLabel->setPixmap(scaledPixmap);
    connect(ui->BuyTicketBtn, &QPushButton::clicked, [this, &user,reseats]() {
            QString flightid = ui->FlightId->text();
            QString sp = ui->StartPoint->text();
            QString ep = ui->EndPoint->text();
            QDateTime st = ui->StartTime->dateTime();
            QDateTime et = ui->EndTime->dateTime();
            int sid = 0;
            Flight f = Flight::Seekres(flightid);
            std::vector<int> seats(1000,0);
            std::vector<QString> passengers = f.getPassengers();
            for(auto passenger : passengers){
                User *curuser = new User(passenger);
                int notnull = curuser->getcurflightsid(flightid);
                seats[notnull] = 1;
                delete curuser;
            }
            for(int i = 1;i <= f.getNum();i++){
                if(seats[i] == 0){
                    sid = i;
                    break;
                }
            }
            if (!flightid.isEmpty() && !sp.isEmpty() && !ep.isEmpty()) {
                user.BuyTicket(flightid, sp, ep, st, et, sid);
                QString useraccount = user.getAccount();
                if(f.addPassenger(useraccount,sid)){
                    ui->RemainSeatsNum->setText(QString::number(reseats-1));
                    QMessageBox::information(nullptr, "提示", "购票成功");
                }else{
                    QMessageBox::information(nullptr, "提示", "无法购买两张票");
                }
            }
    });
}

UserFlightInfo::~UserFlightInfo()
{
    delete ui;
}
