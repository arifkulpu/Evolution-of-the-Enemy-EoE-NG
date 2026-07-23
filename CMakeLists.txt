cmake_minimum_required(VERSION 3.24)

project("EvolutionOfTheEnemyNG" VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fetch fmt
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        10.1.1
)
FetchContent_MakeAvailable(fmt)

# Fetch spdlog
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG        v1.12.0
)
set(SPDLOG_FMT_EXTERNAL ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(spdlog)

# Create dummy spdlogConfig for CommonLibSSE-NG's find_package
file(WRITE "${CMAKE_BINARY_DIR}/spdlogConfig.cmake" "\n")
set(spdlog_DIR "${CMAKE_BINARY_DIR}" CACHE PATH "" FORCE)

# Setup variables for CommonLibSSE-NG
set(RAPIDCSV_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/src" CACHE PATH "" FORCE)
set(BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)

# Configure CommonLibSSE-NG
set(CMAKE_SKIP_INSTALL_RULES ON CACHE BOOL "" FORCE)
FetchContent_Declare(
    CommonLibSSE-NG
    GIT_REPOSITORY https://github.com/CharmedBaryon/CommonLibSSE-NG.git
    GIT_TAG        main
    UPDATE_DISCONNECTED ON
    EXCLUDE_FROM_ALL ON
)
FetchContent_MakeAvailable(CommonLibSSE-NG)

add_library(${PROJECT_NAME} SHARED
    src/main.cpp
    src/LevelSystem.cpp
    src/Settings.cpp
    src/Menu.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE CommonLibSSE::CommonLibSSE)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/PCH.h)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
)
