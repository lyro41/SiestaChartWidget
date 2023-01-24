#ifndef INTERPRETERS_H
#define INTERPRETERS_H

#include <shared/interpreter.h>

#include <string>

namespace Interpreter {
  class SCF : public IInterpreter {
   public:
    SCF(std::string key = "") : key_(key) {}
    ~SCF() = default;

    virtual QList<QPointF> Interpret(const std::vector<OptMove> &moves) override;

   private:
    std::string key_{ "" };
  };

  class Fmax : public IInterpreter {
   public:
    Fmax() = default;
    ~Fmax() = default;

    virtual QList<QPointF> Interpret(const std::vector<OptMove> &moves) override;
  };

  class FreeEpV : public IInterpreter {
   public:
    FreeEpV() = default;
    ~FreeEpV() = default;

    virtual QList<QPointF> Interpret(const std::vector<OptMove> &moves) override;
  };

  class TargetEnthalpy : public IInterpreter {
   public:
    TargetEnthalpy() = default;
    ~TargetEnthalpy() = default;

    virtual QList<QPointF> Interpret(const std::vector<OptMove> &moves) override;
  };
};

#endif // INTERPRETERS_H
