#ifndef LOGICGAME_H
#define LOGICGAME_H

#include <QMainWindow>

#include "Dialog.h"
#include "Homepage.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTimer>
#include <QTime>
#include <QVector>
#include <random>
#include <QPair>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QCloseEvent>

namespace Ui {
class LogicGame;
}

class LogicGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogicGame(QWidget *parent = nullptr);
    ~LogicGame();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void initialize_game();
    void update_timer();
    void play_music();
    void toggle_music();
    void generate_operation();
    void update_operation();

    void check_result();
    void toggle_sound();

    void play_success_sound();
    void play_fail_sound();
    void close_game();
    void open_final_dialog();


private:
    Ui::LogicGame *ui;

    QMediaPlayer *music = new QMediaPlayer();
    QAudioOutput *audio_output_music = new QAudioOutput();

    QMediaPlayer *sound = new QMediaPlayer();
    QAudioOutput *audio_output_sound = new QAudioOutput();
    bool sound_enabled;

    QTimer *timer = new QTimer();
    QTime time;

    int score;
    int correct_result;
    int user_answer;
    int iterator_operation;

    QVector<QPair<int, int>> numbers_to_operation;
    QVector<QString> operations {"+", "-", "+", "-", "+", "-", "+", "-", "+", "-", "+", "-"};

};

#endif // LOGICGAME_H
