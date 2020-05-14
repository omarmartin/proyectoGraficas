/*---------------------------------------------------------*/
/* ----------------   Proyecto --------------------------*/
/*-----------------    2020-2   ---------------------------*/
/*------------- Alumno: ANGUIANO MORALES BENJAMIN ----------*/
/*------------- Alumno: MARTIN MANCILLA ANGEL OMAR ----------*/
/*------------- Alumno: SAINZ VILLASANA SANTIAGO ----------*/
//version 1.0
#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>
#include "camera.h"
#include "Model.h"
#include "Texture.h"
#include "SOIL2/SOIL2.h"
#include <Windows.h>
#include <mmsystem.h>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 1280;
int SCR_HEIGHT = 720;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;
GLuint skyboxVBO, skyboxVAO;

//Camera
Camera camera(glm::vec3(1400.0f, 1000.0f, 2000.0f));
double	lastX = 0.0f,
		lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.1f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, 3.0f);
glm::vec3 lightDirection(0.0f, -1.0f, -1.0f);

void myData(void);
void myData2(void);
void display(Shader,Model);
void getResolution(void);
void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);

//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
		movZ = -5.0f,
		rotX = 0.0f;

GLfloat helices = 50.0f;

//Texture
unsigned int	t_smile;
//Animacion
float	movAuto_z = 0.0f,
		movAuto_x = 0.0f,
		elevaPiernas = 0.0f,
		bajaPiernas = 0.0f,
		orienta = 0.0f;
bool	animacion = false,
		recorrido1 = true,
		recorrido2 = false,
		recorrido3 = false,
		recorrido4 = false;

//Keyframes
		float	posX = 0.0f,
		posY = 0.0f,
		posZ = 0.0f,
		rotRodIzq = 0.0f,
		giroMonito = 0.0f,
		movBrazo = 0.0f,
		movCabeza = 0.0f,
		movOtraPierna = 0.0f,
		movOtroBrazo = 0.0f,

		posXPerro = 0.0f,
		posYPerro = 0.0f,
		posZPerro = 0.0f,
		patasDerPerro = 0.0f,
		patasIzqPerro = 0.0F,
		cabezaPerro = 0.0f,
		giroPerro = 0.0f,

		posXGato1 = 0.0f,
		posYGato1 = 0.0f,
		posZGato1 = 0.0f,
		patasDerGato1 = 0.0f,
		patasIzqGato1 = 0.0F,
		cabezaGato1 = 0.0f,
		giroGato1 = 0.0f,

		posXGato2 = 0.0f,
		posYGato2 = 0.0f,
		posZGato2 = 0.0f,
		patasDerGato2 = 0.0f,
		patasIzqGato2 = 0.0F,
		cabezaGato2 = 0.0f,
		giroGato2 = 0.0f,

		posXcubone = 0.0f,
		posYcubone = 0.0f,
		posZcubone = 0.0f,
		piernaDercubone = 0.0f,
		piernaIzqcubone = 0.0F,
		brazoDercubone = 0.0f,
		brazoIzqcubone = 0.0F,
		cabezacubone = 0.0f,
		girocubone = 0.0f,
		hueso = 0.0f;

		float	incX = 0.0f,
			incY = 0.0f,
			incZ = 0.0f,
			rotInc = 0.0f,
			giroMonitoInc = 0.0f,
			movBrazoInc = 0.0f,
			movCabezaInc = 0.0f,
			movOtraPiernaInc = 0.0f,
			movOtroBrazoInc = 0.0f,
			//PERRO
			posXPerroInc = 0.0f,
			posYPerroInc = 0.0f,
			posZPerroInc = 0.0f,
			patasDerPerroInc = 0.0f,
			patasIzqPerroInc = 0.0F,
			cabezaPerroInc = 0.0f,
			giroPerroInc = 0.0f,

			//GATO1
			posXGato1Inc = 0.0f,
			posYGato1Inc = 0.0f,
			posZGato1Inc = 0.0f,
			patasDerGato1Inc = 0.0f,
			patasIzqGato1Inc = 0.0F,
			cabezaGato1Inc = 0.0f,
			giroGato1Inc = 0.0f,


			//GATO2
			posXGato2Inc = 0.0f,
			posYGato2Inc = 0.0f,
			posZGato2Inc = 0.0f,
			patasDerGato2Inc = 0.0f,
			patasIzqGato2Inc = 0.0F,
			cabezaGato2Inc = 0.0f,
			giroGato2Inc = 0.0f,

			posXcuboneInc = 0.0f,
			posYcuboneInc = 0.0f,
			posZcuboneInc = 0.0f,
			piernaDercuboneInc = 0.0f,
			piernaIzqcuboneInc = 0.0F,
			brazoDercuboneInc = 0.0f,
			brazoIzqcuboneInc = 0.0F,
			cabezacuboneInc = 0.0f,
			girocuboneInc = 0.0f,
			huesoInc = 0.0f;




#define MAX_FRAMESheli 30
int i_max_steps = 100;
int i_curr_steps = 0;

#define MAX_FRAMEStaxi 20

#define MAX_FRAMESperro 15

#define MAX_FRAMEScubone 20

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float rotRodIzq;
	float giroMonito;
	float movBrazo;
	float movCabeza;
	float movOtraPierna;
	float movOtroBrazo;

	float posXPerro;
	float posYPerro;
	float posZPerro;
	float patasDerPerro;
	float patasIzqPerro;
	float cabezaPerro;
	float giroPerro;

	float posXGato1;
	float posYGato1;
	float posZGato1;
	float patasDerGato1;
	float patasIzqGato1;
	float cabezaGato1;
	float giroGato1;

	float posXGato2;
	float posYGato2;
	float posZGato2;
	float patasDerGato2;
	float patasIzqGato2;
	float cabezaGato2;
	float giroGato2;

	float posXcubone;
	float posYcubone;
	float posZcubone;
	float piernaDercubone;
	float piernaIzqcubone;
	float brazoDercubone;
	float brazoIzqcubone;
	float cabezacubone;
	float girocubone;
	float hueso;

}FRAME;

FRAME KeyFrame[MAX_FRAMESheli], KeyFrame1[MAX_FRAMEStaxi], KeyFrame2[MAX_FRAMESperro], KeyFrame3[MAX_FRAMEScubone];
//FRAME KeyFrameGato1[MAX_FRAMES];
int FrameIndex = 20;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame3[0].posXcubone = -30;
	KeyFrame3[0].posYcubone = 15;
	KeyFrame3[0].posZcubone = 10;
	KeyFrame3[0].girocubone = 0;
	KeyFrame3[0].piernaDercubone = 0;
	KeyFrame3[0].piernaIzqcubone = 0;
	KeyFrame3[0].brazoDercubone = 0;
	KeyFrame3[0].brazoIzqcubone = 0;
	KeyFrame3[0].cabezacubone = 0;
	KeyFrame3[0].hueso = 0;


	KeyFrame3[1].posXcubone = 0;
	KeyFrame3[1].posYcubone = 0;
	KeyFrame3[1].posZcubone = 0;
	KeyFrame3[1].girocubone = 0;
	KeyFrame3[1].piernaDercubone = 1000;
	KeyFrame3[1].piernaIzqcubone = -1000;
	KeyFrame3[1].cabezacubone = 500;
	KeyFrame3[1].cabezacubone = 0;

	KeyFrame3[2].posXcubone = 0;
	KeyFrame3[2].posYcubone = 0;
	KeyFrame3[2].posZcubone = 0;
	KeyFrame3[2].girocubone = 0;
	KeyFrame3[2].piernaDercubone = 10000;
	KeyFrame3[2].piernaIzqcubone = -10000;
	KeyFrame3[2].cabezacubone = 5000;
	KeyFrame3[2].hueso = 0;

	KeyFrame[0].posXGato1 = -175.0;
	KeyFrame[0].posYGato1 = -285.0;
	KeyFrame[0].posZGato1 = 0.0;
	KeyFrame[0].giroGato1 = 0.0;
	KeyFrame1[0].posXGato2 = 0.0;
	KeyFrame1[0].posYGato2 = 0.0;
	KeyFrame1[0].posZGato2 = 0;
	KeyFrame1[0].giroGato2 = 90;
	KeyFrame2[0].posXPerro = 0;
	KeyFrame2[0].posYPerro = -15;
	KeyFrame2[0].posZPerro = 0;
	KeyFrame2[0].giroPerro = 0;
	KeyFrame2[0].patasDerPerro = 20;
	KeyFrame2[0].patasIzqPerro = -20;
	KeyFrame2[0].cabezaPerro = 5;

	KeyFrame[1].posXGato1 = -175.0;
	KeyFrame[1].posYGato1 = 0.0;
	KeyFrame[1].posZGato1 = 0.0;
	KeyFrame[1].giroGato1 = 0.0;
	KeyFrame1[1].posXGato2 = 30;
	KeyFrame1[1].posYGato2 = 0;
	KeyFrame1[1].posZGato2 = -705;
	KeyFrame1[1].giroGato2 = 45;
	KeyFrame2[1].posXPerro = 0;
	KeyFrame2[1].posYPerro = 40;
	KeyFrame2[1].posZPerro = 110;
	KeyFrame2[1].giroPerro = 0;
	KeyFrame2[1].patasDerPerro = 10;
	KeyFrame2[1].patasIzqPerro = -10;
	KeyFrame2[1].cabezaPerro = -5;

	KeyFrame[2].posXGato1 = 375.0;
	KeyFrame[2].posYGato1 = 180.0;
	KeyFrame[2].posZGato1 = -440.0;
	KeyFrame[2].giroGato1 = -40.0;
	KeyFrame1[2].posXGato2 = -380;
	KeyFrame1[2].posYGato2 = 0;
	KeyFrame1[2].posZGato2 = -1585;
	KeyFrame1[2].giroGato2 = 30;
	KeyFrame2[2].posXPerro = 25;
	KeyFrame2[2].posYPerro = 0;
	KeyFrame2[2].posZPerro = 180;
	KeyFrame2[2].giroPerro = 60;
	KeyFrame2[2].patasDerPerro = 0;
	KeyFrame2[2].patasIzqPerro = 0;
	KeyFrame2[2].cabezaPerro = 5;

	KeyFrame[3].posXGato1 = 1210.0;
	KeyFrame[3].posYGato1 = 180.0;
	KeyFrame[3].posZGato1 = -1150.0;
	KeyFrame[3].giroGato1 = -65.0;
	KeyFrame1[3].posXGato2 = -740;
	KeyFrame1[3].posYGato2 = 0;
	KeyFrame1[3].posZGato2 = -1900;
	KeyFrame1[3].giroGato2 = 90;
	KeyFrame2[3].posXPerro = 435;
	KeyFrame2[3].posYPerro = 10;
	KeyFrame2[3].posZPerro = 45;
	KeyFrame2[3].giroPerro = 130;
	KeyFrame2[3].patasDerPerro = 15;
	KeyFrame2[3].patasIzqPerro = -15;
	KeyFrame2[3].cabezaPerro = -5;

	KeyFrame[4].posXGato1 = 1650.0;
	KeyFrame[4].posYGato1 = -770.0;
	KeyFrame[4].posZGato1 = -1565.0;
	KeyFrame[4].giroGato1 = -100.0;
	KeyFrame1[4].posXGato2 = -830;
	KeyFrame1[4].posYGato2 = 0;
	KeyFrame1[4].posZGato2 = -2115;
	KeyFrame1[4].giroGato2 = -40;
	KeyFrame2[4].posXPerro = 720;
	KeyFrame2[4].posYPerro = 10;
	KeyFrame2[4].posZPerro = 335;
	KeyFrame2[4].giroPerro = 50;
	KeyFrame2[4].patasDerPerro = 5;
	KeyFrame2[4].patasIzqPerro = -5;
	KeyFrame2[4].cabezaPerro = 5;

	KeyFrame[5].posXGato1 = 1775.0;
	KeyFrame[5].posYGato1 = -155.0;
	KeyFrame[5].posZGato1 = -1675.0;
	KeyFrame[5].giroGato1 = -280.0;
	KeyFrame1[5].posXGato2 = -860;
	KeyFrame1[5].posYGato2 = 0;
	KeyFrame1[5].posZGato2 = -2310;
	KeyFrame1[5].giroGato2 = 10;
	/*KeyFrame2[5].posXPerro = 740;
	KeyFrame2[5].posYPerro = -15;
	KeyFrame2[5].posZPerro = 335;
	KeyFrame2[5].giroPerro = 50;
	KeyFrame2[5].patasDerPerro = 20;
	KeyFrame2[5].patasIzqPerro = -20;
	KeyFrame2[5].cabezaPerro = -5;*/

	KeyFrame[6].posXGato1 = -195.0;
	KeyFrame[6].posYGato1 = 325.0;
	KeyFrame[6].posZGato1 = -2310.0;
	KeyFrame[6].giroGato1 = -270.0;
	KeyFrame1[6].posXGato2 = -925;
	KeyFrame1[6].posYGato2 = 0;
	KeyFrame1[6].posZGato2 = -2495;
	KeyFrame1[6].giroGato2 = 60;
	/*KeyFrame2[6].posXPerro = 1025;
	KeyFrame2[6].posYPerro = 130;
	KeyFrame2[6].posZPerro = 605;
	KeyFrame2[6].giroPerro = 50;
	KeyFrame2[6].patasDerPerro = 0;
	KeyFrame2[6].patasIzqPerro = 0;
	KeyFrame2[6].cabezaPerro = 5;*/

	KeyFrame[7].posXGato1 = -330.0;
	KeyFrame[7].posYGato1 = -65.0;
	KeyFrame[7].posZGato1 = -2310.0;
	KeyFrame[7].giroGato1 = -270.0;
	KeyFrame1[7].posXGato2 = -2020;
	KeyFrame1[7].posYGato2 = 0;
	KeyFrame1[7].posZGato2 = -2495;
	KeyFrame1[7].giroGato2 = 60;
	/*KeyFrame2[7].posXPerro = 1025;
	KeyFrame2[7].posYPerro = 125;
	KeyFrame2[7].posZPerro = 560;
	KeyFrame2[7].giroPerro = 140;
	KeyFrame2[7].patasDerPerro = 0;
	KeyFrame2[7].patasIzqPerro = 0;
	KeyFrame2[7].cabezaPerro = 0;*/

	KeyFrame[8].posXGato1 = -2275;
	KeyFrame[8].posYGato1 = 0;
	KeyFrame[8].posZGato1 = -2420;
	KeyFrame[8].giroGato1 = 140;
	KeyFrame1[8].posXGato2 = -2020;
	KeyFrame1[8].posYGato2 = 0;
	KeyFrame1[8].posZGato2 = -2495;
	KeyFrame1[8].giroGato2 = 60;
	/*KeyFrame2[8].posXPerro = 1025;
	KeyFrame2[8].posYPerro = 125;
	KeyFrame2[8].posZPerro = 560;
	KeyFrame2[8].giroPerro = 140;
	KeyFrame2[8].patasDerPerro = 0;
	KeyFrame2[8].patasIzqPerro = 0;
	KeyFrame2[8].cabezaPerro = 0;*/

	KeyFrame[9].posXGato1 = -2380;
	KeyFrame[9].posYGato1 = 0;
	KeyFrame[9].posZGato1 = -2225;
	KeyFrame[9].giroGato1 = 180;
	KeyFrame1[9].posXGato2 = -2020;
	KeyFrame1[9].posYGato2 = 0;
	KeyFrame1[9].posZGato2 = -2495;
	KeyFrame1[9].giroGato2 = 60;
	/*KeyFrame2[9].posXPerro = 1025;
	KeyFrame2[9].posYPerro = 125;
	KeyFrame2[9].posZPerro = 560;
	KeyFrame2[9].giroPerro = 140;
	KeyFrame2[9].patasDerPerro = 0;
	KeyFrame2[9].patasIzqPerro = 0;
	KeyFrame2[9].cabezaPerro = 0;*/

	KeyFrame[10].posXGato1 = -2405;
	KeyFrame[10].posYGato1 = 0;
	KeyFrame[10].posZGato1 = -950;
	KeyFrame[10].giroGato1 = 170;
	KeyFrame1[10].posXGato2 = -2020;
	KeyFrame1[10].posYGato2 = 0;
	KeyFrame1[10].posZGato2 = -2495;
	KeyFrame1[10].giroGato2 = 60;
	/*KeyFrame2[10].posXPerro = 1025;
	KeyFrame2[10].posYPerro = 125;
	KeyFrame2[10].posZPerro = 560;
	KeyFrame2[10].giroPerro = 140;
	KeyFrame2[10].patasDerPerro = 0;
	KeyFrame2[10].patasIzqPerro = 0;
	KeyFrame2[10].cabezaPerro = 0;*/

	

	

	//KeyFrame[FrameIndex].patasDerGato2 = patasDerGato2;
	//KeyFrame[FrameIndex].patasIzqGato2 = patasIzqGato2;
	//KeyFrame[FrameIndex].cabezaGato2 = cabezaGato2;
	

	/*KeyFrame[FrameIndex].patasDerGato1 = patasDerGato1;
	KeyFrame[FrameIndex].patasIzqGato1 = patasIzqGato1;
	KeyFrame[FrameIndex].cabezaGato1 = cabezaGato1;*/
	
	
	/*KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;
	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].giroMonito = giroMonito;
	KeyFrame[FrameIndex].movBrazo = movBrazo;
	KeyFrame[FrameIndex].movCabeza = movCabeza;
	KeyFrame[FrameIndex].movOtraPierna = movOtraPierna;
	KeyFrame[FrameIndex].movOtroBrazo = movOtroBrazo;

	*/




	/*FrameIndex++;*/
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;
	rotRodIzq = KeyFrame[0].rotRodIzq;
	giroMonito = KeyFrame[0].giroMonito;
	movBrazo = KeyFrame[0].movBrazo;
	movCabeza = KeyFrame[0].movCabeza;
	movOtraPierna = KeyFrame[0].movOtraPierna;
	movOtroBrazo = KeyFrame[0].movOtroBrazo;

	posXPerro = KeyFrame2[0].posXPerro;
	posYPerro = KeyFrame2[0].posYPerro;
	posZPerro = KeyFrame2[0].posZPerro;
	patasDerPerro = KeyFrame2[0].patasDerPerro;
	patasIzqPerro = KeyFrame2[0].patasIzqPerro;
	cabezaPerro = KeyFrame2[0].cabezaPerro;
	giroPerro= KeyFrame2[0].giroPerro;

	posXGato1 = KeyFrame[0].posXGato1;
	posYGato1 = KeyFrame[0].posYGato1;
	posZGato1 = KeyFrame[0].posZGato1;
	patasDerGato1 = KeyFrame[0].patasDerGato1;
	patasIzqGato1 = KeyFrame[0].patasIzqGato1;
	cabezaGato1 = KeyFrame[0].cabezaGato1;
	giroGato1 = KeyFrame[0].giroGato1;

	posXGato2 = KeyFrame1[0].posXGato2;
	posYGato2 = KeyFrame1[0].posYGato2;
	posZGato2 = KeyFrame1[0].posZGato2;
	patasDerGato2 = KeyFrame1[0].patasDerGato2;
	patasIzqGato2 = KeyFrame1[0].patasIzqGato2;
	cabezaGato2 = KeyFrame1[0].cabezaGato2;
	giroGato2 = KeyFrame1[0].giroGato2;

	posXcubone = KeyFrame3[0].posXcubone;
	posYcubone = KeyFrame3[0].posYcubone;
	posZcubone = KeyFrame3[0].posZcubone;
	piernaDercubone = KeyFrame3[0].piernaDercubone;
	piernaIzqcubone = KeyFrame3[0].piernaIzqcubone;
	brazoDercubone = KeyFrame3[0].brazoDercubone;
	brazoIzqcubone = KeyFrame3[0].brazoIzqcubone;
	cabezacubone = KeyFrame3[0].cabezaGato2;
	girocubone = KeyFrame3[0].giroGato2;
	hueso = KeyFrame3[0].hueso;
}

void interpolation(void)
{

	incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;
	rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;
	movBrazoInc = (KeyFrame[playIndex + 1].movBrazo - KeyFrame[playIndex].movBrazo) / i_max_steps;
	movCabezaInc = (KeyFrame[playIndex + 1].movCabeza - KeyFrame[playIndex].movCabeza) / i_max_steps;
	movOtraPiernaInc = (KeyFrame[playIndex + 1].movOtraPierna - KeyFrame[playIndex].movOtraPierna) / i_max_steps;
	movOtroBrazoInc = (KeyFrame[playIndex + 1].movOtroBrazo - KeyFrame[playIndex].movOtroBrazo) / i_max_steps;

	posXPerroInc = (KeyFrame2[playIndex + 1].posXPerro - KeyFrame2[playIndex].posXPerro) / i_max_steps;
	posYPerroInc = (KeyFrame2[playIndex + 1].posYPerro - KeyFrame2[playIndex].posYPerro) / i_max_steps;
	posZPerroInc = (KeyFrame2[playIndex + 1].posZPerro - KeyFrame2[playIndex].posZPerro) / i_max_steps;
	patasDerPerroInc = (KeyFrame2[playIndex + 1].patasDerPerro - KeyFrame2[playIndex].patasDerPerro) / i_max_steps;
	patasIzqPerroInc = (KeyFrame2[playIndex + 1].patasIzqPerro - KeyFrame2[playIndex].patasIzqPerro) / i_max_steps;
	cabezaPerroInc = (KeyFrame2[playIndex + 1].cabezaPerro - KeyFrame2[playIndex].cabezaPerro) / i_max_steps;
	giroPerroInc = (KeyFrame2[playIndex + 1].giroPerro - KeyFrame2[playIndex].giroPerro) / i_max_steps;

	posXGato1Inc = (KeyFrame[playIndex + 1].posXGato1 - KeyFrame[playIndex].posXGato1) / i_max_steps;
	posYGato1Inc = (KeyFrame[playIndex + 1].posYGato1 - KeyFrame[playIndex].posYGato1) / i_max_steps;
	posZGato1Inc = (KeyFrame[playIndex + 1].posZGato1 - KeyFrame[playIndex].posZGato1) / i_max_steps;
	patasDerGato1Inc = (KeyFrame[playIndex + 1].patasDerGato1 - KeyFrame[playIndex].patasDerGato1) / i_max_steps;
	patasIzqGato1Inc = (KeyFrame[playIndex + 1].patasIzqGato1 - KeyFrame[playIndex].patasIzqGato1) / i_max_steps;
	cabezaGato1Inc = (KeyFrame[playIndex + 1].cabezaGato1 - KeyFrame[playIndex].cabezaGato1) / i_max_steps;
	giroGato1Inc = (KeyFrame[playIndex + 1].giroGato1 - KeyFrame[playIndex].giroGato1) / i_max_steps;

	posXGato2Inc = (KeyFrame1[playIndex + 1].posXGato2 - KeyFrame1[playIndex].posXGato2) / i_max_steps;
	posYGato2Inc = (KeyFrame1[playIndex + 1].posYGato2 - KeyFrame1[playIndex].posYGato2) / i_max_steps;
	posZGato2Inc = (KeyFrame1[playIndex + 1].posZGato2 - KeyFrame1[playIndex].posZGato2) / i_max_steps;
	patasDerGato2Inc = (KeyFrame1[playIndex + 1].patasDerGato2 - KeyFrame1[playIndex].patasDerGato2) / i_max_steps;
	patasIzqGato2Inc = (KeyFrame1[playIndex + 1].patasIzqGato2 - KeyFrame1[playIndex].patasIzqGato2) / i_max_steps;
	cabezaGato2Inc = (KeyFrame1[playIndex + 1].cabezaGato2 - KeyFrame1[playIndex].cabezaGato2) / i_max_steps;
	giroGato2Inc = (KeyFrame1[playIndex + 1].giroGato2 - KeyFrame1[playIndex].giroGato2) / i_max_steps;

	posXcuboneInc = (KeyFrame3[playIndex + 1].posXcubone - KeyFrame3[playIndex].posXcubone) / i_max_steps;
	posYcuboneInc = (KeyFrame3[playIndex + 1].posYcubone - KeyFrame3[playIndex].posYcubone) / i_max_steps;
	posZcuboneInc = (KeyFrame3[playIndex + 1].posZcubone - KeyFrame3[playIndex].posZcubone) / i_max_steps;
	piernaDercuboneInc = (KeyFrame3[playIndex + 1].piernaDercubone - KeyFrame3[playIndex].piernaDercubone) / i_max_steps;
	piernaIzqcuboneInc = (KeyFrame3[playIndex + 1].piernaIzqcubone - KeyFrame3[playIndex].piernaIzqcubone) / i_max_steps;
	brazoDercuboneInc = (KeyFrame3[playIndex + 1].brazoDercubone - KeyFrame3[playIndex].brazoDercubone) / i_max_steps;
	brazoIzqcuboneInc = (KeyFrame3[playIndex + 1].brazoIzqcubone - KeyFrame3[playIndex].brazoIzqcubone) / i_max_steps;
	cabezacuboneInc = (KeyFrame3[playIndex + 1].cabezacubone - KeyFrame3[playIndex].cabezacubone) / i_max_steps;
	girocuboneInc = (KeyFrame3[playIndex + 1].girocubone - KeyFrame3[playIndex].girocubone) / i_max_steps;
	huesoInc = (KeyFrame3[playIndex + 1].hueso - KeyFrame3[playIndex].hueso) / i_max_steps;

}



unsigned int generateTextures(const char* filename, bool alfa)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void LoadTextures()
{

	
}

void myData()
{	
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void myData2()
{
	GLfloat skyboxVertices[] = {
		// Positions
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);

	glBindVertexArray(skyboxVAO);

	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

	// SkyBox
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);

}


void animate(void)
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			posX += incX;
			posY += incY;
			posZ += incZ;
			rotRodIzq += rotInc;
			giroMonito += giroMonitoInc;
			movBrazo += movBrazoInc;
			movCabeza += movCabezaInc;
			movOtraPierna += movOtraPiernaInc;
			movOtroBrazo += movOtroBrazoInc;
		
			posXPerro += posXPerroInc;
			posYPerro += posYPerroInc;
			posZPerro += posZPerroInc;
			patasDerPerro = patasIzqPerroInc;
			patasIzqPerro = patasIzqPerroInc;
			cabezaPerro = cabezaPerroInc;
			giroPerro += giroPerroInc;

			posXGato1 += posXGato1Inc;
			posYGato1 += posYGato1Inc;
			posZGato1 += posZGato1Inc;
			patasDerGato1 = patasIzqGato1Inc;
			patasIzqGato1 = patasIzqGato1Inc;
			cabezaGato1 = cabezaGato1Inc;
			giroGato1 += giroGato1Inc;

			posXGato2 += posXGato2Inc;
			posYGato2 += posYGato2Inc;
			posZGato2 += posZGato2Inc;
			patasDerGato2 = patasIzqGato2Inc;
			patasIzqGato2 = patasIzqGato2Inc;
			cabezaGato2 = cabezaGato2Inc;
			giroGato1 += giroGato1Inc;

			posXcubone += posXcuboneInc;
			posYcubone += posYcuboneInc;
			posZcubone += posZcuboneInc;
			piernaDercubone = piernaIzqcuboneInc;
			piernaIzqcubone = piernaIzqcuboneInc;
			brazoDercubone = brazoIzqcuboneInc;
			brazoIzqcubone = brazoIzqcuboneInc;
			cabezacubone = cabezacuboneInc;
			girocubone += girocuboneInc;
			hueso += huesoInc;

			i_curr_steps++;
		}
		if (animacion)
		{
			if (recorrido1)
			{
				movAuto_z -= 10.0f;
				orienta = 0.0f;
				if (movAuto_z < -500.0f)		//2750.0f
				{
					recorrido1 = false;
					recorrido2 = true;
				}
			}
			if (recorrido2)
			{
				movAuto_x -= 5.0f;
				orienta = 90.0f;
				if (movAuto_x < 950.0f)     //3000.0f
				{
					recorrido2 = false;
					recorrido3 = true;
				}
			}
			if (recorrido3)
			{
				movAuto_z += 10.0f;
				orienta = 180.0f;
				if (movAuto_z > 1200.0f)		//2500.0f
				{
					recorrido3 = false;
					recorrido4 = true;
				}
			}
			if (recorrido4)
			{
				movAuto_x += 5.0f;
				orienta = -90.0f;
				if (movAuto_x > 1200.0f)		//3100.0f
				{
					recorrido4 = false;
					recorrido1 = true;
				}
			}

		}

	}
	
}

void display(	Shader shader, Shader skyboxShader, GLuint skybox, 
				Model casa3, Model casa4, Model casa5, Model casa2,
				Model mono, Model taxi, Model casa1, Model piso, 
				Model arboles, Model cesped, Model casa6, Model casa7,
				Model casa8, Model fuente, Model Chopper, Model casa9,
				Model casa10, Model oxxo, Model casa11, Model entrada,
				Model gato1, Model arbol2, Model gato2, Model perro,
				Model basura, Model lampara, Model cruce, Model ninio, 
				Model barda, Model finn, Model cabgato1, Model pdergato1, 
				Model pizqgato1, Model Helice,
				Model brazoDer, Model brazoIzq, Model piernaDer, Model piernaIzq, 
				Model cabeza, Model torso, Model huesoModel)

{
	shader.use();

	//Setup Advanced Lights
	shader.setVec3("viewPos", camera.Position);
	shader.setVec3("dirLight.direction", lightDirection);
	shader.setVec3("dirLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("dirLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setVec3("dirLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));

	shader.setVec3("pointLight[0].position", lightPosition);
	shader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[0].diffuse", glm::vec3(0.3f, 0.3f, 0.3f));
	shader.setVec3("pointLight[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader.setFloat("pointLight[0].constant", 1.0f);
	shader.setFloat("pointLight[0].linear", 0.0009f);
	shader.setFloat("pointLight[0].quadratic", 0.00032f);

	shader.setVec3("pointLight[1].position", glm::vec3(0.0, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
	shader.setVec3("pointLight[1].specular", glm::vec3(1.0f, 0.0f, 1.0f));
	shader.setFloat("pointLight[1].constant", 1.0f);
	shader.setFloat("pointLight[1].linear", 0.09f);
	shader.setFloat("pointLight[1].quadratic", 0.032f);

	shader.setFloat("material_shininess", 32.0f);

	// create transformations and Projection
	glm::mat4 tmp = glm::mat4(1.0f);
	glm::mat4 modelAux = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 5000.0f);
	view = camera.GetViewMatrix();

	// pass them to the shaders
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	shader.setMat4("projection", projection);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.01f, 0.0f));
	model = glm::scale(model, glm::vec3(0.8f, 1.0f, 0.6f));
	shader.setMat4("model", model);
	piso.Draw(shader);

	//Personaje
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1100.0f, 3.0f, 1200.0f));
	model = glm::translate(model, glm::vec3(posXcubone, posYcubone, posZcubone));
	model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
	tmp = model = glm::rotate(model, glm::radians(girocubone), glm::vec3(0.0f, 1.0f, 0.0));
	shader.setMat4("model", model);
	torso.Draw(shader);

	//Pierna Der
	model = glm::translate(tmp, glm::vec3(-140.0f, 200.0f, -0.1f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(-piernaDercubone), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	piernaDer.Draw(shader);


	//Pierna Izq
	model = glm::translate(tmp, glm::vec3(140.0f, 200.0f, -0.1f));
	model = glm::rotate(model, glm::radians(-piernaIzqcubone), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	piernaIzq.Draw(shader);


	//Brazo derecho
	modelAux = model = glm::translate(tmp, glm::vec3(-50.0f, 200.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-100.0f, 250.0f, 0));
	model = glm::rotate(model, glm::radians(brazoDercubone), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.setMat4("model", model);
	brazoDer.Draw(shader);

	//Hueso
	model = glm::translate(modelAux, glm::vec3(-50.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(-100.0f, 250.0f, 0));
	model = glm::rotate(model, glm::radians(hueso), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.setMat4("model", model);
	brazoDer.Draw(shader);

	//Brazo izquierdo
	model = glm::translate(tmp, glm::vec3(50.0f, 200.0f, 0.0f));
	model = glm::translate(model, glm::vec3(100.0f, 250.0f, 0));
	model = glm::rotate(model, glm::radians(brazoIzqcubone), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.setMat4("model", model);
	brazoIzq.Draw(shader);

	//Cabeza
	model = glm::translate(tmp, glm::vec3(0.0f, 550.0f, 0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::translate(model, glm::vec3(0.0f, 2.5f, 0));
	model = glm::rotate(model, glm::radians(cabezacubone), glm::vec3(1.0f, 0.0f, 0.0));
	shader.setMat4("model", model);
	cabeza.Draw(shader);



	//CASA chida
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1642.0f, 0.0f, 250.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(40.0f, 55.0f, 44.0f));
	shader.setMat4("model", model);
	casa1.Draw(shader);
	
	//Casa 2
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1600.0f, 0.0f, 1000.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(40.0f, 40.0f, 40.0f));
	shader.setMat4("model", model);
	casa2.Draw(shader);

	//Casa 3
	model = glm::translate(glm::mat4(1.0f), glm::vec3(850.0f, 0.0f, 1100.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(70.0f, 80.0f, 70.0f));
	shader.setMat4("model", model);
	casa3.Draw(shader);

	//Casa 4
	model = glm::translate(glm::mat4(1.0f), glm::vec3(900.0f, 0.0f, 800.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(40.0f, 40.0f, 40.0f));
	shader.setMat4("model", model);
	casa4.Draw(shader);

	//Casa 5
	model = glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 0.0f, 1100.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(70.0f, 95.0f, 60.0f));
	shader.setMat4("model", model);
	casa5.Draw(shader);

	////Mono
	//model = glm::translate(glm::mat4(1.0f), glm::vec3(1100.0f, 3.0f, 1200.0f));
	//model = glm::rotate(model, glm::radians(movCabeza), glm::vec3(0.0f, 1.0f, 0.0));
	//model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
	//shader.setMat4("model", model);
	//mono.Draw(shader);

	//Taxi
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1200.0f, 1.0f, 1200.0f ));
	model = glm::translate(model, glm::vec3(posXGato2, posYGato2, posZGato2));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	tmp = model = glm::rotate(model, glm::radians(giroGato1), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	shader.setMat4("model", model);
	taxi.Draw(shader);

	//Arboles
	model = glm::translate(glm::mat4(1.0f), glm::vec3(350.0f, 1.0f, -800.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.45f, 0.7f, 0.45f));
	shader.setMat4("model", model);
	arboles.Draw(shader);

	//cesped
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 3.0f, -200.0f));
	model = glm::scale(model, glm::vec3(0.25f, 1.0f, 0.35f));
	shader.setMat4("model", model);
	cesped.Draw(shader);

	//Casa 6
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1000.0f, 1.0f, -1200.0f));
	model = glm::scale(model, glm::vec3(50.0f, 30.0f, 30.0f));
	shader.setMat4("model", model);
	casa6.Draw(shader);

	//Casa 7
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-300.0f, 0.0f, 1100.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
	shader.setMat4("model", model);
	casa7.Draw(shader);

	//Casa 8
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1200.0f, 0.0f, 1100.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
	shader.setMat4("model", model);
	casa8.Draw(shader);

	//Chopper
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1200.0f, 800.0f, 1100.0f));
	model = glm::translate(model, glm::vec3(posXGato1, posYGato1, posZGato1));
	model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
	tmp = model = glm::rotate(model, glm::radians(giroGato1), glm::vec3(0.0f, 1.0f, 0.0));
	shader.setMat4("model", model);
	Chopper.Draw(shader);
	model = glm::rotate(tmp, glm::radians(-89.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(helices), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.setMat4("model", model);
	Helice.Draw(shader);
	helices += 100.0f;


	//fuente
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 10.0f, -500.0f));
	model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
	shader.setMat4("model", model);
	fuente.Draw(shader);

	//Casa 9
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1550.0f, 1.0f, 200.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
	shader.setMat4("model", model);
	casa9.Draw(shader);

	//casa10
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1600.0f, 1.0f, -300.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.3f, 0.5f, 0.3f));
	shader.setMat4("model", model);
	casa10.Draw(shader);

	//Oxxo
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1400.0f, 1.0f, -600.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(5.5f, 4.0f, 5.0f));
	shader.setMat4("model", model);
	oxxo.Draw(shader);

	//casa11
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1550.0f, 1.0f, -1000.0f));
	model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(30.0f, 30.0f, 30.0f));
	shader.setMat4("model", model);
	casa11.Draw(shader);

	//Entrada
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1150.0f, 1.0f, 1200.0f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	shader.setMat4("model", model);
	entrada.Draw(shader);

	//Arbol
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 1.0f, 150.0f));
	model = glm::scale(model, glm::vec3(0.025f, 0.035f, 0.025f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	//Arbol2
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-400.0f, 1.0f, 150.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.025f, 0.035f, 0.025f));
	shader.setMat4("model", model);
	arbol2.Draw(shader);

	//gato1
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-300.0f, 1.0f, -100.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	shader.setMat4("model", model);
	gato1.Draw(shader);
	

	//gato2
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-300.0f, 1.0f, -200.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	shader.setMat4("model", model);
	gato2.Draw(shader);

	//perro

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-300.0f, 1.0f, -500.0f));
	model = glm::translate(model, glm::vec3(posXPerro, posYPerro, posZPerro));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	tmp = model = glm::rotate(model, glm::radians(girocubone), glm::vec3(0.0f, 1.0f, 0.0));
	tmp = model = glm::rotate(model, glm::radians(giroPerro), glm::vec3(0.0f, 1.0f, 0.0));
	shader.setMat4("model", model);
	perro.Draw(shader);

	//PataDer

	model = glm::translate(tmp, glm::vec3(0.0f, 16.0f, -6.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(patasDerPerro), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	pdergato1.Draw(shader);

	//PataIzq

	model = glm::translate(tmp, glm::vec3(0.0f,16.0f, 14.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(patasIzqPerro), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.setMat4("model", model);
	pizqgato1.Draw(shader);
	

	//cabeza Perro

	model = glm::translate(tmp, glm::vec3(0.0f, 24.0f, -8.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(cabezaPerro), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	cabgato1.Draw(shader);

	//Basura
	model = glm::translate(glm::mat4(1.0f), glm::vec3(750.0f, 1.0f, 85.0f));
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	shader.setMat4("model", model);
	basura.Draw(shader);

	////lampara
	//model = glm::translate(glm::mat4(1.0f), glm::vec3(750.0f, 1.0f, -150.0f));
	//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
	//shader.setMat4("model", model);
	//lampara.Draw(shader);

	//Ninio
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1250.0f, 1.0f, -600.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
	shader.setMat4("model", model);
	ninio.Draw(shader);

	//Finn
	model = glm::translate(glm::mat4(1.0f), glm::vec3(750.0f, 1.0f, -50.0f));
	//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0));
	tmp = model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	shader.setMat4("model", model);
	finn.Draw(shader);
	////brazoDerFinn
	//model = glm::rotate(tmp, glm::radians(-89.0f), glm::vec3(1.0f, 0.0f, 0.0));
	//model = glm::rotate(model, glm::radians(movOtraPierna), glm::vec3(0.0f, 1.0f, 0.0));
	//shader.setMat4("model", model);
	//brazoDerFinn.Draw(shader);

	 

	//-------------------------------------------------------------------

	//Barda
	model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 3.0f, 1450.0f));
	//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.005f, 1.0f, 0.0025));
	model = glm::scale(model, glm::vec3(70.0f, 25.0f, 1.0f));
	shader.setMat4("model", model);
	barda.Draw(shader);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1020.0f, 3.0f, 1450.0f));
	//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.005f, 1.0f, 0.0025));
	model = glm::scale(model, glm::vec3(100.0f, 25.0f, 1.0f));
	shader.setMat4("model", model);
	barda.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1980.0f, 3.0f, 650.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(100.0f, 25.0f, 1.0f));
	shader.setMat4("model", model);
	barda.Draw(shader);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1980.0f, 3.0f, -650.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(100.0f, 25.0f, 1.0f));
	shader.setMat4("model", model);
	barda.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-900.0f, 3.0f, -1480.0f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.005f, 1.0f, 0.0025));
	model = glm::scale(model, glm::vec3(132.0f, 25.0f, 1.0f));
	shader.setMat4("model", model);
	barda.Draw(shader);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1000.0f, 3.0f, -1480.0f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.005f, 1.0f, 0.0025));
	model = glm::scale(model, glm::vec3(120.0f, 25.0f, 1.0f));
	shader.setMat4("model", model);
	barda.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(1980.0f, 3.0f, 660.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(100.0f, 25.0f, 1.0f));
	shader.setMat4("model", model);
	barda.Draw(shader);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1980.0f, 3.0f, -700.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(100.0f, 25.0f, 1.0f));
	shader.setMat4("model", model);
	barda.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(1750.0f, 3.0f, 1450.0f));
	//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.005f, 1.0f, 0.0025));
	model = glm::scale(model, glm::vec3(30.0f, 25.0f, 1.0f));
	shader.setMat4("model", model);
	barda.Draw(shader);
	//-------------------------------------------------------------------

	//Cruce
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1160.0f, 3.0f, 1100.0f));
	model = glm::scale(model, glm::vec3(0.098f, 1.0f, 0.05));
	shader.setMat4("model", model);
	cruce.Draw(shader);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(1160.0f, 3.0f, 450.0f));
	model = glm::scale(model, glm::vec3(0.1f, 1.0f, 0.05));
	shader.setMat4("model", model);
	cruce.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(800.0f, 3.0f, -550.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.25f, 1.0f, 0.05));
	shader.setMat4("model", model);
	cruce.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1250.0f, 4.0f, -1000.0f));
	model = glm::scale(model, glm::vec3(0.1f, 1.0f, 0.05));
	shader.setMat4("model", model);
	cruce.Draw(shader);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-1250.0f, 4.0f, 450.0f));
	model = glm::scale(model, glm::vec3(0.1f, 1.0f, 0.05));
	shader.setMat4("model", model);
	cruce.Draw(shader);
	//-------------------------------------------------------------------
	// Draw skybox as last
	glDepthFunc(GL_LEQUAL);  // Change depth function so depth test passes when values are equal to depth buffer's content
	skyboxShader.use();
	view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix

	skyboxShader.setMat4("view", view);
	skyboxShader.setMat4("projection", projection);

	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // Set depth function back to default
}

int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 10 2020-2", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, my_input);
    glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	LoadTextures();
	myData2();
	glEnable(GL_DEPTH_TEST);
	
	//Shaders
	Shader modelShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");

	// Load models
	Model casa1 = ((char *)"Models/Casa1/casa1.obj");
	Model casa2 = ((char *)"Models/Casa2/Casa2.obj");
	Model casa3 = ((char *)"Models/Casa3/houseF.obj");
	Model casa4 = ((char *)"Models/Casa4/Casita4.obj");
	Model casa5 = ((char *)"Models/Casa5/Casa5.obj");
	Model mono = ((char *)"Models/Mono/Mono.obj");
	Model taxi = ((char *)"Models/Taxi/Taxi.obj");
	Model arboles = ((char*)"Models/Bosque/Bosque.obj");
	Model cesped = ((char*)"Models/Cesped/Cesped.obj");
	Model casa6 = ((char*)"Models/Casa6/Casa6.obj");
	Model casa7 = ((char*)"Models/Casa7/Casa7.obj");
	Model casa8 = ((char*)"Models/Casa7/Casa8.obj");
	Model Chopper = ((char*)"Models/Chopper/chopper.obj");
	Model Helice = ((char*)"Models/Chopper/Helice.fbx");

	Model fuente = ((char*)"Models/Fuente/Fountain.obj");
	Model casa9 = ((char*)"Models/Casa8/Casa9.obj");
	Model pisoModel = ((char *)"Models/Piso/Piso.obj");
	Model casa10 = ((char*)"Models/Casa10/Casa10.obj");
	Model oxxo = ((char*)"Models/Oxxo/Oxxo.obj");
	Model casa11 = ((char*)"Models/Casa7/Casa11.obj");
	Model entrada = ((char*)"Models/Entrada/Entrada.obj");
	Model arbol2 = ((char*)"Models/Bosque/Arbol2/Arbol2.obj");
	Model basura = ((char*)"Models/Basura/Basura.obj");
	Model lampara = ((char*)"Models/Lampara/Lampara.obj");
	Model cruce = ((char*)"Models/Cruce/Cruce.obj");
	Model ninio = ((char*)"Models/Personas/Ninio/Ninio.obj");
	Model finn = ((char*)"Models/Personas/Finn/Finn.obj");
	//Model brazoDerFinn = ((char*)"Models/Finn/BrazoDerecho.fbx");
	

	Model barda = ((char*)"Models/Barda/fance.obj");

	Model gato1 = ((char*)"Models/Perro/Gato1.obj");

	Model perro = ((char*)"Models/Perro/torso.fbx");
	Model cabgato1 = ((char*)"Models/perro/cabeza.fbx");
	Model pdergato1 = ((char*)"Models/Perro/patasDelanteras.fbx");
	Model pizqgato1 = ((char*)"Models/Perro/patasTraseras.fbx");

	Model gato2 = ((char*)"Models/Animales/Gato2/Gato2.obj");

	Model cabeza = ((char*)"Models/cuboneFBX/cabeza.fbx");
	Model torso = ((char*)"Models/cuboneFBX/torso.obj");
	Model hueso = ((char*)"Models/cuboneFBX/hueso.fbx");
	Model piernaDer = ((char*)"Models/cuboneFBX/piernaDer.fbx");
	Model piernaIzq = ((char*)"Models/cuboneFBX/piernaIzq.fbx");
	Model brazoDer = ((char*)"Models/cuboneFBX/brazoDer.fbx");
	Model brazoIzq = ((char*)"Models/cuboneFBX/brazoIzq.fbx");

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMESheli; i++)
	{
		/*KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].giroMonito = 0;

		KeyFrame2[i].posXPerro = 0;
		KeyFrame2[i].posYPerro = 0;
		KeyFrame2[i].posZPerro = 0;
		KeyFrame2[i].patasDerPerro = 0;
		KeyFrame2[i].patasIzqPerro = 0;
		KeyFrame2[i].cabezaPerro = 0;
		KeyFrame2[i].giroPerro = 0;*/

		KeyFrame[i].posXGato1 = 0;
		KeyFrame[i].posYGato1 = 0;
		KeyFrame[i].posZGato1 = 0;
		KeyFrame[i].patasDerGato1 = 0;
		KeyFrame[i].patasIzqGato1 = 0;
		KeyFrame[i].cabezaGato1 = 0;
		KeyFrame[i].giroGato1 = 0;

		/*KeyFrame1[i].posXGato2 = 0;
		KeyFrame1[i].posYGato2 = 0;
		KeyFrame1[i].posZGato2 = 0;
		KeyFrame1[i].patasDerGato2 = 0;
		KeyFrame1[i].patasIzqGato2 = 0;
		KeyFrame1[i].cabezaGato2 = 0;
		KeyFrame1[i].giroGato2 = 0;*/

	}

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMEStaxi; i++)
	{
		/*KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].giroMonito = 0;

		KeyFrame2[i].posXPerro = 0;
		KeyFrame2[i].posYPerro = 0;
		KeyFrame2[i].posZPerro = 0;
		KeyFrame2[i].patasDerPerro = 0;
		KeyFrame2[i].patasIzqPerro = 0;
		KeyFrame2[i].cabezaPerro = 0;
		KeyFrame2[i].giroPerro = 0;

		KeyFrame[i].posXGato1 = 0;
		KeyFrame[i].posYGato1 = 0;
		KeyFrame[i].posZGato1 = 0;
		KeyFrame[i].patasDerGato1 = 0;
		KeyFrame[i].patasIzqGato1 = 0;
		KeyFrame[i].cabezaGato1 = 0;
		KeyFrame[i].giroGato1 = 0;*/

		KeyFrame1[i].posXGato2 = 0;
		KeyFrame1[i].posYGato2 = 0;
		KeyFrame1[i].posZGato2 = 0;
		KeyFrame1[i].patasDerGato2 = 0;
		KeyFrame1[i].patasIzqGato2 = 0;
		KeyFrame1[i].cabezaGato2 = 0;
		KeyFrame1[i].giroGato2 = 0;

	}

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMESperro; i++)
	{
		/*KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].giroMonito = 0;*/

		KeyFrame2[i].posXPerro = 0;
		KeyFrame2[i].posYPerro = 0;
		KeyFrame2[i].posZPerro = 0;
		KeyFrame2[i].patasDerPerro = 0;
		KeyFrame2[i].patasIzqPerro = 0;
		KeyFrame2[i].cabezaPerro = 0;
		KeyFrame2[i].giroPerro = 0;

		/*KeyFrame[i].posXGato1 = 0;
		KeyFrame[i].posYGato1 = 0;
		KeyFrame[i].posZGato1 = 0;
		KeyFrame[i].patasDerGato1 = 0;
		KeyFrame[i].patasIzqGato1 = 0;
		KeyFrame[i].cabezaGato1 = 0;
		KeyFrame[i].giroGato1 = 0;

		KeyFrame1[i].posXGato2 = 0;
		KeyFrame1[i].posYGato2 = 0;
		KeyFrame1[i].posZGato2 = 0;
		KeyFrame1[i].patasDerGato2 = 0;
		KeyFrame1[i].patasIzqGato2 = 0;
		KeyFrame1[i].cabezaGato2 = 0;
		KeyFrame1[i].giroGato2 = 0;*/

	}

	//Inicialización de KeyFrames
	for (int i = 0; i < MAX_FRAMEScubone; i++)
	{
		/*KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].giroMonito = 0;*/

		KeyFrame3[i].posXcubone = 0;
		KeyFrame3[i].posYcubone = 0;
		KeyFrame3[i].posZcubone = 0;
		KeyFrame3[i].piernaDercubone = 0;
		KeyFrame3[i].hueso = 0;
		KeyFrame3[i].piernaIzqcubone = 0;
		KeyFrame3[i].brazoDercubone = 0;
		KeyFrame3[i].brazoIzqcubone = 0;
		KeyFrame3[i].cabezacubone = 0;
		KeyFrame3[i].girocubone = 0;

		/*KeyFrame[i].posXGato1 = 0;
		KeyFrame[i].posYGato1 = 0;
		KeyFrame[i].posZGato1 = 0;
		KeyFrame[i].patasDerGato1 = 0;
		KeyFrame[i].patasIzqGato1 = 0;
		KeyFrame[i].cabezaGato1 = 0;
		KeyFrame[i].giroGato1 = 0;

		KeyFrame1[i].posXGato2 = 0;
		KeyFrame1[i].posYGato2 = 0;
		KeyFrame1[i].posZGato2 = 0;
		KeyFrame1[i].patasDerGato2 = 0;
		KeyFrame1[i].patasIzqGato2 = 0;
		KeyFrame1[i].cabezaGato2 = 0;
		KeyFrame1[i].giroGato2 = 0;*/

	}




	// Load textures
	vector<const GLchar*> faces;
	faces.push_back("SkyBox/right.tga");
	faces.push_back("SkyBox/left.tga");
	faces.push_back("SkyBox/top.tga");
	faces.push_back("SkyBox/bottom.tga");
	faces.push_back("SkyBox/back.tga");
	faces.push_back("SkyBox/front.tga");

	GLuint cubemapTexture = TextureLoading::LoadCubemap(faces);

	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	// render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        // input
        // -----
        //my_input(window);
		animate();
		
        // render
        // Background color
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//display(modelShader, ourModel, llantasModel);
		display(modelShader, SkyBoxshader, cubemapTexture,
			casa3, casa4,
			casa5, casa2, mono, taxi,
			casa1, pisoModel, arboles, cesped, casa6, casa7,
			casa8, fuente, Chopper, casa9, casa10, oxxo,
			casa11, entrada, gato1, arbol2, gato2, perro, basura,
			lampara, cruce, ninio, barda, finn, cabgato1, pdergato1, pizqgato1,
			Helice, brazoDer, brazoIzq, piernaDer, piernaIzq, cabeza, torso, hueso);
		
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//To Configure Model
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		posYPerro += 5.0;
		posYGato1 += 5.0;
		posYGato2 += 5.0;
		posYcubone += 5.0;
	}
		
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) 
	{
			posYPerro -= 5.0;
			posYGato1 -= 5.0;
			posYGato2 -= 5.0;
			posYcubone -= 5.0;
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		posZPerro -= 5.0;
		posZGato1 -= 5.0;
		posZGato2 -= 5.0;
		posZcubone -= 5.0;
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		posZPerro += 5.0;
		posZGato1 += 5.0;
		posZGato2 += 5.0;
		posZcubone += 5.0;
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		posXPerro -= 5.0;
		posXGato1 -= 5.0;
		posXGato2 -= 5.0;
		posXcubone -= 5.0;
	}
		
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		posXPerro += 5.0;
		posXcubone += 20;
		posXGato1 += 5.0;
		posXGato2 += 5.0;
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		giroPerro -= 5.0;
		girocubone -= 20.0;
		giroGato1 -= 5.0;
		giroGato2 -= 5.0;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		giroPerro += 5.0;
		girocubone += 20.0;
		giroGato1 += 5.0;
		giroGato2 += 5.0;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		patasDerPerro -= 5.0;
		piernaDercubone -= 400;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		patasDerPerro += 5.0;
		piernaDercubone += 400;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		patasIzqPerro -= 5.0;
		piernaIzqcubone -= 400;
	}

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		patasIzqPerro += 5.0;
		piernaIzqcubone += 400;
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		cabezaPerro -= 5.0;
		cabezacubone -= 400;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		cabezaPerro += 5.0;
		cabezacubone += 400;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		piernaDercubone += 400;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		piernaDercubone -= 400;
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		piernaIzqcubone -= 400;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		piernaIzqcubone += 400;
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		piernaIzqcubone += 400;
	}

	
	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		PlaySound(TEXT("Venus-Bananarama.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	if (glfwGetKey(window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
		PlaySound(NULL, 0, 0);
	
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		saveFrame();

	
	//To play KeyFrame animation 
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		
		if (play == false && (FrameIndex > 1))
		{
			resetElements();
			//First Interpolation
			
			interpolation();
			
			play = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			play = false;
		}
	}

	//To Save a KeyFrame
	//DATOS DEL PERRO
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		printf("PosXPerro %f   PosYPerro %f   PosZPerro %f   GiraPerro %f  patasDer %f  patasIzq %f  cabeza %f \n", 
			posXPerro, posYPerro, posZPerro, giroPerro, patasDerPerro, patasIzqPerro, cabezaPerro);
	}
	//DATOS DEL HELICOPTERO
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		printf("PosXGato1 %f   PosYGato1 %f   PosZGato1 %f   GiraMonito %f \n",
			posXGato1, posYGato1, posZGato1, giroGato1);
	}
	//DATOS DEL TAXI
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		printf("PosXGato1 %f   PosYGato1 %f   PosZGato1 %f   GiraMonito %f \n",
			posXGato1, posYGato1, posZGato1, giroGato1);
	}
	//DATOS DEL CUBONE
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		printf("PosXcubone %f   PosYcubone %f   PosZcubone %f   Giracubone %f PiernaDer %f  piernaIzq %f  brazoDer %f brazoIzq %f  cabeza %f   hueso %f \n",
			posXcubone, posYcubone, posZcubone, girocubone, piernaDercubone,
			piernaIzqcubone, brazoDercubone, brazoIzqcubone, cabezacubone, hueso);
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void resize(GLFWwindow* window, int width, int height)
{
    // Set the Viewport to the size of the created window
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}