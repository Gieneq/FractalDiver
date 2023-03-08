cmake_minimum_required(VERSION 3.0.0)
project(fractaldiver VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall )
#add_compile_options(-Wall -Wextra -pedantic -Werror)

# SDL2 
set(CMAKE_PREFIX_PATH SDL2/cmake/)
find_package(SDL2 REQUIRED)

#include_directories(${SDL2_INCLUDE_DIRS})
#add_definitions(-DSDL_MAIN_HANDLED)
#g++ -std=c++17 Test.cpp -I"include" -L"lib" -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o Test

add_executable(fractaldiver Maths.cpp main.cpp Engine.cpp MainRenderer.cpp FractalViewer.cpp)


target_link_libraries(fractaldiver PRIVATE SDL2::SDL2)

add_custom_command(TARGET fractaldiver POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy
         ${CMAKE_SOURCE_DIR}/SDL2/x86_64-w64-mingw32/bin/SDL2.dll
         ${CMAKE_CURRENT_BINARY_DIR})

# include(CTest)
# enable_testing()

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)

