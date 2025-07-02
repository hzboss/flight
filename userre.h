#ifndef USERRE_H
#define USERRE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

namespace Ui {
class UserRe;
}

class UserRe : public QDialog
{
    Q_OBJECT

public:
    explicit UserRe(QWidget *parent = nullptr);
    ~UserRe();
    static bool UserExist(QString& Account);
    bool addUserAccount(QString& Account,int Gender,int Age,QString& Password);

private:
    Ui::UserRe *ui;

public slots:
    void createURwindow();
};

#endif // USERRE_H
