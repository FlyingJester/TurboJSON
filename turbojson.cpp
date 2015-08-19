#include "turbojson.hpp"

namespace Turbo {

JSON::Value::~Value(){}

class StringValue : public JSON::Value {
protected:
    const std::string string;
public:
    StringValue(const std::string &s)
      : string(s){}

    virtual ~StringValue(){}

    JSON::Type type() const override { return JSON::String; };
    const std::string &String() const override { return string; }
};

template<bool B>
class BooleanValue : public JSON::Value {
public:

    virtual ~BooleanValue(){}

    JSON::Type type() const override { return JSON::Boolean; };
    bool Boolean() const override { return B; }
};

class NullValue : public JSON::Value {
public:

    virtual ~NullValue(){}

    JSON::Type type() const override { return JSON::Null; };
};

class NumberValue : public JSON::Value {
    const double number;
public:
    NumberValue(double n)
      : number(n) {}

    virtual ~NumberValue(){}

    JSON::Type type() const override { return JSON::Number; };
    double Number() const override {return number; };
};

class ObjectValue : public JSON::Value {
public:

    virtual ~ObjectValue(){}

    std::map<std::string, std::unique_ptr<Value> >map;
    JSON::Type type() const override { return JSON::Object; };
    const std::map<std::string, std::unique_ptr<Value> > *Object() const override { return &map; };
};

class ArrayValue : public JSON::Value {
public:

    virtual ~ArrayValue(){}

    std::vector<std::unique_ptr<Value> >array;
    JSON::Type type() const override { return JSON::Array; };
    const std::vector<std::unique_ptr<Value> > *Array() const override { return &array; };
};



}


