#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>
#include "adminre.h"

namespace Ui {
class AdminLogin;
}

class AdminLogin : public QDialog
{
    Q_OBJECT

public:
    explicit AdminLogin(QWidget *parent = nullptr);
    ~AdminLogin();
    static bool AdminSeekInfo(QString& Account,QString& PassWord);

private:
    Ui::AdminLogin *ui;
    AdminRe *ar;

public slots:
    void createAMwindow();
};

#endif // ADMINLOGIN_H
