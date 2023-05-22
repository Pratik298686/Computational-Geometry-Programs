#include <GLFW/glfw3.h>
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
	std::vector<Vertex> vertex;
};

class Facet
{
public:
	Normal faceNormal;
	std::vector<Vertex> vert2;
};

void display()
{
    
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
			if (std::string::npos != line.find("endfacet"))
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

				std::cout << ptr->faceNormal.x << " " << ptr->faceNormal.y <<" " << ptr->faceNormal.z << std::endl;
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
    glBegin(GL_3D);
    glEnd();
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Triangle Example", NULL, NULL);
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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        display();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
