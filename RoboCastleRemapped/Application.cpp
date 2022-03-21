#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Geometry/Geo/Vertex.h"

#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
std::string ParseShader(const std::string& FilePath);

int main() {
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "GLFW failed to initialize" << std::endl;
		return -1;
	}

	GLFWwindow* win = glfwCreateWindow(800, 800, "Robo-Castle:Remapped", nullptr, nullptr);
	glfwMakeContextCurrent(win);
	if (win == NULL) {
		std::cout << "Window Not Intitialized" << std::endl;
		return -1;
	}
	if (glewInit() != GLEW_OK){
		std::cout << "Glew Failed To Initilaize!!" << std::endl;
		return -1;
	}
	std::vector<Geometry::Vertex> verts;
	verts.push_back(Geometry::Vertex(-0.5f, -0.5f, 0.0f)); //BL
	verts.push_back(Geometry::Vertex(0.5f, -0.5f, 0.0f)); //BR
	verts.push_back(Geometry::Vertex(0.5f, 0.5f, 0.0f)); //UR
	verts.push_back(Geometry::Vertex(-0.5f, 0.5f, 0.0f));	//TL
	
	unsigned int indices[6]{ 0,1,2,2,3,0 };
	unsigned int VBO,EBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verts.size() * Geometry::Vertex::GetSize(), verts[0].GetRef(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Geometry::Vertex::GetSize(), (void*)0);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_DYNAMIC_DRAW);

	

	//Shaders
	std::string vsSrc = ParseShader("Shaders/VertexShader.shader");
	std::string fsSrc = ParseShader("Shaders/FragmentShader.shader");

	char* vsSrcC = new char[(vsSrc.size() * sizeof(char)) + 1];
	char* fsSrcC = new char[(fsSrc.size() * sizeof(char)) + 1];
	
	strcpy_s(vsSrcC, (vsSrc.size() * sizeof(char)) + 1, vsSrc.c_str());
	strcpy_s(fsSrcC, (fsSrc.size() * sizeof(char)) + 1, fsSrc.c_str());

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSrcC, nullptr);
	glCompileShader(vs);

	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSrcC, nullptr);
	glCompileShader(fs);

	unsigned int Program = glCreateProgram();
	glAttachShader(Program, vs);
	glAttachShader(Program, fs);

	glLinkProgram(Program);
	glUseProgram(Program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	while (!glfwWindowShouldClose(win)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
std::string ParseShader(const std::string& FilePath) {
	std::ifstream ReadStream;
	ReadStream.open(FilePath);
	std::stringstream StrStream;
	std::string CurrentLine;
	while (std::getline(ReadStream, CurrentLine)) {
		StrStream << CurrentLine << '\n';
	}
	ReadStream.close();
	return StrStream.str();
}