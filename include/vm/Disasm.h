#ifndef DISASM_H
#define DISASM_H

#include "vm/BaseVM.h"
#include "common/Logger.h"
#include "bytecode/opcode.h"

#include <map>
#include <cstring>

namespace jc::vm {
    const std::map<bytecode::OpCode, std::string> opcode_names = {
        {bytecode::OpCode::NOP,                 "NOP"},
        {bytecode::OpCode::Pop,                 "Pop"},
        {bytecode::OpCode::Halt,                "Halt"},
        {bytecode::OpCode::NullConst,           "NullConst"},
        {bytecode::OpCode::FalseConst,          "FalseConst"},
        {bytecode::OpCode::TrueConst,           "TrueConst"},
        {bytecode::OpCode::IntConst,            "IntConst"},
        {bytecode::OpCode::FloatConst,          "FloatConst"},
        {bytecode::OpCode::StringConst,         "StringConst"},
        {bytecode::OpCode::DefineGlobal,        "DefineGlobal"},
        {bytecode::OpCode::LoadGlobal,          "LoadGlobal"},
        {bytecode::OpCode::StoreGlobal,         "StoreGlobal"},
        {bytecode::OpCode::LoadLocal,           "LoadLocal"},
        {bytecode::OpCode::StoreLocal,          "StoreLocal"},
        {bytecode::OpCode::LoadUpvalue,         "LoadUpvalue"},
        {bytecode::OpCode::StoreUpvalue,        "StoreUpvalue"},
        {bytecode::OpCode::CloseUpvalue,        "CloseUpvalue"},
        {bytecode::OpCode::Closure,             "Closure"},
        {bytecode::OpCode::Jump,                "Jump"},
        {bytecode::OpCode::JumpFalse,           "JumpFalse"},
        {bytecode::OpCode::Invoke,              "Invoke"},
        {bytecode::OpCode::InvokeNF,            "InvokeNF"},
        {bytecode::OpCode::InvokeMethod,        "InvokeMethod"},
        {bytecode::OpCode::InvokeNFMethod,      "InvokeNFMethod"},
        {bytecode::OpCode::GetProperty,         "GetProperty"},
        {bytecode::OpCode::SetProperty,         "SetProperty"},
    };

    class Disasm : public BaseVM {
    public:
        Disasm();
        explicit Disasm(const common::DisasmOptions & options);
        ~Disasm() override = default;

        void before_eval() override;
        void before_opcode(bytecode::OpCode opcode) override;
        void after_opcode() override;
//    void unknown_opcode() override;
        void _nop() override;
        void _pop() override;
        void _null_const() override;
        void _false_const() override;
        void _true_const() override;
        void _int_const() override;
        void _float_const() override;
        void _string_const() override;
        void _define_global() override;
        void _load_global() override;
        void _store_global() override;
        void _load_local() override;
        void _store_local() override;
        void _get_upvalue() override;
        void _set_upvalue() override;
        void _close_upvalue() override;
        void _closure() override;
        void _jump() override;
        void _jump_false() override;
        void _invoke() override;
        void _invoke_nf() override;
        void _invoke_nf_method() override;
        void _invoke_method() override;
        void _get_property() override;
        void _set_property() override;

        static void print_bytes(const bytecode::byte_list & bytes, bool with_indent = false);

        // Byte-code reading //
        bytecode::bytelist_it peek_it() override;
        void advance(int distance) override;
        std::size_t ip{0};

        // Debug //
    public:
        common::DisasmOptions options{};
        common::Logger log;
    };
}

#endif // DISASM_H
