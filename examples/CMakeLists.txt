cmake_minimum_required(VERSION 3.10)

# Add Executable
add_executable(example_summarize summarize_text.cpp)

# Add Link Libraries and Include Dir
target_link_libraries(example_summarize PUBLIC Parser)
target_include_directories(example_summarize PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/lib/include"
                          )