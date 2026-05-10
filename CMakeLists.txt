cmake_minimum_required(VERSION 3.18)

project(hlv_g_lattice_engine
    VERSION 1.0.0
    DESCRIPTION "HLV G-Lattice Simulation Lab — C++ Core Engine"
    LANGUAGES CXX
)

# ------------------------------------------------------------
# 1. C++ Standard + Safety
# ------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Strong warnings for engine code
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ------------------------------------------------------------
# 2. Dependencies
# ------------------------------------------------------------
find_package(Eigen3 REQUIRED NO_MODULE)
find_package(nlohmann_json REQUIRED)
find_package(pybind11 REQUIRED)
find_package(Python COMPONENTS Interpreter Development REQUIRED)

# ------------------------------------------------------------
# 3. Python Extension Module
# ------------------------------------------------------------
pybind11_add_module(hlv_engine
    src/cpp_core/bindings.cpp
)

target_include_directories(hlv_engine PRIVATE
    src/cpp_core
)

target_link_libraries(hlv_engine PRIVATE
    Eigen3::Eigen
    nlohmann_json::nlohmann_json
)

# ------------------------------------------------------------
# 4. Optimization Flags
# ------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    if (NOT MSVC)
        target_compile_options(hlv_engine PRIVATE -O3 -march=native -ffast-math)
    endif()
endif()

# ------------------------------------------------------------
# 5. RPATH Handling (Critical for Python Wheels)
# ------------------------------------------------------------
set_target_properties(hlv_engine PROPERTIES
    BUILD_RPATH_USE_ORIGIN ON
    INSTALL_RPATH_USE_ORIGIN ON
)

# ------------------------------------------------------------
# 6. Installation Rules (for pip install .)
# ------------------------------------------------------------
install(TARGETS hlv_engine
    LIBRARY DESTINATION ${Python_SITEARCH}
)

# ------------------------------------------------------------
# 7. Summary Output
# ------------------------------------------------------------
message(STATUS "HLV Engine Build Configuration:")
message(STATUS "  C++ Standard:        ${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type:          ${CMAKE_BUILD_TYPE}")
message(STATUS "  Python Site-Packages: ${Python_SITEARCH}")
