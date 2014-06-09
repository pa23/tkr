cmake_minimum_required(VERSION 2.8)

set(APP_NAME tkr)
set(APP_VERSION "1.0.1")

project(${APP_NAME})

set(CMAKE_BUILD_TYPE RELEASE)
set(EXECUTABLE_OUTPUT_PATH "bin")

set(
  HEADERS
  src/auxfunctions.hpp
  src/configuration.hpp
  src/constants.hpp
  src/identification.hpp
  src/tkrparameters.hpp
  )

set(
  SOURCES
  src/auxfunctions.cpp
  src/configuration.cpp
  src/main.cpp
  src/tkrparameters.cpp
  )

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -W -pedantic")

if(MINGW)
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_SHARED_LIBS OFF)
else()
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_SHARED_LIBS ON)
endif()

find_package(Boost COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIR})
endif()

if(MINGW)
  set(BUILD_STATIC_LIBS ON)
  set(BUILD_SHARED_LIBS OFF)
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
else()
  set(BUILD_STATIC_LIBS OFF)
  set(BUILD_SHARED_LIBS ON)
endif()

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(
  ${PROJECT_NAME}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_LIBRARIES}
  )
