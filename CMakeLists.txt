cmake_minimum_required (VERSION 3.18)

project (hexview LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package (gempyre REQUIRED)

if(USE_HIILLOS)
    include(hiillos)
endif()

if(USE_CONFIG)
    set(CONFIG_FILE gui/gempyre.conf)
endif()

include(gempyre)

include_directories(include)
add_executable(${PROJECT_NAME}
   src/main.cpp
   gui/hexview.html
   gui/hexview.css)

if(USE_HIILLOS)
    hiillos_make_application(${PROJECT_NAME})
endif()

gempyre_add_resources(PROJECT ${PROJECT_NAME}
    TARGET include/hexview_resource.h
    SOURCES gui/hexview.html gui/hexview.css gui/text_x_hex.png ${CONFIG_FILE})

target_link_libraries ( ${PROJECT_NAME}
   gempyre::gempyre)


