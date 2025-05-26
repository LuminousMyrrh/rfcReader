cmake_minimum_required(VERSION 3.19)
project(rfcReader LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SPDLOG_DIR "${CMAKE_SOURCE_DIR}/spdlog")
set(SPDLOG_INCLUDE_DIR "${SPDLOG_DIR}/include")
set(SPDLOG_LIBRARY "${SPDLOG_DIR}/build/libspdlog.a")

if(NOT EXISTS "${SPDLOG_LIBRARY}")
    message(FATAL_ERROR "libspdlog.a not found at ${SPDLOG_LIBRARY}. Please ensure spdlog is built.")
endif()

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Core)

qt_standard_project_setup()

qt_add_executable(rfcReader
    src/main.cpp
    headers/engine.h src/engine.cpp
    headers/rfcworker.h src/rfcworker.cpp
    headers/networkmanager.h src/networkmanager.cpp
    headers/logger.h src/logger.cpp
    resources.qrc
    headers/settings.h src/settings.cpp
)

target_link_libraries(rfcReader
    PRIVATE
        ${SPDLOG_LIBRARY}
        Qt::Core
        Qt::Quick
)

target_include_directories(rfcReader
    PRIVATE
        ${SPDLOG_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/headers)

include(GNUInstallDirs)

install(TARGETS rfcReader
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET rfcReader
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
