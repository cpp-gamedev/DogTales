cmake_minimum_required(VERSION 3.23)

project(DogTales VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
  bave
  GIT_REPOSITORY https://github.com/karnkaul/bave
  GIT_TAG 532fa551c0d90ac25eb93e91a730b526f6071559
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ext/bave"
)

FetchContent_MakeAvailable(bave)

add_subdirectory(DogTales)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(compile_commands_path "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")

# On Linux compile_commands.json can be symlinked to the project root, but not on Windows.
# So we ask CMake to copy it instead. This will only happen when CMake configure is triggered.
# In other words, trigger it yourself to update the file in the project root.
if(EXISTS "${compile_commands_path}")
  message(STATUS "Copying compile_commands.json from ${compile_commands_path}")
  file(COPY "${compile_commands_path}" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

enable_testing()
add_test(NAME DogTalesUnitTests COMMAND DogTales -t)
