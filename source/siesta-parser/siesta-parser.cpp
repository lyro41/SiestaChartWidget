#include <siesta-parser.h>

#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <cstring>

std::vector<OptMove> Parser::ParseCGOptMoves(std::FILE *stream) const {
  std::vector<OptMove> result(0);
  char buff[BUFFSIZE];
  bool is_good = true;
  while (std::fscanf(stream, "%s", buff) != EOF) {
    if (std::strcmp(buff, "Begin") == 0) {
      int move;
      if (std::fscanf(stream, " CG opt. move = %d", &move) == 1) {
        if (move == result.size()) {
          while (std::fscanf(stream, "%s", buff) != EOF) {
            if (std::strcmp(buff, "iscf") == 0) {
              is_good = false;
              result.push_back(OptMove{});
              std::vector<std::string> keys;
              keys.push_back(buff);
              char buff_c = std::fgetc(stream);
              while (buff_c != '\n') {
                int i = 0;
                while (std::isspace(buff_c)) {
                  buff_c = std::fgetc(stream);
                }
                while (!std::isspace(buff_c)) {
                  buff[i++] = buff_c;
                  buff_c = std::fgetc(stream);
                }
                buff[i] = '\0';
                keys.push_back(buff);
              }
              while (std::fscanf(stream, "%s", buff) != EOF && std::strcmp(buff, "SCF") != 0) {
                if (std::strcmp(buff, "scf:") == 0) {
                  for (int i = 0; i < keys.size(); ++i) {
                    std::fscanf(stream, "%s", buff);
                    if (std::feof(stream)) {
                      errno = ENOMSG;
                      return result;
                    }
                    result.back().scf[keys[i]].push_back(std::strtod(buff, NULL));
                  }
                } else {
                  std::fscanf(stream, "%*[^\n]\n");
                }
              }
            } else if (std::strcmp(buff, "siesta:") == 0) {
              if (std::fscanf(stream, "%[^\n]s\n", buff) != EOF) {
                if (std::strcmp(buff, " Atomic forces (eV/Ang):") == 0) {
                  while (std::fscanf(stream, "%s", buff) != EOF) {
                    if (std::strcmp(buff, "Max") == 0) {
                      if (std::fscanf(stream, "%lf", &(result.back().Fmax)) != 1) {
                        errno = EINVAL;
                        return result;
                      } else {
                        break;
                      }
                    }
                  }
                }
              }
            } else if (std::strcmp(buff, "(Free)E") == 0) {
              if (std::fscanf(stream, " + p*V (eV/cell) %lf", &(result.back().FreeE_pV)) != 1) {
                errno = EINVAL;
                return result;
              }
            } else if (std::strcmp(buff, "Target") == 0) {
              if (std::fscanf(stream, " enthalpy (eV/cell) %lf", &(result.back().target_enthalpy)) != 1) {
                errno = EINVAL;
                return result;
              }
              is_good = true;
              break;
            }
          }
        }
      }
      continue;
    }
  }
  if (!is_good) {
    result.pop_back();
  }
  return result;
}
