#include <qparser.h>

#ifdef __unix__
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#endif // __unix__

#include <QThread>

QParser::QParser(QObject *parent, int pid, int delay)
  : QObject(parent)
  , pid_(pid)
  , delay_(delay) {
  return;
}

void QParser::RunParser() {
  std::string source_path = std::string(EXECUTION_DIR) + "/" + SIESTA_OUTPUT;
  bool stopped = false;
  while (!stopped) {
    int status;
    #ifdef __unix__
    int wpid = waitpid(pid_, &status, WNOHANG);
    if (wpid < 0) {
      return;
    } else if (wpid > 0) {
      stopped = true;
    }
    #elif _WIN32
    stopped = true;
    #endif
    QThread::sleep(delay_);
    #ifdef __unix__
    kill(pid_, SIGSTOP);
    #endif
    std::FILE *stream = std::fopen((std::string(EXECUTION_DIR) + "/" + SIESTA_OUTPUT).c_str(), "r");
    if (stream == NULL) {
      errno = ENOENT;
      return;
    }
    auto data = this->ParseCGOptMoves(stream);
    std::fclose(stream);
    #ifdef __unix__
    kill(pid_, SIGCONT);
    #endif
    emit Parsed(data);
  }
  return;
}
