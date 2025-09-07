#ifndef ISTATE_H_
#define ISTATE_H_

namespace Compiler {

class IState {
public:
    virtual ~IState() = default;
    virtual bool IsStartState() const = 0;
    virtual bool IsAcceptingState() const = 0;
    virtual void SetStartState(bool isStart) = 0;
    virtual void SetAcceptingState(bool isAccepting) = 0;
};

}  // namespace Compiler

#endif  // ISTATE_H_