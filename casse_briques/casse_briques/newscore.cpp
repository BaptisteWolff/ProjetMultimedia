#include "newscore.h"
#include "ui_newscore.h"

NewScore::NewScore(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewScore)
{
    ui->setupUi(this);
}

NewScore::~NewScore()
{
    delete ui;
}

void NewScore::setScore(int score)
{
    this->score_ = score;
    ui->label_score->setText("Score : " + QString::number(score_));
}

void NewScore::on_pushButton_released()
{
    this->hide();
}

QString NewScore::getPlayerName()
{
    return ui->lineEdit->text();
}
