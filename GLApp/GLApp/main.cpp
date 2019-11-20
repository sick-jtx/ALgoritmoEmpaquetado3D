#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include "Empaquetado.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 650

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void DrawCube(Caja caja);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
int turno=1;
GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
Empaquetado empaquetado(halfScreenWidth,halfScreenHeight);


int main(void) {
	GLFWwindow *window;

	// Initialize the library
	if (!glfwInit()) {
		return -1;
	}
	srand(time(NULL));
	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);


	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	glViewport(0.0f, 0.0f, screenWidth, screenHeight); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
	glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
	glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000); // essentially set coordinate system
	glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
	glLoadIdentity(); // same as above comment


	
	//////// inicializar lo que quieras
	empaquetado.pos_generator(0);
	empaquetado.salida_datos();
	empaquetado.pos_draw_generatoor();

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		// Render OpenGL here

		glPushMatrix();
		glTranslatef(halfScreenWidth, halfScreenHeight, -500);
		glRotatef(rotationX, 1, 0, 0);
		glRotatef(rotationY, 0, 1, 0);
		glTranslatef(-halfScreenWidth, -halfScreenHeight, 500);
		
		/////////



		DrawCube(empaquetado.contenedor);
		for (Caja i : empaquetado.colocados)if(i.contenedor==turno)DrawCube(i);


		/////////
		glPopMatrix();


		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}



void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
	//std::cout << key << std::endl;

	const GLfloat rotationSpeed = 10;

	// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		switch (key) {
			case GLFW_KEY_UP:
				rotationX -= rotationSpeed;
				break;
			case GLFW_KEY_DOWN:
				rotationX += rotationSpeed;
				break;
			case GLFW_KEY_RIGHT:
				rotationY += rotationSpeed;
				break;
			case GLFW_KEY_LEFT:
				rotationY -= rotationSpeed;
				break;
			case GLFW_KEY_TAB:
				turno++;
				if (turno == empaquetado.ncontendores + 1)turno = 1;
				cout << turno;
				break;
		}


	}
}


void DrawCube(Caja caja) {
	



	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3ub(caja.R,caja.G,caja.B);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, caja.vertices);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
}