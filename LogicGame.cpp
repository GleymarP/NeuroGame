#include "LogicGame.h"
#include "ui_LogicGame.h"

LogicGame::LogicGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LogicGame)
{
    ui->setupUi(this);

    connect(ui->music, SIGNAL(clicked()), this, SLOT(toggle_music()));
    connect(ui->sound, SIGNAL(clicked()), this, SLOT(toggle_sound()));
    connect(timer, SIGNAL(timeout()), this, SLOT(update_timer()));

    connect(ui->user_input, SIGNAL(returnPressed()), this, SLOT(check_result()));

    connect(music, &QMediaPlayer::errorOccurred, [](QMediaPlayer::Error error) {
        qDebug() << "Error de reproducción:" << error;
    });

    QRegularExpression regex("^-?\\d*$");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex, this);

    ui->user_input->setValidator(validator);

    initialize_game();
}


void LogicGame::update_timer()
{
    time = time.addSecs(-1);
    ui->timer_text->setText(time.toString("mm:ss"));

    if(time.toString() == "00:00:00")
    {
        open_final_dialog();
    }
}


void LogicGame::play_music()
{
    music->setAudioOutput(audio_output_music);
    music->setSource(QUrl("qrc:/assets/sounds/treacherous.ogg"));
    audio_output_music->setVolume(100);
    music->play();
}


void LogicGame::toggle_music()
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


void LogicGame::toggle_sound()
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


void LogicGame::play_success_sound()
{
    sound->setAudioOutput(audio_output_sound);
    sound->setSource(QUrl("qrc:/assets/sounds/succes.wav"));
    audio_output_sound->setVolume(100);
    sound->play();
}


void LogicGame::play_fail_sound()
{
    sound->setAudioOutput(audio_output_sound);
    sound->setSource(QUrl("qrc:/assets/sounds/failure.wav"));
    audio_output_sound->setVolume(100);
    sound->play();
}


void LogicGame::check_result()
{
    if(iterator_operation < 10)
    {
        if(operations[iterator_operation] == "+")
        {
            correct_result = numbers_to_operation[iterator_operation].first + numbers_to_operation[iterator_operation].second;
        }
        else
        {
            correct_result = numbers_to_operation[iterator_operation].first - numbers_to_operation[iterator_operation].second;
        }

        QString user_answer_text = ui->user_input->text();
        user_answer = user_answer_text.toInt();

        if(correct_result == user_answer)
        {
            ui->feedback->setStyleSheet("background-image: url(:/assets/images/check);");
            play_success_sound();
            score += 10;
            ui->score->setText(QString::number(score));

        }
        else
        {
            ui->feedback->setStyleSheet("background-image: url(:/assets/images/cross);");
            play_fail_sound();
            if(score > 0)
            {
                score -= 5;
            }
            ui->score->setText(QString::number(score));
        }
        ui->user_input->clear();

        iterator_operation++;
        ui->operation_number->setText(QString::number(iterator_operation));

        if(iterator_operation < 10)
        {
            update_operation();
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


void LogicGame::generate_operation()
{

    std::random_device rd {};
    std::mt19937 rng{rd()};
    std::uniform_int_distribution<int> dist{1, 20};
    std::uniform_int_distribution<int> dist_1{1, 10};


    for(int i = 0; i < 10; ++i)
    {
        numbers_to_operation.append(qMakePair(dist(rng), dist_1(rng)));
    }

}


void LogicGame::update_operation()
{


        ui->current_addend_1->setText(QString::number(numbers_to_operation[iterator_operation].first));
        ui->current_addend_2->setText(QString::number(numbers_to_operation[iterator_operation].second));
        ui->current_equal->setText(" = ");

        if(operations[iterator_operation] == "+")
        {
            ui->current_operation->setText(" + ");
        }
        else
        {
            ui->current_operation->setText(" - ");
        }



    if(iterator_operation > 0)
    {
        ui->previous_addend_1->setText(QString::number(numbers_to_operation[iterator_operation - 1].first));
        ui->previous_addend_2->setText(QString::number(numbers_to_operation[iterator_operation - 1].second));
        ui->previous_equal->setText(" = ");
        ui->previous_result->setText(QString::number(user_answer));

        if(operations[iterator_operation - 1] == "+")
        {
            ui->previous_opeation->setText(" + ");
        }
        else
        {
            ui->previous_opeation->setText(" - ");
        }

    }

    if(iterator_operation < 9)
    {
        ui->incoming_addend_1->setText(QString::number(numbers_to_operation[iterator_operation + 1].first));
        ui->incoming_addend_2 ->setText(QString::number(numbers_to_operation[iterator_operation + 1].second));
        ui->incoming_equal->setText(" = ");

        if(operations[iterator_operation + 1] == "+")
        {
            ui->incoming_opeation->setText(" + ");
        }
        else
        {
            ui->incoming_opeation->setText(" - ");
        }
    }
    else
    {
        ui->incoming_addend_1->setText(" ");
        ui->incoming_addend_2 ->setText(" ");
        ui->incoming_equal->setText(" ");
        ui->incoming_opeation->setText("  ");

    }

}


void LogicGame::initialize_game()
{
    play_music();

    time.setHMS(0,4,0);
    ui->timer_text->setText(time.toString("mm:ss"));
    timer->start(1000);

    score = 0;
    ui->score->setText(QString::number(score));

    iterator_operation = 0;
    generate_operation();
    update_operation();

}

void LogicGame::close_game()
{
    Homepage *homepage = new Homepage(this);
    homepage->show();
    this->hide();
}

void LogicGame::open_final_dialog()
{
    Dialog *dialog = new Dialog(this, "¡Buen trabajo!", QString::number(score), "Puntuación");
    connect(dialog, &Dialog::accept_dialog, this, &LogicGame::close_game);
    dialog->exec();
    timer->stop();
    music->stop();
    ui->frame->setEnabled(false);
}

void LogicGame::closeEvent(QCloseEvent *event)
{
    timer->stop();
    music->stop();
    event->accept();
}

LogicGame::~LogicGame()
{

    delete ui;
}



