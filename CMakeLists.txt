cmake_minimum_required(VERSION 2.8.4)

# Название проекта
set(PROJECT_NAME stepik-splay-tree)
project(${PROJECT_NAME})

# Настройки компилятора: стандарт и предупреждения
add_compile_options(-std=c++11 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -fPIC -g)

# Задание заголовочных файлов
set(COMMON_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/)
include_directories(${COMMON_INCLUDE_DIR})

# Задание исходных файлов
file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Непосредственное создание библиотеки
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

# Создание CLI
set(PROJECT_NAME_CLI splay-tree-cli)
add_executable(${PROJECT_NAME_CLI} cli.cpp)
target_link_libraries(${PROJECT_NAME_CLI} ${PROJECT_NAME})

# Инициализация тестирования
enable_testing()
set(PROJECT_NAME_TEST test-${PROJECT_NAME})

# Пакет GTest для тестирования
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDE_DIR})

# Исходные файлы тестов
file(GLOB_RECURSE TEST_SOURCE_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)

# Пакет потоков
find_package(Threads REQUIRED)

# Создание исполняемых файлов
add_executable(${PROJECT_NAME_TEST} ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME_TEST} ${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_test(test_all ${PROJECT_NAME_TEST})
