# Notes

## **to create a window**
```C++
    GLFWwindow *window=glfwCreateWindow(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);
    glfwMakeContextCurrent(window);
```

## **the concepts of objects and client-server are vital**
OpenGL works like a server, while we,programmers, use api provided by it.

Remeber to generate an object and bind it with the target.

## **make use of high-efficency methods**
it's not hard to find that when it comes to efficency EBO > VBO > VAO.
and when use a method, the values sent to the Shader must mach with it as well.

```C++
    //here's a way to use EBO.
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO); 
    //generate done.
    glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //bind done.
    //ps: after binding VBO and EBO with their targets, the size of Buffer must be declared by glBufferData.

    const unsigned int aPos = 0;
    const unsigned int aColor = 1;
    glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(aPos);
	glVertexAttribPointer(aColor, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(aColor);
    //atrribute appointment done
    //ps:the first value of glVertexAttribPointer is the index of attribute which is written in the Vertax Shader. Thus, they should match , or error will occur.
```

## **vital concepts of Coordinate Systems**
V<sub>clip</sub>=M<sub>projection</sub> ⋅ M<sub>view</sub> ⋅ M<sub>model</sub> ⋅ V<sub>local</sub>

M<sub>projection</sub> : perspective change
```C++
glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
```

 M<sub>view</sub> : rotation

```C++
glm::mat4 model = glm::mat4(1.0f);
model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
```

M<sub>model</sub> : translate(平移)
```C++
glm::mat4 view = glm::mat4(1.0f);
// note that we're translating the scene in the reverse direction of where we want to move
view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
```
PS : remeber to use the uniform to pass those mats to Shaders
```C++
myShader->setMat("view", view);
```

## **turn 2D image to 3D image**
after using those mats, one should also do the followings
```C++
    glEnable(GL_DEPTH_TEST);
    while(drawing)
    {
        //clear the buffer to avoid overlapping serveral images. 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ...
        ...
        //use 2 Buffer to prevent user from seeing an unfinshed image, so show the completed one and draw another one behind.
        glfwSwapBuffers(window);
		glfwPollEvents();
    }
    
```
