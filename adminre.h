#ifndef ADMINRE_H
#define ADMINRE_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

namespace Ui {
class AdminRe;
}

class AdminRe : public QDialog
{
    Q_OBJECT

public:
    explicit AdminRe(QWidget *parent = nullptr);
    ~AdminRe();
    static bool AdminExist(QString& Account);
    bool addAdminAccount(QString& Account,QString& Password);

private:
    Ui::AdminRe *ui;

public slots:
    void createARwindow();
};

#endif // ADMINRE_H
