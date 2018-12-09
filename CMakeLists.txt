set(CMAKE_VERBOSE_MAKEFILE on)

cmake_minimum_required(VERSION 3.10)
project(Spode)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Og")

#Throwing flags at the wall and seeing what sticks
#SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -pedantic -Wextra -fmodulo-sched -fmodulo-sched-allow-regmoves -fgcse-lm -fgcse-sm -faggressive-loop-optimizations -fdeclone-ctor-dtor -fdevirtualize-speculatively -fdevirtualize-at-ltrans -flifetime-dse=2 -flive-range-shrinkage -fira-region=one -fira-loop-pressure -fno-ira-share-save-slots -fsched-pressure -fsched-spec-load -fsched-spec-load-dangerous -fsched-stalled-insns-dep=0 -freschedule-modulo-scheduled-loops -fipa-pta -fgraphite-identity -floop-nest-optimize -ftree-loop-vectorize -fvect-cost-model=cheap -fsimd-cost-model=dynamic -flimit-function-alignment -fweb -flto -flto-partition=max -ffast-math -funsafe-math-optimizations -fsplit-loops -fbranch-target-load-optimize2 -fbtr-bb-exclusive")

option(USE_PGO "Enable the use of Profile Guided Optimization" OFF)
option(MAKE_PGO_PROF "Make a new PGO profile. Program will run slowly. If OFF, gcc will use existing profile for optimizations." OFF)


if(USE_PGO MATCHES ON)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-dir=../cmake-pgo-datadir/")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Ofast")
endif()

if ((USE_PGO MATCHES ON) AND (MAKE_PGO_PROF MATCHES ON))
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-generate")
elseif(USE_PGO MATCHES ON)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-use")
endif()

#add_definitions(-DDISABLE_ASSERT)
MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )

add_executable(Spode src/main.cpp src/Board.cpp src/Board.h src/Board.cpp src/Board.h src/Move.cpp src/Move.h src/Util.h src/Perft.h src/Perft.cpp src/Searcher.cpp src/Searcher.h src/AssertionFailure.h src/Bitboard.cpp src/Bitboard.h)

unset(USE_PGO CACHE)
unset(MAKE_PGO_PROF CACHE)