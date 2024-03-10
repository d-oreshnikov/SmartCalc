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

/**
 * @brief SmartCalc window class. It inherits from QMainWindow, so
 * it has all of QMainWindow's attributes and methods
 * CalcWindow has functionality for handling signals from user, parsing
 * input equation calculating inputed equation and drawing resulting graph
 */
class CalcWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief CalcWindow constructor. Also connects ui buttons with backend
     * 
     * @param parent Parent class value
     */
    CalcWindow(QWidget *parent = nullptr);

    /**
     * @brief CalcWindow destructor. Cleans allocated memory and destroy CalcWindow object
     */
    ~CalcWindow();

private slots:
    /**
     * @brief Function for handling signals from user
     */
    void psignal();

    /**
     * @brief Function for handling memory (M+, M-, M) buttons
     */
    void mmemory();

    /**
     * @brief Function for handling backspace button
     */
    void mbackspace();

    /**
     * @brief Function for setting cursor to starting position
     */
    void scursor();

    /**
     * @brief Function for making equation based user input
     */
    void mequation();

    /**
     * @brief Function for cleaning LabelEdit field
     */
    void cclear();

    /**
     * @brief Function for calculating inputed equation after '=' sign is pressed
     */
    void cequal();

    /**
     * @brief Function for drawing graph after 'Graph' button in pressed
     * 
     */
    void cgraph();

private:
    Ui::CalcWindow *ui;
    eflag flag = SUCCESS;
    bool contains_x = false;
    bool mbuf = false;
    QString buf = "";
};

#endif  // CALCWINDOW_H
