#include "Dialog.h"
#include "ui_Dialog.h"

Dialog::Dialog(QWidget *parent, QString message, QString final_score, QString score_text)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->message->setText(message);
    ui->score->setText(final_score);
    ui->score_text->setText(score_text);

    connect(this, &Dialog::finished, this, [this](){
        emit accept_dialog();
    });
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_ok_button_clicked()
{
    close();
}

