#ifndef FLIGHT_H
#define FLIGHT_H
#include <QString>
#include <QDateTime>
#include "user.h"


class Flight
{
public:
    Flight(QString fid,QString sp,QString ep,QDateTime st,QDateTime et,double p,int numsofseats);
    static std::vector<Flight> Filtres(QString startpoint,QString endpoint);
    static Flight Seekres(QString flightid);
    void setTime(QDateTime& start,QDateTime& end);
    void setPrice(double price);
    bool addPassenger(const QString useraccount,int sid);
    void deletePassenger(const QString useraccount);
    std::vector<QString>& getPassengers();
    QString getFlightid();
    QString getStartpoint();
    QString getEndpoint();
    QDateTime& getStarttime();
    QDateTime& getEndtime();
    double getPrice();
    int getNum();
    ~Flight(){}

private:
    QString Flightid;
    QString Startpoint;
    QString Endpoint;
    QDateTime Starttime;
    QDateTime Endtime;
    double Price;
    int Numofseats;
    std::vector<QString> Passengers;
};

#endif // FLIGHT_H
