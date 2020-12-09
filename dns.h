#ifndef DNS_H
#define DNS_H

#include <QMainWindow>

namespace Ui {
class DNS;
}

class DNS : public QMainWindow
{
    Q_OBJECT

public:
    explicit DNS(QWidget *parent = nullptr);
    ~DNS();
    int respuesta;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::DNS *ui;
};

#endif // DNS_H
