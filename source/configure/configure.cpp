#include <config.h>
#include <configure.h>

#include <cstdio>
#include <cstring>

#include <filesystem>

int ChangeSiestaPath(const std::string &new_path) {
  if (!new_path.ends_with(SIESTA_EXE_NAME))  {
    return ENOEXEC;
  }

  if (!std::filesystem::exists(new_path)) {
    return ENOENT;
  }

  std::FILE *istream = std::fopen(SIESTA_CONFIG, "r");
  if (istream == NULL) {
    std::FILE *ostream = std::fopen(SIESTA_CONFIG, "w");
    if (ostream == NULL) {
      return ENOENT;
    }
    std::fprintf(ostream, "%s %s\n", SIESTA_CFG_KEY_PATH, new_path.c_str());
    std::fclose(ostream);
    return 0;
  }
  
  std::FILE *ostream = std::fopen((std::string(SIESTA_CONFIG) + "_tmp").c_str(), "w");
  if (ostream == NULL) {
    return ENOENT;
  }

  char buff[BUFFSIZE];
  while (std::fscanf(istream, "%s", buff) != EOF) {
    if (std::strcmp(buff, SIESTA_CFG_KEY_PATH) == 0) {
      std::fprintf(ostream, "%s %s", SIESTA_CFG_KEY_PATH, new_path.c_str());
      std::fscanf(istream, "%*[^\n]\n");
    } else {
      std::fprintf(ostream, "%s ", buff);
      std::fscanf(istream, "%[^\n]s\n", buff);
      std::fprintf(ostream, "%s\n", buff);
    }
  }
  std::fclose(istream);
  std::fclose(ostream);
  std::remove(SIESTA_CONFIG);
  std::rename((std::string(SIESTA_CONFIG) + "_tmp").c_str(), SIESTA_CONFIG);
  return 0;
}
