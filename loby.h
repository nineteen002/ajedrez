#ifndef LOBY_H
#define LOBY_H

#include <QDialog>
#include "packages.h"
#include "QMessageBox"
#include "socket.h"

namespace Ui {
class Loby;
}

class Loby : public QDialog
{
    Q_OBJECT

public:
    explicit Loby(QWidget *parent = nullptr);
    ~Loby();
    Socket* socket;
    void closeConnection();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
private:
    Ui::Loby *ui;

    QString nameUser;
    Packages *packageLog;
};

#endif // LOBY_H
