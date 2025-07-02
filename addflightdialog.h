#ifndef ADDFLIGHTDIALOG_H
#define ADDFLIGHTDIALOG_H

#include <QDialog>
#include "flight.h"
#include "admin.h"

namespace Ui {
class AddFlightDialog;
}

class AddFlightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFlightDialog(QWidget *parent = nullptr);
    ~AddFlightDialog();

private:
    Ui::AddFlightDialog *ui;
};

#endif // ADDFLIGHTDIALOG_H
