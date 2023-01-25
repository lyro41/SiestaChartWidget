#include <siesta-manager/siesta-manager.h>

#include <cerrno>
#include <cstdio>
#include <cstring>

#ifdef __unix__ 

std::string CreateShellScript(const std::string &siesta_path) {
  std::string script_path = std::string(EXECUTION_DIR) + "/" + SHELL_SCRIPT_NAME;
  std::FILE *stream = std::fopen(script_path.c_str(), "w");
  if (stream == NULL) {
    throw; // TODO: show an exception
  } else {
    {
      // move to execution directory
      std::fprintf(stream, "cd %s \n", 
                           EXECUTION_DIR);

      // remove non-actual link to siesta executable
      std::fprintf(stream, "find . -maxdepth 1 -type l -executable -name %s -delete \n", 
                           SIESTA_EXE_NAME);

      // make new link to siesta executable
      std::fprintf(stream, "ln -s %s \n", 
                           siesta_path.c_str());

      // start calculation process and restream error messages to log file
      std::fprintf(stream, "./%s < %s > %s \n", 
                           SIESTA_EXE_NAME, SIESTA_SOURCE, SIESTA_OUTPUT);

      // after calculation start parsing output files

      std::fclose(stream);
      return script_path;
    } 
  }
}

int LaunchSiesta() {
  CreateShellScript(GetSiestaPath());

  #ifdef __unix__
  return system((std::string("sh ") + EXECUTION_DIR + "/" + SHELL_SCRIPT_NAME).c_str());
  #endif // __unix__

  return ECANCELED;
}

#endif // __unix__

std::string GetSiestaPath() {
  std::FILE *stream = std::fopen(SIESTA_CONFIG, "r");
  if (stream == NULL) {
    return std::string("\0");
  }
  char buff[BUFFSIZE];
  while (std::fscanf(stream, (std::string(SIESTA_CFG_KEY_PATH) + " %[^\n]s\n").c_str(), buff) != 1) {
    if (std::feof(stream)) {
      return std::string("\0");
    }
  }
  std::fclose(stream);
  return std::string(buff);
}
