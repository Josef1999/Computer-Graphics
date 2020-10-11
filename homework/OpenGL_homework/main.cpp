
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#define UNBIND 0
//Vertex Shader 中attribute
const unsigned int aPos = 0;
const unsigned int aColor = 1;

//窗口size
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
int main()
{

	
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "myCube", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	Shader* myShader = new Shader("testshader.vs", "testshader.fs");

	float vertices[] = {
		// 沿Z轴，从正轴看向负轴，Y正轴为上，X正轴为右
		// 从右上角沿顺时钟方向存储正反面上的点
		//位置            //颜色
		//正面
		0.5f,  0.5f, 0.5f,0.0f,0.0f,0.0f,  //右上 0
		0.5f, -0.5f, 0.5f,0.0f,0.0f,1.0f,  //右下 1
		-0.5f, -0.5f,0.5f,0.0f,1.0f,0.0f,  //左下 2
		-0.5f,  0.5f,0.5f,0.0f,1.0f,1.0f,  //左上 3

		//背面
		0.5f,  0.5f, -0.5f,1.0f,0.0f,0.0f, //右上 4
		0.5f, -0.5f, -0.5f,1.0f,0.0f,1.0f, //右下 5
		-0.5f, -0.5f,-0.5f,1.0f,1.0f,0.0f, //左下 6
		-0.5f,  0.5f,-0.5f,1.0f,1.0f,1.0f, //左上 7
	};
	unsigned int indices[] = {  
		//正面 0,1,2,3
		1, 3, 0,
		1, 3, 2,

		//背面 4,5,6,7
		5, 7, 4,
		5, 7, 6,

		//左面 7,6,2,3
		6, 3, 7,
		6, 3, 2,

		//右面 4,5,1,0
		5, 0, 4,
		5, 0, 1,

		//上面 4,0,3,7
		0, 7, 4,
		0, 7, 3,

		//下面 5,1,2,6
		1, 6, 5,
		1, 6, 2

	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);  
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(aPos);
	glVertexAttribPointer(aColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(aColor);

	
	glBindBuffer(GL_ARRAY_BUFFER, UNBIND);
	glBindVertexArray(UNBIND);
	
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		
		
		glm::mat4 view=glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 proj = glm::mat4(1.0f); 
		proj= glm::perspective(glm::radians(45.0f), (float)WIDTH / ((float)HEIGHT), 0.1f, 100.0f);

		myShader->use();
		myShader->setMat("proj", proj);
		myShader->setMat("view", view);
		myShader->setMat("model", model);
		glBindVertexArray(VAO); 
		glDrawElements(GL_TRIANGLES, 6*2*3, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	
	glfwTerminate();
	return 0;
}

