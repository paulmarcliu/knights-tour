cmake_minimum_required(VERSION 2.8.8)

set (PROJECT_NAME_STR runTests)
project (${PROJECT_NAME_STR} C CXX)

find_package(Threads REQUIRED)

if (CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-Wall -ansi -Wno-deprecated -pthread)
endif()


set (COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

enable_testing()
set (PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
set (GTEST_LIB_DIRS /usr/lib)

include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*.cpp)
file(GLOB MODEL_SRC_FILES ${PROJECT_SOURCE_DIR}/model/*.cpp)
file(GLOB VIEW_SRC_FILES ${PROJECT_SOURCE_DIR}/view/*.cpp)
file(GLOB CONTROLLER_SRC_FILES ${PROJECT_SOURCE_DIR}/controller/*.cpp)
file(GLOB KNIGHT_SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES} ${MODEL_SRC_FILES})
add_executable(knight ${MODEL_SRC_FILES} ${VIEW_SRC_FILES} ${CONTROLLER_SRC_FILES} ${KNIGHT_SRC_FILES})

target_link_libraries(${PROJECT_TEST_NAME}
	${GTEST_LIB_DIRS}/libgtest.a
	${GTEST_LIB_DIRS}/libgtest_main.a
	)

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})
add_test(test1 ${PROJECT_TEST_NAME})
