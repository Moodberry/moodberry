cmake_minimum_required(VERSION 3.10)
project(moodberry_cli)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add executable
add_executable(moodberry
    src/main.cpp
)

# Install step (optional)
install(TARGETS moodberry DESTINATION bin)
