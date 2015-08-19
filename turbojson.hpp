#pragma once
#include <vector>
#include <map>
#include <string>
#include <memory>

namespace TurboJSON {

    enum Type {Null, Boolean, String, Number, Object, Array};
    class Value {
    public:
    
        virtual ~Value();
    
        virtual Type type() const = 0;

        virtual bool Boolean() const { return false; };
        virtual double Number() const { return 0.0; }
        virtual const std::string &String() const { static const std::string _ = ""; return _; };
        virtual const std::vector<std::unique_ptr<Value> > *Array() const { return nullptr; };
        virtual const std::map<std::string, std::unique_ptr<Value> > *Object() const { return nullptr; };

    };

    Value *Parse(const std::string &source);

} // namespace TurboJSON
