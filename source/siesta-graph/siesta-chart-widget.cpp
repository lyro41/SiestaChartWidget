#include <config.h>
#include <siesta-chart-widget.h>

#include <cmath>

#include <string>

#include <QFile>
#include <QPainter>
#include <QPixmap>
#include <QString>

const double kEps = 1e-5;

SiestaChartWidget::SiestaChartWidget(QWidget *parent) 
  : QWidget(parent)
  , layout_(new QGridLayout(this)) {
  this->setMinimumWidth(1280);
  this->setMinimumHeight(720);
}

SiestaChartWidget::~SiestaChartWidget() {
  SaveCharts();
  delete layout_;
}

void SiestaChartWidget::AddChart(SiestaChart *chart) {
  chart_views_.append(new QChartView(chart));
  this->UpdateLayout();
  this->repaint();
  return;
}

void SiestaChartWidget::SaveCharts() {
  for (int i = 0; i < chart_views_.size(); ++i) {
    QPixmap pixmap(chart_views_[i]->size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    chart_views_[i]->render(&painter);
    QFile file(QString(CHARTS_OUTPUT) + "/" + QString::number(i) + ".png");
    file.open(QIODevice::WriteOnly);
    pixmap.save(&file, "PNG");
    file.close();
  }
}

void SiestaChartWidget::UpdateLayout() {
  int h = std::floor(std::sqrt(chart_views_.size()) + kEps) + kEps;
  int w = h * h == chart_views_.size() ? h : h + 1;
  delete layout_;
  layout_ = new QGridLayout(this);
  for (int i = 0; i < chart_views_.size(); ++i) {
    layout_->addWidget(chart_views_[i], i / w, i % w);
  }
  return;
}
