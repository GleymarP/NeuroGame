#ifndef CONCENTRATIONGAME_H
#define CONCENTRATIONGAME_H
#include "Homepage.h"
#include "Dialog.h"
#include <QMainWindow>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QVector>
#include <QString>
#include <random>
#include <QTimer>
#include <QDir>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QPixmap>
#include <QCloseEvent>


namespace Ui {
class ConcentrationGame;
}

class ConcentrationGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConcentrationGame(QWidget *parent = nullptr);
    ~ConcentrationGame();


private slots:
    void initialize_game();
    void initial_animation();
    void generate_pattern();
    void show_animal(QString animal);
    void show_pattern(QVector<QString>& sequence);
    void sequence_input();
    void check_sequence(QVector<QString>& sequence, QVector<QString>& user_input);
    void reset_game();
    void close_game();




private:
    Ui::ConcentrationGame *ui;

    int level;
    QVector <QString> sequence;
    QVector <QString> user_input;
    QMediaPlayer *sound = new QMediaPlayer();
    QAudioOutput *audio_output_sound = new QAudioOutput();
    bool sound_enabled;

};

#endif // CONCENTRATIONGAME_H
