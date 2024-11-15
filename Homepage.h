#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include "MemoryGame.h"
#include "ConcentrationGame.h"
#include "MotorGame.h"
#include "LogicGame.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Homepage;
}
QT_END_NAMESPACE

class Homepage : public QMainWindow
{
    Q_OBJECT

public:
    Homepage(QWidget *parent = nullptr);
    ~Homepage();

private slots:
    void on_memory_button_clicked();

    void on_concentration_button_clicked();

    void on_motor_button_clicked();

    void on_logic_button_clicked();

private:
    Ui::Homepage *ui;
};
#endif // HOMEPAGE_H
