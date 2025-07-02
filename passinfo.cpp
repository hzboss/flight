#include "passinfo.h"
#include "ui_passinfo.h"

PassInfo::PassInfo(User* user,QString fid,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PassInfo)
{
    ui->setupUi(this);
    ui->AccountLine->setText(user->getAccount());
    int gender = user->getGender();
    if(gender == 1){
        ui->GenderLine->setText("男");
    }else{
        ui->GenderLine->setText("女");
    }
    ui->AgeLine->setText(QString::number(user->getAge()));
    int sid = user->getcurflightsid(fid);
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
}

PassInfo::~PassInfo()
{
    delete ui;
}
