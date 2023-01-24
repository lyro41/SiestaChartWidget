//! @file siesta-manager.h
//! @authors Люпа Р.А.
//! @note Ответственный: Полевой Д.В.
//! @brief Головной заголовок для библиотеки siesta-manager

#ifndef SIESTA_LAUNCH_H
#define SIESTA_LAUNCH_H

#include <config.h>

#include <string>

#ifdef __unix__

/// @brief функция для создания bash-скрипта для подключения SIESTA во время исполнения программы
/// @param[in] siesta_path путь до исполняемого файла SIESTA
/// @return путь до bash-скрипта
std::string CreateShellScript(const std::string &siesta_path);

#endif // __unix__

/// @brief функция получения пути до исполняемого файла SIESTA из файла siesta.cfg
/// @return путь до исполняемого файла SIESTA
std::string GetSiestaPath();
/// @brief функция для запуска работы SIESTA
/// @return код ошибки выполнения функции
int LaunchSiesta();

#endif // SIESTA_LAUNCH_H
