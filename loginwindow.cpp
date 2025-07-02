#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "adminlogin.h"
#include "userlogin.h"
#include <QDebug>
#include "adminmainwindow.h"
#include "usermainwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
    , amw(nullptr)
    , umw(nullptr)
{
    ui->setupUi(this);
    setFixedSize(400,300); // 固定窗口大小
    QIcon mainloginicon = QIcon(":/photosources/login1.jpeg");
    this->setWindowIcon(mainloginicon);
    QIcon userlogicon = QIcon(":/photosources/userlogin.jpeg");
    ui->UserLoginBtn->setIcon(userlogicon);
    QIcon adminlogicon = QIcon(":/photosources/adminlogin.jpg");
    ui->AdminLoginBtn->setIcon(adminlogicon);
    ui->UserLoginBtn->setMinimumSize(80,60);
    ui->AdminLoginBtn->setMinimumSize(80,60); // 固定按钮大小

    connect(ui->UserLoginBtn,&QPushButton::clicked,this,&LoginWindow::createULwindow);
    connect(ui->AdminLoginBtn,&QPushButton::clicked,this,&LoginWindow::createALwindow); // 连接跳出对应登录窗口的函数
}

void LoginWindow::createALwindow(){
    this->hide();
    AdminLogin *adl = new AdminLogin();
    adl->exec();
}

void LoginWindow::createULwindow(){
    this->hide();
    UserLogin *usl = new UserLogin();
    usl->exec();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
