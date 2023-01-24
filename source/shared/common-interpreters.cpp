#include <shared/common-interpreters.h>

QList<QPointF> Interpreter::SCF::Interpret(const std::vector<OptMove> &moves) {
  QList<QPointF> points;
  for (int i = 0; i < moves.size(); ++i) {
    for (int j = 0; j < moves[i].scf.at(key_).size(); ++j) {
      points.append(QPointF{ static_cast<double>(points.size()), moves[i].scf.at(key_)[j] });
    }
  }
  return points;
}

QList<QPointF> Interpreter::Fmax::Interpret(const std::vector<OptMove> &moves) {
  QList<QPointF> points;
  for (int i = 0; i < moves.size(); ++i) {
    points.append(QPointF{ static_cast<double>(i), moves[i].Fmax });
  }
  return points;
}

QList<QPointF> Interpreter::FreeEpV::Interpret(const std::vector<OptMove> &moves) {
  QList<QPointF> points;
  for (int i = 0; i < moves.size(); ++i) {
    points.append(QPointF{ static_cast<double>(i), moves[i].FreeE_pV });
  }
  return points;
}

QList<QPointF> Interpreter::TargetEnthalpy::Interpret(const std::vector<OptMove> &moves) {
  QList<QPointF> points;
  for (int i = 0; i < moves.size(); ++i) {
    points.append(QPointF{ static_cast<double>(i), moves[i].target_enthalpy });
  }
  return points;
}
