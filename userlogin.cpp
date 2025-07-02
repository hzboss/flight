#include "userlogin.h"
#include "ui_userlogin.h"
#include <QDebug>
#include <QMessageBox>
#include "loginwindow.h"

UserLogin::UserLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserLogin)
{
    ui->setupUi(this);
    setWindowTitle("用户登录");
    setFixedSize(350,250);
    QIcon icon = QIcon(":/photosources/login2.jpg");
    this->setWindowIcon(icon);

    QIcon eyeicon1 = QIcon(":/photosources/password1.jpg");
    QIcon eyeicon2 = QIcon(":/photosources/password2.jpg");
    ui->EyeBtn->setIcon(eyeicon2);
    connect(ui->EyeBtn,&QPushButton::clicked,[this,eyeicon1,eyeicon2](){
        if(ui->UserPassLine->echoMode() == QLineEdit::Password){
            ui->UserPassLine->setEchoMode(QLineEdit::Normal);
            ui->EyeBtn->setIcon(eyeicon1);
        }else{
            ui->UserPassLine->setEchoMode(QLineEdit::Password);
            ui->EyeBtn->setIcon(eyeicon2);
        }
    });

    ur = new UserRe(this);

    connect(ui->UserReBtn,&QPushButton::clicked,ur,&UserRe::createURwindow);
    connect(ui->UserisLoginBtn,&QPushButton::clicked,[this](){
        QString UserAcc = ui->UserAccLine->text();
        QString UserPass = ui->UserPassLine->text();
        if(UserAcc.isEmpty()||UserPass.isEmpty()){
            QMessageBox::warning(this, "Warning", "账号或密码不能为空！");
            return;
        }
        bool LoginSuccess = UserSeekInfo(UserAcc,UserPass);
        if(LoginSuccess){
            QMessageBox::information(nullptr, "提示", "已成功登录");
            this->accept();
            User* curuser = new User(UserAcc);
            createUMwindow(*curuser);
        }else{
            QMessageBox::warning(this, "Warning", "账号或密码错误！");
        }
    });
}

void UserLogin::createUMwindow(User& user){
    UserMainWindow *umw = new UserMainWindow(user);
    umw->show();
}

bool UserLogin::UserSeekInfo(QString& Account,QString& Password){
    //在用户数据库中查找有无对应信息，有则返回true，无则返回false
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    QString sql="select * from user where Account='"+Account+"'&& Password='"+Password+"'";
    q.exec(sql);
    if(!q.next()){
        db.close();
        return false;
    }
    db.close();
    return true;
}

UserLogin::~UserLogin()
{
    delete ui;
}
