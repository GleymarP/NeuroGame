#ifndef MEMORYGAME_H
#define MEMORYGAME_H
#include <QMainWindow>

#include "Homepage.h"
#include "Dialog.h"
#include <QPropertyAnimation>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QTime>
#include <QVector>
#include <QMap>
#include <random>
#include <QMediaPlayer>
#include <QUrl>
#include <QDir>
#include <QAudioOutput>
#include <QCloseEvent>



namespace Ui
{
class MemoryGame;
}

class MemoryGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit MemoryGame(QWidget *parent = nullptr);
    ~MemoryGame();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void update_timer();
    void deal_cards(QVector<QString>& cards, QMap<QString, QString>& distribution);
    void define_partial_result();
    void define_final_result();
    void show_image();
    void reveal_card();
    void restart_cards();
    void initial_animation();
    void initialize_game();
    void mix_cards(QVector<QString>& cards);
    void play_music();
    void play_success_sound();
    void play_fail_sound();
    void toggle_music();
    void toggle_sound();
    void close_game();


private:
    Ui::MemoryGame *ui;

    QTimer *timer = new QTimer();
    QTime time;

    QMap<QString, QString> distribution;
    QVector<QString> cards {"card_1", "card_2", "card_3", "card_4", "card_5", "card_6", "card_7", "card_8", "card_9", "card_10",
                           "card_11", "card_12", "card_13", "card_14", "card_15", "card_16", "card_17", "card_18", "card_19", "card_20"};

    int remaining_couples;
    int score;
    bool play_started;

    QPushButton *current_card;
    QPushButton *previous_card;

    QMediaPlayer *music = new QMediaPlayer();
    QAudioOutput *audio_output_music = new QAudioOutput();

    QMediaPlayer *sound = new QMediaPlayer();
    QAudioOutput *audio_output_sound = new QAudioOutput();
    bool sound_enabled;



};

#endif // MEMORYGAME_Hs
