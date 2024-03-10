#ifndef GRAPH_H_
#define GRAPH_H_

#include <QWidget>

extern "C" {   
#include "../../backend/calculation/calculation.h"
}

namespace Ui { class Graph; }

class Graph : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Graph class constructor. Also connects graph drawing button with backend
     * 
     * @param parent Parent class value
     */
    Graph(QWidget* parent = nullptr);

    /**
     * @brief Graph class destructor. Cleans allocated memory and destroy Graph object
     */
    ~Graph();

    /**
     * @brief Function 
     */
    void scalling();
    void setscale();
    eflag plot(char* equation);
    void pgraph();

private slots:
    void cplot();
    void setdefcoords();

private:
    Ui::Graph* ui;
    double lx = -100;
    double rx =  100;
    double ly = -100;
    double ry =  100;
    double step = 0.0;
    std::pair<std::vector<double>, std::vector<double>> points;
};

#endif  // GRAPH_H_
