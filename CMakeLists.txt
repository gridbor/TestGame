cmake_minimum_required(VERSION 3.16)

project(TestGame)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(third_path "./libs/link")
set(glm_DIR "${third_path}/glm/glm_install/share/glm")

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

file(GLOB_RECURSE source_files LIST_DIRECTORIES FALSE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.c* src/*.h*)
foreach(source_file IN ITEMS ${source_files})
  get_filename_component(source_path ${source_file} PATH)
  string(REPLACE "/" "\\" group_path ${source_path})
  source_group(${group_path} FILES ${source_file})
endforeach()

set(glad_lib "${third_path}/glad")
add_subdirectory("${third_path}/glfw")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")

add_executable(${PROJECT_NAME} WIN32 ${source_files} ${glad_lib}/src/glad.c)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src" "${glad_lib}/include" "${third_path}/stb" "${third_path}/glm/glm_install/include")
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_gl_LIBRARY} glm::glm glfw)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
