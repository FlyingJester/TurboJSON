#include "turbojson.hpp"
#include "whitespace.h"
#include "parse_number.h"
#include "string.h"

namespace TurboJSON {

Value::~Value(){}

class StringValue : public Value {
protected:
    const std::string string;
public:
    StringValue(const std::string &s)
      : string(s){}

    virtual ~StringValue(){}

    Type type() const override { return TurboJSON::String; };
    const std::string &String() const override { return string; }
};

template<bool B>
class BooleanValue : public Value {
public:

    virtual ~BooleanValue(){}

    Type type() const override { return TurboJSON::Boolean; };
    bool Boolean() const override { return B; }
};

class NullValue : public Value {
public:

    virtual ~NullValue(){}

    Type type() const override { return TurboJSON::Null; };
};

class NumberValue : public Value {
    const double number;
public:
    NumberValue(double n)
      : number(n) {}

    virtual ~NumberValue(){}

    Type type() const override { return TurboJSON::Number; };
    double Number() const override {return number; };
};

class ObjectValue : public Value {
public:

    virtual ~ObjectValue(){}

    std::map<std::string, std::unique_ptr<Value> >map;
    Type type() const override { return TurboJSON::Object; };
    const std::map<std::string, std::unique_ptr<Value> > *Object() const override { return &map; };
};

class ArrayValue : public Value {
public:

    virtual ~ArrayValue(){}

    std::vector<std::unique_ptr<Value> >array;
    Type type() const override { return TurboJSON::Array; };
    const std::vector<std::unique_ptr<Value> > *Array() const override { return &array; };
};

Value *ParseNumber(const std::string &str, std::string::const_iterator &i, const std::string::const_iterator){
    double that;
    
    const int difference = ::ParseNumber(str.c_str() + (i - str.cbegin()), &that);
    if(difference<0)
        return nullptr;
    
    i+=difference;
    
    return new NumberValue(that);
    
}

Value *ParseValue(const std::string &str, std::string::const_iterator &i, const std::string::const_iterator end){
    switch(*i){
        case '[':
        
        case '{':
        case '"':
        
        case '0':
        case '9':
        case '8':
        case '7':
        case '6':
        case '5':
        case '4':
        case '3':
        case '2':
        case '1':
            return ParseNumber(str, i, end);
            
        case 'n':
            if(compare_strings(str.c_str() + (i - str.cbegin()), "null", 4))
                return new NullValue();
            else
                return nullptr;
        case 't':
            if(compare_strings(str.c_str() + (i - str.cbegin()), "true", 4))
                return new NullValue();
            else
                return nullptr;
            
        case 'f':
            if(compare_strings(str.c_str() + (i - str.cbegin()), "false", 5))
                return new NullValue();
            else
                return nullptr;
        
        break;
        default:
            return nullptr;
    }
    return nullptr;
}

Value *Parse(const std::string &source){
    std::string::const_iterator i = source.cbegin() + skip_whitespace(source.c_str(), source.length());
    
    if(*i=='[' || *i=='{'){
        return ParseValue(source, i, source.cend());
    }
    else{
        printf("Illegal char '%c' at start of JSON root\n", *i);
        return nullptr;
    }
}

} // namespace TurboJSON
