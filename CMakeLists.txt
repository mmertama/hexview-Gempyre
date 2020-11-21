cmake_minimum_required (VERSION 3.8)

set(NAME hexview)
project (${NAME})

set(CMAKE_CXX_STANDARD 17)

set(GEMPYRE_PATH $ENV{GEMPYRE_DIR})

include_directories(
    ${GEMPYRE_PATH}/gempyrelib/include
    ${GEMPYRE_PATH}/affiliates/include
   include
)

find_package (gempyre REQUIRED PATHS ${GEMPYRE_PATH})
include(${GEMPYRE_PATH}/scripts/addResource.cmake_script)

find_package (Python3 COMPONENTS Interpreter)

execute_process(COMMAND ${Python3_EXECUTABLE} -m pip install pywebview --user --quiet)
execute_process(COMMAND ${Python3_EXECUTABLE} -m pip install websockets --user --quiet)

add_executable(${PROJECT_NAME}
   src/main.cpp
   gui/${NAME}.html
   gui/${NAME}.css
   ${GEMPYRE_PATH}/affiliates/py_client/pyclient.py
   )

#pyclient.py shall be in in ${gempyre_DIR} and ${GEMPYRE_PATH}/affiliates/py_client, not sure which one prefer


add_custom_target(
    pyfile ALL
    DEPENDS ${GEMPYRE_PATH}/affiliates/py_client/pyclient.py
    COMMAND ${CMAKE_COMMAND} -E copy
            ${GEMPYRE_PATH}/affiliates/py_client/pyclient.py
            ${CMAKE_CURRENT_BINARY_DIR}/pyclient.py)

add_dependencies(${PROJECT_NAME} pyfile)

add_definitions(-DG_PYTHON="${Python3_EXECUTABLE}")
add_definitions(-DG_EXTENSION="${CMAKE_CURRENT_BINARY_DIR}/pyclient.py")

addResource(PROJECT ${PROJECT_NAME} TARGET include/${NAME}_resource.h SOURCES gui/${NAME}.html gui/${NAME}.css gui/text_x_hex.png)

target_link_libraries (${PROJECT_NAME} gempyre)

