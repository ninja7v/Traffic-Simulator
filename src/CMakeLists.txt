add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(my_program
 PRIVATE
  ../headers
  second_dir/)
