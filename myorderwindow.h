#ifndef MYORDERWINDOW_H
#define MYORDERWINDOW_H

#include <QWidget>
#include "user.h"

namespace Ui {
class MyOrderWindow;
}

class MyOrderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MyOrderWindow(User &user,QWidget *parent = nullptr);
    ~MyOrderWindow();

private:
    Ui::MyOrderWindow *ui;
};

#endif // MYORDERWINDOW_H
