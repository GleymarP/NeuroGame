#include "Homepage.h"
#include "./ui_Homepage.h"


Homepage::Homepage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Homepage)
{
    ui->setupUi(this);
}

Homepage::~Homepage()
{
    delete ui;
}

void Homepage::on_memory_button_clicked()
{
    MemoryGame *memory_game = new MemoryGame(this);
    memory_game->show();
    this->hide();
}


void Homepage::on_concentration_button_clicked()
{
    ConcentrationGame *concentration_game = new ConcentrationGame(this);
    concentration_game->show();
    this->hide();
}


void Homepage::on_motor_button_clicked()
{
    MotorGame *motor_game = new MotorGame(this);
    motor_game->show();
    this->hide();
}


void Homepage::on_logic_button_clicked()
{
    LogicGame *logic_game = new LogicGame(this);
    logic_game->show();
    this->hide();
}

