include(FetchContent)

FetchContent_Declare(cereal 
    URL https://github.com/USCiLab/cereal/archive/refs/tags/v1.3.2.tar.gz
) 

message(STATUS ${cereal_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin) 

add_executable(t_cereal test_cereal.cpp)
target_include_directories(t_cereal PRIVATE ${cereal_SOURCE_DIR}/include)