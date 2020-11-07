#include "vm/BaseVM.h"

//////////////
// Bytecode //
//////////////
uint8_t BaseVM::peek() const {
    return chunk.code[index];
}

opcode_it BaseVM::peek_it() {
    return chunk.code.begin() + index;
}

void BaseVM::advance(int distance) {
    index += distance;
}

uint8_t BaseVM::read() {
    uint8_t b = peek();
    advance();
    return b;
}

uint16_t BaseVM::read2() {
    uint16_t s;
    std::copy(peek_it(), peek_it() + 2, reinterpret_cast<uint8_t*>(&s));
    advance(2);
    return s;
}

uint32_t BaseVM::read4() {
    uint32_t i;
    std::copy(peek_it(), peek_it() + 4, reinterpret_cast<uint8_t*>(&i));
    advance(4);
    return i;
}

uint64_t BaseVM::read8() {
    uint64_t l;
    std::copy(peek_it(), peek_it() + 8, reinterpret_cast<uint8_t*>(&l));
    advance(8);
    return l;
}

///////////
// Stack //
///////////
void BaseVM::push(const Value & value) {
    stack.push_back(value);
}

Value BaseVM::pop() {
    Value back = stack.back();
    stack.pop_back();
    return back;
}

Value BaseVM::top(uint64_t offset) {
    return *(stack.end() - offset - 1);
}

///////////////
// Constants //
///////////////
constant_ptr BaseVM::read_const() {
    // Note: read_const automatically reads constant offset and advances
    const auto & offset = read8();
    if (offset >= chunk.constants.size()) {
        // TODO: Throw error
    }
    return chunk.constants.at(offset);
}

std::shared_ptr<IntConstant> BaseVM::read_int_const() {
    constant_ptr constant = read_const();
    if (constant->type != ConstantType::Int) {
        throw DevError("Invalid constant type, (int) expected");
    }
    return std::static_pointer_cast<IntConstant>(constant);
}

std::shared_ptr<FloatConstant> BaseVM::read_float_const() {
    constant_ptr constant = read_const();
    if (constant->type != ConstantType::Float) {
        throw DevError("Invalid constant type, (float) expected");
    }
    return std::static_pointer_cast<FloatConstant>(constant);
}

std::shared_ptr<StringConstant> BaseVM::read_string_const() {
    constant_ptr constant = read_const();
    if (constant->type != ConstantType::String) {
        throw DevError("Invalid constant type, (string) expected");
    }
    return std::static_pointer_cast<StringConstant>(constant);
}

////////////
// Errors //
////////////
void BaseVM::error(const std::string & msg) {
    // TODO: Use VM exceptions
    throw JacyException(msg);
}
