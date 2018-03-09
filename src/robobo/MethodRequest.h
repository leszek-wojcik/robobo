#ifndef METHOD_REQUEST_INCLUDED
#define METHOD_REQUEST_INCLUDED

#include <tuple>

class MethodRequestBase
{
    public:
        bool persistent;
        MethodRequestBase(): persistent(0) { }
        virtual void execute();
};

template<int ...> struct seq {};
template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};
template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };

template <class AO, typename ...Args>
class MethodRequest: public MethodRequestBase
{
    public:
        std::tuple<Args...> params;
        void (AO::*method_to_call)(Args...) ;
        AO &object;

        MethodRequest(AO &o, void (AO::*method)(Args...), Args... x):
            params(x...),
            object(o),
            method_to_call(method)
        {
        }

        void execute()
        {
            callFunc(typename gens<sizeof...(Args)>::type());
        }

        template<int ...S>
        void callFunc(seq<S...>)
        {
           (object.*method_to_call)(std::get<S>(params) ...);
        }

};

#define MR1(classtype,object,funct,argtype,argval)  new  MethodRequest<classtype, argtype>( object, & classtype::funct, argval)

#define MR0(classtype,object,funct)  new  MethodRequest<classtype >( object, & classtype::funct )

#endif
