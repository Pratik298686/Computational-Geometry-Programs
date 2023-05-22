
/*
#include <iostream>
#define GLFW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

double first = 1.0f, second = 0.0f, third = 0.0f;

void display(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);

    glColor3f(first, second, third);
    glVertex2f(-0.5f, -0.5f);

    glColor3f(third, first, second);
    glVertex2f(0.5f, -0.5f);

    glColor3f(second, third, first);
    glVertex2f(0.0f, 0.5f);

    glEnd();
    glfwSwapBuffers(window);
}

void update()
{
    if (first >= 0 && second < 1 && third == 0)
    {
        first -= 0.001;
        second += 0.001;
    }
    else if (first <= 0 && second > 0 && third < 1)
    {
        first = 0;
        second -= 0.001;
        third += 0.001;
    }
    else if (first <= 1 && second <= 0 && third > 0)
    {
        first += 0.001;
        second = 0;
        third -= 0.001;

    }
    else
    {
        first = 1;
        second = 0;
        third = 0;
    }
}

int main()
{
    // glfw: initialize and configure
   // ------------------------------
    glfwInit();
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(500, 500, "Triangle Color", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT); // Clear the screen with... red, green, blue.

        display(window);

        //update the color
        update();

        glfwWaitEventsTimeout(0.00001);

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}*/

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glut.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class Vertex
{
public:
    float x, y, z;
};

class Normal
{
public:
    float x, y, z;
    //std::vector<Vertex> vertex;
};

class Facet
{
public:
    Normal faceNormal;
    std::vector<Vertex> vert2;
};

void display()
{

    //std::ifstream file("C:\\Users\\Pratik Padman\\Downloads\\STL\\STL\\ASCII\\cube with hole_fine.stl");
    std::ifstream file("C:\\Users\\Pratik Padman\\Downloads\\asciistlcube1.stl");
    std::string line, name1, name2;
    float x, y, z;
    Normal norm;
    Vertex vert;
    Facet face;

    std::vector<Facet> allTriangleFacets;
    int p = 0, q = 0;
    std::vector<std::string> vec;
    std::getline(file, line);

    int i = 0, j = 0, k;
    if (file.is_open())
    {
        k = 0;
        Facet* ptr = new Facet();
        //ptr = nullptr;

        while (std::getline(file, line))
        {
            if (i > 4 && j > 6)
            {
                i = 0;
                j = 0;
            }
            std::stringstream ss(line);
            if (std::string::npos != line.find("normal"))
            {
                ptr = new Facet();
            }
            else if (std::string::npos != line.find("endfacet"))
            {
                delete ptr;
            }
            if (std::string::npos != line.find("normal"))
            {
                ptr = new Facet();
                ss >> name1 >> name2 >> x >> y >> z;
                ptr->faceNormal.x = (float)x;
                ptr->faceNormal.y = (float)y;
                ptr->faceNormal.z = (float)z;

                //std::cout << ptr->faceNormal.x << " " << ptr->faceNormal.y << " " << ptr->faceNormal.z << std::endl;
            }
            else if (std::string::npos != line.find("vertex"))
            {
                ss >> name1 >> x >> y >> z;
                vert.x = (float)x;
                vert.y = (float)y;
                vert.z = (float)z;
                //std::cout << vert.x << " " << vert.y << " " << vert.z << std::endl;
                ptr->vert2.push_back(vert);
            }

            if ((std::string::npos != line.find("normal") || std::string::npos != line.find("vertex")) && i == 4)
            {
                allTriangleFacets.push_back(*ptr);
            }
            i++;
            j++;
        }
        file.close();
    }
    /* Draw a triangle */
    //glEnable(GL_DEPTH_TEST);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    //glPointSize(2);
    glBegin(GL_QUADS);
    for (int i = 0; i < allTriangleFacets.size(); i++)
    {
        glNormal3f(allTriangleFacets[i].faceNormal.x, allTriangleFacets[i].faceNormal.y, allTriangleFacets[i].faceNormal.z);

            glVertex3f(allTriangleFacets[i].vert2[0].x, allTriangleFacets[i].vert2[0].y, allTriangleFacets[i].vert2[0].z);
            glVertex3f(allTriangleFacets[i].vert2[1].x, allTriangleFacets[i].vert2[1].y, allTriangleFacets[i].vert2[1].z);
            glVertex3f(allTriangleFacets[i].vert2[2].x, allTriangleFacets[i].vert2[2].y, allTriangleFacets[i].vert2[2].z);

        
    }
    glEnd();
}

int main()
{
    GLFWwindow* window;
    float angle = 0.0f;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 960, "Triangle Example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Set the viewport */
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        /* Clear the background to black */
        glShadeModel(GL_LINEAR);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up the projection matrix
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
        // Set up the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -6.0f);
        glScalef(20.0, 20.0, 20.0);
        angle += 0.1f;
        glRotatef(angle, 1.0f, 1.0f, 0.0f);

        display();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
