add_library(CsgoIn MODULE dllmain.cpp)
target_include_directories(CsgoIn PRIVATE ${CMAKE_SOURCE_DIR}/game/include)