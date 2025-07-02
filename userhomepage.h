#ifndef USERHOMEPAGE_H
#define USERHOMEPAGE_H

#include <QWidget>
#include "user.h"
#include <QTimer>

namespace Ui {
class UserHomePage;
}

class UserHomePage : public QWidget
{
    Q_OBJECT

public:
    explicit UserHomePage(User &user,QWidget *parent = nullptr);
    ~UserHomePage();

private:
    Ui::UserHomePage *ui;
    QTimer *timer;

private slots:
    void updateTime();
};

#endif // USERHOMEPAGE_H
