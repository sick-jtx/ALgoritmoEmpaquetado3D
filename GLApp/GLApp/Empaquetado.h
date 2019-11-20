#pragma once

#include<vector>
#include<fstream>

#include "Caja.h"
using namespace std;


class Empaquetado {
public:
	//Empaquetado();
	~Empaquetado();
	Empaquetado(GLfloat anchop,GLfloat largop);
	bool espacio(int x,int y,int z);
	bool alcanza(int z,int i);
	void pos_generator(int z);
	void pos_draw_generatoor();

	int ncontendores;
	

	int anchodisp, largodisp;
	GLfloat anchop, largop;

	vector<Caja>objetos;
	vector<Caja>colocados;
	Caja contenedor;

	ifstream inp;
	ofstream out;
};

//Empaquetado::Empaquetado() {}

Empaquetado::~Empaquetado() {}

Empaquetado::Empaquetado(GLfloat anchop, GLfloat largop){
	GLfloat x, y, z, ancho, largo, alto;
	this->anchop = anchop;
	this->largop = largop;
	inp.open("input.txt");
	out.open("output.txt");
	int n,m;
	char tipo;
	int R, G, B;

	inp >> alto >> ancho >> largo;
	inp >> n;
	R = rand() % 255;
	G = rand() % 255;
	B = rand() % 255;
	contenedor = Caja(alto, ancho, largo, R, G, B, '-');
	for(int i=0;i<n;i++){
		inp >> m >> tipo >> alto >> ancho >> largo;
		R = rand() % 255;
		G = rand() % 255;
		B = rand() % 255;
		for (int k = 0; k < m; k++)objetos.push_back(Caja(alto, ancho, largo, R, G, B, tipo));
	}
	sort(objetos.begin(), objetos.end());


	ncontendores = 1;

}

void Empaquetado::pos_generator(int z){
	int aux = 0;
	
	for (int i = 0; i < contenedor.ancho; i++)
	{
		
		for (int k = 0; k < contenedor.largo; k++)
		{
			if(espacio(k,i,z)){
				for(int j=0;j<objetos.size();j++){
					if (alcanza(z, j)) {
						objetos[j].SetPositionAlgorithm(k, i, z,ncontendores);
						aux = max(aux, int(objetos[j].alto));
						colocados.push_back(objetos[j]);
						break;
					}
				}
			}
		}
	}
	for(Caja i:objetos){

		if(i.z==-1){
			if(aux==0){
				ncontendores++;
				pos_generator(0);
			}
			else pos_generator(z + aux);
		}
	}
}
bool Empaquetado::espacio(int x,int y,int z){
	anchodisp = contenedor.ancho - y;
	largodisp = contenedor.largo - x;
	
	for(int i=y;i<contenedor.ancho;i++){
		for(int k=x;k<contenedor.largo;k++){
			for(Caja c:colocados){
				if (c.contenedor == ncontendores && c.z == z) {
					if (c.pertenece(k, i)) {
						if (k == x && i == y)return false;
						anchodisp = min(i - y + 1, anchodisp);
						largodisp = min(k - x, largodisp);
					}
				}
			}
		}
	}
	return true;
}

bool Empaquetado::alcanza(int z,int i){
	if (objetos[i].orientacion != 0)return false;
	objetos[i].orientacion=1;
	if(z+objetos[i].alto<=contenedor.alto){
		if(objetos[i].ancho<=anchodisp && objetos[i].largo<=largodisp){
			return true;
		}
	}

	swap(objetos[i].ancho, objetos[i].largo);
	objetos[i].orientacion = 2;
	if (z + objetos[i].alto <= contenedor.alto) {
		if (objetos[i].ancho <= anchodisp && objetos[i].largo <= largodisp) {
			return true;
		}
	}

	swap(objetos[i].alto, objetos[i].ancho);
	objetos[i].orientacion = 3;
	if (z + objetos[i].alto <= contenedor.alto) {
		if (objetos[i].ancho <= anchodisp && objetos[i].largo <= largodisp) {
			return true;
		}
	}

	swap(objetos[i].ancho, objetos[i].largo);
	objetos[i].orientacion = 4;
	if (z + objetos[i].alto <= contenedor.alto) {
		if (objetos[i].ancho <= anchodisp && objetos[i].largo <= largodisp) {
			return true;
		}
	}

	swap(objetos[i].alto, objetos[i].largo);
	objetos[i].orientacion = 5;
	if (z + objetos[i].alto <= contenedor.alto) {
		if (objetos[i].ancho <= anchodisp && objetos[i].largo <= largodisp) {
			return true;
		}
	}

	swap(objetos[i].ancho, objetos[i].largo);
	objetos[i].orientacion = 6;
	if (z + objetos[i].alto <= contenedor.alto) {
		if (objetos[i].ancho <= anchodisp && objetos[i].largo <= largodisp) {
			return true;
		}
	}
	objetos[i].orientacion = 0;
	return false;
}

void Empaquetado::pos_draw_generatoor(){
	contenedor.SetPositionFix(0, 0, 0);
	contenedor.SetPositionDraw(anchop, largop, contenedor.alto, contenedor.ancho, contenedor.largo);
	out << "num\tformato\tcoordenadas\torientacion" << endl;
	for (int i = 0; i < objetos.size(); i++) {
		out<<colocados[i].contenedor<<"\t"<<colocados[i].tipo<<"\t("<< colocados[i].x << ", " << colocados[i].y << ", " << colocados[i].z <<")\t"<<colocados[i].orientacion<< endl;
		colocados[i].SetPositionFix(colocados[i].x, colocados[i].y, colocados[i].z);
		colocados[i].SetPositionDraw(anchop, largop, contenedor.alto, contenedor.ancho, contenedor.largo);
	}

}