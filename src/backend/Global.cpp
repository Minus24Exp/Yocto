#include "backend/Global.h"
#include "backend/Interpreter.h"
#include "object/objects.h"

#include <iostream>

Global::Global() : ip(Interpreter::get_instance()) {}

std::shared_ptr<Null> null_obj;

// Classes //
class_ptr cObject;
class_ptr cClass;
class_ptr cNull;
class_ptr cBool;
class_ptr cInt;
class_ptr cFloat;
class_ptr cString;
class_ptr cFunc;

// Easter egg
obj_ptr YOCTO(NFArgs && args){
    std::cout <<
    "(_|   |                        \n"
    "  |   |   __    __   _|_   __  \n"
    "  |   |  /  \\  /      |   /  \\\n"
    "   \\_/|/ \\__/  \\___/  |_/ \\__/\n"
    "     /|\n"
    "     \\|\n"
    << std::endl;
    return nullptr;
}

obj_ptr Yo_print(NFArgs && args){
    std::cout << obj_to_str(args["o"]);
    return nullptr;
}

obj_ptr Yo_println(NFArgs && args){
    std::cout << obj_to_str(args["o"]) << std::endl;
    return nullptr;
}

obj_ptr Yo_repr(NFArgs && args){
    std::cout << args["o"]->repr() << std::endl;
    return nullptr;
}

void Global::reg(){
    const auto scope = ip.get_scope();
    
    // Classes //
    cObject = std::make_shared<Class>("Object", nullptr);

    cClass = std::make_shared<Class>("Class", cObject);

    cNull = std::make_shared<Class>("Null", cObject);

    null_obj = std::make_shared<Null>();

    cBool = std::make_shared<Class>("Bool", cObject);

    cInt = std::make_shared<Class>("Int", cObject);

    cFloat = std::make_shared<Class>("Float", cObject);

    cString = std::make_shared<Class>("String", cObject);
    
    cFunc = std::make_shared<Class>("Func", cObject);

    // IO //
    scope->define_nf("print", make_nf(scope, "print", { {"o"} }, Yo_print));
    scope->define_nf("println", make_nf(scope, "println", { {"o"} }, Yo_println));
    scope->define_nf("repr", make_nf(scope, "repr", { {"o"} }, Yo_repr));


    // Easter egg
    scope->define_nf("YOCTO", make_nf(scope, "YOCTO", {}, YOCTO));
}