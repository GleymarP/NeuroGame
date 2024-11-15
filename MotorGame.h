#ifndef MOTORGAME_H
#define MOTORGAME_H

#include <QMainWindow>

#include "Homepage.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QTime>
#include <QVector>
#include <QString>
#include <QMap>
#include <QList>
#include <QCloseEvent>

namespace Ui {
class MotorGame;
}

class MotorGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MotorGame(QWidget *parent = nullptr);
    ~MotorGame();

protected:
    void closeEvent(QCloseEvent *event) override;


private slots:
    void initialize_game();
    void update_timer();
    void play_music();
    void play_success_sound();
    void play_fail_sound();
    void toggle_music();
    void toggle_sound();

    void check_match();
    void assign_image(QVector<QString>& buttons, QMap<QString, QString>& distribution);
    void show_images(QMap<QString, QString>& distribution);
    void mix_buttons(QVector<QString>& buttons);
    void assign_image_to_search(QMap<QString, QString> &distribution);
    void hide_images();
    void open_final_dialog();
    void close_game();
    void restart_game();


private:
    Ui::MotorGame *ui;


    QMediaPlayer *music = new QMediaPlayer();
    QAudioOutput *audio_output_music = new QAudioOutput();

    QMediaPlayer *sound = new QMediaPlayer();
    QAudioOutput *audio_output_sound = new QAudioOutput();
    bool sound_enabled;


    int score;

    QTimer *timer = new QTimer();
    QTime time;
    QString animal_to_search;


    QVector<QString> buttons {"button_1", "button_2", "button_3", "button_4", "button_5",
                                "button_6", "button_7", "button_8", "button_9", "button_10",
                             "button_11", "button_12", "button_13", "button_14", "button_15"};

    QMap<QString, QString> distribution;

    int numbers_of_plays;


};

#endif // MOTORGAME_H
