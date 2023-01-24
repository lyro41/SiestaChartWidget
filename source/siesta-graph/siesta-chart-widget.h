#ifndef SIESTACHARTWIDGET_H
#define SIESTACHARTWIDGET_H

#include <siesta-graph/siesta-chart.h>

#include <QtCharts>

#include <QGridLayout>
#include <QWidget>

#include <QList>

class SiestaChartWidget : public QWidget {
 Q_OBJECT

 public:
  SiestaChartWidget(QWidget *parent = nullptr);
  ~SiestaChartWidget();

  void AddChart(SiestaChart *chart);
  void SaveCharts();

 private:
  void UpdateLayout();

  QGridLayout *layout_{ nullptr };
  QList<QChartView *> chart_views_;
};

#endif // SIESTACHARTWIDGET_H
