#ifndef TICKET_H
#define TICKET_H
#include <QString>
#include <QDateTime>

class Ticket
{
public:
    Ticket();
    Ticket(const QString fid, const QString sp, const QString ep, const QDateTime& st, const QDateTime& et, int sid, QString oa)
        : Fid(fid), Sp(sp), Ep(ep), St(st), Et(et), Sid(sid) ,OAcc(oa){}
    bool operator==(const Ticket& other) const {
        return Fid == other.Fid && Sid == other.Sid;
    }
    QString getFid() const{
        return Fid;
    }
    QString getSp(){
        return Sp;
    }
    QString getEp(){
        return Ep;
    }
    QDateTime getSt(){
        return St;
    }
    QDateTime getEt(){
        return Et;
    }
    int getSid(){
        return Sid;
    }
    QString getOAcc() const{
        return OAcc;
    }

private:
    QString Fid;
    QString Sp;
    QString Ep;
    QDateTime St;
    QDateTime Et;
    int Sid;
    QString OAcc;
};

#endif // TICKET_H
