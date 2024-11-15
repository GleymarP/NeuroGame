#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    Dialog(QWidget *parent = nullptr, QString message = "default", QString final_score = "0", QString score_text = "Puntuación");
    ~Dialog();

private slots:
    void on_ok_button_clicked();

signals:
    void accept_dialog();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
