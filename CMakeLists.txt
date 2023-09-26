cmake_minimum_required(VERSION 3.22)
project(project03)

set(CMAKE_CXX_STANDARD 17)

add_executable(project03 main.cpp Scheme.h Relation.h Parameter.h Parser.h Predicate.h Rule.h Scanner.h Token.h DatalogProgram.h Interpreter.h Database.h)
