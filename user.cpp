#include "user.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QVector>
#include <QDateTime>

User::User(QString account):Account(account){
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    q.exec("select * from user where account='"+account+"'");
    while(q.next()){
        this->Age=q.value("age").toInt();
        this->Gender=q.value("gender").toInt();
        QString jsonString = q.value("seat").toString();
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8(), &parseError); //把解析出来的json字符串转换成utf8编码，才能实现对象转换。
        QJsonObject seats=jsonDoc.object();
        for(auto i=seats.begin();i!=seats.end();i++){
            QString fid=i.key();
            int sid = i.value().toString().toInt();
            QString sp;
            QString ep;
            QDateTime st;
            QDateTime et;
            QSqlQuery q1;
            q1.exec("select * from planes_list where id='"+fid+"'");
            while(q1.next()){
                sp=q1.value("departure").toString();
                ep=q1.value("destination").toString();
                st=q1.value("d_time").toDateTime();
                et=q1.value("l_time").toDateTime();
            }
            Tickets.push_back(Ticket(fid,sp,ep,st,et,sid,this->Account));
        }
    }

    // 从数据库中导入相应的票务信息构成完整的User类，即User.tickets = ...
}

void User::BuyTicket(QString fid,QString sp,QString ep,QDateTime st,QDateTime et,int sid){
    // 更新数据库用户表中的Tickets数组
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    q.prepare(QString("update user set seat=json_insert(coalesce(seat,'{}'),'$.%1',:sid) where account='"+Account+"'").arg(fid));
    q.executedQuery();
    q.bindValue(":sid",sid);
    db.transaction();
    int exist = 0;
    if(q.exec()){
        db.commit();
    }else{
        db.rollback();
        QMessageBox::information(nullptr, "提示", "购票失败");
    }
    db.close();
}

void User::RefundTicket(QString fid){
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    q.prepare(QString("update user set seat = json_remove(seat,'$.%1') where account='"+this->Account+"'").arg(fid));
    db.transaction();
    q.executedQuery();
    if(q.exec()){
        db.commit();
        qDebug() << Account << "退票" << fid;
    }else{
        db.rollback();
    }
    db.close();
}

std::vector<Ticket> & User::getTickets(){
    return Tickets;
}

QString User::getAccount(){
    return Account;
}

int User::getcurflightsid(QString fid){
    for(int i = 0;i < Tickets.size();i++){
        if(Tickets[i].getFid() == fid){
            return Tickets[i].getSid();
        }
    }
    return 10000;
}

int User::getAge(){
    return Age;
}
int User::getGender(){
    return Gender;
}
