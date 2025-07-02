#ifndef USERLOGIN_H
#define USERLOGIN_H

#include <QDialog>
#include "userre.h"
#include "user.h"

namespace Ui {
class UserLogin;
}

class UserLogin : public QDialog
{
    Q_OBJECT

public:
    explicit UserLogin(QWidget *parent = nullptr);
    ~UserLogin();
    static bool UserSeekInfo(QString& Account,QString& Password);

private:
    Ui::UserLogin *ui;
    UserRe *ur;

public slots:
    void createUMwindow(User& user);
};

#endif // USERLOGIN_H
