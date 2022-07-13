find_package(Boost REQUIRED) 

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin) 

if(Boost_FOUND)
    message(STATUS "=== boost found ===")
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(test_str "test_str.cpp") 
    target_link_libraries(test_str ${Boost_LIBRARIES})
else()
    message(STATUS "[Warning] Boost Not found!!!")
endif()