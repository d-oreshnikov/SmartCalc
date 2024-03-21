#ifndef CALCWINDOW_H
#define CALCWINDOW_H

#include <QMainWindow>
#include "graph.h"

extern "C" {
#include "../../backend/parser/parser.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class CalcWindow; }
QT_END_NAMESPACE

// SmartCalc window class. It inherits from QMainWindow, so
// it has all of QMainWindow's attributes and methods
// CalcWindow has functionality for handling signals from user, parsing
// input equation calculating inputed equation and drawing resulting graph
 
class CalcWindow : public QMainWindow {
    Q_OBJECT

public:
    // CalcWindow constructor. Also connects ui buttons with backend
    CalcWindow(QWidget *parent = nullptr);

    //CalcWindow destructor. Cleans allocated memory and destroy CalcWindow object
    ~CalcWindow();

private slots:

    //Function for handling signals from user
    void psignal();

    //  Function for handling backspace button
    void mbackspace();

    // Function for setting cursor to starting position
    void scursor();

    // Function for making equation based user input
    void mequation();

    // Function for cleaning LabelEdit field
    void cclear();

    //  Function for calculating inputed equation after '=' sign is pressed
    void cequal();

    // Function for drawing graph after 'Graph' button in pressed
    void cgraph();

//    // Function for credit calculater after 'Credit' button in pressed
//    void ccredit();

//    // Function for deposit calculater after 'Deposit button in pressed
//    void cdepos();

private:
    Ui::CalcWindow *ui;
    eflag flag = SUCCESS;
    bool contains_x = false;
    bool mbuf = false;
    QString buf = "";
};

#endif  // CALCWINDOW_H
