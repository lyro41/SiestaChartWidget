#ifndef SIESTAGRAPH_H
#define SIESTAGRAPH_H

#include <siesta-graph/siesta-chart-widget.h>
#include <siesta-graph/qparser.h>

#include <QMainWindow>

class MainWindow : public QMainWindow {
 Q_OBJECT

 public:
  MainWindow(QParser *parser, QWidget *parent = nullptr);
  ~MainWindow();

 private:
  SiestaChartWidget *chart_widget_{ nullptr };
};

#endif // SIESTAGRAPH_H
