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
vector<GLfloat> vertices;
vector<GLfloat> indices;
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
int optionchk;
glm::mat4 Projection;
float pan_x, pan_y, zoom;
float l1, r1;
float radius;
float camx;
float camz;
float cameraSpeed = 0.5f;
glm::vec3 cameraPos;
glm::vec3 cameraFront;
glm::vec3 cameraUp;
float lastx = 240, lasty = 240;
float xoffset, yoffset, sensitivity = 0.5f;
float yaw, pitch;
float rotz, roty, rotx;
glm::mat4 trans;
glm::vec3 cha;

GLfloat cubeVertices[] = {
    0.1f, 0.1f,-0.1f, // triangle 2 : begin
    -0.1f,-0.1f,-0.1f,
    -0.1f, 0.1f,-0.1f, // triangle 2 : end
    0.1f, 0.1f,-0.1f,
    0.1f,-0.1f,-0.1f,
    -0.1f,-0.1f,-0.1f,

    -0.1f,-0.1f,-0.1f, // triangle 1 : begin
    -0.1f,-0.1f, 0.1f,
    -0.1f, 0.1f, 0.1f, // triangle 1 : end
    -0.1f,-0.1f,-0.1f,
    -0.1f, 0.1f, 0.1f,
    -0.1f, 0.1f,-0.1f,

    -0.1f, 0.1f, 0.1f,
    -0.1f,-0.1f, 0.1f,
    0.1f,-0.1f, 0.1f,
    0.1f, 0.1f, 0.1f,
    -0.1f, 0.1f, 0.1f,
    0.1f,-0.1f, 0.1f,

    0.1f, 0.1f, 0.1f,
    0.1f,-0.1f,-0.1f,
    0.1f, 0.1f,-0.1f,
    0.1f,-0.1f,-0.1f,
    0.1f, 0.1f, 0.1f,
    0.1f,-0.1f, 0.1f,

    0.1f,-0.1f, 0.1f,
    -0.1f,-0.1f,-0.1f,
    0.1f,-0.1f,-0.1f,
    0.1f,-0.1f, 0.1f,
    -0.1f,-0.1f, 0.1f,
    -0.1f,-0.1f,-0.1f,

    0.1f, 0.1f, 0.1f,
    0.1f, 0.1f,-0.1f,
    -0.1f, 0.1f,-0.1f,
    0.1f, 0.1f, 0.1f,
    -0.1f, 0.1f,-0.1f,
    -0.1f, 0.1f, 0.1f,
};

GLfloat cubeVertices2[] = {
    0.4f, 0.4f,0.2f, // triangle 2 : begin
    0.2f,0.2f,0.2f,
    0.2f, 0.4f,0.2f, // triangle 2 : end
    0.4f, 0.4f,0.2f,
    0.4f,0.2f,0.2f,
    0.2f,0.2f,0.2f,

    0.2f,0.2f,0.2f, // triangle 1 : begin
    0.2f,0.2f, 0.4f,
    0.2f, 0.4f, 0.4f, // triangle 1 : end
    0.2f,0.2f,0.2f,
    0.2f, 0.4f, 0.4f,
    0.2f, 0.4f,0.2f,

    0.2f, 0.4f, 0.4f,
    0.2f,0.2f, 0.4f,
    0.4f,0.2f, 0.4f,
    0.4f, 0.4f, 0.4f,
    0.2f, 0.4f, 0.4f,
    0.4f,0.2f, 0.4f,

    0.4f, 0.4f, 0.4f,
    0.4f,0.2f,0.2f,
    0.4f, 0.4f,0.2f,
    0.4f,0.2f,0.2f,
    0.4f, 0.4f, 0.4f,
    0.4f,0.2f, 0.4f,

    0.4f,0.2f, 0.4f,
    0.2f,0.2f,0.2f,
    0.4f,0.2f,0.2f,
    0.4f,0.2f, 0.4f,
    0.2f,0.2f, 0.4f,
    0.2f,0.2f,0.2f,

    0.4f, 0.4f, 0.4f,
    0.4f, 0.4f,0.2f,
    0.2f, 0.4f,0.2f,
    0.4f, 0.4f, 0.4f,
    0.2f, 0.4f,0.2f,
    0.2f, 0.4f, 0.4f,
};

GLfloat cubeColors[] = {
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,

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

GLfloat cubeColors2[] = {0,};

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

    glBindVertexArray(VertexArrayID[0]);
    glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    attribA = glGetAttribLocation(programID, "vtxPosition");
    glVertexAttribPointer(attribA, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(attribA);

    glBindBuffer(GL_ARRAY_BUFFER, buf[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColors2), cubeColors2, GL_STATIC_DRAW);
    attribB = glGetAttribLocation(programID, "a_color");
    glVertexAttribPointer(attribB, 4, GL_FLOAT, GL_FALSE, 0, (void*)1);
    glEnableVertexAttribArray(attribB);
    float xv = 1.0f, yv = 2.0f, zv = 3.0f;
    float d = sqrt(14);

    if (key)
    {
        xv = px;
        yv = py;
        d = sqrt(px * px + py * py + 9.0f);
        printf("%f ", xv);
    }
    glm::vec3 upvector(0.0f, 1.0f, 0.0f);
    glm::vec3 z(xv / d, yv / d, -zv / d);

    glm::vec3 x = glm::cross(upvector, z);
    glm::vec3 y = glm::cross(x, z);

    glBindVertexArray(VertexArrayID[0]);

    if (optionchk == 1)
        Projection = glm::perspective(glm::radians(145.0f), (float)480.0 / (float)480.0, 0.1f, 100.0f);
    else if (optionchk == 2)
        Projection = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.0f, 100.0f);

    glm::mat4 View = glm::lookAt(
        cameraPos,cameraPos+cameraFront,cameraUp
    );

    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View * Model;
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    glm::mat4 trans;
    matTrans = glGetUniformLocation(programID, "trans");
    
    for (int idxX = -10.0; idxX <= 10.0; idxX += 1.0)
    {
        for (int idxY = -10.0; idxY <= 10.0; idxY += 1.0)
        {
            GLuint matLoc = glGetUniformLocation(programID, "wmat");
            glm::mat4 wmat;
            wmat = glm::translate(glm::vec3(idxX, idxY, 0.0f));

            glUniformMatrix4fv(matLoc, 1, GL_FALSE, &wmat[0][0]);

            glBindVertexArray(VertexArrayID[0]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

    glutSwapBuffers();
}

void Pan(float dx, float dy)
{
    pan_x += dx;
    pan_y += dy;
}

void Zoom(float factor)
{
    zoom *= factor;
    pan_x *= factor;
    pan_y *= factor;
}

void myMouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        px = float(2.0f * x / 480.0f - 1.0f);
        py = float(1.0f - (2.0f * y) / 480.0f);
        key++;
        printf("%f ", px);
        glutPostRedisplay();
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        px = float(2.0f * x / 480.0f - 1.0f);
        py = float(1.0f - (2.0f * y) / 480.0f);
        key++;
        xoffset = x - lastx;
        yoffset = y - lasty;

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch += yoffset;

        if (pitch < 89.0f)
            pitch = 89.f;
        if (pitch < -89.0f)
            pitch = -89.f;

        glutPostRedisplay();
    }
}

void myKeyboard(unsigned char key, int x, int y)
{
    if (rotx != 0)
        rotx = rotx;
    optionchk = 0;
    switch (key)
    {
        case 'o':
            optionchk = 2;
            glUniformMatrix4fv(matTrans, 1, GL_FALSE, &trans[0][0]);
            glutPostRedisplay();
            break;
        case 'p':
            optionchk = 1;
            glUniformMatrix4fv(matTrans, 1, GL_FALSE, &trans[0][0]);
            glutPostRedisplay();
            break;
        case 'a':
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            glUniformMatrix4fv(matTrans, 1, GL_FALSE, &trans[0][0]);
            glutPostRedisplay();
            break;
        case 'd':
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            glUniformMatrix4fv(matTrans, 1, GL_FALSE, &trans[0][0]);
            glutPostRedisplay();
            break;
        case 'w':
            cameraPos += cameraSpeed * cameraFront;
            glUniformMatrix4fv(matTrans, 1, GL_FALSE, &trans[0][0]);
            glutPostRedisplay();
            break;
        case 's':
            cameraPos -= cameraSpeed * cameraFront;
            glUniformMatrix4fv(matTrans, 1, GL_FALSE, &trans[0][0]);
            glutPostRedisplay();
            break;
        case 'z':
            rotx -= 0.001;

            cha.x = rotx;
            cha.y = roty;
            cha.z = 1.0f;
            printf("%lf ", rotx);
          
            trans = glm::rotate(trans, -rotx, glm::vec3(0.f, 1.0f, 0.f));
            glUniformMatrix4fv(matTrans, 1, GL_FALSE, &trans[0][0]);
            glutPostRedisplay();
            break;
        case 'x':
            rotx += 0.001;
            printf("%lf ", rotx);
            trans = glm::rotate(trans, rotx, glm::vec3(0.f, 1.0f, 0.f));
            glUniformMatrix4fv(matTrans, 1, GL_FALSE, &trans[0][0]);
            glutPostRedisplay();
            break;
        case 'c':
            roty += 0.001;
            printf("%lf ", roty);
            trans = glm::rotate(trans, -roty, glm::vec3(1.f, 0.0f, 0.f));
            glUniformMatrix4fv(matTrans, 1, GL_FALSE, &trans[0][0]);
            glutPostRedisplay();
            break;
        case 'v':
            roty += 0.001;
            printf("%lf ", roty);
            trans = glm::rotate(trans, roty, glm::vec3(1.f, 0.0f, 0.f));
            glUniformMatrix4fv(matTrans, 1, GL_FALSE, &trans[0][0]);
            glutPostRedisplay();
            break;
        default:
            break;
    }

}

void change_color()
{
    for (int i = 0; i < 144; i++)
    {
        cubeColors2[i] = cubeColors[i];
        if(i%4==0)
            cubeColors2[i] = cubeColors[i] - 0.1;
        if (i % 4 == 1)
            cubeColors2[i] = cubeColors[i] - 0.1;
    }
}


void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glGenBuffers(2, buf);
    glGenVertexArrays(2, VertexArrayID);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(480, 480);
    glutCreateWindow("Simple OpenGL Window");

    init();
    programID = LoadShaders("VertexShader.txt", "FragmentShader.txt");
    glUseProgram(programID);
    change_color();
    radius = 10.0f;
    r1 = 0;
    l1 = 0;
    camx = 0;
    camz = 1;
    rotx = 0.0f;
    roty = 0.f;
    cameraPos = glm::vec3(0.f, 0.f, 3.f);
    cameraFront = glm::vec3(0.f, 0.f, -1.f);
    cameraUp = glm::vec3(0.f, 1.f, 0.f);

    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    glutDisplayFunc(renderScene);
    glutMainLoop();
    glDeleteVertexArrays(2, VertexArrayID);

    return 1;
}
