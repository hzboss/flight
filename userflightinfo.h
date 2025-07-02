#ifndef USERFLIGHTINFO_H
#define USERFLIGHTINFO_H

#include <QWidget>
#include "flight.h"

namespace Ui {
class UserFlightInfo;
}

class UserFlightInfo : public QWidget
{
    Q_OBJECT

public:
    explicit UserFlightInfo(User& user,QWidget *parent = nullptr);
    ~UserFlightInfo();
    UserFlightInfo(Flight& flight,User& user,QWidget *parent = nullptr);

private:
    Ui::UserFlightInfo *ui;
    int flightNum;
};

#endif // USERFLIGHTINFO_H
