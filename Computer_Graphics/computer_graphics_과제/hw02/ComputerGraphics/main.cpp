
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

using namespace std;
vector<GLfloat> vertices;
GLuint programID;
GLuint colorLoc;
GLfloat* temp;
GLuint VertexArrayID[2];
GLuint buf[4];
GLint attribA;
GLint attribB;
GLint matTrans;
GLint viewTrans;
glm::vec3 z(1.0f, 2.0f, -3.0f);
int key;
float px, py;

GLfloat cubeVertices[] = {
    0.6f, 0.1f,-0.1f,
    0.4f,-0.1f,-0.1f,
    0.4f, 0.1f,-0.1f,
    0.6f, 0.1f,-0.1f,
    0.6f,-0.1f,-0.1f,
    0.4f,-0.1f,-0.1f,

    0.4f,-0.1f,-0.1f,
    0.4f,-0.1f, 0.1f,
    0.4f, 0.1f, 0.1f,
    0.4f,-0.1f,-0.1f,
    0.4f, 0.1f, 0.1f,
    0.4f, 0.1f,-0.1f,

    0.4f, 0.1f, 0.1f,
    0.4f,-0.1f, 0.1f,
    0.6f,-0.1f, 0.1f,
    0.6f, 0.1f, 0.1f,
    0.4f, 0.1f, 0.1f,
    0.6f,-0.1f, 0.1f,

    0.6f, 0.1f, 0.1f,
    0.6f,-0.1f,-0.1f,
    0.6f, 0.1f,-0.1f,
    0.6f,-0.1f,-0.1f,
    0.6f, 0.1f, 0.1f,
    0.6f,-0.1f, 0.1f,

    0.6f,-0.1f, 0.1f,
    0.4f,-0.1f,-0.1f,
    0.6f,-0.1f,-0.1f,
    0.6f,-0.1f, 0.1f,
    0.4f,-0.1f, 0.1f,
    0.4f,-0.1f,-0.1f,

    0.6f, 0.1f, 0.1f,
    0.6f, 0.1f,-0.1f,
    0.4f, 0.1f,-0.1f,
    0.6f, 0.1f, 0.1f,
    0.4f, 0.1f,-0.1f,
    0.4f, 0.1f, 0.1f,
};

GLfloat cubeVertices2[] = {
    -0.4f, 0.1f,-0.1f,
    -0.6f,-0.1f,-0.1f,
    -0.6f, 0.1f,-0.1f,
    -0.4f, 0.1f,-0.1f,
    -0.4f,-0.1f,-0.1f,
    -0.6f,-0.1f,-0.1f,

    -0.6f,-0.1f,-0.1f,
    -0.6f,-0.1f, 0.1f,
    -0.6f, 0.1f, 0.1f,
    -0.6f,-0.1f,-0.1f,
    -0.6f, 0.1f, 0.1f,
    -0.6f, 0.1f,-0.1f,

    -0.6f, 0.1f, 0.1f,
    -0.6f,-0.1f, 0.1f,
    -0.4f,-0.1f, 0.1f,
    -0.4f, 0.1f, 0.1f,
    -0.6f, 0.1f, 0.1f,
    -0.4f,-0.1f, 0.1f,

    -0.4f, 0.1f, 0.1f,
    -0.4f,-0.1f,-0.1f,
    -0.4f, 0.1f,-0.1f,
    -0.4f,-0.1f,-0.1f,
    -0.4f, 0.1f, 0.1f,
    -0.4f,-0.1f, 0.1f,

    -0.4f,-0.1f, 0.1f,
    -0.6f,-0.1f,-0.1f,
    -0.4f,-0.1f,-0.1f,
    -0.4f,-0.1f, 0.1f,
    -0.6f,-0.1f, 0.1f,
    -0.6f,-0.1f,-0.1f,

    -0.4f, 0.1f, 0.1f,
    -0.4f, 0.1f,-0.1f,
    -0.6f, 0.1f,-0.1f,
    -0.4f, 0.1f, 0.1f,
    -0.6f, 0.1f,-0.1f,
    -0.6f, 0.1f, 0.1f,
};

GLfloat cubeColors[] = {
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,

    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,

    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,

    1.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,
    1.0, 1.0, 0.0, 1.0,

    1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 1.0, 1.0,

    0.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,
    0.0, 1.0, 1.0, 1.0,
};

GLint mouseAttrib;
int pa[2];
int chkmouse;
//GLuint programID;

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
    if(VertexShaderStream.is_open())
    {
        string Line = "";
        while(getline(VertexShaderStream, Line))
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
    vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

    //Read the fragment shader code from the file
    string FragmentShaderCode;
    ifstream FragmentShaderStream(fragment_file_path, ios::in);
    if(FragmentShaderStream.is_open())
    {
        string Line = "";
        while(getline(FragmentShaderStream, Line))
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
    vector<char> FragmentShaderErrorMessage(InfoLogLength);
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
    vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
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

    glBindVertexArray(VertexArrayID[0]);
    glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    attribA = glGetAttribLocation(programID, "vtxPosition");
    glVertexAttribPointer(attribA, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(attribA);

    glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
    attribB = glGetAttribLocation(programID, "a_color");
    glVertexAttribPointer(attribB, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(attribB);
    
    float xv=1.0f, yv=2.0f, zv=3.0f;
    float d = sqrt(14);

    if (key)
    {
        xv = px;
        yv = py;
        d = sqrt(px * px + py * py + 9.0f);
    }
    glm::vec3 upvector(0.0f, 1.0f, 0.0f);
    glm::vec3 z(xv / d, yv / d, -zv / d);

    glm::vec3 x = glm::cross(upvector, z);
    glm::vec3 y = glm::cross(x, z);
    
    glm::vec4 Position = glm::vec4(glm::vec3(0.0f) , 1.0f);
    glm::mat4 Model = glm::mat4(1.0f);
    
    glm::mat4 Mymat = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f),upvector);
    
    Model[0] = glm::vec4(x, 0.0f); // x
    Model[1] = glm::vec4(y, 0.0f); // y
    Model[2] = glm::vec4(z, 0.0f); // z
    Model[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    glm::vec4 Transformed = Model * Position;
    
    GLfloat matv[16] = {
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
    };
    
    matTrans = glGetUniformLocation(programID, "trans");
    glBindVertexArray(VertexArrayID[0]);
    glUniformMatrix4fv(matTrans, 1, GL_FALSE, &Model[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertices) / 3);
    
    
    glBindVertexArray(VertexArrayID[1]);
    glBindBuffer(GL_ARRAY_BUFFER, buf[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices2), cubeVertices2, GL_STATIC_DRAW);
    attribA = glGetAttribLocation(programID, "vtxPosition");
    glVertexAttribPointer(attribA, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(attribA);

    glBindBuffer(GL_ARRAY_BUFFER, buf[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors), cubeColors, GL_STATIC_DRAW);
    attribB = glGetAttribLocation(programID, "a_color");
    glVertexAttribPointer(attribB, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(attribB);
    
    glUniformMatrix4fv(matTrans, 1, GL_FALSE, &Model[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(cubeVertices2) / 3);

    glutSwapBuffers();
}

void myMouse(int button, int state, int x, int y)
{
    px = float(2.0f * x / 480.0f - 1.0f);
    py = float(1.0f - (2.0f * y) / 480.0f);
    key ++;
    
    glutPostRedisplay();
    
//    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//    {
//
//        px = float(2.0f * x / 480.0f - 1.0f);
//        py = float(1.0f - (2.0f * y) / 480.0f);
//        printf("%d %d", x, y);
//        key ++;
//        printf("%f ", px);
//        glutPostRedisplay();
//    }
}

void init()
{
    //select the background color
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glGenBuffers(4, buf);
    glGenVertexArrays(2, VertexArrayID);
}

int main(int argc, char **argv)
{
    //init GLUT and create Window
    //initialize the GLUT
    glutInit(&argc, argv);
    //GLUT_DOUBLE enables double buffering (drawing to a background buffer while the other buffer is displayed)
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_DOUBLE | GLUT_RGBA);
    //These two functions are used to define the position and size of the window.
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(480, 480);
    //This is used to define the name of the window.
    glutCreateWindow("Simple OpenGL Window");

    //call initization function
    init();
    
    programID = LoadShaders("VertexShader.txt", "FragmentShader.txt");
    glUseProgram(programID);
    
    //3.
    glutMouseFunc(myMouse);
    glutDisplayFunc(renderScene);

    //enter GLUT event processing cycle
    glutMainLoop();

    glDeleteVertexArrays(2, VertexArrayID);
    
    return 1;
}

