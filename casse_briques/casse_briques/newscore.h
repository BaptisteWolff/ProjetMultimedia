#ifndef NEWSCORE_H
#define NEWSCORE_H

#include <QDialog>
#include "cassebriques.h"

namespace Ui {
class NewScore;
}

class NewScore : public QDialog
{
    Q_OBJECT

public:
    explicit NewScore(QWidget *parent = 0);
    ~NewScore();
    //void setCasseBriques(CasseBriques *casseBriques){casseBriques_ = casseBriques;}
    void setScore(int score);
    QString getPlayerName();

private slots:
    void on_pushButton_released();

private:
    Ui::NewScore *ui;
    //CasseBriques *casseBriques_;
    int score_;
};

#endif // NEWSCORE_H
