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


