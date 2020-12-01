#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <utility>
#include "parser/Token.h"
#include "tree/Node.h"

namespace jc {
    const int RECURSION_DEPTH_LIMIT = 1000;

    /**
     * @brief The base class of all exceptions in Jacy
     * @details All other exceptions count as "Uncaught"
     *
     * @param msg String message to print when caught
     */
    class JacyException : public std::exception {
    public:
        explicit JacyException(std::string msg) : message(std::move(msg)) {}
        JacyException(std::string msg, Position pos) : message(std::move(msg)), pos(std::move(pos)) {}

        std::string what() noexcept {
            // TODO!: Move to Logger
            std::string compound_msg;

            if (pos.line > 0 && pos.column > 0) {
                compound_msg += pos.filename + ":" + std::to_string(pos.line) + ":" + std::to_string(pos.column) + ": ";
            }

            compound_msg += message;

            return compound_msg;
        }

    private:
        const std::string message;
        Position pos;
    };

    ///////////////////////
    // Common Exceptions //
    ///////////////////////

    /**
     * FileNotFoundException
     */
    class FileNotFoundException : public JacyException {
    public:
        FileNotFoundException() : JacyException("File not found") {}
        explicit FileNotFoundException(const std::string & details) : JacyException("File not found: "+ details) {}
    };

    /**
     * IllegalArgumentException
     */
    class IllegalArgumentException : public JacyException {
    public:
        IllegalArgumentException() : JacyException("Illegal argument") {}
        explicit IllegalArgumentException(const std::string & details) : JacyException("Illegal argument: "+ details) {}
    };

    /**
     * ExpectedException
     * @brief Exception for cases when something was expected but wrong thing was given
     */
    class ExpectedException : public JacyException {
    public:
        ExpectedException(const std::string & expected, const parser::Token & given_token)
            : JacyException(expected + ", " + given_token.to_string() + " given", given_token.pos) {}
    };

    /////////////////////////
    // Parsing Exceptions //
    /////////////////////////
    class ParserException : public JacyException {
    public:
        explicit ParserException(const std::string & msg, Position pos) : JacyException(msg, pos) {}

        ParserException(const std::string & pre_msg, const parser::Token & t, const std::string & post_msg)
                : ParserException(pre_msg +" "+ t.to_string() +" "+ post_msg, t.pos) {}

        ParserException(const std::string & pre_msg, const parser::Token & t)
                : ParserException(pre_msg, t, "") {}
    };

    /**
     * UnexpectedTokenException
     */
    class UnexpectedTokenException : public ParserException {
    public:
        explicit UnexpectedTokenException(const parser::Token & t) : ParserException("Unexpected", t) {}
        explicit UnexpectedTokenException(const std::string & token_str, Position pos)
            : ParserException("Unexpected "+ token_str, std::move(pos)) {}
    };

    /**
     * ExpectedException
     * @brief Unexpected end of file
     */
    class UnexpectedEofException : public ParserException {
    public:
        explicit UnexpectedEofException(Position pos) : ParserException("Unexpected end of file", std::move(pos)) {}
    };

    /////////////////////////////
    // Compile-time Exceptions //
    /////////////////////////////
    class CTException : public JacyException {
    public:
        explicit CTException(const std::string & msg) : JacyException(msg) {}
    };

    ////////////////////////
    // Runtime Exceptions //
    ////////////////////////

    /**
     * RuntimeError
     *
     * @param msg String error message
     * @param pos Position where error occurred
     * @param in_file File where error occurred
     */
    class RuntimeError : public JacyException {
    public:
        RuntimeError(const std::string & msg, const Position & pos) : JacyException(msg, pos) {}
    };

    /**
     * RecursionDepthLimit
     * @brief Error that occurs when maximum recursion depth limit exceeded
     *
     * @param pos Position where error occurred
     * @param in_file File where error occurred
     */
    class RecursionDepthExceeded : public RuntimeError {
    public:
        explicit RecursionDepthExceeded(const Position & pos)
            : RuntimeError("Maximum recursion depth exceeded ("+ std::to_string(RECURSION_DEPTH_LIMIT) +")", pos) {}
    };

    // Verifier Errors //
    class UndefinedBehavior : public RuntimeError {

    };

    /////////////////////////
    // Internal Exceptions //
    /////////////////////////

    /**
     * InternalException
     * @brief Used to be caught inside. If exception was shown in console it means that something is wrong inside.
     */
    class InternalException : public JacyException {
    public:
        explicit InternalException(const std::string & msg) : JacyException("[Internal_Exception] " + msg) {}
    };

    /**
     * IUndefinedEntity
     * @brief Internal exception that may be thrown to say that something is undefined.
     */
    class IUndefinedEntity : public InternalException {
    public:
        IUndefinedEntity() : InternalException("IUndefinedEntity") {}
    };

    //////////////////////
    // Other Exceptions //
    //////////////////////

    // Dev Error used in cases there something was wrong with source code
    // It's mostly like a hint for developers
    class DevError : public JacyException {
    public:
        explicit DevError(const std::string & msg) : JacyException("[Dev Error]: "+ msg) {}
    };
}

#endif