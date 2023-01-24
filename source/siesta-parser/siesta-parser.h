//! @file siesta-parser.h
//! @authors Люпа Р.А.
//! @note Ответственный: Полевой Д.В.
//! @brief Головной заголовок для библиотеки siesta-parser

#ifndef SIESTAPARSER_H
#define SIESTAPARSER_H

#include <config.h>

#include <cstdio>

#include <map>
#include <string>
#include <vector>

/// @brief структура данных, содержащая основную информацию о системе атомов 
/// @brief во время итерации CG opt. move программы SIESTA
struct OptMove {
  /// @brief словарь, содержащий информацию об SCF-сходимости
  std::map<std::string, std::vector<double>> scf;
  /// @brief параметр Fmax системы атомов после итерации
  double Fmax{ 0.0 };
  /// @brief параметр [(free)E + p*V] системы атомов после итерации
  double FreeE_pV{ 0.0 };
  /// @brief параметр target enthalpy системы атомов после итерации
  double target_enthalpy{ 0.0 };
};

/// @brief отвечает за парсинг выходных данных программы SIESTA
class Parser {
 public:
  /// @brief конструктор по умолчанию
  Parser() = default;
  /// @brief деструктор по умолчанию
  ~Parser() = default;
  /// @brief функция парсинга выходных данных программы SIESTA
  /// @param stream указатель на файловый поток C для чтения данных программы SIESTA
  /// @return массив структур типа OptMove, содержащего ключевые данные работы программы
  std::vector<OptMove> ParseCGOptMoves(std::FILE *stream) const;
};

#endif // SIESTAPARSER_H
