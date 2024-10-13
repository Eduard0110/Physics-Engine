# CMakeList.txt : CMake project for SFMLphysics, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set(SOURCE_FILES
	main.cpp
	world.cpp
	object.cpp)

add_executable (${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(SFMLphysics ${CMAKE_SOURCE_DIR}/lib/sfml-audio.lib)
target_link_libraries(SFMLphysics ${CMAKE_SOURCE_DIR}/lib/sfml-graphics.lib)
target_link_libraries(SFMLphysics ${CMAKE_SOURCE_DIR}/lib/sfml-network.lib)
target_link_libraries(SFMLphysics ${CMAKE_SOURCE_DIR}/lib/sfml-system.lib)
target_link_libraries(SFMLphysics ${CMAKE_SOURCE_DIR}/lib/sfml-window.lib)

include_directories(${CMAKE_SOURCE_DIR}/include)

set_property(TARGET SFMLphysics PROPERTY CXX_STANDARD 17)
set_property(TARGET SFMLphysics PROPERTY CXX_STANDARD_REQUIRED ON)


# TODO: Add tests and install targets if needed.
