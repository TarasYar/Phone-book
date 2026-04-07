
cmake_minimum_required(VERSION 3.20)

# ───────────────────────────────
# 1. Назва проекту і стандарт C++
# ───────────────────────────────
project(MyProject
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ───────────────────────────────
# 2. Режим збірки за замовчуванням
# ───────────────────────────────
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# ───────────────────────────────
# 3. Генерація compile_commands.json
# ───────────────────────────────
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ───────────────────────────────
# 4. Загальні опції компілятора
# ───────────────────────────────
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

# ───────────────────────────────
# 5. Автоматичний пошук усіх вихідних файлів
# ───────────────────────────────
file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/src/*.cxx"
)

# ───────────────────────────────
# 6. Автоматичний пошук усіх include директорій
# ───────────────────────────────
file(GLOB_RECURSE INCLUDE_DIRS RELATIVE ${PROJECT_SOURCE_DIR} "${PROJECT_SOURCE_DIR}/include/*")
set(UNIQUE_INCLUDE_DIRS "")
foreach(dir ${INCLUDE_DIRS})
    if(IS_DIRECTORY "${PROJECT_SOURCE_DIR}/${dir}")
        list(APPEND UNIQUE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/${dir}")
    endif()
endforeach()

# ───────────────────────────────
# 7. Створюємо executable
# ───────────────────────────────
add_executable(${PROJECT_NAME} ${SOURCES})

# ───────────────────────────────
# 8. Налаштування target
# ───────────────────────────────
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE ${COMMON_WARNINGS})
target_include_directories(${PROJECT_NAME} PRIVATE ${UNIQUE_INCLUDE_DIRS})

# ───────────────────────────────
# 9. Опціональне лінкування бібліотек
# ───────────────────────────────
# target_link_libraries(${PROJECT_NAME} PRIVATE mylib)

# ───────────────────────────────
# 10. Тести (опційно)
# ───────────────────────────────
enable_testing()
# add_subdirectory(tests)

# ───────────────────────────────
# 11. Інсталяція (опційно)
# ───────────────────────────────
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
