#include "ia_plantsvszombies.h"
#include <QApplication>
#include <time.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    IA_PlantsvsZombies w;
    w.show();

    return a.exec();
}
