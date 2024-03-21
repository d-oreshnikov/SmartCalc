#include "calcwindow.h"
#include "./ui_calcwindow.h"

CalcWindow::CalcWindow(QWidget *parent) 
    : QMainWindow(parent)
    , ui(new Ui::CalcWindow)
{
    ui->setupUi(this);
    scursor();

    // Util buttons
    connect(ui->ButtonGraph, SIGNAL(clicked()), this, SLOT(cgraph()));
//    connect(ui->ButtonDeposit, SIGNAL(clicked()), this, SLOT(cdepos()));
//    connect(ui->ButtonCredit, SIGNAL(clicked()), this, SLOT(ccredit()));
    connect(ui->ButtonBackspace, SIGNAL(clicked()), this, SLOT(mbackspace()));

    // Number buttons
    connect(ui->Button0, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->Button1, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->Button2, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->Button3, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->Button4, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->Button5, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->Button6, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->Button7, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->Button8, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->Button9, SIGNAL(clicked()), this, SLOT(psignal()));

    // X button
    connect(ui->ButtonX, SIGNAL(clicked()), this, SLOT(psignal()));

    // Brackets buttons
    connect(ui->ButtonOpenBracket, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonCloseBracket, SIGNAL(clicked()), this, SLOT(psignal()));

    // Operators buttons
    connect(ui->ButtonMinus, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonPlus, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonDiv, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonMult, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonPow, SIGNAL(clicked()), this, SLOT(psignal()));

    // Dot button
    connect(ui->ButtonDot, SIGNAL(clicked()), this, SLOT(psignal()));

    // Funcs buttons
    connect(ui->ButtonSin, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonCos, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonTan, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonAsin, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonAcos, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonAtan, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonLog, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonLn, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonMod, SIGNAL(clicked()), this, SLOT(psignal()));
    connect(ui->ButtonSqrt, SIGNAL(clicked()), this, SLOT(psignal()));

    // Equal button
    connect(ui->ButtonEqual, SIGNAL(clicked()), this, SLOT(psignal()));
}


//CalcWindow destructor. Cleans allocated memory and destroy CalcWindow object
CalcWindow::~CalcWindow()
{
    delete ui;
}


void CalcWindow::psignal() {
    QPushButton* button = (QPushButton*)sender();
    QString btext = button->text();

    if (ui->InputDisplay->text() == "ERROR" || ui->InputDisplay->text() == "nan") {
        cclear();
        flag = SUCCESS;
    }

    if (btext == "=") {
        cequal();
        return;
    }

    mequation();
}

//  Function for handling backspace button
void CalcWindow::mbackspace() {
    QPushButton* button = (QPushButton*)sender();
    QString newedit = ui->InputDisplay->text();

    if (button->text() == "Del" && newedit == "") scursor();
    else if (button->text() == "Del") {
        newedit.chop(1);
    }

    ui->InputDisplay->setText(newedit);
}

void CalcWindow::scursor() { ui->InputDisplay->setCursorPosition(0); }


void CalcWindow::mequation() {
    QPushButton* button = (QPushButton*)sender();
    QString btext = button->text();

    if (ui->InputDisplay->text() == "") {
        if (btext == ".") ui->InputDisplay->setText("0" + btext);
        else if (btext.contains("s") || btext.contains("a") || btext.contains("l")) {
            ui->InputDisplay->setText(btext + "(");
        } else ui->InputDisplay->setText(btext);
    } else {
        if (btext.contains("s") || btext.contains("a") || btext.contains("l")) {
            ui->InputDisplay->setText(ui->InputDisplay->text() + btext + "(");
        } else ui->InputDisplay->setText(ui->InputDisplay->text() + btext);
    }
}

void CalcWindow::cclear() {
    ui->InputDisplay->setText("");
}

void CalcWindow::cequal() {
    double ans = 0.0;
    QString input_experssion = ui->InputDisplay->text();
    QByteArray sequence = input_experssion.toLocal8Bit();
    char* infix = sequence.data();

    eflag flag = calculate_equation(infix, 0, &ans);

    if (flag) ui->InputDisplay->setText("ERROR");
    else {
        QString ansstr = QString::number(ans, 'g', 8);
        ui->InputDisplay->setText(ansstr);
    }

    flag = SUCCESS;
}

void CalcWindow::cgraph() {
    Graph* graph = new Graph();

    QString equation = ui->InputDisplay->text();
    QByteArray sequence = equation.toLocal8Bit();
    char *infix = sequence.data();
    size_t ilength = 0;
    token* infix_tokens = tokenize(infix, &ilength);

    if (infix_tokens) {
        graph->scalling();
        graph->plot(infix);
        graph->pgraph();

        graph->show();

    } else ui->InputDisplay->setText("ERROR");
    
    free(infix_tokens);
}

