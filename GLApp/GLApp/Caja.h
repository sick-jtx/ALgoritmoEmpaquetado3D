#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>     
#include <stdlib.h>     
#include <time.h>
#include <algorithm>

int max(int a, int b) { return (a > b) ? a : b; }

class Caja {
public:
	Caja();
	~Caja();
	Caja(GLfloat alto, GLfloat ancho, GLfloat largo, GLfloat R, GLfloat G, GLfloat B, char tipo);
	void SetPositionDraw(GLfloat anchop, GLfloat largop, GLfloat altoc, GLfloat largoc, GLfloat anchoc);
	void SetPositionFix(int x, int y, int z);
	void SetPositionAlgorithm(int x, int y, int z, int contenedor);

	bool pertenece(int xp, int yp);
	bool operator<(Caja a);
	GLfloat vertices[72];
	GLfloat x, y, z;
	GLfloat alto, ancho, largo;
	GLfloat R, G, B;
	char tipo;
	int contenedor;
	int orientacion;

};

Caja::Caja() {}

Caja::~Caja() {}

Caja::Caja(GLfloat alto, GLfloat ancho, GLfloat largo, GLfloat R, GLfloat G, GLfloat B, char tipo) {
	this->tipo = tipo;
	this->alto = alto;
	this->ancho = ancho;
	this->largo = largo;


	x = -1;
	y = -1;
	z = -1;
	orientacion = 0;
	contenedor = 0;

	this->R = R;
	this->G = G;
	this->B = B;
}

void Caja::SetPositionDraw(GLfloat anchop, GLfloat largop, GLfloat altoc, GLfloat anchoc, GLfloat largoc) {

	this->x += anchop - largoc + largo;
	this->y += largop - anchoc + ancho;
	this->z += -500 - altoc + alto;





	GLfloat vert[72] = {
		//
											// front face
			x - largo, y + ancho, z + alto, // top left
			x + largo, y + ancho, z + alto, // top right
			x + largo, y - ancho, z + alto, // bottom right
			x - largo, y - ancho, z + alto, // bottom left

											// back face
			x - largo, y + ancho, z - alto, // top left
			x + largo, y + ancho, z - alto, // top right
			x + largo, y - ancho, z - alto, // bottom right
			x - largo, y - ancho, z - alto, // bottom left

											// left face
			x - largo, y + ancho, z + alto, // top left
			x - largo, y + ancho, z - alto, // top right
			x - largo, y - ancho, z - alto, // bottom right
			x - largo, y - ancho, z + alto, // bottom left

											// right face
			x + largo, y + ancho, z + alto, // top left
			x + largo, y + ancho, z - alto, // top right
			x + largo, y - ancho, z - alto, // bottom right
			x + largo, y - ancho, z + alto, // bottom left

											// top face
			x - largo, y + ancho, z + alto, // top left
			x - largo, y + ancho, z - alto, // top right
			x + largo, y + ancho, z - alto, // bottom right
			x + largo, y + ancho, z + alto, // bottom left

											// top face
			x - largo, y - ancho, z + alto, // top left
			x - largo, y - ancho, z - alto, // top right
			x + largo, y - ancho, z - alto, // bottom right
			x + largo, y - ancho, z + alto  // bottom left
	};

	for (int i = 0; i < 72; i++)vertices[i] = vert[i];
}
void Caja::SetPositionFix(int x, int y, int z) {
	largo *= 5.0f;
	alto *= 5.0f;
	ancho *= 5.0f;
	int a = largo;
	int b = alto;
	int c = ancho;
	this->alto = a;
	this->ancho = b;
	this->largo = c;

	this->x = y*10.f;
	this->y = z*10.f;
	this->z = x*10.f;
}
void Caja::SetPositionAlgorithm(int x, int y, int z, int contenedor) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->contenedor = contenedor;
}

bool Caja::pertenece(int xp, int yp) {
	return xp > x && xp < x + largo && yp > y && yp < y + ancho;
}

bool Caja::operator<(Caja a){
	int x = max(max(int(ancho), int(largo)), int(alto));
	int y = max(max(int(a.ancho), int(a.largo)), int(a.alto));
	return x > y;
}