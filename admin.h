#ifndef ADMIN_H
#define ADMIN_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "flight.h"
class Admin
{
public:
    Admin();
    bool addPlane(Flight& flight);
    bool deletePlane(QString pid);

private:
    QString Account;
    QString Password; // 皆可删

};

#endif // ADMIN_H
