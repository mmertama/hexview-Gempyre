cmake_minimum_required (VERSION 3.18)

project (hexview LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package (gempyre REQUIRED)

include(gempyre)


include_directories(include)
add_executable(${PROJECT_NAME}
   src/main.cpp
   gui/hexview.html
   gui/hexview.css)

gempyre_add_resources(PROJECT ${PROJECT_NAME} TARGET include/hexview_resource.h SOURCES gui/hexview.html gui/hexview.css gui/text_x_hex.png)

target_link_libraries ( ${PROJECT_NAME}
   gempyre::gempyre)


