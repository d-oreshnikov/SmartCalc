#include "calcwindow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    /*
    Description:
        Entry point function for running SmartCalc application

    Args:
        (int) args    : Number of arguments provided with invoking executable file
        (char**) argv : Actual arguments provided with invoking executable file

    Returns:
        None (only runs SmartCalc application)
    */

    QApplication a(argc, argv);

    CalcWindow w;
    w.setWindowTitle("SmartCalc v1.0");
    w.show();

    return a.exec();
}
