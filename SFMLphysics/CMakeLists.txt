# Specify where to place the built executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add source files and the executable
set(SOURCE_FILES
    main.cpp
    demo.cpp
    world.cpp
    object.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link the libraries to the executable
target_link_libraries(SFMLphysics 
    ${CMAKE_SOURCE_DIR}/lib/sfml-audio.lib
    ${CMAKE_SOURCE_DIR}/lib/sfml-graphics.lib
    ${CMAKE_SOURCE_DIR}/lib/sfml-network.lib
    ${CMAKE_SOURCE_DIR}/lib/sfml-system.lib
    ${CMAKE_SOURCE_DIR}/lib/sfml-window.lib
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Set the C++ standard
set_property(TARGET SFMLphysics PROPERTY CXX_STANDARD 17)
set_property(TARGET SFMLphysics PROPERTY CXX_STANDARD_REQUIRED ON)

# Step 1: Copy DLLs from 'dlls/' to the same folder as the .exe after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/dlls/ $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Step 2: Copy the entire 'assets/' folder to the same folder as the .exe after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets/ $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

# Step 3: Set the output folder to be the same as the executable folder for release
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
