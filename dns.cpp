#include "dns.h"
#include "ui_dns.h"
#include <QLineEdit>
DNS::DNS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DNS)
{
    ui->setupUi(this);

}

DNS::~DNS()
{
    delete ui;
}

void DNS::on_pushButton_2_clicked()
{
    this->close();
}

void DNS::on_pushButton_clicked()
{
    dnsName = ui->direccion->text();
    port = ui->puerto->text();

}
