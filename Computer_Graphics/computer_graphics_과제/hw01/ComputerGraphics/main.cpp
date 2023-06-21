
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <OpenGL/gl3.h>
#include <GLut/glut.h>

using namespace std;

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
    glClear(GL_COLOR_BUFFER_BIT);
    //Let's draw something here
    
    if (chkmouse == 0)
    {
        glDrawArrays(GL_LINES, 0, 2);
    }
    else if (chkmouse == 1)
    {
        //glVertexAttrib4iv(mouseAttrib,pa);
        glVertexAttrib3f(mouseAttrib, pa[0], pa[1], 0);
        glDrawArrays(GL_POINTS, 0, 1);
    }
    
    //define the size of point and draw a point.
    //glDrawArrays(GL_POINTS, 0, 1);

    //Double buffer
    glutSwapBuffers();
}

void processMouse(int button, int state, int x, int y)
{

    if ((state == GLUT_DOWN) && (state == GLUT_LEFT_BUTTON))
    {
        pa[0]=(float)x;
        pa[1]=(float)y;
    
        //glVertexAttrib4v(mouseAttrib,pa);
    }
//    glutPostRedisplay();
}

void processMouseActiveMotion(int x, int y)
{
    pa[0] = x;
    pa[1] = y;
    
}

void processMouseEntry(int state)
{
    if (state == GLUT_LEFT)
        chkmouse = 0;
    else
        chkmouse = 1;
}

void init()
{
    //select the background color
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
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
    
    //1.
    //Generate VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    //3.
    GLuint programID = LoadShaders("VertexShader.txt", "FragmentShader.txt");
    glUseProgram(programID);

    /* 실습 1 */
    GLint posAttrib = glGetAttribLocation(programID, "vtxPosition");
    
    GLfloat vertices[2][3] = {
       {-0.90,-0.90,0.0},
       {0.90,-0.90,0.0}
    };
    GLuint buf[1];
    glGenBuffers(1, buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, ((void*)(0)));
    glEnableVertexAttribArray(posAttrib);
    mouseAttrib = posAttrib;

    //void glutMouseFunc(void (*func)(int button, int state, int x, int y));
    glutMouseFunc(processMouse);
    glutMotionFunc(processMouseActiveMotion);
    //glutPassiveMotionFunc(processMousePassiveMotion);
    glutEntryFunc(processMouseEntry);
    //chkmouse = 0;
    //void glutMotionFunc(void (*func) (int x, int y));
    //void glutPassiveMotionFunc(void (*func) (int x, int y));
    
    glutDisplayFunc(renderScene);
    //glutEntryFunc(processMouseEntry);
    chkmouse = 0;
    
    //enter GLUT event processing cycle
    glutMainLoop();

    glDeleteVertexArrays(1, &VertexArrayID);
    
    return 1;
}

