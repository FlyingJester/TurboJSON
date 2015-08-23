#pragma once
#include "parse.h"
#include "object.h"
#include "value.h"
#include <string>
#include <map>
#include <vector>
#include <cstdio>
#include <cassert>

namespace Turbo {
    
    typedef std::map<std::string, struct Turbo_Value> Object;
    typedef std::vector<struct Turbo_Value> Array;


    template<class ObjectClass = Object>
    void ConvertObject(ObjectClass &to, struct Turbo_Value &in){
        assert(in.type==TJ_Object);
        
        to.clear();
        
        for(unsigned i = 0; i<in.length; i++){
            to[in.value.object[i].name] = in.value.object[i].value;
        }
    }

    template<class ArrayClass = Array >
    void ConvertArray(ArrayClass &to, struct Turbo_Value &in){
        assert(in.type==TJ_Array);
        
        to.resize(in.length);
        
        for(unsigned i = 0; i<in.length; i++){
            to[i] = in.value.array[i];
        }
    }
    
    template<class T = std::string>
    T GetString(const struct Turbo_Value &in){
        assert(in.type==TJ_String);
        return in.value.string;
    }
        
    template<class T = double>
    T GetNumber(const struct Turbo_Value &in){
        assert(in.type==TJ_Number); 
        return in.value.number;
    }
    
    static inline bool GetBoolean(const struct Turbo_Value &in){
        assert(in.type==TJ_Boolean);
        return in.value.boolean;
    }
    
} // namespace Turbo
