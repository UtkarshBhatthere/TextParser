add_library(Parser STATIC parser.cpp)
target_include_directories(Parser PUBLIC include)
install(TARGETS Parser LIBRARY DESTINATION lib)