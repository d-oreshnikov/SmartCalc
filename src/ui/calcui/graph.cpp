#include "graph.h"
#include "ui_graph.h"

Graph::Graph(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Graph)
{
    ui->setupUi(this);
    connect(ui->Reprint, SIGNAL(clicked()), this, SLOT(cplot()));
    connect(ui->setDefault, SIGNAL(clicked()), this, SLOT(setdefcoords()));
}

Graph::~Graph()
{
    delete ui;
}

void Graph::setscale() {
    this->lx = ui->xfromSlider->value();
    this->rx = ui->xtoSlider->value();

    this->ly = ui->yfromSlider->value();
    this->ry = ui->ytoSlider->value();
}

void Graph::setdefcoords() {
    this->ui->xfromSlider->setValue(0);
    this->ui->xtoSlider->setValue(0);
    this->lx = lx;
    this->rx = rx;

    this->ui->yfromSlider->setValue(0);
    this->ui->ytoSlider->setValue(0);
    this->ly = ly;
    this->ry = ry;
}

void Graph::scalling() {
    if (rx - lx <= 10) this->step = 0.00001;
    else if (rx - lx <= 100) this->step = 0.0001;
    else if (rx - lx <= 1000) this->step = 0.001;
    else if (rx - lx <= 10000) this->step = 0.01;
    else if (rx - lx <= 100000) this->step = 0.1;
    else if (rx - lx > 100000) this->step = 0.5;
}

eflag Graph::plot(char* equation) {
    eflag flag = SUCCESS;

    for (double x = lx; x <= rx; x += step) {
        double ans = 0;
        flag = calculate_equation(equation, x, &ans);

        if (flag == SUCCESS) {
            this->points.first.push_back(x);
            this->points.second.push_back(ans);
        }
    }

    return flag;
}

void Graph::cplot() {
    this->setscale();
    this->scalling();
    ui->graph->yAxis->setRange(this->ly, this->ry);
    ui->graph->xAxis->setRange(this->lx, this->rx);
    ui->graph->replot();
}

void Graph::pgraph() {
    ui->graph->yAxis->setRange(this->ly, this->ry);
    ui->graph->xAxis->setRange(this->lx, this->rx);
    ui->graph->addGraph();
    ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->graph->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));

    QVector<double> x_points = QVector<double>(this->points.first.begin(), this->points.first.end());
    QVector<double> y_points = QVector<double>(this->points.second.begin(), this->points.second.end());

    ui->graph->graph(0)->addData(x_points, y_points);
    ui->graph->replot();
    ui->graph->setInteraction(QCP::iRangeZoom, true);
    ui->graph->setInteraction(QCP::iRangeDrag, true);
}
