#include "object/Object.h"
#include "object/Class.h"
#include "object/BaseFunc.h"
#include "object/String.h"

Object::Object() {}

Object::Object(scope_ptr scope, Class * _class)
    : Scope(scope, _class->get_instance_fields()),
      _class(_class)
{
    
}

bool Object::truthy() const {
    return true;
}

std::string Object::repr() const {
    return "<object_"+ _class->get_name() +">";
}

obj_ptr Object::get(const std::string & name) const {
    obj_ptr field = Scope::get(name);

    if(!field){
        return nullptr;
    }

    func_ptr maybe_func = std::dynamic_pointer_cast<BaseFunc>(field);

    if(maybe_func){
        return maybe_func->bind(std::const_pointer_cast<Object>(shared_from_this()));
    }else{
        return field;
    }
}

string_ptr obj_to_str(obj_ptr obj){
    // If object has method `to_s` and it returns string then use it
    if(obj->has("to_s")){
        func_ptr to_s = cast_to_func(obj->get("to_s"));
        if(to_s){
            string_ptr string = cast_to_s(to_s->call());
            if(string){
                return string;
            }
        }
    }

    // Otherwise represent object
    return std::make_shared<String>(obj->repr());
}