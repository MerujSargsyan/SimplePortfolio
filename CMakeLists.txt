cmake_minimum_required(VERSION 3.10)
project(Simple_Portfolio C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES src/main.c)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_executable(Simple_Portfolio ${SOURCE_FILES})

set_target_properties(Simple_Portfolio PROPERTIES OUTPUT_NAME "main")

target_include_directories(Simple_Portfolio PRIVATE lib/raylib/src)

if (APPLE)
    # macOS 
    target_link_libraries(Simple_Portfolio PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/raylib/src/libraylib.a
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework OpenGL"
        "-lm"
        "-ldl"
    )
elseif (UNIX)
    # Linux 
    target_link_libraries(Simple_Portfolio PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/raylib/src/libraylib.a
        "-lm"
        "-lpthread"
        "-ldl"
        "-lX11"
    )
elseif (WIN32)
    # Windows 
    target_link_libraries(Simple_Portfolio PRIVATE
        ${CMAKE_SOURCE_DIR}/lib/raylib/src/libraylib.a
        "-lm"
        "-lpthread"
        "-ldl"
        "-lX11"
    )
endif ()
