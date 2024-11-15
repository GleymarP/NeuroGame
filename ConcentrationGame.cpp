#include "ConcentrationGame.h"
#include "ui_ConcentrationGame.h"


ConcentrationGame::ConcentrationGame(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ConcentrationGame)
{
    ui->setupUi(this);

    connect(ui->frog, SIGNAL(clicked()), this, SLOT(sequence_input()));
    connect(ui->cat, SIGNAL(clicked()), this, SLOT(sequence_input()));
    connect(ui->chick, SIGNAL(clicked()), this, SLOT(sequence_input()));
    connect(ui->sheep, SIGNAL(clicked()), this, SLOT(sequence_input()));
    connect(ui->start, SIGNAL(clicked()), this, SLOT(initialize_game()));

}


void ConcentrationGame::sequence_input()
{

    QPushButton *current_animal = qobject_cast<QPushButton*>(sender());
    QString name_animal = current_animal->objectName();
    user_input.append(name_animal);
    check_sequence(sequence, user_input);
}


void  ConcentrationGame::check_sequence(QVector<QString>& sequence, QVector<QString>& user_input)
{

    for(size_t i = 0; i < user_input.size(); ++i)
    {
        if(sequence[i] != user_input[i])
        {
            sequence.clear();
            ui->frame->setEnabled(false);
            Dialog *dialog = new Dialog(this, "Oops ¡Casi lo logras!", QString::number(level), "Rondas: ");
            dialog->setWindowTitle("");

            connect(dialog, &Dialog::accept_dialog, this, &ConcentrationGame::close_game);
            dialog->exec();
        }
    }

    if(user_input.size() == sequence.size())
    {
        if(sequence == user_input)
        {
            level++;
            ui->level->setText(QString::number(level));
            reset_game();
        }
        else
        {

            sequence.clear();
            ui->frame->setEnabled(false);

            Dialog *dialog = new Dialog(this, "Oops ¡Casi lo logras!", QString::number(level), "Rondas: ");
            dialog->setWindowTitle("");

            connect(dialog, &Dialog::accept_dialog, this, &ConcentrationGame::close_game);
            dialog->exec();

        }
    }
}


void ConcentrationGame::show_animal(QString animal)
{
    sound->setAudioOutput(audio_output_sound);
    sound->setSource(QUrl("qrc:/assets/sounds/"+ animal +".wav"));
    audio_output_sound->setVolume(100);
    sound->play();

}


void ConcentrationGame::show_pattern(QVector<QString> &sequence)
{
    ui->frame->setEnabled(false);
    QPushButton *recent_animal;

    QString animal;

    for (int i = 0; i < sequence.size(); ++i)
    {
        animal = sequence[i];

        recent_animal = ConcentrationGame::findChild<QPushButton*>(animal);

        QTimer::singleShot(  (i + 1) * 800 , this, [this, animal, recent_animal]()
        {
            show_animal(animal);
        });

    }

    ui->frame->setEnabled(true);

}



void ConcentrationGame::generate_pattern()
{
    std::random_device rd {};
    std::mt19937 rng{rd()};
    std::uniform_int_distribution<int> dist{0, 3};
    int random_number = dist(rng);

    switch (random_number) {
    case 0:
        sequence.append("frog");
        break;
    case 1:
         sequence.append("cat");
        break;
    case 2:
        sequence.append("sheep");
        break;
    case 3:
        sequence.append("chick");
        break;
    default:
        break;
    }
}


void ConcentrationGame::initial_animation()
{
    QPropertyAnimation *anim_1 = new QPropertyAnimation (ui->frog , "pos", this);
    anim_1->setDuration(1000);
    anim_1->setStartValue(QPoint(540, 303));
    anim_1->setEndValue(QPoint(540, 123));
    anim_1->start();

    QPropertyAnimation *anim_2 = new QPropertyAnimation (ui->chick , "pos", this);
    anim_2->setDuration(1000);
    anim_2->setStartValue(QPoint(540, 303));
    anim_2->setEndValue(QPoint(340, 303));
    anim_2->start();

    QPropertyAnimation *anim_3 = new QPropertyAnimation (ui->sheep , "pos", this);
    anim_3->setDuration(1000);
    anim_3->setStartValue(QPoint(540, 303));
    anim_3->setEndValue(QPoint(540, 483));
    anim_3->start();

    QPropertyAnimation *anim_4 = new QPropertyAnimation (ui->cat , "pos", this);
    anim_4->setDuration(1000);
    anim_4->setStartValue(QPoint(540, 303));
    anim_4->setEndValue(QPoint(740, 303));
    anim_4->start();

}


void ConcentrationGame::initialize_game()
{

    initial_animation();
    sequence.clear();
    level = 0;
    reset_game();
    ui->start->hide();
}


void ConcentrationGame::reset_game()
{
    ui->level->setText(QString::number(level));
    user_input.clear();
    generate_pattern();
    show_pattern(sequence);

}


void ConcentrationGame::close_game()
{
    Homepage *homepage = new Homepage(this);
    homepage->show();
    this->hide();
}


ConcentrationGame::~ConcentrationGame()
{
    delete ui;
}
