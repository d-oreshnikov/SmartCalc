#include "calcwindow.h"

#include <QApplication>
#include <QLabel>

 // Entry point function for running SmartCalc application
int main(int argc, char *argv[]) {

    QApplication a(argc, argv);

    CalcWindow w;
    w.setWindowTitle("SmartCalc v1.0");
    w.show();

    return a.exec();
}
