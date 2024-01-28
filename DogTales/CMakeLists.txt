set(generated_header_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
configure_file(src/build_version.hpp.in "${generated_header_dir}/src/build_version.hpp" @ONLY)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE
  bave::bave
  bave::bave-compile-options
)

target_include_directories(${PROJECT_NAME} PRIVATE
  .
  "${generated_header_dir}"
)

file(GLOB_RECURSE sources LIST_DIRECTORIES false CONFIGURE_DEPENDS "src/*.?pp")

target_sources(${PROJECT_NAME} PRIVATE ${sources})
