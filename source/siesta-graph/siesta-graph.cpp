#include <siesta-graph.h>
#include <shared/common-interpreters.h>

MainWindow::MainWindow(QParser *parser, QWidget *parent) 
  : QMainWindow(parent)
  , chart_widget_(new SiestaChartWidget) {
  this->setWindowTitle("SIESTA Visualizer");
  this->setCentralWidget(chart_widget_);
  auto chart1 = new SiestaChart(new Interpreter::Fmax(), "Fmax");
  connect(parser, &QParser::Parsed, chart1, &SiestaChart::Notify);
  auto chart2 = new SiestaChart(new Interpreter::FreeEpV(), "(free)E + p*V");
  connect(parser, &QParser::Parsed, chart2, &SiestaChart::Notify);
  auto chart3 = new SiestaChart(new Interpreter::TargetEnthalpy(), "Target Enthalpy");
  connect(parser, &QParser::Parsed, chart3, &SiestaChart::Notify);
  auto chart4 = new SiestaChart(new Interpreter::SCF("Eharris(eV)"), "Eharris(eV)");
  connect(parser, &QParser::Parsed, chart4, &SiestaChart::Notify);
  auto chart5 = new SiestaChart(new Interpreter::SCF("E_KS(eV)"), "E_KS(eV)");
  connect(parser, &QParser::Parsed, chart5, &SiestaChart::Notify);
  auto chart6 = new SiestaChart(new Interpreter::SCF("FreeEng(eV)"), "FreeEng(eV)");
  connect(parser, &QParser::Parsed, chart6, &SiestaChart::Notify);
  auto chart7 = new SiestaChart(new Interpreter::SCF("dDmax"), "dDmax");
  connect(parser, &QParser::Parsed, chart7, &SiestaChart::Notify);
  auto chart8 = new SiestaChart(new Interpreter::SCF("Ef(eV)"), "Ef(eV)");
  connect(parser, &QParser::Parsed, chart8, &SiestaChart::Notify);
  auto chart9 = new SiestaChart(new Interpreter::SCF("dHmax(eV)"), "dHmax(eV)");
  connect(parser, &QParser::Parsed, chart9, &SiestaChart::Notify);
  chart_widget_->AddChart(chart1);
  chart_widget_->AddChart(chart2);
  chart_widget_->AddChart(chart3);
  chart_widget_->AddChart(chart4);
  chart_widget_->AddChart(chart5);
  chart_widget_->AddChart(chart6);
  chart_widget_->AddChart(chart7);
  chart_widget_->AddChart(chart8);
  chart_widget_->AddChart(chart9);
  return;
}

MainWindow::~MainWindow() {
  delete chart_widget_;
}
