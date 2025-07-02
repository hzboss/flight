#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>
#include "addflightdialog.h"
#include <QTimer>

namespace Ui {
class AdminMainWindow;
}

class AdminMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMainWindow(QWidget *parent = nullptr);
    ~AdminMainWindow();

private:
    Ui::AdminMainWindow *ui;
    QTimer *timer;

private slots:
    void AddFlightBtnClicked();
    void updateTime();
};

#endif // ADMINMAINWINDOW_H
