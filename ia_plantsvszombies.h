#ifndef IA_PLANTSVSZOMBIES_H
#define IA_PLANTSVSZOMBIES_H

#include <QMainWindow>

namespace Ui {
class IA_PlantsvsZombies;
}

class IA_PlantsvsZombies : public QMainWindow
{
    Q_OBJECT

public:
    explicit IA_PlantsvsZombies(QWidget *parent = 0);
    ~IA_PlantsvsZombies();

private slots:
    void on_pushButton_clicked();


private:
    Ui::IA_PlantsvsZombies *ui;
};

#endif // IA_PLANTSVSZOMBIES_H
