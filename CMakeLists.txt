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


add_executable(${PROJECT_NAME}
   src/main.cpp
   gui/${NAME}.html
   gui/${NAME}.css
   )

addResource(PROJECT ${PROJECT_NAME} TARGET include/${NAME}_resource.h SOURCES gui/${NAME}.html gui/${NAME}.css gui/text_x_hex.png)

target_link_libraries (${PROJECT_NAME} gempyre)

