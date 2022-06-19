include(FetchContent)

FetchContent_Declare(zeromq GIT_REPOSITORY https://github.com/zeromq/libzmq.git GIT_TAG v4.3.2 ) 
FetchContent_Declare(cppzmq GIT_REPOSITORY https://github.com/zeromq/cppzmq.git GIT_TAG v4.8.0 ) 
FetchContent_MakeAvailable(zeromq)
FetchContent_MakeAvailable(cppzmq)
# FetchContent_Populate(cppzmq)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin) 

add_executable(t_zmq test_zmq.cpp)
target_include_directories(t_zmq PRIVATE ${cppzmq_SOURCE_DIR})
target_link_libraries(t_zmq
    PRIVATE cppzmq ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(t_zmq_mt test_zmq_mt.cpp)
target_include_directories(t_zmq_mt PRIVATE ${cppzmq_SOURCE_DIR})
target_link_libraries(t_zmq_mt
    PRIVATE cppzmq ${CMAKE_THREAD_LIBS_INIT}
)