#include "MemoryGame.h"
#include "ui_MemoryGame.h"

MemoryGame::MemoryGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MemoryGame)
{
    ui->setupUi(this);


    connect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));

    connect(ui->card_1, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_2, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_3, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_4, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_5, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_6, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_7, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_8, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_9, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_10, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_11, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_12, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_13, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_14, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_15, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_16, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_17, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_18, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_19, SIGNAL(clicked()), this, SLOT(reveal_card()));
    connect(ui->card_20, SIGNAL(clicked()), this, SLOT(reveal_card()));

    connect(ui->music, SIGNAL(clicked()), this, SLOT(toggle_music()));
    connect(ui->sound, SIGNAL(clicked()), this, SLOT(toggle_sound()));


    initialize_game();

}


void MemoryGame::update_timer()
{
    time = time.addSecs(-1);
    ui->timer_text->setText(time.toString("mm:ss"));
    define_final_result();
}

void MemoryGame::play_music()
{
    music->setAudioOutput(audio_output_music);
    music->setSource(QUrl("qrc:/assets/sounds/evermore.ogg"));
    audio_output_music->setVolume(100);
    music->play();
}

void MemoryGame::toggle_music()
{
    if(music->playbackState() == QMediaPlayer::PlayingState)
    {
        music->pause();
        ui->music->setStyleSheet("border-image: url(:/assets/images/music-slash.png);");
    }
    else
    {
        music->play();
        ui->music->setStyleSheet("border-image: url(:/assets/images/music);");
    }
}

void MemoryGame::play_success_sound()
{
    sound->setAudioOutput(audio_output_sound);
    sound->setSource(QUrl("qrc:/assets/sounds/succes.wav"));
    audio_output_sound->setVolume(100);
    sound->play();
}

void MemoryGame::play_fail_sound()
{
    sound->setAudioOutput(audio_output_sound);
    sound->setSource(QUrl("qrc:/assets/sounds/failure.wav"));
    audio_output_sound->setVolume(100);
    sound->play();
}

void MemoryGame::toggle_sound()
{
    sound_enabled = !sound_enabled;

    if(sound_enabled)
    {
        ui->sound->setStyleSheet("border-image: url(:/assets/images/volume_down)");
    }
    else
    {
        ui->sound->setStyleSheet("border-image: url(:/assets/images/volume_mute)");
    }
}

void MemoryGame::mix_cards(QVector<QString> &cards)
{
    std::random_device rd {};
    std::mt19937 rng{rd()};
    std::shuffle(cards.begin(), cards.end(), rng);
}


void MemoryGame::deal_cards(QVector<QString> &cards, QMap<QString, QString> &distribution)
{
    mix_cards(cards);
    auto iterator = cards.begin();

    for(int i = 1; i <= 10; ++i)
    {
        QString file_name = QString::number(i) + ".png";
        distribution[*iterator] = file_name;
        iterator++;
        distribution[*iterator] = file_name;
        iterator++;
    }
}


void MemoryGame::define_partial_result()
{
    if(distribution[current_card->objectName()] == distribution[previous_card->objectName()])
    {
        score += 10;
        ui->Score->setText(QString::number(score));
        remaining_couples--;

        if(sound_enabled)
        {
            play_success_sound();
        }

        define_final_result();

    }
    else
    {
        if(score > 0)
        {
            score -= 5;
        }
        ui->Score->setText(QString::number(score));
        ui->frame->setEnabled(false);
        QTimer::singleShot(1500, this, SLOT(restart_cards()));

        if(sound_enabled)
        {
            play_fail_sound();
        }
    }
}

void MemoryGame::define_final_result()
{

    if(remaining_couples == 0)
    {

        timer->stop();
        music->stop();
        Dialog *dialog = new Dialog(this, "¡Buen trabajo!", QString::number(score), "Puntuación");

        connect(dialog, &Dialog::accept_dialog, this, &MemoryGame::close_game);
        dialog->exec();

    }
    else
    {
        if(time.toString() == "00:00:00")
        {
            timer->stop();
            music->stop();
            ui->frame->setEnabled(false);
            Dialog *dialog = new Dialog(this, "Oops ¡Casi lo logras!", QString::number(score));
            connect(dialog, &Dialog::accept_dialog, this, &MemoryGame::close_game);
            dialog->exec();

        }

    }

}

void MemoryGame::close_game()
{
    Homepage *homepage = new Homepage(this);
    homepage->show();
    this->hide();
}

void MemoryGame::show_image()
{
    QString name_card = current_card->objectName();
    QString img = distribution[name_card];
    current_card->setStyleSheet("#" + name_card + " { background-image: url(://assets/images/" + img + "); }");
}

void MemoryGame::reveal_card()
{
    current_card = qobject_cast<QPushButton*>(sender());
    show_image();
    current_card->setEnabled(false);

    if(!play_started)
    {
        previous_card = current_card;
        play_started = true;
    }
    else
    {
        define_partial_result();
        play_started = false;

    }
}


void MemoryGame::restart_cards()
{
    current_card->setStyleSheet("#" + current_card->objectName() + "{background-image: url(:/assets/images/pattern.png);}");
    previous_card->setStyleSheet("#" + previous_card->objectName() + "{background-image: url(:/assets/images/pattern.png);}");
    current_card->setEnabled(true);
    previous_card->setEnabled(true);
    ui->frame->setEnabled(true);
}


void MemoryGame::initial_animation()
{
    QPropertyAnimation *anim01 = new QPropertyAnimation (ui->card_1, "pos", this);
    anim01->setDuration(1000);
    anim01->setStartValue(QPoint(489, 242));
    anim01->setEndValue(QPoint(12, 17));
    anim01->start();


    QPropertyAnimation *anim02 = new QPropertyAnimation (ui->card_2, "pos", this);
    anim02->setDuration(1000);
    anim02->setStartValue(QPoint(489, 242));
    anim02->setEndValue(QPoint(246, 17));
    anim02->start();

    QPropertyAnimation *anim03 = new QPropertyAnimation (ui->card_3, "pos", this);
    anim03->setDuration(1000);
    anim03->setStartValue(QPoint(489, 242));
    anim03->setEndValue(QPoint(480, 17));
    anim03->start();

    QPropertyAnimation *anim04 = new QPropertyAnimation (ui->card_4, "pos", this);
    anim04->setDuration(1000);
    anim04->setStartValue(QPoint(489, 242));
    anim04->setEndValue(QPoint(715, 17));
    anim04->start();

    QPropertyAnimation *anim05 = new QPropertyAnimation (ui->card_5, "pos", this);
    anim05->setDuration(1000);
    anim05->setStartValue(QPoint(489, 242));
    anim05->setEndValue(QPoint(948, 17));
    anim05->start();

    QPropertyAnimation *anim06 = new QPropertyAnimation (ui->card_6, "pos", this);
    anim06->setDuration(1000);
    anim06->setStartValue(QPoint(489, 242));
    anim06->setEndValue(QPoint(12, 175));
    anim06->start();

    QPropertyAnimation *anim07 = new QPropertyAnimation (ui->card_7, "pos", this);
    anim07->setDuration(1000);
    anim07->setStartValue(QPoint(489, 242));
    anim07->setEndValue(QPoint(246, 175));
    anim07->start();

    QPropertyAnimation *anim08 = new QPropertyAnimation (ui->card_8, "pos", this);
    anim08->setDuration(1000);
    anim08->setStartValue(QPoint(489, 242));
    anim08->setEndValue(QPoint(480, 175));
    anim08->start();

    QPropertyAnimation *anim09 = new QPropertyAnimation (ui->card_9, "pos", this);
    anim09->setDuration(1000);
    anim09->setStartValue(QPoint(489, 242));
    anim09->setEndValue(QPoint(715, 175));
    anim09->start();

    QPropertyAnimation *anim10 = new QPropertyAnimation (ui->card_10, "pos", this);
    anim10->setDuration(1000);
    anim10->setStartValue(QPoint(489, 242));
    anim10->setEndValue(QPoint(950, 175));
    anim10->start();

    QPropertyAnimation *anim11 = new QPropertyAnimation (ui->card_11, "pos", this);
    anim11->setDuration(1000);
    anim11->setStartValue(QPoint(489, 242));
    anim11->setEndValue(QPoint(12, 329));
    anim11->start();

    QPropertyAnimation *anim12 = new QPropertyAnimation (ui->card_12, "pos", this);
    anim12->setDuration(1000);
    anim12->setStartValue(QPoint(489, 242));
    anim12->setEndValue(QPoint(246, 329));
    anim12->start();

    QPropertyAnimation *anim13 = new QPropertyAnimation (ui->card_13, "pos", this);
    anim13->setDuration(1000);
    anim13->setStartValue(QPoint(489, 242));
    anim13->setEndValue(QPoint(480, 329));
    anim13->start();

    QPropertyAnimation *anim14 = new QPropertyAnimation (ui->card_14, "pos", this);
    anim14->setDuration(1000);
    anim14->setStartValue(QPoint(489, 242));
    anim14->setEndValue(QPoint(718, 329));
    anim14->start();

    QPropertyAnimation *anim15 = new QPropertyAnimation (ui->card_15, "pos", this);
    anim15->setDuration(1000);
    anim15->setStartValue(QPoint(489, 242));
    anim15->setEndValue(QPoint(948, 329));
    anim15->start();

    QPropertyAnimation *anim16 = new QPropertyAnimation (ui->card_16, "pos", this);
    anim16->setDuration(1000);
    anim16->setStartValue(QPoint(489, 242));
    anim16->setEndValue(QPoint(12, 483));
    anim16->start();

    QPropertyAnimation *anim17 = new QPropertyAnimation (ui->card_17, "pos", this);
    anim17->setDuration(1000);
    anim17->setStartValue(QPoint(489, 242));
    anim17->setEndValue(QPoint(246, 483));
    anim17->start();

    QPropertyAnimation *anim18 = new QPropertyAnimation (ui->card_18, "pos", this);
    anim18->setDuration(1000);
    anim18->setStartValue(QPoint(489, 242));
    anim18->setEndValue(QPoint(480, 483));
    anim18->start();

    QPropertyAnimation *anim19 = new QPropertyAnimation (ui->card_19, "pos", this);
    anim19->setDuration(1000);
    anim19->setStartValue(QPoint(489, 242));
    anim19->setEndValue(QPoint(715, 483));
    anim19->start();

    QPropertyAnimation *anim20 = new QPropertyAnimation (ui->card_20, "pos", this);
    anim20->setDuration(1000);
    anim20->setStartValue(QPoint(489, 242));
    anim20->setEndValue(QPoint(950, 483));
    anim20->start();
}




void MemoryGame::initialize_game()
{

    play_music();
    sound_enabled = true;

    initial_animation();

    play_started = false;

    score = 0;
    ui->Score->setText(QString::number(score));

    remaining_couples = 10;

    time.setHMS(0,5,0);
    ui->timer_text->setText(time.toString("mm:ss"));
    timer->start(1000);

    deal_cards(cards, distribution);

    ui->frame->setEnabled(true);

}

void MemoryGame::closeEvent(QCloseEvent *event)
{
    timer->stop();
    music->stop();
    event->accept();
}


MemoryGame::~MemoryGame()
{
    delete ui;
}
