#include "turbojson.hpp"

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

Value *Parse(const std::string &source);

} // namespace TurboJSON
