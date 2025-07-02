#ifndef PASSINFO_H
#define PASSINFO_H

#include <QWidget>
#include "user.h"

namespace Ui {
class PassInfo;
}

class PassInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PassInfo(User* user,QString fid,QWidget *parent = nullptr);
    ~PassInfo();

private:
    Ui::PassInfo *ui;
};

#endif // PASSINFO_H
