#ifndef SHOWPASSINFOWINDOW_H
#define SHOWPASSINFOWINDOW_H

#include <QWidget>
#include <QDialog>
#include "flight.h"
#include "passinfo.h"

namespace Ui {
class ShowPassInfoWindow;
}

class ShowPassInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ShowPassInfoWindow(Flight& flight,QWidget *parent = nullptr);
    ~ShowPassInfoWindow();

private:
    Ui::ShowPassInfoWindow *ui;

};

#endif // SHOWPASSINFOWINDOW_H
