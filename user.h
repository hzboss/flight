#ifndef USER_H
#define USER_H
#include <QString>
#include "ticket.h"

class User
{
public:
    User(QString account);
    void BuyTicket(QString fid,QString sp,QString ep,QDateTime st,QDateTime et,int sid);
    void RefundTicket(QString fid);
    QString getAccount();
    std::vector<Ticket>& getTickets();
    int getcurflightsid(QString fid);
    int getGender();
    int getAge();
    ~User(){}
private:
    QString Account;
    // QString Password;
    int Gender;
    int Age;
    std::vector<Ticket> Tickets;

};

#endif // USER_H
