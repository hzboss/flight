#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "userlogin.h"

namespace Ui {
class UserMainWindow;
}

class UserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserMainWindow(User& user,QWidget *parent = nullptr);
    ~UserMainWindow();
    void onSwitchAccount();
    void onExit();

private:
    Ui::UserMainWindow *ui;
};

#endif // USERMAINWINDOW_H
