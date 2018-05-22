#ifndef NEWSCORE_H
#define NEWSCORE_H

#include <QDialog>
#include <cassebriques.h>

namespace Ui {
class NewScore;
}

class NewScore : public QDialog
{
    Q_OBJECT

public:
    explicit NewScore(QWidget *parent = 0);
    ~NewScore();
    void setScore(CasseBriques casseBriques);

private:
    Ui::NewScore *ui;
};

#endif // NEWSCORE_H
