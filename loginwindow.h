#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "adminlogin.h"
#include "userlogin.h"
#include "adminmainwindow.h"
#include "usermainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private:
    Ui::LoginWindow *ui;
    AdminLogin *al;
    UserLogin *ul;
    AdminMainWindow *amw;
    UserMainWindow *umw;

public slots:
    void createULwindow();
    void createALwindow();
};
#endif // LOGINWINDOW_H
