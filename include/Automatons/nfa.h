#ifndef NFA_H_
#define NFA_H_

#include <concepts>
#include <type_traits>
#include <functional>
#include <unordered_map>
#include <vector>
#include "istate.h"


namespace Compiler {

template <typename T, template <class> typename A>
concept Alphabet = requires(const std::remove_reference_t<A<T>&> a) {
    { std::hash<std::remove_cvref_t<A<T>>>{}(a) } -> std::convertible_to<std::size_t>;
};

template <class T,template <class> typename A>
concept HashKey =
    std::equality_comparable<T> && requires(const T& t) {
        { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
    };

template <typename T, template <class> typename A>
concept HasEpsilon = requires {
    { A<T>::epsilon } -> std::convertible_to<T>;
};

class NState : public IState{
    bool isStartState;
    bool isAcceptingState;

public:
    NState() : isStartState(false), isAcceptingState(false) {}
    NState(bool iss, bool ias = false): isStartState(iss), isAcceptingState(ias){}    
    ~NState() = default;

    bool IsStartState() const override{return isStartState;}
    bool IsAcceptingState() const override{return isAcceptingState;}
    void SetStartState(bool isStart) override {isStartState = isStart;}
    void SetAcceptingState(bool isAccepting)override {isAcceptingState = isAccepting;}
};

template <typename T, template <class> typename A>
requires HasEpsilon<T, A> && HashKey<T, A>
class NfaFragment {
private:
    std::unordered_map<std::shared_ptr<NState>, std::unordered_map<T, std::vector<std::shared_ptr<NState>>>> transitions;
    std::shared_ptr<NState> startState;
    std::vector<std::shared_ptr<NState>> acceptStates;
public:
    
    NfaFragment(){}

    NfaFragment(std::shared_ptr<NState> start, const vector<std::shared_ptr<NState>> &accepts)
        : startState(start), acceptStates(accepts) {
        
            startState->SetStartState(true);
        
            for (auto& state : acceptStates) {
                state->SetAcceptingState(true);
            }
    }

    NfaFragment(const NfaFragment& other) = default;
    NfaFragment(NfaFragment&& other) = default;

    NfaFragment& operator=(const NfaFragment& other) = default;
    NfaFragment& operator=(NfaFragment&& other) = default;

    NfaFragment& addTransition(NfaFragment& from, const T& symbol, NfaFragment& to) {
       
        for(auto &aptr : from.acceptStates){
            aptr->SetAcceptingState(false);
            from.transitions[aptr][T] = to.startState;
        }

        to.startState->SetStartState(false);
        from.acceptStates.clear();
        return *this;
    }

    ~NfaFragment() = default;

    static NfaFragment createSingleStateFragment(std::shared_ptr<NState> s){
        s->SetAcceptingState(true);
        s->SetStartState(true);
        NfaFragment frag(s,std::vector<std::shared_ptr<NState>>{s});
        return frag;
    }

    static NfaFragment createBasicFragment(const T& symbol) {
        auto start = std::shared_ptr<NState>::make_shared(true,false);
        auto accept = std::shared_ptr<NState>::make_shared(false,true);

        auto frag1 = createSingleStateFragment(start);
        auto frag2 = createSingleStateFragment(accept);
    
        NfaFragment fragment;
        fragment.addTransition(frag1, symbol, frag2);
        return fragment;
    }

    static NfaFragment createEpsilonFragment() {
        auto start = std::shared_ptr<NState>::make_shared(true,false);
        auto accept = std::shared_ptr<NState>::make_shared(false,true);

        NfaFragment fragment;
        fragment.addTransition(start, A<T>::epsilon, accept);
        return fragment;
    }

    static NfaFragment createUnionFragment(NfaFragment& frag1, NfaFragment& frag2) {
       
    }


    namespace std {
    template<>
    struct hash<shared_ptr<NState>> {
        size_t operator()(const std::shared_ptr<NState>& ptr) const {
            return hash<NState*>()(ptr.get());
        }
    };
}

};

}  // namespace Compiler

#endif  // NFA_H_