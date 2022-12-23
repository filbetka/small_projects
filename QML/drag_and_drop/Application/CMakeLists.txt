cmake_minimum_required(VERSION 3.18)

find_package(Qt5 5.15.2 COMPONENTS Widgets Quick REQUIRED)

# ---------------------------------------------------------------------------------------------------------------------
# Application
# ---------------------------------------------------------------------------------------------------------------------

set(SOURCE_DIR source)
set(SOURCES
    ${SOURCE_DIR}/main.cpp
)
set_property(SOURCE ${SOURCES} PROPERTY COMPILE_FLAGS ${COMPILE_WARNING_ERROR_FLAGS})

file(GLOB HEADERS public/*.h)
qt5_add_resources(QT_RESOURCES qml/Application.qrc)

add_executable(Application WIN32 source/main.cpp ${QT_RESOURCES})
#add_library(Application STATIC ${SOURCES} ${HEADERS} ${QT_RESOURCES})
target_include_directories(Application PUBLIC public)
target_link_libraries(Application PUBLIC Qt5::Widgets Qt5::Quick)
target_compile_definitions(Application PUBLIC APPLICATION_NAME="DragAndDrop" APPLICATION_VERSION="1.0.0")
set_target_properties(Application PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    OUTPUT_NAME "DragAndDrop"
)