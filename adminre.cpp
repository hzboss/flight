#include "adminre.h"
#include "ui_adminre.h"
#include <QDebug>
#include <QMessageBox>

AdminRe::AdminRe(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AdminRe)
{
    ui->setupUi(this);

    setWindowTitle("管理员注册");

    setFixedSize(350,300);
    QIcon icon = QIcon(":/photosources/rg.jpeg");
    this->setWindowIcon(icon);

    QIcon eyeicon1 = QIcon(":/photosources/password1.jpg");
    QIcon eyeicon2 = QIcon(":/photosources/password2.jpg");
    ui->EyeBtn1->setIcon(eyeicon2);
    ui->EyeBtn2->setIcon(eyeicon2);
    connect(ui->EyeBtn1,&QPushButton::clicked,[this,eyeicon1,eyeicon2](){
        if(ui->AdminPassLine->echoMode() == QLineEdit::Password){
            ui->AdminPassLine->setEchoMode(QLineEdit::Normal);
            ui->EyeBtn1->setIcon(eyeicon1);
        }else{
            ui->AdminPassLine->setEchoMode(QLineEdit::Password);
            ui->EyeBtn1->setIcon(eyeicon2);
        }
    });
    connect(ui->EyeBtn2,&QPushButton::clicked,[this,eyeicon1,eyeicon2](){
        if(ui->AdminDePassLine->echoMode() == QLineEdit::Password){
            ui->AdminDePassLine->setEchoMode(QLineEdit::Normal);
            ui->EyeBtn2->setIcon(eyeicon1);
        }else{
            ui->AdminDePassLine->setEchoMode(QLineEdit::Password);
            ui->EyeBtn2->setIcon(eyeicon2);
        }
    });

    connect(ui->AdminisReBtn,&QPushButton::clicked,[this](){
        QString AdminAcc = ui->AdminAccLine->text();
        QString AdminPass = ui->AdminPassLine->text();
        QString AdminDePass = ui->AdminDePassLine->text();
        QString InRegCode = ui->InRegCodeLine->text();
        QString RegCode = "123456";
        if(AdminAcc.isEmpty()||AdminPass.isEmpty()){
            QMessageBox::warning(this, "Warning", "账号或密码不能为空！");
            return;
        }
        if(AdminPass!=AdminDePass){
            QMessageBox::warning(this,"Warning","两次输入密码不同，请检查后重新输入！");
            return;
        }
        if(InRegCode!=RegCode){
            QMessageBox::warning(this,"Warning","注册码不正确，请检查后重新输入！");
            return;
        }
        // 向管理员数据库中录入新成员信息，已存在则注册失败
        bool addsuccess = addAdminAccount(AdminAcc,AdminPass);
        if(addsuccess){
            QMessageBox::information(nullptr, "提示", "已成功注册");
            this->accept();
        }else{
            QMessageBox::warning(this,"Warning","注册失败！");
            return;
        }
    });
}

void AdminRe::createARwindow(){
    AdminRe *adr = new AdminRe();
    adr->exec();
}

bool AdminRe::addAdminAccount(QString& Account,QString& Password){
    //录入管理员信息
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    QString sql="insert into admin values('"+Account+"','"+Password+"') ";
    db.transaction();
    if(q.exec(sql)){
        db.commit();
    }else{
        db.rollback();
        db.close();
        return false;
    }
    db.close();
    return true;
}

AdminRe::~AdminRe()
{
    delete ui;
}
