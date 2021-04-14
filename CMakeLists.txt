cmake_minimum_required (VERSION 3.18)

set(NAME hexview)
project (${NAME})

set(CMAKE_CXX_STANDARD 17)

set(GEMPYRE_PATH $ENV{GEMPYRE_DIR})

include_directories(
   include
)

find_package (gempyre REQUIRED)
include(addResource)


#NOAF find_package (Python3 COMPONENTS Interpreter)
#NOAF execute_process(COMMAND ${Python3_EXECUTABLE} -m pip install pywebview --user --quiet)
#NOAF execute_process(COMMAND ${Python3_EXECUTABLE} -m pip install websockets --user --quiet)


add_executable(${PROJECT_NAME}
   src/main.cpp
   gui/${NAME}.html
   gui/${NAME}.css
#NOAF   ${GEMPYRE_PATH}/affiliates/py_client/pyclient.py
   )

#pyclient.py shall be in in ${gempyre_DIR} and ${GEMPYRE_PATH}/affiliates/py_client, not sure which one prefer


#NOAF add_custom_target(
#NOAF    pyfile ALL
#NOAF    DEPENDS ${GEMPYRE_PATH}/affiliates/py_client/pyclient.py
#NOAF    COMMAND ${CMAKE_COMMAND} -E copy
#NOAF            ${GEMPYRE_PATH}/affiliates/py_client/pyclient.py
#NOAF            ${CMAKE_CURRENT_BINARY_DIR}/pyclient.py)

#NOAF add_dependencies(${PROJECT_NAME} pyfile)

#NOAF add_definitions(-DG_PYTHON="${Python3_EXECUTABLE}")
#NOAF add_definitions(-DG_EXTENSION="${CMAKE_CURRENT_BINARY_DIR}/pyclient.py")

addResource(PROJECT ${PROJECT_NAME} TARGET include/${NAME}_resource.h SOURCES gui/${NAME}.html gui/${NAME}.css gui/text_x_hex.png)

target_link_libraries (${PROJECT_NAME} gempyre::gempyre)

