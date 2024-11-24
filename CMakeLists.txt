cmake_minimum_required(VERSION 3.5)

project(OpenGL_API_V6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OpenGL_API_V6 main.cpp renderer.cpp renderer.h shader.cpp shader.h vertexarray.cpp
    vertexarray.h vertexbuffer.cpp vertexbuffer.h camera.cpp camera.h controls.cpp controls.h
    fpscontrols.cpp fpscontrols.h navigationcontrols.cpp navigationcontrols.h object.cpp object.h texture.cpp texture.h
    shaders/SimpleFragmentShader.fragmentshader shaders/SimpleVertexShader.vertexshader imgui/imgui.cpp
    uvbuffer.cpp uvbuffer.h imgui/imgui.h imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_internal.h imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp imgui/imstb_rectpack.h imgui/imstb_textedit.h imgui/imstb_truetype.h
    imgui/imconfig.h stb_image/stb_image.cpp stb_image/stb_image.h
    pointlight.h pointlight.cpp imgui/backends/imgui_impl_glfw.cpp imgui/backends/imgui_impl_glfw.h imgui/backends/imgui_impl_opengl2.cpp
    imgui/backends/imgui_impl_opengl3.cpp imgui/backends/imgui_impl_opengl3.h imgui/backends/imgui_impl_opengl3_loader.h


)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)


find_path(GLM_INCLUDE_DIR glm/glm.hpp)
if (GLM_INCLUDE_DIR)
    message(STATUS "Found GLM in ${GLM_INCLUDE_DIR}")
    target_include_directories(OpenGL_API_V6 PRIVATE ${GLM_INCLUDE_DIR})
else()
    message(FATAL_ERROR "GLM not found. Install GLM or specify the GLM_INCLUDE_DIR.")
endif()


target_link_libraries(OpenGL_API_V6 PRIVATE OpenGL::GL GLEW::GLEW glfw)


include(GNUInstallDirs)
install(TARGETS OpenGL_API_V6
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
