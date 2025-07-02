#include "flight.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
using namespace std;


Flight::Flight(QString fid,QString sp,QString ep,QDateTime st,QDateTime et,double p,int numsofseats):Flightid(fid),Startpoint(sp),Endpoint(ep),Starttime(st),Endtime(et),Price(p),Numofseats(numsofseats){}

vector<Flight> Flight::Filtres(QString startpoint,QString endpoint){
    // 实现给定起点终点的航班查找，返回一个类型为Flight的vector数组
    // 循环将数据库中信息赋值给vector中每个flight对象
    vector<Flight> list;
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    QString sql="select * from planes_list where departure='"+startpoint+"'&& destination='"+endpoint+"'";
    q.exec(sql);

    while(q.next()){
        QString id=q.value("id").toString();
        QString sp=q.value("departure").toString();
        QString ep=q.value("destination").toString();
        QDateTime st=q.value("d_time").toDateTime();
        QDateTime et=q.value("l_time").toDateTime();
        double p= q.value("price").toDouble();
        int c=q.value("capacity").toInt();
        Flight f(id,sp,ep,st,et,p,c);
        list.push_back(f);
    }
    db.close();
    return list;

}

Flight Flight::Seekres(QString flightid){
    // 实现给定编号的航班查找，返回该航班对象
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    QString sql="select * from planes_list where id='"+flightid+"'";
    QString id="null";
    QString sp="null";
    QString ep="null";
    QDateTime st(QDateTime::currentDateTime());
    QDateTime et(QDateTime::currentDateTime());
    double p=0;
    int c=0;
    q.exec(sql);
    while(q.next()){
        id=q.value("id").toString();
        sp=q.value("departure").toString();
        ep=q.value("destination").toString();
        st=q.value("d_time").toDateTime();
        et=q.value("l_time").toDateTime();
        p = q.value("price").toDouble();
        c =q.value("capacity").toInt();

    }
    // 需从数据库中导入该航班信息并逐个赋值给flight
    Flight flight(id,sp,ep,st,et,p,c);
    return flight;
}

void Flight::setTime(QDateTime& start,QDateTime& end){
    // 实现航班时间的修改
    Starttime = start;
    Endtime = end;
    // 数据库中更改对应航班的时间
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    if(q.exec("select * from planes_list where id='"+Flightid+"'")){
        if(!q.next()){return ;}
    }
    QString sql="update planes_list set d_time=:d_time, l_time=:l_time where id='"+Flightid+"' ";
    db.transaction();
    q.prepare(sql);
    q.bindValue(":d_time",start);
    q.bindValue(":l_time",end);
    if(q.exec()){
        db.commit();
    }else{
        db.rollback();
    }
    db.close();
}

void Flight::setPrice(double price){
    // 实现航班票价的修改
    Price = price;
    // 数据库中更改对应航班的票价
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    if(q.exec("select * from planes_list where id='"+Flightid+"'")){
        if(!q.next()){return ;}
    }
    QString sql="update planes_list set price=:price where id='"+Flightid+"' ";
    q.prepare(sql);
    q.bindValue(":price",price);
    if(q.exec()){
        db.commit();
    }else{
        db.rollback();
    }
    db.close();
}

vector<QString>& Flight:: getPassengers(){
    if(Passengers.empty()){
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
        QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
        db.setHostName("127.0.0.1");
        db.setUserName("root");
        db.setDatabaseName("mydb");
        db.setPassword("root");
        db.setPort(3306);
        db.open();
        QSqlQuery q;
        q.prepare(QString("select account from %1").arg(this->Flightid));
        q.exec();
        while(q.next()){
            Passengers.push_back(q.value("account").toString());
        }
        db.close();
    }
    // 实现查看该航班乘客的信息，返回一个类型为QString的vector数组
    return Passengers;
}

bool Flight::addPassenger(const QString account,int seat){
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QString fid=this->Flightid;
    QSqlQuery q;
    int gender=-1,age=-1;
    q.exec("select gender,age from user where account='"+account+"'");
    while(q.next()){
        gender=q.value("gender").toInt();
        age=q.value("age").toInt();
    }
    q.prepare(QString("INSERT INTO %1 (account, gender, age, seat) VALUES (:account, :gender, :age, :seat)").arg(fid));
    q.bindValue(":account",account);
    q.bindValue(":gender",gender);
    q.bindValue(":age",age);
    q.bindValue(":seat",seat);
    q.executedQuery();
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

void Flight::deletePassenger(const QString account){
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    QString fid=this->Flightid;
    q.prepare(QString("delete from %1 where account='"+account+"'").arg(fid));
    db.transaction();
    if(q.exec()){
        db.commit();
    }else{
        db.rollback();
    }
    db.close();

}

QString Flight::getFlightid(){
    return Flightid;
}

QString Flight::getStartpoint(){
    return Startpoint;
}

QString Flight::getEndpoint(){
    return Endpoint;
}

QDateTime& Flight::getStarttime(){
    return Starttime;
}

QDateTime& Flight::getEndtime(){
    return Endtime;
}

double Flight::getPrice(){
    return Price;
}

int Flight::getNum(){
    return Numofseats;
}

