cmake_minimum_required(VERSION 3.22)
project(project03)

set(CMAKE_CXX_STANDARD 17)

add_executable(project03 main.cpp Lexer/Scheme.h Relation.h Lexer/Parameter.h Parser.h Lexer/Predicate.h Lexer/Rule.h Lexer/Lexer.h Lexer/Token.h DatalogProgram.h Interpreter.h Database.h)
