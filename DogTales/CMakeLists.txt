add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE
  bave::bave
)

target_include_directories(${PROJECT_NAME} PRIVATE .)

file(GLOB_RECURSE sources LIST_DIRECTORIES false CONFIGURE_DEPENDS "src/*.?pp")

target_sources(${PROJECT_NAME} PRIVATE ${sources})
