#ifndef LOBY_H
#define LOBY_H

#include <QDialog>
#include "socket.h"
#include "packages.h"

namespace Ui {
class Loby;
}

class Loby : public QDialog
{
    Q_OBJECT

public:
    explicit Loby(QWidget *parent = nullptr);
    ~Loby();

    void closeConnection();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
private:
    Ui::Loby *ui;
    Socket* socket;
    QString nameUser;
    Packages *packageLog;
};

#endif // LOBY_H
