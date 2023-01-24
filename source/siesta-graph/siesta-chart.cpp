#include <siesta-chart.h>

#include <QLineSeries>

SiestaChart::SiestaChart(IInterpreter *interpreter,
                         QString title, 
                         QGraphicsItem *parent, 
                         Qt::WindowFlags wFlags)
  : interpreter_(interpreter)
  , QChart(parent, wFlags) {
  this->setTitle(title);
  this->addSeries(new QLineSeries());
  this->legend()->hide();
  this->createDefaultAxes();
  return;
}

SiestaChart::~SiestaChart() {
  delete interpreter_;
  return;
}

void SiestaChart::Notify(const std::vector<OptMove> &moves) {
  QList<QPointF> points = interpreter_->Interpret(moves);
  this->removeAllSeries();
  auto series = new QLineSeries();
  series->append(points);
  this->addSeries(series);
  this->createDefaultAxes();
  return;
}
