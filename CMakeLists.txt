cmake_minimum_required (VERSION 3.15)

project(game_2d)
set(GAME_NAME "PenisRing")

set(SRC_DIR_ENGINE ${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
set(SRC_DIR_GAME ${CMAKE_CURRENT_SOURCE_DIR}/src/game)

set(SRCS_ENGINE
    ${SRC_DIR_ENGINE}/input_manager.cpp
    ${SRC_DIR_ENGINE}/timer.cpp
    ${SRC_DIR_ENGINE}/shader.cpp
    ${SRC_DIR_ENGINE}/vertex_buffer.cpp
    ${SRC_DIR_ENGINE}/index_buffer.cpp
    ${SRC_DIR_ENGINE}/vertex_array.cpp
    ${SRC_DIR_ENGINE}/texture.cpp
    ${SRC_DIR_ENGINE}/quad.cpp
    ${SRC_DIR_ENGINE}/renderer.cpp
)

set(SRCS_GAME
    ${SRC_DIR_GAME}/game.cpp
    ${SRC_DIR_GAME}/camera2d.cpp
    ${SRC_DIR_GAME}/player.cpp
)

set(SRCS_EXTERNAL
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad_4.6/src/glad.c
    ${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image/stb_image.cpp
)

add_executable(${GAME_NAME} main.cpp ${SRCS_ENGINE} ${SRCS_GAME} ${SRCS_EXTERNAL})

target_compile_features(${GAME_NAME} PRIVATE cxx_std_17)
	
if(WIN32)
	target_include_directories(${GAME_NAME} PRIVATE 
	   ${CMAKE_CURRENT_SOURCE_DIR}/include/engine
	   ${CMAKE_CURRENT_SOURCE_DIR}/include/game
	   ${CMAKE_CURRENT_SOURCE_DIR}/external/glad_4.6/include
	   ${CMAKE_CURRENT_SOURCE_DIR}/external/glm/
	   ${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image/
	   ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.24.1/include/
	)
	target_link_libraries(${GAME_NAME} PRIVATE 
	   ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.24.1/lib/x64/SDL2.lib
	   ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL2-2.24.1/lib/x64/SDL2main.lib
	)
endif()