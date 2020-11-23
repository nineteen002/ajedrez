#ifndef LOBY_H
#define LOBY_H

#include <QDialog>
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
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::Loby *ui;
};

#endif // LOBY_H
