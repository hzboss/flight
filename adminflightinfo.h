#ifndef ADMINFLIGHTINFO_H
#define ADMINFLIGHTINFO_H

#include <QWidget>
#include "flight.h"
#include "showpassinfowindow.h"
#include "admin.h"

namespace Ui {
class AdminFlightInfo;
}

class AdminFlightInfo : public QWidget
{
    Q_OBJECT

public:
    explicit AdminFlightInfo(Flight& flight,QWidget *parent = nullptr);
    ~AdminFlightInfo();

private:
    Ui::AdminFlightInfo *ui;
    QTimer *timer;

private slots:
    void onShowPassInfoBtnClicked();
};

#endif // ADMINFLIGHTINFO_H
