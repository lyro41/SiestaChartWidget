#ifndef QPARSER_H
#define QPARSER_H

#include <siesta-parser/siesta-parser.h>

#include <QObject>

class QParser : public QObject, public Parser {
 Q_OBJECT

 public:
  QParser(QObject *parent = nullptr, int pid = 0, int delay = 3);
  ~QParser() = default;

 public slots:
  void RunParser();

 signals:
  void Parsed(const std::vector<OptMove> &moves);
  void SiestaStopped();

 private:
  int pid_{ 0 };
  int delay_{ 3 };
};

#endif // QPARSER_H
