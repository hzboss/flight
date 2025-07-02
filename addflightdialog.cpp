#include "addflightdialog.h"
#include "ui_addflightdialog.h"
#include <QMessageBox>

AddFlightDialog::AddFlightDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddFlightDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("新航班信息录入");
    QIcon icon = QIcon(":/photosources/addflight.jpeg");
    this->setWindowIcon(icon);
    connect(ui->DeterminBtn,&QPushButton::clicked,[this](){
        QString nfid = ui->NewFlightIdLine->text();
        QString nsp = ui->NewStartPointLine->text();
        QString nep = ui->NewEndPointLine->text();
        QDateTime nst = ui->NewStartTimeLine->dateTime();
        QDateTime net = ui->NewEndTimeLine->dateTime();
        QDateTime curtime = QDateTime::currentDateTime();
        double np = ui->NewPriceLine->value();
        int nos = ui->NumOfSeatsLine->value();
        if(nfid.isEmpty() || nsp.isEmpty() || nep.isEmpty() || nst.isNull() || net.isNull()){
            QMessageBox::warning(this, "Warning", "航班编号等信息不能为空！");
            return;
        }else if(np == 0 || nos == 0){
            QMessageBox::warning(this, "Warning", "票价或座位数不能为零！");
            return;
        }else if(nst >= net || nst <= curtime || net <= curtime){
            QMessageBox::warning(this, "Warning", "时间更改错误！");
        }else{
            Flight newflight = Flight(nfid,nsp,nep,nst,net,np,nos);
            Admin tempadmin = Admin();
            bool success = tempadmin.addPlane(newflight);
            if(success){
                QMessageBox::information(nullptr, "提示", "已添加该航班");
            }
            this->accept();
        }
    });
    connect(ui->CancelBtn,&QPushButton::clicked,this,&QDialog::close);
}

AddFlightDialog::~AddFlightDialog()
{
    delete ui;
}
