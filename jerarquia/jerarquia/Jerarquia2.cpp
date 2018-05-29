//Semestre 2018 - 2
//************************************************************//
//************************************************************//
//************** Alumno (s): *********************************//
//*************											******//
//*************											******//
//************************************************************//
//************************************************************//
#include "WINDOWS.h"
#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"
#include <mmsystem.h>
#include <iostream>
#include <fstream>

//Solo para Visual Studio 2015
#if (_MSC_VER >= 1900)
#   pragma comment( lib, "legacy_stdio_definitions.lib" )
#endif

using namespace std;

int w = 500, h = 500;
int frame=0,time,timebase=0;
int deltaTime = 0;

float rot = 180.0f, movX = 0, mX = 0, mZ = 0, rot2 = 0,
movZ = 0.0, rotTires = 0.0, rotK = 180.0, MX = -34, MY = 30,
rotB = 180, movBX = 0, movBZ = 0;

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

GLfloat Ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[]= { 0.0f, 107.0f, 0.0f, 1.0f };			// Light Position
GLfloat Position2[]= { 0.0f, 0.0f, -5.0f, 1.0f };	// Light Position

GLfloat Material_Rojo[] = { 1.0, 0.0, 0.0, 0.6 };
GLfloat Material_Blanco[] = { 1.0, 1.0, 1.0 };
GLfloat Material_Verde[] = { 0.0, 1.0, 0.0 };
GLfloat Material_Negro[] = { 0.0, 0.0, 0.0 };
GLfloat Material_Amarillo[] = { 1.0, 1.0, 0.0 };


CTexture text1, t_mural, t_coche;
CTexture text2;
CTexture text3;	//Flecha
CTexture tabique1;
CTexture minterior1;
CTexture techoC;
CTexture techoEx;
CTexture tPiso;
CTexture pasto;
CTexture gris;
CTexture ventana;
CTexture puer, puer2;
CTexture sill, mad, bur, madb, madn, escrit, teclado, met, mac,
cb, cc, mac2, mouse, madn2, madc, piedra, libro, libro2, post1, tapa;
CTexture lamp, lamp1, marron, respaldo, almohada, almohada1, colchon, base,
cajon, carp, madebl, cds0, cds1, cuadrocd;

/*ELEMENTOS CUARTO PRINCIPAL */
CTexture ventanal, piso2, pos2, alf, blanco, resp_principal, 
colchon2, base_c;

CTexture A1, A2, A3, A4, A5; // Cielo;

CTexture tree;

CFiguras cuarto;
CFiguras techoCuarto;
CFiguras sky;
CFiguras pisoCuarto;
CFiguras muro;
CFiguras s, b, m, k, t, a;

CModel silla_office, bocho, avion, sofa, maceta, spider, audifonos, lampara_mesa;

CModel silla_prins;


bool f_animacion = false, f_mover = false, f_mover2 = false,
mov_avion = false,
a_animacion = false,
avanza = false,
recorrido1 = false,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false,
recorrido5 = true,
m_animacion = false,
m_mover = false, m_mover2 = false,
p_mover = false, p_animacion = false, p_mover2 = false,

mov_bocho = false,
b_animacion = false,
avanza2 = false,
recorridob1 = false,
recorridob2 = false,
recorridob3 = false,
recorridob4 = false,
recorridob5 = true;

class Wave {

public:
	Wave(char * filename);
	~Wave();
	void play(bool async = true);
	void stop();
	bool isok();

private:
	char * buffer;
	bool ok;
	HINSTANCE HInstance;
};

void Wave::stop(){
	PlaySound(NULL, 0, 0);
}

Wave::Wave(char * filename)
{
	ok = false;
	buffer = 0;
	HInstance = GetModuleHandle(0);

	ifstream infile(filename, ios::binary);

	if (!infile)
	{
		std::cout << "Wave::file error: " << filename << std::endl;
		return;
	}

	infile.seekg(0, ios::end);   // get length of file
	int length = infile.tellg();
	buffer = new char[length];    // allocate memory
	infile.seekg(0, ios::beg);   // position to start of file
	infile.read(buffer, length);  // read entire file

	infile.close();
	ok = true;
}

Wave::~Wave()
{
	PlaySound(NULL, 0, 0); // STOP ANY PLAYING SOUND
	delete[] buffer;      // before deleting buffer.
}
void Wave::play(bool async)
{
	if (!ok)
		return;

	if (async)
		PlaySound(buffer, HInstance, SND_MEMORY | SND_ASYNC);
	else
		PlaySound(buffer, HInstance, SND_MEMORY);
}

bool Wave::isok()
{
	return ok;
}

Wave sample("sample.wav");


//Fachada recamara 1
void cascaron_recamara1(void) {
	glPushMatrix(); //paredes
		glTranslatef(0, 20, 0);
		cuarto.skybox2(60.0, 85.0, 85.0, gris.GLindex);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 50, 0);
		techoCuarto.prisma(1, 90, 90,techoC.GLindex, techoEx.GLindex, gris.GLindex);// TECHO DE LA CASA
		glPushMatrix();//muro izquierdo
			glTranslatef(-41.99, -30, 0);
			muro.prisma_gen(60, 1, 85, marron.GLindex, marron.GLindex);
		glPopMatrix();
		glPushMatrix();//muro derecho
			glTranslatef(41.99, -30, 0);
			muro.prisma_gen(60, 1, 85, marron.GLindex, marron.GLindex);
		glPopMatrix();
		glPushMatrix();//ventana
			glTranslatef(-10, -30, -42);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			muro.prisma(30, 30, 1, ventana.GLindex, gris.GLindex, gris.GLindex);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();
		//muro ventanas
		glPushMatrix();
			glTranslatef(23.74,-30 , -42);
			glRotatef(90, 1, 0, 0);
			muro.prisma(1, 37.5, 60, gris.GLindex, minterior1.GLindex, gris.GLindex );
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-33.74, -30, -42);
			glRotatef(90, 1, 0, 0);
			muro.prisma(1, 17.5, 60, gris.GLindex, minterior1.GLindex, gris.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-10, -52.5, -42);
			glRotatef(90, 1, 0, 0);
			muro.prisma(1, 30, 15, gris.GLindex, minterior1.GLindex, gris.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-10, -7.5, -42);
			glRotatef(90, 1, 0, 0);
			muro.prisma(1, 30, 15, gris.GLindex, minterior1.GLindex, gris.GLindex);
		glPopMatrix();// fin muro ventana
		// Muro puerta *******************************
		glPushMatrix();
			glTranslatef(-27.5, -35, 42);
			glRotatef(rot, 0, 1, 0);
			glTranslatef(-7.5, 0, 0);
			muro.prisma(50, 15, .5, puer2.GLindex, gris.GLindex, gris.GLindex);//puerta exterior
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-27.5, -35, 42.5);
			glRotatef(rot, 0, 1, 0);
			glTranslatef(-7.5, 0, 0);
			muro.prisma(50, 15, .5, puer.GLindex, gris.GLindex, gris.GLindex); //puerta interior
		glPopMatrix();
		glPushMatrix();
			glTranslatef(15, -30, 42.5);
			glRotatef(90, 1, 0, 0);
			muro.prisma(1, 54.9, 60, minterior1.GLindex, gris.GLindex, gris.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-35, -30, 42.5);
			glRotatef(90, 1, 0, 0);
			muro.prisma(1, 14.9, 60, minterior1.GLindex, gris.GLindex, gris.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-20, -5, 42.5);
			glRotatef(90, 1, 0, 0);
			muro.prisma(1, 15.2, 10, minterior1.GLindex, gris.GLindex, gris.GLindex);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -10, 0);
	pisoCuarto.prisma(1, 85, 85, gris.GLindex, tPiso.GLindex, gris.GLindex);// piso cuarto
		/*//pasto
		glTranslatef(0, -1, 0);
		pisoCuarto.prisma(1, 350, 350, pasto.GLindex, pasto.GLindex, pasto.GLindex);
		//patio
		glTranslatef(-62.5, 1, -10);
		pisoCuarto.prisma(1, 40, 60, piedra.GLindex, piedra.GLindex, piedra.GLindex);*/
	glPopMatrix();
}


//fachada recamara 2 - Rec. principal
void cascaron_recamara2(void) {
	glPushMatrix(); //paredes
		glTranslatef(0, 20, 0);
		cuarto.skybox3(50.0, 29.0, 52.0, gris.GLindex);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 45, 0);
		techoCuarto.prisma(1, 29.0, 52,techoC.GLindex, techoEx.GLindex, gris.GLindex);// TECHO DE LA CASA
		//**********muro izquierdo
		glPushMatrix();
			glTranslatef(-14.22, -25.5, -15);
			muro.prisma_gen(50, 0.5, 20, gris.GLindex, marron.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-14.23, -30, 0.5);
			glRotatef(90, 0, 1, 0);
			glRotatef(rot, 0, 1, 0);
			glTranslatef(-2.5, 0, 0);
			muro.prisma(40, 6.0, 0.5, puer2.GLindex, gris.GLindex, gris.GLindex);//puerta baño exterior
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-14.22, -30, 0.5);
			glRotatef(90, 0, 1, 0);
			glRotatef(rot, 0, 1, 0);
			glTranslatef(-2.5, 0, 0);
			muro.prisma(40, 6.0, 0.5, puer.GLindex, gris.GLindex, gris.GLindex); //puerta baño interior
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-14.22, -5, -2.0);
			muro.prisma_gen(10, 0.5, 6, gris.GLindex, marron.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-14.22, -25.5, 13.50);
			muro.prisma_gen(50, 0.5, 25, gris.GLindex, marron.GLindex);
		glPopMatrix();
		glPushMatrix();//muro derecho
			glTranslatef(14.22, -25, 0);
			glRotatef(180, 0, 0, 1);
			muro.prisma_gen(50, 0.5, 51.99, gris.GLindex, blanco.GLindex);
		glPopMatrix();
		glPushMatrix();//ventana
			glTranslatef(0, -25, -25.5);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.1);
			muro.prisma(25, 15, 0.2, ventanal.GLindex, gris.GLindex, gris.GLindex);
			glDisable(GL_ALPHA_TEST);
		glPopMatrix();
		//muro ventanas
		glPushMatrix();
			glTranslatef(0, -6.2 , -25.5);
			glRotatef(90, 1, 0, 0);
			glRotatef(180, 0, 0, 1);
			muro.prisma_gen(1, 15, 12.5, gris.GLindex, blanco.GLindex);//minterior1.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0 , -44, -25.5);
			glRotatef(90, 1, 0, 0);
			glRotatef(180, 0, 0, 1);
			muro.prisma_gen(1, 15, 13.5, gris.GLindex, blanco.GLindex);//minterior1.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-11, -25.5, -25.5);
			glRotatef(90, 1, 0, 0);
			muro.prisma(1, 7, 50.5, gris.GLindex, blanco.GLindex, gris.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(11, -25.5, -25.5);
			glRotatef(90, 1, 0, 0);
			muro.prisma(1, 7, 50.5, gris.GLindex, blanco.GLindex, gris.GLindex);
		glPopMatrix();// fin muro ventana
		// Muro puerta *******************************
		glPushMatrix();
			glTranslatef(-13.5, -30, 25.5);
			glRotatef(rot, 0, 1, 0);
			glTranslatef(-2.5, 0, 0);
			muro.prisma(40, 6.0, 0.5, puer2.GLindex, gris.GLindex, gris.GLindex);//puerta exterior
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-13.5, -30, 25.6);
			glRotatef(rot, 0, 1, 0);
			glTranslatef(-2.5, 0, 0);
			muro.prisma(40, 6.0, 0.5, puer.GLindex, gris.GLindex, gris.GLindex); //puerta interior
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3.0, -25.1, 25.8);
			glRotatef(90, 1, 0, 0);
			muro.prisma(0.6, 22.5, 51, blanco.GLindex, gris.GLindex, gris.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-11.0, -4.85, 25.8);
			glRotatef(90, 1, 0, 0);
			muro.prisma(0.6, 6, 10.45, blanco.GLindex, gris.GLindex, gris.GLindex);
		glPopMatrix();//fin muro puerta
	glPopMatrix();

	
	glPushMatrix();
		glTranslatef(0, -5.5, 0);
		pisoCuarto.prisma(1, 29, 51, gris.GLindex, piso2.GLindex, gris.GLindex);// piso cuarto
	glPopMatrix();
}

void silla() {
	glPushMatrix();
		glTranslatef(0.2, 3.6, 1);
		glPushMatrix();
			glScalef(.4, 2.2, 2);
			s.prisma_gen(1, 1, 1, mad.GLindex, mad.GLindex);// A
		glPopMatrix();
		glPushMatrix();
				glTranslatef(0.9, -1.35, 0);
			glPushMatrix();
				glScalef(2.2, 0.5, 2);
				s.prisma_gen(1, 1, 1, sill.GLindex, sill.GLindex); // B
			glPopMatrix();
			glPushMatrix();////////////////
					glTranslatef(-0.9, -1.25, -0.8);
				glPushMatrix();
					glScalef(0.4, 2, 0.4);
					s.prisma_gen(1, 1, 1, mad.GLindex, mad.GLindex);// C
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.9, -1.25, -0.8);
				glPushMatrix();
					glScalef(0.4, 2, 0.4);
					s.prisma_gen(1, 1, 1, mad.GLindex, mad.GLindex);// D
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.9, -1.25, 0.8);
				glPushMatrix();
					glScalef(0.4, 2, 0.4);
					s.prisma_gen(1, 1, 1, mad.GLindex, mad.GLindex);// E
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.9, -1.25, 0.8);
				glPushMatrix();
					glScalef(0.4, 2, 0.4);
					s.prisma_gen(1, 1, 1, mad.GLindex, mad.GLindex);// F
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
	
void librero() {
	glPushMatrix();
		glTranslatef(1, 0.1, -0.5);
		glPushMatrix();
				glScalef(2, 0.2, 1);
				b.prisma_gen(1, 1, 1, madn.GLindex, madn.GLindex);//A
		glPopMatrix();
		glPushMatrix();// Inicio nodo 1
			glTranslatef(3, 0.65, 0);
			glPushMatrix();
				glScalef(4, 1.5, 1);
				b.prisma_gen(1, 1, 1, bur.GLindex, madb.GLindex);//B
			glPopMatrix();
			glPushMatrix();// nodo interno
				glTranslatef(4, -1.5, 0);
				glPushMatrix();
					glScalef(4, 1.5, 1);
					b.prisma_gen(1, 1, 1, bur.GLindex, madb.GLindex);//C
				glPopMatrix();
				glPushMatrix();
					glPushMatrix();
						glTranslatef(3, -0.65, 0);
						glScalef(2, 0.2, 1);
						b.prisma_gen(1, 1, 1, madn.GLindex, madn.GLindex);//D
					glPopMatrix();
					glPushMatrix();
						glTranslatef(3.9, 0.0, 0);
						glScalef(0.2, 1.4, 1);
						b.prisma_gen(1, 1, 1, madn.GLindex, madn.GLindex);//D
					glPopMatrix();
					glPushMatrix();
						glTranslatef(3, 0.65, 0);
						glScalef(2, 0.2, 1);
						b.prisma_gen(1, 1, 1, madn.GLindex, madn.GLindex);//D
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();// fin nodo interno
		glPopMatrix();// Fin nodo 1
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.1, 0.75, -0.5);
		glScalef(0.2, 1.5, 1);
		b.prisma_gen(1, 1, 1, madn.GLindex, madn.GLindex);//A
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1, 1.4, -0.5);
		glScalef(2, 0.2, 1);
		b.prisma_gen(1, 1, 1, madn.GLindex, madn.GLindex);//A
	glPopMatrix();
}

void mesa() {
	glPushMatrix();
		glTranslatef(4, .25, 2.5);
		glPushMatrix();//mesa
			glScalef(8, 0.5, 5);
			glRotatef(90, 1, 0, 0);
			m.prisma_gen(1, 1, 1, escrit.GLindex, escrit.GLindex);
		glPopMatrix(); // fin mesa
		glPushMatrix();
			glPushMatrix();//Compu
			glTranslatef(1, 0.35, -1);//base
				glPushMatrix();
					glScalef(1, 0.1, 1);
					m.prisma_gen(1, 1, 1, met.GLindex, met.GLindex);
				glPopMatrix();
				glPushMatrix();//cuerpo 1
					glTranslatef(0, 0, -0.2);
					glPushMatrix();
						glScalef(0.1, 2, .1);
						m.cilindro(1, 1, 10, met.GLindex);
					glPopMatrix();
					glPushMatrix();//pantalla
						glTranslatef(0, 1.5, 0.1);
						glPushMatrix();
							glScalef(3, 2, 0.1);
							m.prisma_gen(1, 1, 1, mac.GLindex, mac2.GLindex);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();//Fin compu
			glPushMatrix();// teclado
				glTranslatef(-1, 0.35, 1);
				glScalef(2, 0.1, 1);
				glRotatef(270, 1, 0, 0);
				m.prisma_gen(1, 1, 1, teclado.GLindex, madn.GLindex);
			glPopMatrix();//Fin teclado
			glPushMatrix();// mouse
				glTranslatef(1, 0.35, 1);
				glScalef(0.4, 0.05, 0.6);
				glRotatef(270, 1, 0, 0);
				m.prisma_gen(1, 1, 1, mouse.GLindex, mac2.GLindex);
			glPopMatrix();//Fin mouse
		glPopMatrix();
	glPopMatrix();
}

void buro() {
	glPushMatrix();
		glPushMatrix();
			glTranslatef(1, 0.1, -0.5);
			glScalef(2, 0.2, 1);
			b.prisma_gen(1, 1, 1, madn.GLindex, madn.GLindex);//A
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.1, 0.75, -0.5);
			glScalef(0.2, 1.5, 1);
			b.prisma_gen(1, 1, 1, madn.GLindex, madn.GLindex);//A
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1, 1.4, -0.5);
			glScalef(2, 0.2, 1);
			b.prisma_gen(1, 1, 1, madn.GLindex, madn.GLindex);//A
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.9, 0.75, -0.5);
			glScalef(0.2, 1.5, 1);
			b.prisma_gen(1, 1, 1, madn.GLindex, madn.GLindex);//A
		glPopMatrix();
	glPopMatrix();
}

void estante() {
	glPushMatrix();
		glPushMatrix();
			glTranslatef(1.35, 1.75, 1.5);
			glScalef(2.7, 3.5, 3);
			m.skybox2(1, 1, 1, escrit.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.35, 1.75, 0);
			glRotatef(90, 1, 0, 0);
			glScalef(3, 0.1, 3.5);
			m.prisma_gen(1, 1, 1, madc.GLindex, madc.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.35, 1.75, 0.75);
			glRotatef(90, 1, 0, 0);
			glScalef(3, 0.1, 3.5);
			m.prisma_gen(1, 1, 1, madc.GLindex, madc.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.35, 1.75, 1.5);
			glRotatef(90, 1, 0, 0);
			glScalef(3, 0.1, 3.5);
			m.prisma_gen(1, 1, 1, madc.GLindex, madc.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.35, 1.75, 2.25);
			glRotatef(90, 1, 0, 0);
			glScalef(3, 0.1, 3.5);
			m.prisma_gen(1, 1, 1, madc.GLindex, madc.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.35, 1.75, 3);
			glRotatef(90, 1, 0, 0);
			glScalef(3, 0.1, 3.5);
			m.prisma_gen(1, 1, 1, madc.GLindex, madc.GLindex);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.35, 1.75, 3.75);
			glRotatef(90, 1, 0, 0);
			glScalef(3, 0.1, 3.5);
			m.prisma_gen(1, 1, 1, madc.GLindex, madc.GLindex);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1.35, 1.75, 0.375);
			glRotatef(90, 1, 0, 0);
			glScalef(2.65, 0.64, 3.5);
			glRotatef(180, 0, 0, 1);
			b.prisma_gen(1, 1, 1, escrit.GLindex, cc.GLindex);//A
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.35, 1.75, 1.125);
			glRotatef(90, 1, 0, 0);
			glScalef(2.65, 0.64, 3.5);
			b.prisma_gen(1, 1, 1, escrit.GLindex, cb.GLindex);//A
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.35, 1.75, 1.875);
			glRotatef(90, 1, 0, 0);
			glScalef(2.65, 0.64, 3.5);
			b.prisma_gen(1, 1, 1, escrit.GLindex, cb.GLindex);//A
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.35, 1.75, 2.625);
			glRotatef(90, 1, 0, 0);
			glScalef(2.65, 0.64, 3.5);
			b.prisma_gen(1, 1, 1, escrit.GLindex, cb.GLindex);//A
		glPopMatrix();
	glPopMatrix();
}
void libros() {
	glPushMatrix();
		glTranslatef(0, 0, 0);
		//glScalef(4, 4, 2);
		m.prisma_gen(4, 4, 2, tapa.GLindex, libro.GLindex);
	glPopMatrix();
}
void libros2() {
	glPushMatrix();
	glTranslatef(0, 0, 0);
	m.prisma_gen(4, 4, 4,libro2.GLindex, tapa.GLindex);
	glPopMatrix();
}

void cuadro() {
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glScalef(4, 4, 0.5);
		m.prisma_gen(1, 1, 1, post1.GLindex, gris.GLindex);
	glPopMatrix();
}

void cuadro3() {
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glScalef(4, 4, 0.5);
		m.prisma_gen(1, 1, 1, pos2.GLindex, gris.GLindex);
	glPopMatrix();
}

void lampara(){
	glPushMatrix();
			glTranslatef(0, 0, 0);
			glScalef(3.5, 2, 5);
			k.prisma_gen(1, 1, 1, lamp.GLindex, lamp.GLindex);//
	glPopMatrix();
	glPushMatrix();
			glTranslatef(0, -.6, 0);
			glScalef(3, 1, 4.5);
			k.prisma_gen(1, 1, 1, lamp1.GLindex, lamp1.GLindex);
	glPopMatrix();
}

void cama(){// respaldo de la pared
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glScalef(1, 10, 10);
		k.prisma_gen(1, 1, 1, respaldo.GLindex, respaldo.GLindex);//
	glPopMatrix();
}

void cama2() {
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glPushMatrix();//base color negro
			glTranslatef(10, 4.5, 26.66666667);
			glScalef(20, 9, 29);
			t.prisma_gen(1, 1, 1, base.GLindex, base.GLindex);//
		glPopMatrix();
		glPushMatrix();//cajones /cajon1
				glTranslatef(10, 4.5, 6.083333335);
				glPushMatrix();//Cajon2
					glTranslatef(0, 6.25, 0);
						glPushMatrix();//cajon3
							glTranslatef(0, 0, 12.1666667);
								glPushMatrix();//cajon4
									glTranslatef(0, 0, 12.1666667);
									glScalef(20, 3.5, 12.1666667);
									t.prisma_gen(1, 1, 1, cajon.GLindex, cajon.GLindex);//fin cajon4
								glPopMatrix();
							glScalef(20, 3.5, 12.1666667);
							t.prisma_gen(1, 1, 1, cajon.GLindex, cajon.GLindex);//fin cajon3
						glPopMatrix();
					glScalef(20, 3.5, 12.1666667);
					t.prisma_gen(1, 1, 1, cajon.GLindex, cajon.GLindex);//fin cajon2
				glPopMatrix();
			glScalef(20, 9, 12.1666667);
			t.prisma_gen(1, 1, 1, cajon.GLindex, cajon.GLindex);// fin cajon1
		glPopMatrix();
		glPushMatrix();//colchon
			glTranslatef(10, 14.5, 18.25);
			glPushMatrix();//almohada
					glTranslatef(0, 3, -14.75);
					glPushMatrix();//almohada1
						glTranslatef(-3, 2.4, 3.5);
						glPushMatrix();//alm.ohada1.5
							glTranslatef(5.5, 4, 0);
							glRotatef(180, 1, 0, 1);
							glRotatef(90, 1, 0, 1);
							glScalef(8, 2, 8);
							t.prisma_gen(1, 1, 1, almohada1.GLindex, almohada1.GLindex);
						glPopMatrix();//fin Almohada1.5
						glRotatef(-133, 1, 0, 0);
						glScalef(8, 2, 8);
						t.prisma_gen(1, 1, 1, almohada1.GLindex, almohada1.GLindex);
					glPopMatrix();//fin almohada1*/
					glRotatef(180, 0, 0, 1);
					glScalef(20, 2, 7);
					t.prisma_gen(1, 1, 1, almohada.GLindex, almohada.GLindex);
				glPopMatrix(); //fin almohada
			glRotatef(180, 0, 0, 1);
			glScalef(20, 4, 36.5);
			t.prisma_gen(1, 1, 1, colchon.GLindex, colchon.GLindex);
		glPopMatrix();//fin colchon
	glPopMatrix();
}

void carpetas() {
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glScalef(4, 6, 4);
		t.prisma_gen(1, 1, 1, carp.GLindex, carp.GLindex);
	glPopMatrix();
}

void mueblem() {
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glPushMatrix();
			glTranslatef(0.5, 6, 4);
			glPushMatrix();
					glTranslatef(7, 0, 0);
					glPushMatrix();//a
						glTranslatef(-3.5, -2, 0);
						glPushMatrix();//b
							glTranslatef(0, 4, 0);
								glPushMatrix();//c
									glTranslatef(0, 4, 0);
									glScalef(8, 1, 6);
									t.prisma_gen(1, 1, 1, madebl.GLindex, madebl.GLindex);
								glPopMatrix();//fin C
							glScalef(6, 1, 6);
							t.prisma_gen(1, 1, 1, madebl.GLindex, madebl.GLindex);
							glPopMatrix();//Fin B
						glScalef(6, 1, 6);
						t.prisma_gen(1, 1, 1, madebl.GLindex, madebl.GLindex);
						glPopMatrix();//Fin C
				glScalef(1, 12, 6);
				t.prisma_gen(1, 1, 1, madebl.GLindex, madebl.GLindex);
				glPopMatrix();
		glScalef(1, 12, 6);
		t.prisma_gen(1, 1, 1, madebl.GLindex, madebl.GLindex);
		glPopMatrix();
	glPopMatrix();
}

void cds() {
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glPushMatrix();
			glTranslatef(4, 6, 3);
			glPushMatrix();
				glTranslatef(0, 4, 0);
				glScalef(7, 3, 6);
				t.prisma_gen(1, 1, 1, cds0.GLindex, gris.GLindex);
			glPopMatrix();
		glScalef(7, 3, 6);
		t.prisma_gen(1, 1, 1, cds1.GLindex, madebl.GLindex);
		glPopMatrix();
	glPopMatrix();
}

void cuadro2() {
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glScalef(10, 22, 1);
		m.prisma_gen(1, 1, 1, cuadrocd.GLindex, gris.GLindex);
	glPopMatrix();
}

void arbol()
{
	glPushMatrix();
					glDisable(GL_LIGHTING);
					glEnable( GL_ALPHA_TEST );
					//glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
					glAlphaFunc( GL_GREATER, 0.1 );
					//glEnable(GL_BLEND);     // Turn Blending On
					//glBlendFunc(GL_SRC_ALPHA,GL_ONE);
					glBindTexture(GL_TEXTURE_2D, tree.GLindex);
					glBegin(GL_QUADS); //plano
						glColor3f(1.0, 1.0, 1.0);
						glNormal3f( 0.0f, 0.0f, 1.0f);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
					glEnd();
			glPopMatrix();

			glPushMatrix();
					glRotatef(45, 0, 1, 0);
					glBegin(GL_QUADS); //plano
						glColor3f(1.0, 1.0, 1.0);
						glNormal3f( 0.0f, 0.0f, 1.0f);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
					glEnd();
			glPopMatrix();

			glPushMatrix();
					glRotatef(-45, 0, 1, 0);
					glBegin(GL_QUADS); //plano
						glColor3f(1.0, 1.0, 1.0);
						glNormal3f( 0.0f, 0.0f, 1.0f);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
					glEnd();
			glPopMatrix();

			glPushMatrix();
					glRotatef(90, 0, 1, 0);
					glBegin(GL_QUADS); //plano
						glColor3f(1.0, 1.0, 1.0);
						glNormal3f( 0.0f, 0.0f, 1.0f);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0, 0.0, 0.0);
						glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
						glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 20.0, 0.0);
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-10.0, 20.0, 0.0);
					glEnd();
					glDisable( GL_ALPHA_TEST );
					//glDisable(GL_BLEND);        // Turn Blending Off
					//glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
					glEnable(GL_LIGHTING);
				
			glPopMatrix();
}

void cuarto1() {
	glPushMatrix();// casa
				glScalef(0.55, 0.70, 0.80);
				glTranslatef(0, 0, 0); 
				glRotatef(180, 0, 1, 0);
				glColor3f(1.0, 1.0, 1.0);
				glDisable(GL_LIGHTING);
				glScalef(0.3, 0.3, 0.3);
				cascaron_recamara1();

				//silla 1 y 2
				glPushMatrix();
					glTranslatef(-40.5, -9, 0);
					glScalef(3, 3.5, 2.5);
					silla();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-40.5, -9, 6);
					glScalef(3, 3.5, 2.5);
					silla();
				glPopMatrix();
				// Inicio librero
				glPushMatrix();
					glTranslatef(39, 35, -30);
					glRotatef(270, 0, 1, 0);
					glScalef(2.2, 4.8, 2.5);
					librero();
				glPopMatrix();
				glPushMatrix();//Buro
					glTranslatef(39, 27.8, -21.2);
					glRotatef(270, 0, 1, 0);
					glScalef(2.2, 4.8, 2.5);
					buro();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(39, 21.6, -21.2);
					glRotatef(270, 0, 1, 0);
					glScalef(2.2, 4.8, 2.5);
					buro();
				glPopMatrix();
				glPushMatrix();
					glTranslatef(39, 15.4, -21.2);
					glRotatef(270, 0, 1, 0);
					glScalef(2.2, 4.8, 2.5);
					buro();
				glPopMatrix();//Fin buro
				//ESCRITORIO
				glPushMatrix();
					glTranslatef(40.5, 10.0, -5.0);
					glRotatef(270, 0, 1, 0);
					glScalef(2.2, 4.8, 2.5);
					mesa();
				glPopMatrix();

				//Estante
				glPushMatrix();
					glTranslatef(39, 8.9, 5.5);
					glScalef(3, 6, 2.5);
					glRotatef(90, 1, 0, 0);
					glRotatef(90, 0, 0, 1);
					estante();
				glPopMatrix();

				glPushMatrix();
					glTranslatef(40.5, -11.0, -120);
					glScalef(3, 6, 2.5);
					arbol();
				glPopMatrix();


				glPushMatrix();//poster
					glTranslatef(-41, 31, -19.5);
					glScalef(1, 6, 2);
					glRotatef(90, 0, 1, 0);
					cuadro();
				glPopMatrix();

				glPushMatrix();//libros
					glTranslatef(40, 31.2, -19.1);
					glScalef(0.8, 1.2, 1);
					glRotatef(90, 0, 1, 0);
					libros();
				glPopMatrix();
				glPushMatrix();//libros
					glTranslatef(40, 18.7, -19.3);
					glScalef(0.8, 1.2, 1);
					glRotatef(90, 0, 1, 0);
					libros();
				glPopMatrix();
				glPushMatrix();//libros
					glTranslatef(40.2, 30.8, -6.2);
					glScalef(0.5, 1.1, 0.9);
					glRotatef(270, 0, 1, 0);
					libros2();
				glPopMatrix();
				glPushMatrix();//libros
					glTranslatef(40.2, 38, -27.8);
					glScalef(0.5, 1.1, 0.9);
					glRotatef(270, 0, 1, 0);
					libros2();
				glPopMatrix();

				// Lampara
				glPushMatrix();
					glTranslatef(0, 47, 0);
					glScalef(3, 2, 2);
					lampara();
				glPopMatrix();

				// cama pared
				glPushMatrix();
					glTranslatef(41, 2, -23.25);
					glScalef(1, 2.5, 3.65);
					cama();
				glPopMatrix();

				//cama base, cajones y colchon
				glPushMatrix();
					glTranslatef(21.5, -9.5, -41.5);
					glScalef(1, 1, 1);
					cama2();
				glPopMatrix();

				glPushMatrix();//carpetas
					glTranslatef(37, 2.5, -2.33);
					glScalef(1, 1, 1);
					carpetas();
				glPopMatrix();

				glPushMatrix();//mueble stereo
					glTranslatef(-41, -9.5, -42.5);
					glScalef(1, 1, 1);
					mueblem();
				glPopMatrix();
				glPushMatrix();//cds
					glTranslatef(-41, -9.5, -41.5);
					glScalef(1, 1, 1);
					cds();
				glPopMatrix();
				glPushMatrix();//cds cuadro
					glTranslatef(41, 28, 27);
					glRotatef(-90, 0, 1, 0);
					glScalef(1, 1, 1);
					cuadro2();
				glPopMatrix();
				
				glPushMatrix(); //moto 3d
					//glTranslatef(-34, -6, 30);
					glTranslatef(MX, -6, MY);
					glRotatef(220, 0, 1, 0);
					glScalef(0.01, 0.02, 0.01);
					//glTranslatef(MX, -6, MY);
					glColor3f(0.0, 0.0, 1.0);
					spider.GLrender(NULL, _SHADED, 1);
				glPopMatrix();
				glPushMatrix(); //maceta 3d
					glTranslatef(-35, 10.0, -37.5);
					glRotatef(90, 0, 1, 0);
					glScalef(15, 25, 15);
					glColor3f(0.0, 0.0, 1.0);
					maceta.GLrender(NULL, _SHADED, 1);
				glPopMatrix();

				glPushMatrix(); //sofa 3ds
					glTranslatef(12, 3.1, 33);
					//glRotatef(90, 0, 1, 0);
					glScalef(1.2, 1.2, .5);
					glColor3f(0.0, 0.0, 1.0);
					sofa.GLrender(NULL, _SHADED, 1);
				glPopMatrix();
				glPushMatrix(); //silla 3ds
					glTranslatef(115.0, -7.0 ,10.0);
					glScalef(0.015,0.02,0.015);
					glRotatef(mX, 0, 1, 0);
					silla_office.GLrender(NULL,_SHADED, 1);
				glPopMatrix();
				glPushMatrix(); //bocho 3ds
					glTranslatef(-60.0, 2.5, -10.0);
					glScalef(4, 4, 3);
					glTranslatef(movBX, 0, movBZ);
					glRotatef(rotB, 0, 1, 0);
					bocho.GLrender(NULL, _SHADED, 1);
				glPopMatrix();
				glPushMatrix(); //avion 3ds
					glTranslatef(-25.0, 15.5, -10.0); 
					glRotatef(-90, 1, 0, 0);
					glScalef(3, 3, 5);
					glTranslatef(movX, movZ, 2);
					glRotatef(rotK, 0, 0, 1);
					avion.GLrender(NULL, _SHADED, 1);
				glPopMatrix();
				glPushMatrix(); //audifonos 3ds
					glTranslatef(32, 13.8, -1);
					glScalef(50, 40, 50);
					audifonos.GLrender(NULL, _SHADED, 1);
				glPopMatrix();
				glPushMatrix(); //lampara 3ds
					glTranslatef(35, 12.5, 10);
					glScalef(0.005, .010, .005);
					glRotatef(135, 0, 1, 0);
					lampara_mesa.GLrender(NULL, _SHADED, 1);
				glPopMatrix();


			glEnable(GL_LIGHTING);
			glPopMatrix();
}

void alfombra() {
	glPushMatrix();
		glTranslatef(0, 0, 0);
		glScalef(4, 0.5, 5);
		m.prisma_gen(1, 1, 1, alf.GLindex, gris.GLindex);
	glPopMatrix();
}

void respaldo_principal() {
	glPushMatrix();
		glTranslatef(-.10, 0, -.1);
		m.prisma_gen(0.2, 5, 6, resp_principal.GLindex, madn.GLindex);
	glPopMatrix();
}

void cama_principal() {
	glPushMatrix();
		glTranslatef(0, -.4, 0);
		m.prisma_gen(2, 5, 6, colchon2.GLindex, madn.GLindex);//colchon
		glPushMatrix();
			glTranslatef(0, -2.55, 0);
			m.prisma_gen(3, 5, 6, madn.GLindex, base_c.GLindex);// base colchon
		glPopMatrix();
	glPopMatrix();
	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, -0.5, -3); 
		glRotatef(90, 1, 0, 0);
		m.prisma_gen(0.5, 3, 0.5, resp_principal.GLindex, resp_principal.GLindex);
			glPushMatrix();
				glTranslatef(0, 0, .48);
				m.prisma_gen(0.45, 3, 0.4, respaldo.GLindex, respaldo.GLindex);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-1, 0, 2);
				glScalef(0.4, 0.1, 3);
				m.prisma_gen(1, 1, 1, respaldo.GLindex, respaldo.GLindex);
			glPopMatrix();


	glPopMatrix();
}

void cuarto2() {
		glPushMatrix();// cuarto2
		glScalef(1.5, 0.70, 0.80);//glScalef(0.3, 0.3, 0.3);
		glTranslatef(0, 0, 0); 
		//glRotatef(180, 0, 1, 0);
		glColor3f(1, 1, 1);
		glDisable(GL_LIGHTING);
		glScalef(0.3, 0.3, 0.3);//glScalef(3.0, 1.8, 2);	
			cascaron_recamara2();// Se dibuja recamara


			glPushMatrix();//poster
				glTranslatef(14, 28, 0);
				glScalef(0.2, 5, 1.5);
				glRotatef(270, 0, 1, 0);
				cuadro3();
			glPopMatrix();

			glPushMatrix();//alfombra
				glTranslatef(-2, -5, 0);
				glRotatef(0, 0, 1, 0);
				glScalef(3, 0.5, 4);
				alfombra();
			glPopMatrix();

			glPushMatrix();//respaldo cama
				glTranslatef(13.8, 5.5, 0);
				glRotatef(90, 0, 0, 1);
				glScalef(4, 0.5, 2.5);
				respaldo_principal();
			glPopMatrix();

			glPushMatrix();// cama
				glTranslatef(7.5, 4, 0);
				glScalef(2.5, 2, 2);
				cama_principal();
			glPopMatrix();

			//Modelos silla
			/*glPushMatrix(); 
				glTranslatef(0, 3, 0);
				glScalef(.10, .15, .10);
				silla_prins.GLrender(NULL, _SHADED, 1);
			glPopMatrix();*/



		glEnable(GL_LIGHTING);
		glPopMatrix();
}


void InitGL ( GLvoid )     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel (GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT1, GL_AMBIENT, Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Specular);



	//glEnable ( GL_COLOR_MATERIAL );

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	//Audio

	

	//Fin audio

	t_coche.LoadTGA("Textura/02.tga");
	t_coche.BuildGLTexture();
	t_coche.ReleaseImage();


	t_mural.LoadTGA("Textura/mural.tga");
	t_mural.BuildGLTexture();
	t_mural.ReleaseImage();
    
    text1.LoadBMP("01.bmp");
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadBMP("logopumas.bmp");
	text2.BuildGLTexture();
	text2.ReleaseImage();

	text3.LoadTGA("city/arrow.tga");
	text3.BuildGLTexture();
	text3.ReleaseImage();


	tree.LoadTGA("tree01.tga");
	tree.BuildGLTexture();
	tree.ReleaseImage();

	/////////////////////////
	techoC.LoadTGA("texturas/techo.tga");
	techoC.BuildGLTexture();
	techoC.ReleaseImage();

	techoEx.LoadTGA("texturas/techo1.tga");
	techoEx.BuildGLTexture();
	techoEx.ReleaseImage();

	minterior1.LoadTGA("texturas/muro2.tga");
	minterior1.BuildGLTexture();
	minterior1.ReleaseImage();

	tPiso.LoadTGA("texturas/mozaico3.tga");
	tPiso.BuildGLTexture();
	tPiso.ReleaseImage();

	pasto.LoadTGA("texturas/pasto.tga");
	pasto.BuildGLTexture();
	pasto.ReleaseImage();

	gris.LoadTGA("texturas/gris.tga");
	gris.BuildGLTexture();
	gris.ReleaseImage();

	ventana.LoadTGA("texturas/ventana.tga");
	ventana.BuildGLTexture();
	ventana.ReleaseImage();

	puer.LoadTGA("texturas/puerta1.tga");
	puer.BuildGLTexture();
	puer.ReleaseImage();

	puer2.LoadTGA("texturas/puerta2.tga");
	puer2.BuildGLTexture();
	puer2.ReleaseImage();

	sill.LoadTGA("texturas/cojin2.tga");
	sill.BuildGLTexture();
	sill.ReleaseImage();

	mad.LoadTGA("texturas/madera2.tga");
	mad.BuildGLTexture();
	mad.ReleaseImage();

	madb.LoadTGA("texturas/madb.tga");
	madb.BuildGLTexture();
	madb.ReleaseImage();

	madn.LoadTGA("texturas/madn.tga");
	madn.BuildGLTexture();
	madn.ReleaseImage();

	madn2.LoadTGA("texturas/madn2.tga");
	madn2.BuildGLTexture();
	madn2.ReleaseImage();

	bur.LoadTGA("texturas/puertaslib.tga");
	bur.BuildGLTexture();
	bur.ReleaseImage();

	escrit.LoadTGA("texturas/mesa.tga");
	escrit.BuildGLTexture();
	escrit.ReleaseImage();

	teclado.LoadTGA("texturas/teclado.tga");
	teclado.BuildGLTexture();
	teclado.ReleaseImage();

	met.LoadTGA("texturas/metal.tga");
	met.BuildGLTexture();
	met.ReleaseImage();

	mac.LoadTGA("texturas/mac.tga");
	mac.BuildGLTexture();
	mac.ReleaseImage();

	mac2.LoadTGA("texturas/mac2.tga");
	mac2.BuildGLTexture();
	mac2.ReleaseImage();

	madc.LoadTGA("texturas/madc.tga");
	madc.BuildGLTexture();
	madc.ReleaseImage();

	cb.LoadTGA("texturas/cajones2.tga");
	cb.BuildGLTexture();
	cb.ReleaseImage();

	cc.LoadTGA("texturas/cajones.tga");
	cc.BuildGLTexture();
	cc.ReleaseImage();

	mouse.LoadTGA("texturas/mouse.tga");
	mouse.BuildGLTexture();
	mouse.ReleaseImage();

	piedra.LoadTGA("texturas/piso_p.tga");
	piedra.BuildGLTexture();
	piedra.ReleaseImage();

	libro.LoadTGA("texturas/libros.tga");
	libro.BuildGLTexture();
	libro.ReleaseImage();

	libro2.LoadTGA("texturas/libros2.tga");
	libro2.BuildGLTexture();
	libro2.ReleaseImage();

	tapa.LoadTGA("texturas/portada.tga");
	tapa.BuildGLTexture();
	tapa.ReleaseImage();

	post1.LoadTGA("texturas/post1.tga");
	post1.BuildGLTexture();
	post1.ReleaseImage();

	audifonos._3dsLoad("aud.3ds");
	audifonos.LoadTextureImages();
	audifonos.GLIniTextures();
	audifonos.ReleaseTextureImages();

	lampara_mesa._3dsLoad("lamp.3ds");
	lampara_mesa.LoadTextureImages();
	lampara_mesa.GLIniTextures();
	lampara_mesa.ReleaseTextureImages();

	silla_office._3dsLoad("silla.3ds");
	silla_office.LoadTextureImages();
	silla_office.GLIniTextures();
	silla_office.ReleaseTextureImages();

	bocho._3dsLoad("bocho.3ds");
	bocho.LoadTextureImages();
	bocho.GLIniTextures();
	bocho.ReleaseTextureImages();

	avion._3dsLoad("toy.3ds");
	avion.LoadTextureImages();
	avion.GLIniTextures();
	avion.ReleaseTextureImages();

	sofa._3dsLoad("Sofa2.3ds");

	maceta._3dsLoad("plant.3ds");

	spider._3dsLoad("moto.3ds");
	spider.LoadTextureImages();
	spider.GLIniTextures();
	spider.ReleaseTextureImages();

	lamp.LoadTGA("texturas/lamp.tga");
	lamp.BuildGLTexture();
	lamp.ReleaseImage();

	lamp1.LoadTGA("texturas/lamp2.tga");
	lamp1.BuildGLTexture();
	lamp1.ReleaseImage();

	marron.LoadTGA("texturas/marron.tga");
	marron.BuildGLTexture();
	marron.ReleaseImage();

	respaldo.LoadTGA("texturas/respaldo.tga");
	respaldo.BuildGLTexture();
	respaldo.ReleaseImage();

	base.LoadTGA("texturas/base.tga");
	base.BuildGLTexture();
	base.ReleaseImage();

	almohada.LoadTGA("texturas/almohada.tga");
	almohada.BuildGLTexture();
	almohada.ReleaseImage();

	almohada1.LoadTGA("texturas/almohada1.tga");
	almohada1.BuildGLTexture();
	almohada1.ReleaseImage();

	colchon.LoadTGA("texturas/colchon.tga");
	colchon.BuildGLTexture();
	colchon.ReleaseImage();

	cajon.LoadTGA("texturas/cajon.tga");
	cajon.BuildGLTexture();
	cajon.ReleaseImage();

	carp.LoadTGA("texturas/carp.tga");
	carp.BuildGLTexture();
	carp.ReleaseImage();

	madebl.LoadTGA("texturas/madebl.tga");
	madebl.BuildGLTexture();
	madebl.ReleaseImage();

	cds0.LoadTGA("texturas/cds.tga");
	cds0.BuildGLTexture();
	cds0.ReleaseImage();

	cds1.LoadTGA("texturas/cds1.tga");
	cds1.BuildGLTexture();
	cds1.ReleaseImage();

	cuadrocd.LoadTGA("texturas/cuadroCD.tga");
	cuadrocd.BuildGLTexture();
	cuadrocd.ReleaseImage();



	/**			casa 2			*/
	ventanal.LoadTGA("texturas2/ventanal.tga");
	ventanal.BuildGLTexture();
	ventanal.ReleaseImage();

	piso2.LoadTGA("texturas2/piso_mad.tga");
	piso2.BuildGLTexture();
	piso2.ReleaseImage();

	pos2.LoadTGA("texturas2/post2.tga");
	pos2.BuildGLTexture();
	pos2.ReleaseImage();

	blanco.LoadTGA("texturas2/blanco2.tga");
	blanco.BuildGLTexture();
	blanco.ReleaseImage();

	alf.LoadTGA("texturas2/alfombra3.tga");
	alf.BuildGLTexture();
	alf.ReleaseImage();

	resp_principal.LoadTGA("texturas2/respaldo.tga");
	resp_principal.BuildGLTexture();
	resp_principal.ReleaseImage();

	colchon2.LoadTGA("texturas2/colchon.tga");
	colchon2.BuildGLTexture();
	colchon2.ReleaseImage();

	base_c.LoadTGA("texturas2/base_c.tga");
	base_c.BuildGLTexture();
	base_c.ReleaseImage();

	A1.LoadTGA("01.tga");
	A1.BuildGLTexture();
	A1.ReleaseImage();

	A2.LoadTGA("02.tga");
	A2.BuildGLTexture();
	A2.ReleaseImage();

	A3.LoadTGA("03.tga");
	A3.BuildGLTexture();
	A3.ReleaseImage();

	A4.LoadTGA("04.tga");
	A4.BuildGLTexture();
	A4.ReleaseImage();

	A5.LoadTGA("05.tga");
	A5.BuildGLTexture();
	A5.ReleaseImage();




	silla_prins._3dsLoad("texturas2/lamp.3DS");
	silla_prins.LoadTextureImages();
	silla_prins.GLIniTextures();
	silla_prins.ReleaseTextureImages();




	//END NEW//////////////////////////////

	objCamera.Position_Camera(0,2.5f,3, 0,2.5f,0, 0, 1, 0);

}


void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glPushMatrix();
		glRotatef(g_lookupdown,1.0f,0,0);

		
		gluLookAt(	objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
					objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
					objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
		
		glPushMatrix();		
		
			/*glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0,60,0);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, Material_Blanco);
				glColor3f(1.0, 1.0, 1.0);
				sky.skybox(300.0, 300.0, 300.0,text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();*/


			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0, 75, 0);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, Material_Blanco);
				glColor3f(1.0, 1.0, 1.0);
				sky.skybox(150.0, 150.0, 150.0, A1.GLindex, A4.GLindex, A3.GLindex, A2.GLindex);
				glEnable(GL_LIGHTING);
				glPushMatrix();
				glDisable(GL_LIGHTING);
					glTranslatef(0, 75, 0);
					glScalef(250, 1, 250);
					glColor3f(1.0, 1.0, 1.0);
					k.prisma2(A5.GLindex, A5.GLindex);
				glEnable(GL_LIGHTING);
				glPopMatrix();
			glPopMatrix();
			
			glPushMatrix();
			glTranslatef(-8, 2.5, 0);
			glScalef(1.2, 1.2, 1.5);
				cuarto2();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(8, 3, 0);
				glScalef(0.8, 1, 0.8);
				cuarto1();
			glPopMatrix();
			/*glPushMatrix();
			glTranslatef(10, 0, 0);
				glScalef(0.3, 0.3, 0.3);
				glColor3f(1, 1, 1);
				m.skybox(20, 8, 5.2*4, 0, 0, 0, 0);//cuarto1();
			glPopMatrix();*/









		glPopMatrix(); 
	glPopMatrix();

	glutSwapBuffers ( );

}

void animacion()
{
	
	/**Animacion de la silla*/
	if (f_animacion) {

		if (f_mover) {
			mX += 1.0;
			if (mX > 8) {
				f_mover = false;
				//mX = 15;
			}
		}

		if (f_mover2){

			mX -= 1;
			if (mX < 0) {
				f_mover2 = false;
				//mX = 0;
			}
		}
	}

	/**Animacion de la moto*/
	if (m_animacion) {

		if (m_mover) {
			MX += 0.839;
			MY -= 0.839;
			if (MX > 15) {
				m_mover = false;
			}
		}

		if (m_mover2) {
			MX -= 0.839;
			MY += 0.839;
			if (MX <-34) {
				m_mover2 = false;
				//mX = 0;
			}
		}
	}

	/*ANIMACION AVION*/
					  
	if (a_animacion)
	{
		if (avanza)
		{
			movZ += 1.0;
			if (movZ > 20 )
				avanza = false;
		}
		else
		{
			movZ -= 1.0;
			if (movZ < 0)
				avanza = true;
		}
	} 

	if (mov_avion){

			if (recorrido1)
			{
				rotK = 180;
				movZ = movZ + 0.1;// ++;
				if (movZ>8)
				{
					recorrido1 = false;
					recorrido2 = true;
				}
			}
			if (recorrido2)
			{
				rotK = 90;
				movX = movX + 0.1;//++;
				if (movX > 18)
				{
					recorrido2 = false;
					recorrido3 = true;

				}
			}
			if (recorrido3)
			{
				rotK = 0;
				movZ = movZ - 0.1;//--;
				if (movZ<-13)
				{
					recorrido3 = false;
					recorrido4 = true;
				}
			}
			if (recorrido4)
			{
				rotK = 270;
				movX = movX - 0.1;//--;
				if (movX<0)
				{
					recorrido4 = false;
					recorrido5 = true;
				}
			}
			if (recorrido5)
			{
				rotK = 180;
				movZ = movZ + 0.1;//++;
				if (movZ>0)
				{
					recorrido5 = false;
					recorrido1 = true;
				}
			}
		
	}
	
	if (a_animacion)
	{
		if (avanza)
		{
			movZ += 1.0;
			if (movZ > 20)
				avanza = false;
		}
		else
		{
			movZ -= 1.0;
			if (movZ < 0)
				avanza = true;
		}
	}

	if (mov_bocho) {

		if (recorridob1)
		{
			rotB = 180;
			movBZ ++;
			if (movBZ > 25)
			{
				recorridob1 = false;
				recorridob2 = true;
			}
		}
		if (recorridob2)
		{
			rotB = 270;
			movBX ++;
			if (movBX > 30)
			{
				recorridob2 = false;
				recorridob3 = true;

			}
		}
		if (recorridob3)
		{
			rotB = 0;
			movBZ --;
			if (movBZ < -23)
			{
				recorridob3 = false;
				recorridob4 = true;
			}
		}
		if (recorridob4)
		{
			rotB = 90;
			movBX --;
			if (movBX < 0)
			{
				recorridob4 = false;
				recorridob5 = true;
			}
		}
		if (recorridob5)
		{
			rotB = 180;
			movBZ ++;
			if (movBZ > 0)
			{
				recorridob5 = false;
				recorridob1 = true;
			}
		}
	}



	/*	Animacion puerta	*/
	if (p_animacion) {

		if (p_mover) {
			//rot += 1.0;
			rot++;
			if (rot > 265) {
				p_mover = false;
				rot = 265;
			}
		}

		if (p_mover2) {

			rot--;//= 1;
			if (rot < 179) {
				p_mover2 = false;
				rot = 180;
			}
		}
	}



	glutPostRedisplay();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
  if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);	

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	
	glFrustum (-0.1, 0.1,-0.1, 0.1, 0.1, 300.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

void keyboard ( unsigned char key, int x, int y )  // Create Keyboard Function
{
	switch ( key ) {

		case 'w':   //Movimientos de camara
		case 'W':
			objCamera.Move_Camera( CAMERASPEED+0.1 );//0.2
			break;

		case 's':
		case 'S':
			objCamera.Move_Camera(-(CAMERASPEED+0.1));
			break;

		case 'a':
		case 'A':
			objCamera.Strafe_Camera(-(CAMERASPEED+0.2));//0.4
			break;

		case 'd':
		case 'D':
			objCamera.Strafe_Camera( CAMERASPEED+0.2 );
			break;

			/*Movimiento de la puerta*/
		case 'p':
			p_mover ^= true;
			p_animacion = true;
			break;
		case 'P':
			p_mover2 ^= true;
			p_animacion = true;
			break;

			/*Movimiento de la silla*/
		case 'l':
			f_mover ^= true;
			f_animacion = true;
			break;
		case 'L':
			f_mover2 ^= true;
			f_animacion = true;
			break;

		case 'm':
		case 'M':
			mov_avion ^= true;
				a_animacion = false;
		break;
		case 'n':
		case 'N':
			mov_bocho ^= true;
			b_animacion = false;
				
			break;
		//Movimiento moto
		case 't':
			m_mover ^= true;
			m_animacion = true;
			break;
		case 'T':
			m_mover2 ^= true;
			m_animacion = true;
			break;

		case 27:        // Cuando Esc es presionado...
			exit ( 0 );   // Salimos del programa
			break;        
		default:        // Cualquier otra
			break;
  }

  glutPostRedisplay();
}

void arrow_keys ( int a_keys, int x, int y )  // Funcion para manejo de teclas especiales (arrow keys)
{
  switch ( a_keys ) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_END: //
		sample.stop();
		break;

	case GLUT_KEY_HOME: //
		sample.play();
		break;

    case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= .50f;//g_lookupdown -= 1.0f;
		break;

    case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += .50f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View( CAMERASPEED);
		break;

    default:
		break;
  }
  glutPostRedisplay();
}

int main ( int argc, char** argv )   // Main Function
{
	
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
  glutInitWindowSize  (2000, 2000);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Jerarquia"); // Nombre de la Ventana
  //glutFullScreen     ( );         // Full Screen
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc    ( keyboard );	//Indicamos a Glut función de manejo de teclado
  glutSpecialFunc     ( arrow_keys );	//Otras
  glutIdleFunc		  ( animacion );

  
  
  glutMainLoop        ( );          // 

  

  return 0;
}
