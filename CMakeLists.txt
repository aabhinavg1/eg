# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(YourProjectName VERSION 1.0)

# Specify the C++ standard to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the source files for your project
# Adjust this according to the structure of your project
add_executable(${PROJECT_NAME}
    main.cpp          # Your main application file
    src/dependencies/Subscriber.cpp  # Include Subscriber.cpp from the dependencies folder
)

# Add include directories for the project
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include  # If there are any header files in include, include that folder
    ${PROJECT_SOURCE_DIR}/src/dependencies  # Add the dependencies folder for Subscriber.h
)

# If you have dependencies, you can link them here
# For example, if you use a library or another module
# target_link_libraries(${PROJECT_NAME} PRIVATE some_library)

# If you have tests, you can add them like this
enable_testing()
add_subdirectory(tests)

# Optional: specify where the output files should be generated
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
