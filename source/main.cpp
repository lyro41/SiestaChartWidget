#include <config.h>
#include <configure/configure.h>
#include <siesta-manager/siesta-manager.h>
#include <siesta-graph/siesta-graph.h>
#include <siesta-graph/qparser.h>

#include <cerrno>
#include <cstdio>
#include <cstring>

#ifdef __unix__
#include <unistd.h>
#endif // __unix__

#include <iostream>
#include <filesystem>

#include <QObject>
#include <QThread>

int main(int argc, char *argv[]) {
  qRegisterMetaType<std::vector<OptMove>>("std::vector<OptMove>");
  if (argv[argc] != 0) {
    return E2BIG;
  }
  bool siesta = false;
  int delay = 3;
  for (int i = 1; i < argc; ++i) {
    if (std::strcmp(argv[i], CMD_PATH) == 0 ||
        std::strcmp(argv[i], CMD_PATH_SHORT) == 0) {
      if (i + 1 == argc) {
        return EINVAL;
      }
      int err_code = ChangeSiestaPath(argv[++i]);
      if (err_code != 0) {
        return err_code;
      }
    } else if (std::strcmp(argv[i], CMD_LAUNCH) == 0 ||
               std::strcmp(argv[i], CMD_LAUNCH_SHORT) == 0) {
      siesta = true;
    } else if (std::strcmp(argv[i], CMD_DELAY) == 0 ||
               std::strcmp(argv[i], CMD_DELAY_SHORT) == 0) {
      if (i + 1 == argc) {
        return EINVAL;
      }
      delay = std::atoi(argv[++i]);
    }
  }

  #ifdef __unix__
  int pid = fork();
  if (pid == 0) {
    if (siesta) {
      return LaunchSiesta();
    } else {
      return 0;
    }
  } else if (pid < 0) {
    return errno;
  }
  #elif _WIN32
  int pid = 0;
  #endif // __unix__

  #ifdef _WIN32 
  if (siesta) {
    std::cout << "warning: siesta isn't implemented for Windows yet\n";
  }
  // Graph()
  #endif // Windows

  QApplication siesta_graph_app(argc, argv);
  QParser *parser = new QParser(nullptr, pid, delay);
  MainWindow main_window(parser);
  QThread *thread = new QThread();
  QObject::connect(thread, SIGNAL(started()), parser, SLOT(RunParser()));
  QObject::connect(parser, SIGNAL(SiestaStopped()), thread, SLOT(quit()));
  QObject::connect(parser, SIGNAL(SiestaStopped()), parser, SLOT(deleteLater()));
  QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  parser->moveToThread(thread);
  thread->start();
  main_window.show();
  int execution = siesta_graph_app.exec();
  thread->exit();
  return execution;
}
