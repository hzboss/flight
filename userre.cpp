#include "userre.h"
#include "ui_userre.h"
#include <QDebug>
#include <QMessageBox>

UserRe::UserRe(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserRe)
{
    ui->setupUi(this);

    setWindowTitle("用户注册");
    setFixedSize(350,350);
    QIcon icon = QIcon(":/photosources/rg.jpeg");
    this->setWindowIcon(icon);

    QIcon eyeicon1 = QIcon(":/photosources/password1.jpg");
    QIcon eyeicon2 = QIcon(":/photosources/password2.jpg");
    ui->EyeBtn1->setIcon(eyeicon2);
    ui->EyeBtn2->setIcon(eyeicon2);
    connect(ui->EyeBtn1,&QPushButton::clicked,[this,eyeicon1,eyeicon2](){
        if(ui->UserPassLine->echoMode() == QLineEdit::Password){
            ui->UserPassLine->setEchoMode(QLineEdit::Normal);
            ui->EyeBtn1->setIcon(eyeicon1);
        }else{
            ui->UserPassLine->setEchoMode(QLineEdit::Password);
            ui->EyeBtn1->setIcon(eyeicon2);
        }
    });
    connect(ui->EyeBtn2,&QPushButton::clicked,[this,eyeicon1,eyeicon2](){
        if(ui->UserDePassLine->echoMode() == QLineEdit::Password){
            ui->UserDePassLine->setEchoMode(QLineEdit::Normal);
            ui->EyeBtn2->setIcon(eyeicon1);
        }else{
            ui->UserDePassLine->setEchoMode(QLineEdit::Password);
            ui->EyeBtn2->setIcon(eyeicon2);
        }
    });
    connect(ui->UserisReBtn,&QPushButton::clicked,[this](){
        QString UserAcc = ui->UserAccLine->text();
        QString UserPass = ui->UserPassLine->text();
        QString UserDePass = ui->UserDePassLine->text();
        QString Gender = ui->GenderBox->currentText();
        int UserAge = ui->AgeBox->value();
        if(UserAcc.isEmpty()||UserPass.isEmpty()){
            QMessageBox::warning(this, "Warning", "账号或密码不能为空！");
            return;
        }
        if(UserPass!=UserDePass){
            QMessageBox::warning(this,"Warning","两次输入密码不同，请检查后重新输入！");
            return;
        }
        // 向用户数据库中录入新成员信息，已存在则注册失败
        int UserGender = 100;
        if(Gender == "男"){
            UserGender = 1;
        }else{
            UserGender = 0;
        }
        bool addsuccess = addUserAccount(UserAcc,UserGender,UserAge,UserPass);
        if(addsuccess){
            QMessageBox::information(nullptr, "提示", "已成功注册");
            this->accept();
        }else{
            QMessageBox::warning(this,"Warning","注册失败！");
        }
    });
}

void UserRe::createURwindow(){
    UserRe *usr = new UserRe();
    usr->exec();
}

bool UserRe::addUserAccount(QString& Account,int Gender,int Age,QString& Password){
    //录入用户信息
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    QString sql="insert into user(account,password,gender,age)  values('"+Account+"','"+Password+"',:gender,:age) ";
    q.prepare(sql);
    q.bindValue(":gender",Gender);
    q.bindValue(":age",Age);
    db.transaction();
    if(q.exec()){
        db.commit();
    }else{
        db.rollback();
        db.close();
        return false;
    }
    db.close();
    return true;
}

UserRe::~UserRe()
{
    delete ui;
}
