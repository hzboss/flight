#include "showpassinfowindow.h"
#include "ui_showpassinfowindow.h"
#include <QDebug>

ShowPassInfoWindow::ShowPassInfoWindow(Flight& flight, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowPassInfoWindow)
{
    ui->setupUi(this);
    QIcon icon = QIcon(":/photosources/passengers.jpeg");
    this->setWindowIcon(icon);
    this->setWindowTitle(flight.getFlightid() + "乘客信息");
    QWidget *contentWidget = ui->ShowPassArea->widget();
    if (!contentWidget) {
        // 如果没有内容窗口，则创建一个新的
        contentWidget = new QWidget(ui->ShowPassArea);
        ui->ShowPassArea->setWidget(contentWidget);
    }
    QLayout *existingLayout = contentWidget->layout();
    if (existingLayout) {
        while (QLayoutItem *item = existingLayout->takeAt(0)) {
            delete item->widget(); // 删除小部件
            delete item; // 删除布局项
        }
        delete existingLayout; // 删除布局
    }
    QVBoxLayout *layout = new QVBoxLayout(contentWidget);
    std::vector<QString> passengers = flight.getPassengers();
    for (const QString& passenger : passengers) {
        User* user = new User(passenger);
        PassInfo* passinfo = new PassInfo(user,flight.getFlightid());
        layout->addWidget(passinfo);
    }
    contentWidget->setLayout(layout);
}

ShowPassInfoWindow::~ShowPassInfoWindow()
{
    delete ui;
}
