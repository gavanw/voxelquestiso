cmake_minimum_required(VERSION 3.0)
project(VoxelQuest)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

file(GLOB H_FILES "${CMAKE_SOURCE_DIR}/src/cpp/*.h")
file(GLOB HPP_FILES "${CMAKE_SOURCE_DIR}/src/cpp/*.hpp")

set(TEMP_OUTPUT_DIR "${CMAKE_BINARY_DIR}/temp")
set(COMPILED_OUTPUT_DIR "${CMAKE_BINARY_DIR}/compiled")

set(HEADERS_OUTPUT_FILE "${TEMP_OUTPUT_DIR}/f00270_headers.h")
set(MAIN_OUTPUT_FILE "${COMPILED_OUTPUT_DIR}/main.cpp")

add_custom_command(
  OUTPUT "${TEMP_OUTPUT_DIR}"
  COMMAND "${CMAKE_COMMAND}" -E make_directory "${TEMP_OUTPUT_DIR}"
  )

add_custom_command(
  OUTPUT "${COMPILED_OUTPUT_DIR}"
  COMMAND "${CMAKE_COMMAND}" -E make_directory "${COMPILED_OUTPUT_DIR}"
  )

foreach(H_FILE ${H_FILES})
  get_filename_component(H_FILENAME "${H_FILE}" NAME)
  set(H_FILE_OUTPUT "${TEMP_OUTPUT_DIR}/${H_FILENAME}")
  list(APPEND TEMP_H_FILES "${H_FILE_OUTPUT}")
  add_custom_command(
    OUTPUT "${H_FILE_OUTPUT}"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${H_FILE}" "${H_FILE_OUTPUT}"
    DEPENDS "${TEMP_OUTPUT_DIR}"
    MAIN_DEPENDENCY "${H_FILE}"
    )
endforeach(H_FILE)

foreach(HPP_FILE ${HPP_FILES})
  get_filename_component(HPP_FILENAME "${HPP_FILE}" NAME)
  string(REGEX REPLACE "\\.hpp$" ".h" H_FILENAME "${HPP_FILENAME}")
  string(REGEX REPLACE "\\.hpp$" ".e" E_FILENAME "${HPP_FILENAME}")
  list(APPEND TEMP_H_FILES "${TEMP_OUTPUT_DIR}/${H_FILENAME}")
  list(APPEND TEMP_E_FILES "${TEMP_OUTPUT_DIR}/${E_FILENAME}")
  add_custom_command(
    OUTPUT "${TEMP_OUTPUT_DIR}/${E_FILENAME}"
           "${COMPILED_OUTPUT_DIR}/${E_FILENAME}"
           "${TEMP_OUTPUT_DIR}/${H_FILENAME}"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${HPP_FILE}" "${TEMP_OUTPUT_DIR}/${HPP_FILENAME}"
    COMMAND "${CMAKE_SOURCE_DIR}/lzz" -hx e -sx h "${TEMP_OUTPUT_DIR}/${HPP_FILENAME}"
    COMMAND "${CMAKE_COMMAND}" -E touch "${COMPILED_OUTPUT_DIR}/${E_FILENAME}"
    WORKING_DIRECTORY "${TEMP_OUTPUT_DIR}"
    DEPENDS "${TEMP_OUTPUT_DIR}" "${COMPILED_OUTPUT_DIR}"
    MAIN_DEPENDENCY "${HPP_FILE}"
    )
endforeach(HPP_FILE)

list(SORT TEMP_H_FILES)
list(SORT TEMP_E_FILES)

add_custom_command(
  OUTPUT "${HEADERS_OUTPUT_FILE}"
  COMMAND "${CMAKE_COMMAND}"
          -D "INPUT_FILES=\"${TEMP_E_FILES}\""
          -D "OUTPUT_FILE=\"${HEADERS_OUTPUT_FILE}\""
          -P "${CMAKE_SOURCE_DIR}/cmake/cat.cmake"
  DEPENDS "${TEMP_E_FILES}"
  )

list(APPEND TEMP_H_FILES "${HEADERS_OUTPUT_FILE}")
list(SORT TEMP_H_FILES)

add_custom_command(
  OUTPUT "${MAIN_OUTPUT_FILE}"

  COMMAND "${CMAKE_COMMAND}"
          -D "INPUT_FILES=\"${TEMP_H_FILES}\""
          -D "OUTPUT_FILE=\"${MAIN_OUTPUT_FILE}\""
          -P "${CMAKE_SOURCE_DIR}/cmake/cat.cmake"
  DEPENDS "${TEMP_H_FILES}" "${COMPILED_OUTPUT_DIR}"
  )

add_executable("${PROJECT_NAME}" "${MAIN_OUTPUT_FILE}")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})


if (WIN32)
  include_directories(
    "${CMAKE_SOURCE_DIR}/freeglut/include"
    "${CMAKE_SOURCE_DIR}/glew/include"
    "${CMAKE_SOURCE_DIR}/SFML-2.1/include"
  )
  target_link_libraries("${PROJECT_NAME}" opengl32 glu32
    "${CMAKE_SOURCE_DIR}/freeglut/lib/x64/freeglut.lib"
    "${CMAKE_SOURCE_DIR}/glew/lib/Release/x64/glew32.lib"
    "${CMAKE_SOURCE_DIR}/SFML-2.1/lib/sfml-system.lib"
    "${CMAKE_SOURCE_DIR}/SFML-2.1/lib/sfml-audio.lib"
    )
else()
  find_package(OpenGL REQUIRED)
  find_package(GLUT REQUIRED)
  find_package(GLEW REQUIRED)
  find_package(SFML 2 REQUIRED audio)

  include_directories(
    "${OPENGL_INCLUDE_DIR}"
    "${GLUT_INCLUDE_DIR}"
    "${GLEW_INCLUDE_DIR}"
    "${SFML_INCLUDE_DIR}"
    )

  target_link_libraries("${PROJECT_NAME}"
    ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES}
    ${SFML_LIBRARIES})
endif()
