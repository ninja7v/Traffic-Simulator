cmake_minimum_required(VERSION 3.13)
project(TrafficSimulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB SOURCES "src/*.cpp" "Tests/*.cpp")
file(GLOB HEADERS "headers/*.h")

# Include directories
include_directories(
    headers
    Dependencies/GLFW/include
    Dependencies/GL/include
    Dependencies/stb/include
    Dependencies/delaunator/include
)

# Executable
add_executable(TrafficSimulator ${SOURCES} ${HEADERS})
target_compile_definitions(TrafficSimulator PRIVATE $<$<CONFIG:Debug>:DEBUG>)

# Platform specific settings
if(WIN32)
    # Windows Dependencies
    # GLFW
    set(GLFW_LIB_DIR "${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib-vc2022")
    # FreeGLUT
    set(GL_LIB_DIR "${CMAKE_SOURCE_DIR}/Dependencies/GL/lib")

    target_link_directories(TrafficSimulator PRIVATE ${GLFW_LIB_DIR} ${GL_LIB_DIR})
    
    target_link_libraries(TrafficSimulator PRIVATE 
        glfw3 
        freeglut 
        opengl32 
        glu32 
        user32 
        gdi32 
        shell32
    )

    # Copy DLLs to output directory
    add_custom_command(TARGET TrafficSimulator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/Dependencies/GL/lib/freeglut.dll"
        $<TARGET_FILE_DIR:TrafficSimulator>
    )
    
    # Check if glfw3.dll exists and copy it if so (it might be static)
    if(EXISTS "${GLFW_LIB_DIR}/glfw3.dll")
        add_custom_command(TARGET TrafficSimulator POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GLFW_LIB_DIR}/glfw3.dll"
            $<TARGET_FILE_DIR:TrafficSimulator>
        )
    endif()

elseif(UNIX AND NOT APPLE)
    # Linux Dependencies
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW3 REQUIRED glfw3)

    target_link_libraries(TrafficSimulator PRIVATE
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        ${GLFW3_LIBRARIES}
        pthread
        X11
        Xrandr
        Xi
        dl
    )
    
    target_include_directories(TrafficSimulator PRIVATE ${GLFW3_INCLUDE_DIRS})

elseif(APPLE)
    # macOS Dependencies (Basic setup, might need adjustment)
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    find_package(glfw3 REQUIRED)

    target_link_libraries(TrafficSimulator PRIVATE
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
        glfw
    )
endif()
