#include "closure.h"
#include "cons.h"
#include "env.h"
#include "eval.h"
#include "object.h"
#include "print.h"
#include "symbol.h"

pobject closure_new(pobject env, pobject params, pobject code)
{
    pobject o = object_new(T_CLOSURE);
    o->data.closure.env = env;
    o->data.closure.code = cons_new(params, object_prepend_begin(code));
    return o;
}

pobject closure_eval(pobject call_env, pobject closure, pobject params)
{
    pobject params_symbols = cons_car( closure->data.closure.code );
    pobject code = cons_cdr( closure->data.closure.code );
    pobject env  = cons_new( symbol_parent_env, 
                       cons_new( closure->data.closure.env, NIL ) );

    while (params_symbols) {
        env = cons_new( cons_car( params_symbols),
                  cons_new( eval( call_env, cons_car( params ) ), env ) );
        params_symbols = cons_cdr(params_symbols);
        params = cons_cdr(params);
    }

    println(env);

    return eval(env, code);
}
