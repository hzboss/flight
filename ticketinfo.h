#ifndef TICKETINFO_H
#define TICKETINFO_H

#include <QWidget>
#include "flight.h"
#include "user.h"

namespace Ui {
class TicketInfo;
}

class TicketInfo : public QWidget
{
    Q_OBJECT

public:
    explicit TicketInfo(Ticket& ticket,QWidget *parent = nullptr);
    ~TicketInfo();

private:
    Ui::TicketInfo *ui;
};

#endif // TICKETINFO_H
