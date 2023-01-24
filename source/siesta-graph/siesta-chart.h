#ifndef SIESTACHART_H
#define SIESTACHART_H

#include <shared/interpreter.h>

#include <QString>

#include <QtCharts>

class SiestaChart : public QChart {
 Q_OBJECT

 public:
  SiestaChart(IInterpreter *interpreter,
              QString title = "", 
              QGraphicsItem *parent = nullptr, 
              Qt::WindowFlags wFlags = Qt::WindowFlags());
  ~SiestaChart();

 public slots:
  void Notify(const std::vector<OptMove> &moves);

 private:
  IInterpreter *interpreter_{ nullptr };
};

#endif // SIESTACHART_H
