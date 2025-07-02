#include "admin.h"
#include <QMessageBox>

Admin::Admin() {}
bool Admin:: addPlane(Flight& flight){
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    QString sql="insert into planes_list (id,capacity,departure,destination,price,d_time,l_time) values(:fid,:capacity,:dept,:des,:price,:d_time,:l_time)";
    q.prepare(sql);
    q.bindValue(":fid",flight.getFlightid());
    q.bindValue(":capacity",flight.getNum());
    q.bindValue(":dept",flight.getStartpoint());
    q.bindValue(":des",flight.getEndpoint());
    q.bindValue(":price",flight.getPrice());
    q.bindValue(":d_time",flight.getStarttime());
    q.bindValue(":l_time",flight.getEndtime());
    db.transaction();
    if(q.exec()){
        db.commit();
    }else{
        db.rollback();
        qDebug()<<db.lastError().text();
        db.close();
        QMessageBox::warning(nullptr,"Warning","录入失败！");
        return false;
    }
    QSqlQuery q1;
    q1.prepare(QString("create table %1 (account varchar(45) primary key, gender int, age int, seat int)").arg(flight.getFlightid()));
    if(q1.exec()){
        // qDebug()<<"创建航班表成功";
    }else{
        qDebug()<<db.lastError().text();
        db.close();
        return false;
    }
    return true;
}

bool Admin::deletePlane(QString id){
    QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setDatabaseName("mydb");
    db.setPassword("root");
    db.setPort(3306);
    db.open();
    QSqlQuery q;
    QString sql="delete from mydb.planes_list where id='"+id+"' ";
    db.transaction();
    if(q.exec(sql)){
        db.commit();
        // qDebug()<<"删除航班成功";
    }else{
        db.rollback();
        db.close();
        return false;
    }
    QSqlQuery q1;
    q1.prepare(QString("drop table %1").arg(id));
    if(q1.exec()){
        // qDebug()<<"删除航班表成功";
    }else{
        return false;
    }
    db.close();
    return true;
}
