#include "MotorGame.h"
#include "ui_MotorGame.h"

MotorGame::MotorGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MotorGame)
{
    ui->setupUi(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));
    connect(ui->music, SIGNAL(clicked()), this, SLOT(toggle_music()));
    connect(ui->sound, SIGNAL(clicked()), this, SLOT(toggle_sound()));

    connect(ui->button_1, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_2, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_3, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_4, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_5, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_6, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_7, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_8, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_9, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_10, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_11, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_12, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_13, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_14, SIGNAL(clicked()), this, SLOT(check_match()));
    connect(ui->button_15, SIGNAL(clicked()), this, SLOT(check_match()));



    initialize_game();

}


void MotorGame::update_timer()
{
    time = time.addSecs(-1);
    ui->timer_text->setText(time.toString("mm:ss"));

    if(time.toString() == "00:00:00")
    {
        open_final_dialog();
    }
}


void MotorGame::play_music()
{
    music->setAudioOutput(audio_output_music);
    music->setSource(QUrl("qrc:/assets/sounds/champagne_problems.ogg"));
    audio_output_music->setVolume(100);
    music->play();
}


void MotorGame::play_success_sound()
{
    sound->setAudioOutput(audio_output_sound);
    sound->setSource(QUrl("qrc:/assets/sounds/succes.wav"));
    audio_output_sound->setVolume(90);
    sound->play();
}


void MotorGame::play_fail_sound()
{
    sound->setAudioOutput(audio_output_sound);
    sound->setSource(QUrl("qrc:/assets/sounds/failure.wav"));
    audio_output_sound->setVolume(90);
    sound->play();
}


void MotorGame::toggle_music()
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


void MotorGame::toggle_sound()
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


void MotorGame::mix_buttons(QVector<QString> &buttons)
{
    std::random_device rd {};
    std::mt19937 rng{rd()};
    std::shuffle(buttons.begin(), buttons.end(), rng);
}


void MotorGame::assign_image(QVector<QString> &buttons, QMap<QString, QString> &distribution)
{
    mix_buttons(buttons);
    auto iterator = buttons.begin();

    for(int i = 1; i <= 15; ++i)
    {
        QString file_name = "motor_" + QString::number(i) + ".png";
        distribution[*iterator] = file_name;
        iterator++;
    }
}


void MotorGame::assign_image_to_search(QMap<QString, QString> &distribution)
{
    std::random_device rd {};
    std::mt19937 rng{rd()};
    std::uniform_int_distribution<int> dist{1, 15};

    animal_to_search = "button_" + QString::number(dist(rng));
    QString img =  distribution.value(animal_to_search);
    ui->random_animal->setStyleSheet("background-image: url(:/assets/images/"+ img +");");
}


void MotorGame::show_images(QMap<QString, QString>& distribution)
{
    ui->frame->setEnabled(false);
    QList<QPushButton *> buttons_ui = ui->centralwidget->findChildren<QPushButton*>();


    foreach (QPushButton* b, buttons_ui)
    {
        QString button_name = b->objectName();

        if(distribution.contains(button_name))
        {
            QString img = distribution.value(button_name);
            b->setStyleSheet("#" + b->objectName() + "{ background-image: url(:/assets/images/" + img + ");}");
        }

    }
}


void MotorGame::hide_images()
{
    QList<QPushButton *> buttons_ui = ui->frame->findChildren<QPushButton*>();


    foreach (QPushButton* b, buttons_ui)
    {

        b->setStyleSheet("#" + b->objectName() + "{ background-image: url(:/assets/images/ellipse_pattern.png);}");
    }

    ui->frame->setEnabled(true);
}


void MotorGame::check_match()
{

    ui->frame->setEnabled(false);

    if(time.toString() != "00:00:00" && numbers_of_plays <= 10)
    {
        QPushButton *current_button = qobject_cast<QPushButton*>(sender());
        QString user_input = current_button->objectName();
        QString img = distribution.value(user_input);

        current_button->setStyleSheet("#" + user_input + "{ background-image: url(:/assets/images/" + img + ");}");


        if(animal_to_search == user_input)
        {
            play_success_sound();
            score += 10;
            ui->score->setText(QString::number(score));
        }
        else
        {
            play_fail_sound();
            if(score > 0)
            {
                score -= 5;
            }

            ui->score->setText(QString::number(score));
        }



        numbers_of_plays++;
        ui->number_of_plays->setText(QString::number(numbers_of_plays) + " / 10");

        if(numbers_of_plays < 10)
        {
             restart_game();
        }
        else
        {
            open_final_dialog();
        }

    }
    else
    {
        open_final_dialog();
    }
}

void MotorGame::open_final_dialog()
{
    Dialog *dialog = new Dialog(this, "¡Buen trabajo!", QString::number(score), "Puntuación");
    connect(dialog, &Dialog::accept_dialog, this, &MotorGame::close_game);
    dialog->exec();
    timer->stop();
    music->stop();
    ui->frame->setEnabled(false);
}

void MotorGame::restart_game()
{
    ui->frame->setEnabled(false);
    distribution.clear();
    assign_image(buttons, distribution);
    assign_image_to_search(distribution);
    show_images(distribution);
    QTimer::singleShot(1500, this, SLOT( hide_images()));

}

void MotorGame::initialize_game()
{
    play_music();

    time.setHMS(0,3,0);
    ui->timer_text->setText(time.toString("mm:ss"));
    timer->start(1000);

    score = 0;
    numbers_of_plays = 0;
    ui->score->setText(QString::number(score));
    restart_game();
}



void MotorGame::close_game()
{
    Homepage *homepage = new Homepage(this);
    homepage->show();
    this->hide();
}

void MotorGame::closeEvent(QCloseEvent *event)
{
    timer->stop();
    music->stop();
    event->accept();
}

MotorGame::~MotorGame()
{
    delete ui;
}
