#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <OpenGL/gl3.h>
#include <GLut/glut.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

using namespace std;

vector<GLuint> indices = {};
vector<GLfloat> vertices;
//vector<GLuint> index;
GLfloat Radius;
GLuint Stacks;
GLuint Slices;
GLuint programID;
GLuint posAttrib;
GLuint Buffers[4];
GLuint attribB;

glm::mat4 Projection;
glm::vec3 cameraUp;
glm::vec3 cameraFront;
glm::vec3 cameraPos;
GLint matTrans;
GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
    //create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    GLint Result = GL_FALSE;
    int InfoLogLength;

    //Read the vertex shader code from the file
    string VertexShaderCode;
    ifstream VertexShaderStream(vertex_file_path, ios::in);
    if (VertexShaderStream.is_open())
    {
        string Line = "";
        while (getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }

    //Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    //Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    vector<char> VertexShaderErrorMessage(max(InfoLogLength, int(1)));
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

    //Read the fragment shader code from the file
    string FragmentShaderCode;
    ifstream FragmentShaderStream(fragment_file_path, ios::in);
    if (FragmentShaderStream.is_open())
    {
        string Line = "";
        while (getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    //Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    //Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    vector<char> FragmentShaderErrorMessage(max(InfoLogLength, int(1)));
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

    //Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    vector<char> ProgramErrorMessage(max(InfoLogLength, int(1)));
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}


void renderScene(void)
{
    //Clear all pixels
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //Let's draw something here

    //P/ojection = glm::perspective(glm::radians(145.0f), (float)480.0 / (float)480.0, 0.1f, 100.0f);

    //glm::mat4 View = glm::lookAt(
    //    cameraPos, cameraPos + cameraFront, cameraUp
    //);

    //glm::mat4 Model = glm::mat4(1.0f);
    //glm::mat4 mvp = Projection * View * Model;

    //GLuint MatrixID = glGetUniformLocation(programID, "pmat");
    //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    //glm::mat4 trans;
    //matTrans = glGetUniformLocation(programID,"uLightPos");
    //glUniformMatrix4fv(matTrans, 1, GL_FALSE, &trans[0][0]);


    GLuint vtxposID = glGetAttribLocation(programID, "vtxPosition");
    GLuint normalAttrib = glGetAttribLocation(programID, "inNormal");
    
    GLuint projMatrixID = glGetUniformLocation(programID, "pmat");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "vmat");
    GLuint worldMatrixID = glGetUniformLocation(programID, "worldMat");
    GLuint LightPosID = glGetUniformLocation(programID, "uLightPos");

    GLint attribB = glGetAttribLocation(programID, "a_color");

    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 World = glm::translate(glm::vec3(1.0f, 1.0f, 1.0f));
    glm::vec3 LightPos = glm::vec3(1.0f, 1.0f, 1.0f);

    glUniformMatrix4fv(projMatrixID,1,GL_FALSE,&proj[0][0]);
    glUniformMatrix4fv(worldMatrixID, 1, GL_FALSE, &World[0][0]);
    glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
    glUniformMatrix4fv(worldMatrixID, 1, GL_FALSE, &World[0][0]);
    glUniform3fv(LightPosID, 1, &LightPos[0]);



    //define the size of point and draw a point.


    //glDrawElements();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    //Double buffer
    glutSwapBuffers();
}


void init()
{
    //select the background color
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Calc The Vertices
    for (int i = 0; i <= Stacks; ++i) {

        float V = i / (float)Stacks;
        float phi = V * glm::pi <float>();

        // Loop Through Slices
        for (int j = 0; j <= Slices; ++j) {

            float U = j / (float)Slices;
            float theta = U * (glm::pi <float>() * 2);

            // Calc The Vertex Positions
            float x = cosf(theta) * sinf(phi);
            float y = cosf(phi);
            float z = sinf(theta) * sinf(phi);

            // Push Back Vertex Data
            vertices.push_back(x * Radius);
            vertices.push_back(y * Radius);
            vertices.push_back(z * Radius);
        }
    }

    // Calc The Index Positions
    for (int i = 0; i < Slices * Stacks + Slices; ++i) {

        indices.push_back(i);
        indices.push_back(i + Slices + 1);
        indices.push_back(i + Slices);

        indices.push_back(i + Slices + 1);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    //glGenBuffers(2, buf);
    //glGenVertexArrays(2, VertexArrayID);
}


int main(int argc, char** argv)
{
    //init GLUT and create Window
    //initialize the GLUT
    glutInit(&argc, argv);
    //GLUT_DOUBLE enables double buffering (drawing to a background buffer while the other buffer is displayed)
    glutInitDisplayMode(/*GLUT_3_2_CORE_PROFILE |*/ GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    //These two functions are used to define the position and size of the window.
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(480, 480);
    //This is used to define the name of the window.
    glutCreateWindow("Simple OpenGL Window");
    Radius = 0.5;
    Stacks = 30;
    Slices = 30;
    //call initization function
    init();

    //1.
    //Generate VAO

    //3.
    GLuint programID = LoadShaders("VertexShader.txt", "FragmentShader.txt");
    glUseProgram(programID);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);

    glBindVertexArray(VertexArrayID);


    //GLint attribB = glGetAttribLocation(programID, "a_color");
    //glVertexAttribPointer(attribB, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    //glEnableVertexAttribArray(attribB);

    glGenBuffers(2, Buffers);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    posAttrib = glGetAttribLocation(programID, "vtxPosition");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, ((void*)(0)));
    glEnableVertexAttribArray(posAttrib);

    glBindBuffer(GL_ARRAY_BUFFER, Buffers[2]);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);

    //GLint colorLoc = glGetAttribLocation(programID, "a_Color");
    //glVertexAttribPointer(colorLoc,3,GL_FLOAT,GL_FALSE,)
    glutDisplayFunc(renderScene);

    //enter GLUT event processing cycle
    glutMainLoop();

    glDeleteVertexArrays(1, &VertexArrayID);

    return 1;
}
