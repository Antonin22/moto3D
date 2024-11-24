#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "pointlight.h"
#include <glm/gtc/type_ptr.hpp>
#include "imgui/imgui.h"
#include "imgui/imstb_rectpack.h"
#include "imgui/imstb_textedit.h"
#include "imgui/imstb_truetype.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


using namespace std;

int main()
{
    string path = "/home/antonin/Documents/Dev/exos/OpenGL/OpenGL_API_V6";

    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glEnable(GL_CULL_FACE);

    int width=1600, height=1600;
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);

    GLFWwindow* window = glfwCreateWindow(width,height,"OpenGL_API",NULL,NULL);
    glfwSwapInterval(1);
    if (window == NULL) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental=true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    Renderer renderer;
    Shader objectShader("/home/antonin/Documents/Dev/exos/OpenGL/OpenGL_API_V6/shaders/SimpleVertexShader.vertexshader", "/home/antonin/Documents/Dev/exos/OpenGL/OpenGL_API_V6/shaders/SimpleFragmentShader.fragmentshader");
    objectShader.Bind();


    VertexArray va;
    va.Bind();

    Camera cam(width, height);
    NavigationControls controls(window, &cam);

    Object velo("/home/antonin/Documents/Dev/exos/OpenGL/OpenGL_API_V6/obj/bike.obj", "/home/antonin/Documents/Dev/exos/OpenGL/OpenGL_API_V6/textures/UVparfum.png");
    velo.position = glm::vec3(0.0f, -0.5f, 0.0f);
    velo.rotationAngles.y = glm::radians(180.0f);


    cam.computeMatrices(width, height);
    glm::mat4 m = velo.getModelMatrix();
    glm::mat4 v = cam.getViewMatrix();
    glm::mat4 p = cam.getProjectionMatrix();
    glm::mat4 mvp = p * v * m;
    objectShader.setUniformMat4f("MVP", mvp);

    std::vector<glm::vec3> groundVertices = {
        { -10.0f, 0.0f,  0.0f },
        {  10.0f, 0.0f,  0.0f },
        { -10.0f, 0.0f, -500.0f },
        {  10.0f, 0.0f, -500.0f }
    };

    std::vector<glm::vec2> groundUVs = {
        { 0.0f, 0.0f },
        { 1.0f, 0.0f },
        { 0.0f, 10.0f },
        { 1.0f, 10.0f }
    };

    Object ground(groundVertices, groundUVs, "/home/antonin/Documents/Dev/exos/OpenGL/OpenGL_API_V6/textures/route.jpg");
    ground.position = glm::vec3(0.0f, -0.5f, 0.0f);

    GLuint roadTextureID = ground.getTextureID();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, roadTextureID);
    objectShader.setUniform1i("roadTexture", 0);

    glm::mat4 roadModelMatrix = ground.getModelMatrix();
    glm::mat4 roadMVP = p * v * roadModelMatrix;
    objectShader.setUniformMat4f("MVP", roadMVP);



    vector<glm::vec3> g_vertex_buffer_data = {
        glm::vec3(-50.0f,-50.0f,-50.0f),
        glm::vec3(-50.0f,-50.0f, 50.0f),
        glm::vec3(-50.0f, 50.0f, 50.0f),
        glm::vec3(50.0f, 50.0f,-50.0f),
        glm::vec3(-50.0f,-50.0f,-50.0f),
        glm::vec3(-50.0f, 50.0f,-50.0f),
        glm::vec3(50.0f,-50.0f, 50.0f),
        glm::vec3(-50.0f,-50.0f,-50.0f),
        glm::vec3(50.0f,-50.0f,-50.0f),
        glm::vec3(50.0f, 50.0f,-50.0f),
        glm::vec3(50.0f,-50.0f,-50.0f),
        glm::vec3(-50.0f,-50.0f,-50.0f),
        glm::vec3(-50.0f,-50.0f,-50.0f),
        glm::vec3(-50.0f, 50.0f, 50.0f),
        glm::vec3(-50.0f, 50.0f,-50.0f),
        glm::vec3(50.0f,-50.0f, 50.0f),
        glm::vec3(-50.0f,-50.0f, 50.0f),
        glm::vec3(-50.0f,-50.0f,-50.0f),
        glm::vec3(-50.0f, 50.0f, 50.0f),
        glm::vec3(-50.0f,-50.0f, 50.0f),
        glm::vec3(50.0f,-50.0f, 50.0f),
        glm::vec3(50.0f, 50.0f, 50.0f),
        glm::vec3(50.0f,-50.0f,-50.0f),
        glm::vec3(50.0f, 50.0f,-50.0f),
        glm::vec3(50.0f,-50.0f,-50.0f),
        glm::vec3(50.0f, 50.0f, 50.0f),
        glm::vec3(50.0f,-50.0f, 50.0f),
        glm::vec3(50.0f, 50.0f, 50.0f),
        glm::vec3(50.0f, 50.0f,-50.0f),
        glm::vec3(-50.0f, 50.0f,-50.0f),
        glm::vec3(50.0f, 50.0f, 50.0f),
        glm::vec3(-50.0f, 50.0f,-50.0f),
        glm::vec3(-50.0f, 50.0f, 50.0f),
        glm::vec3(50.0f, 50.0f, 50.0f),
        glm::vec3(-50.0f, 50.0f, 50.0f),
        glm::vec3(50.0f,-50.0f, 50.0f)
    };




    vector<glm::vec2> g_uv_buffer_data = {
        glm::vec2(0.000059f, 1.0f-0.000004f),
        glm::vec2(0.000103f, 1.0f-0.336048f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(1.000023f, 1.0f-0.000013f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.999958f, 1.0f-0.336064f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(0.667969f, 1.0f-0.671889f),
        glm::vec2(1.000023f, 1.0f-0.000013f),
        glm::vec2(0.668104f, 1.0f-0.000013f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.000059f, 1.0f-0.000004f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.336098f, 1.0f-0.000071f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(1.000004f, 1.0f-0.671847f),
        glm::vec2(0.999958f, 1.0f-0.336064f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.668104f, 1.0f-0.000013f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.668104f, 1.0f-0.000013f),
        glm::vec2(0.336098f, 1.0f-0.000071f),
        glm::vec2(0.000103f, 1.0f-0.336048f),
        glm::vec2(0.000004f, 1.0f-0.671870f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(0.000103f, 1.0f-0.336048f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.667969f, 1.0f-0.671889f),
        glm::vec2(1.000004f, 1.0f-0.671847f),
        glm::vec2(0.667979f, 1.0f-0.335851f)
    };

    Object o(g_vertex_buffer_data, g_uv_buffer_data, "/home/antonin/Documents/Dev/exos/OpenGL/OpenGL_API_V6/textures/sky2.jpg");


    //Création de la lumière de la moto :

    vector<glm::vec3> velo_vertex_buffer_data = {
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f,  1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        glm::vec3(-1.0f, -1.0f,  1.0f),
        glm::vec3( 1.0f, -1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f,  1.0f, -1.0f),
        glm::vec3( 1.0f, -1.0f, -1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f, -1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f),
        glm::vec3(-1.0f,  1.0f, -1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f,  1.0f,  1.0f),
        glm::vec3(-1.0f,  1.0f,  1.0f),
        glm::vec3( 1.0f, -1.0f,  1.0f)
    };






    vector<glm::vec2> velo_uv_buffer_data = {
        glm::vec2(0.000059f, 1.0f-0.000004f),
        glm::vec2(0.000103f, 1.0f-0.336048f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(1.000023f, 1.0f-0.000013f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.999958f, 1.0f-0.336064f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(0.667969f, 1.0f-0.671889f),
        glm::vec2(1.000023f, 1.0f-0.000013f),
        glm::vec2(0.668104f, 1.0f-0.000013f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.000059f, 1.0f-0.000004f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.336098f, 1.0f-0.000071f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(1.000004f, 1.0f-0.671847f),
        glm::vec2(0.999958f, 1.0f-0.336064f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.668104f, 1.0f-0.000013f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.667979f, 1.0f-0.335851f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.668104f, 1.0f-0.000013f),
        glm::vec2(0.336098f, 1.0f-0.000071f),
        glm::vec2(0.000103f, 1.0f-0.336048f),
        glm::vec2(0.000004f, 1.0f-0.671870f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(0.000103f, 1.0f-0.336048f),
        glm::vec2(0.336024f, 1.0f-0.671877f),
        glm::vec2(0.335973f, 1.0f-0.335903f),
        glm::vec2(0.667969f, 1.0f-0.671889f),
        glm::vec2(1.000004f, 1.0f-0.671847f),
        glm::vec2(0.667979f, 1.0f-0.335851f)
    };

    Object lightVelo(velo_vertex_buffer_data, velo_uv_buffer_data, "/home/antonin/Documents/Dev/exos/OpenGL/OpenGL_API_V6/textures/lum.png");


    glm::vec3 ambientLightColor(0.9f, 0.9f, 0.9f);
    objectShader.setUniform3fv("ambientLight", ambientLightColor);

    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    float lightPower = 20000.0f;

    objectShader.setUniform3fv("lightColor", lightColor);
    objectShader.setUniform1f("lightIntensity", lightPower);
    objectShader.setUniform3fv("lightPosition", velo.position);


    objectShader.setUniform3fv("viewPosition", cam.position);






    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    float lastTime = glfwGetTime();
    float currentTime, deltaTime;
    float speed = 5.0f;
    float traveledDistance = 0.0f;
    float directionChangeDistance = 250.0f;
    bool turning = false;
    int direction = 1;

    bool cameraOnVelo = false;

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)) {
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        controls.update(deltaTime, &objectShader);

        traveledDistance += 1.0f;

        if (traveledDistance >= directionChangeDistance) {
            velo.rotationAngles.y += glm::radians(180.f);
            direction *= -1;
            traveledDistance = 0.0f;
        }

        velo.position.z -= direction * speed * deltaTime;

        glm::vec3 cameraPosition = cam.position;
        glm::vec3 cameraTarget = glm::vec3(0.0f);


        if (cameraOnVelo) {
            cameraPosition = velo.position + glm::vec3(0.0f, 2.0f, 10.0f);
            cameraTarget = velo.position;
        }


        glm::mat4 v = glm::lookAt(
            cameraPosition,
            cameraTarget,
            glm::vec3(0.0f, 1.0f, 0.0f)
            );

        glm::mat4 p = cam.getProjectionMatrix();


        glm::mat4 veloModelMatrix = velo.getModelMatrix();
        glm::mat4 veloMVP = p * v * veloModelMatrix;
        objectShader.setUniformMat4f("MVP", veloMVP);
        renderer.Draw(va, velo, objectShader);


        objectShader.setUniform3fv("ambientLight", ambientLightColor);


        glm::mat4 roadModelMatrix = ground.getModelMatrix();
        glm::mat4 roadMVP = p * v * roadModelMatrix;
        objectShader.setUniformMat4f("MVP", roadMVP);
        renderer.Draw(va, ground, objectShader);

        float lightIntensity = 0.5f + 0.45f * sin(currentTime * 0.5f);
        glm::vec3 variAmbientLight = lightIntensity * ambientLightColor;
        objectShader.setUniform3fv("ambientLight", variAmbientLight);

        m = o.getModelMatrix();
        glm::mat4 skyboxMVP = p * v * m;
        objectShader.setUniformMat4f("MVP", skyboxMVP);
        renderer.Draw(va, o, objectShader);

        // Interface
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Paramètres");
        ImGui::Text("Paramètres d'éclairage et de caméra");


        ImGui::ColorEdit3("Couleur Ambient Light", (float*)&ambientLightColor);


        ImGui::Checkbox("Caméra sur la moto", &cameraOnVelo);

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
        renderer.Clear();
    }

    glfwTerminate();



    glfwTerminate();
    return 0;

}
