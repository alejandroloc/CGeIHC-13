//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader

static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* AzulShader = "shaders/azul.frag";
static const char* CafeShader = "shaders/cafe.frag";
static const char* RojoShaderColor = "shaders/rojo.frag";
static const char* VerdeShaderColor = "shaders/verde.frag";
static const char* VerdeOShaderColor = "shaders/verdeosc.frag";
float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		/*1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,*/

	};
	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, 18);
	meshColorList.push_back(letras);

	GLfloat vertices_letraA[] = {
		// X        Y        Z         R     G     B
		// izquierda
		-0.90f, -0.65f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.85f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.80f, -0.65f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.75f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.85f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.80f, -0.65f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.75f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.85f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.80f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.75f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.70f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.80f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.75f, -0.35f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.70f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.80f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.75f, -0.35f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.70f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.65f, -0.35f, 0.0f,    1.0f, 0.0f, 0.0f,

		// parte intermedia
		-0.75f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.70f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.65f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.60f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.70f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.65f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.60f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.55f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.65f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,

		// parte derecha
		-0.60f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.50f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.55f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.60f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.50f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.55f, -0.35f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.60f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.65f, -0.35f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.55f, -0.35f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.45f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.50f, -0.45f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.55f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.45f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.50f, -0.65f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.55f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,

		-0.45f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.50f, -0.65f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.40f, -0.65f, 0.0f,    1.0f, 0.0f, 0.0f,

		// parte arriba
		-0.75f, -0.35f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.55f, -0.35f, 0.0f,    1.0f, 0.0f, 0.0f,
		-0.65f, -0.15f, 0.0f,    1.0f, 0.0f, 0.0f,
	};

	MeshColor* letraA = new MeshColor();
	letraA->CreateMeshColor(vertices_letraA, 288);
	meshColorList.push_back(letraA);

	GLfloat vertices_letraS[] = {
		//       Y        Z         R     G     B
					// parte superior
		-0.20f,  0.15f, 0.0f,    0.0f, 1.0f, 1.0f,
		0.20f,  0.15f, 0.0f,    0.0f, 1.0f, 1.0f,
		-0.20f,  0.25f, 0.0f,    0.0f, 1.0f, 1.0f,

		0.20f,  0.15f, 0.0f,    0.0f, 1.0f, 1.0f,
		0.20f,  0.25f, 0.0f,    0.0f, 1.0f, 1.0f,
		-0.20f,  0.25f, 0.0f,    0.0f, 1.0f, 1.0f,

		// parte izquierda arriba 
		-0.20f,  0.05f, 0.0f,    0.0f, 1.0f, 1.0f,
		-0.10f,  0.05f, 0.0f,    0.0f, 1.0f, 1.0f,
		-0.20f,  0.15f, 0.0f,    0.0f, 1.0f, 1.0f,

		-0.10f,  0.05f, 0.0f,    0.0f, 1.0f, 1.0f,
		-0.10f,  0.15f, 0.0f,    0.0f, 1.0f, 1.0f,
		-0.20f,  0.15f, 0.0f,    0.0f, 1.0f, 1.0f,

		// parte central
		-0.20f, -0.05f, 0.0f,    0.0f, 1.0f, 1.0f,
		0.20f, -0.05f, 0.0f,    0.0f, 1.0f, 1.0f,
		-0.20f,  0.05f, 0.0f,    0.0f, 1.0f, 1.0f,

		0.20f, -0.05f, 0.0f,    0.0f, 1.0f, 1.0f,
		0.20f,  0.05f, 0.0f,    0.0f, 1.0f, 1.0f,
		-0.20f,  0.05f, 0.0f,    0.0f, 1.0f, 1.0f,

		// parte derecha abajo
		0.10f, -0.15f, 0.0f,    0.0f, 1.0f, 1.0f,
		0.20f, -0.15f, 0.0f,    0.0f, 1.0f, 1.0f,
		0.10f, -0.05f, 0.0f,    0.0f, 1.0f, 1.0f,

		0.20f, -0.15f, 0.0f,    0.0f, 1.0f, 1.0f,
		0.20f, -0.05f, 0.0f,    0.0f, 1.0f, 1.0f,
		0.10f, -0.05f, 0.0f,    0.0f, 1.0f, 1.0f,

		// parte inferior
		-0.20f, -0.25f, 0.0f,    0.0f, 1.0f, 1.0f,
		0.20f, -0.25f, 0.0f,    0.0f, 1.0f, 1.0f,
		-0.20f, -0.15f, 0.0f,    0.0f, 1.0f, 1.0f,

		0.20f, -0.25f, 0.0f,    0.0f, 1.0f, 1.0f,
		0.20f, -0.15f, 0.0f,    0.0f, 1.0f, 1.0f,
		-0.20f, -0.15f, 0.0f,    0.0f, 1.0f, 1.0f
	};

	MeshColor* letraS = new MeshColor();
	letraS->CreateMeshColor(vertices_letraS, 288);
	meshColorList.push_back(letraS);

	GLfloat vertices_letraJ[] = {
		// X        Y        Z         R     G     B
		// arriba 
		0.40f,  0.55f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.80f,  0.55f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.40f,  0.65f, 0.0f,    0.8f, 0.6f, 1.0f,

		0.80f,  0.55f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.80f,  0.65f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.40f,  0.65f, 0.0f,    0.8f, 0.6f, 1.0f,

		// rectangulo derecho
		0.60f,  0.25f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.70f,  0.25f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.60f,  0.55f, 0.0f,    0.8f, 0.6f, 1.0f,

		0.70f,  0.25f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.70f,  0.55f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.60f,  0.55f, 0.0f,    0.8f, 0.6f, 1.0f,

		// rectangulo abajo
		0.40f,  0.15f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.70f,  0.15f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.40f,  0.25f, 0.0f,    0.8f, 0.6f, 1.0f,

		0.70f,  0.15f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.70f,  0.25f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.40f,  0.25f, 0.0f,    0.8f, 0.6f, 1.0f,

		// punta inferior izquierda
		0.40f,  0.25f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.50f,  0.25f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.40f,  0.35f, 0.0f,    0.8f, 0.6f, 1.0f,

		0.50f,  0.25f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.50f,  0.35f, 0.0f,    0.8f, 0.6f, 1.0f,
		0.40f,  0.35f, 0.0f,    0.8f, 0.6f, 1.0f
	};

	MeshColor* letraJ = new MeshColor();
	letraJ->CreateMeshColor(vertices_letraJ, 144);
	meshColorList.push_back(letraJ);




	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		
	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);
	//triangulo verde
	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f, 0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);

	// este se usa y se cambia a rojo
	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);

	// Cuadrado verde
	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);
	// Cuadrado café
	GLfloat vertices_cuadradocafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		-0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		-0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,

	};

	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe);
}


void CreateShaders()
{
	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide indice 0
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras indice 1
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	//shader color para la casa APARTIR DEL INDICE 2

	Shader* shaderRojo = new Shader();
	shaderRojo->CreateFromFiles(vShader,RojoShaderColor); 
	shaderList.push_back(*shaderRojo);

	Shader* shaderAzul = new Shader();
	shaderAzul->CreateFromFiles(vShader, AzulShader);
	shaderList.push_back(*shaderAzul);

	Shader* shaderCafe = new Shader();
	shaderCafe->CreateFromFiles(vShader, CafeShader);
	shaderList.push_back(*shaderCafe);

	Shader* shaderVerdeOsc = new Shader();
	shaderVerdeOsc->CreateFromFiles(vShader, VerdeOShaderColor);
	shaderList.push_back(*shaderVerdeOsc);

	Shader* shaderVerde = new Shader();
	shaderVerde->CreateFromFiles(vShader, VerdeShaderColor);
	shaderList.push_back(*shaderVerde);
}


int main()
{
	mainWindow = Window(800, 800);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f,1.0f,1.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		/*
		//PARTE 1 letras de diferentes colores


		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
	
		//Letra A
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshColorList[1]->RenderMeshColor();

		//Letra S
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshColorList[2]->RenderMeshColor();
		//Letra j
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshColorList[3]->RenderMeshColor();

 		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		// CUADRADO ROJO indice 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -0.4f));
		model = glm::scale(model, glm::vec3(1.0f,1.0f, 0.0f)); // Tamaño
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[3]->RenderMeshColor();
		
		//Techo azul indice 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -0.4f));
		model = glm::scale(model, glm::vec3(0.6f, 0.5f, 0.0f)); // Tamaño
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();

		//cuadrado cafe derecha indice 5
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.9f, -0.4f));
		model = glm::scale(model, glm::vec3(0.22f, 0.22f, 0.0f)); // Tamaño
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[5]->RenderMeshColor();

		//cuadrado cafe izquierda indice 5
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.9f, -0.4f));
		model = glm::scale(model, glm::vec3(0.22f, 0.22f, 0.0f)); // Tamaño
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[5]->RenderMeshColor();

		//triangulo verde obscuro izquierda indice 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.58f, -0.3f));
		model = glm::scale(model, glm::vec3(0.22f, 0.22f, 0.0f)); // Tamaño
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();

		//triangulo verde obscuro derecha indice 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.58f, -0.3f));
		model = glm::scale(model, glm::vec3(0.22f, 0.22f, 0.0f)); // Tamaño
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();

		//puerta verde indice 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -0.3f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.0f)); // Tamaño
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColor();

		//ventana verde indice 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, -0.3f, -0.3f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.0f)); // Tamaño
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColor();

		//ventana verde indice 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, -0.3f, -0.3f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.0f)); // Tamaño
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[4]->RenderMeshColor();

		*/
	//Termina la parte 1 



		//Parte 2 practica 2
		// /*
		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		// cubo central casa
		shaderList[2].useShader(); 
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		//Em
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -3.0f));
		model = glm::scale(model, glm::vec3(1.2f, 1.0f, 1.2f)); // Un techo más ancho
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		// Tronco Derecho
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.9f, -3.0f));
		model = glm::scale(model, glm::vec3(0.22f, 0.22f, 0.22f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		// Tronco Izquierdo
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.9f, -3.0f));
		model = glm::scale(model, glm::vec3(0.22f, 0.22f, 0.22f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		// Hojas Derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.58f, -3.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.5f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();
		// Hojas Izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.58f, -3.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.5f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		// Puerta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -2.8f)); // Z en -2.8 para que salga por delante
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		// Ventana Derecha
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, -0.3f, -2.8f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		// Ventana Izquierda
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, -0.3f, -2.8f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// */ descomentar para probar la parte 1

		glUseProgram(0);
		mainWindow.swapBuffers();
	
		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/