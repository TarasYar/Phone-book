
cmake_minimum_required(VERSION 3.20)

project(MyProject
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(COMMON_WARNINGS
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wconversion
        -Wsign-conversion
        -g
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(COMMON_WARNINGS /W4 /permissive-)
endif()

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/*.cxx"
)

file(GLOB_RECURSE INCLUDE_DIRS RELATIVE ${PROJECT_SOURCE_DIR} "${PROJECT_SOURCE_DIR}/include/*")
set(UNIQUE_INCLUDE_DIRS "")
foreach(dir ${INCLUDE_DIRS})
    if(IS_DIRECTORY "${PROJECT_SOURCE_DIR}/${dir}")
        list(APPEND UNIQUE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/${dir}")
    endif()
endforeach()

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_WARNINGS})
target_include_directories(${PROJECT_NAME} PRIVATE ${UNIQUE_INCLUDE_DIRS})

enable_testing()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
