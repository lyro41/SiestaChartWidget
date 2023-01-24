//! @file interpreter.h
//! @authors Люпа Р.А.
//! @note Ответственный: Полевой Д.В.
//! @brief Головной заголовок для интерфейса интерпретатора

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <siesta-parser/siesta-parser.h>

#include <QList>
#include <QPointF>

#include <vector>

/// @brief опережающее определение структуры OptMove, содержащейся в библиотеке siesta-parser
struct OptMove;

/// @brief интерфейс интерпретатора, переводящего данные исполнения SIESTA в координаты точек для графика
class IInterpreter {
 public:
  /// @brief перевод данных исполнения SIESTA в координаты точек для построения графика
  /// @param moves ключевая информация об итерациях программы SIESTA
  /// @return пригодный для построения графика формат массива точек
  virtual QList<QPointF> Interpret(const std::vector<OptMove> &moves) = 0;
};

#endif // INTERPRETER_H
