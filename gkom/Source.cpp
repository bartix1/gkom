// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
// #include <GL/glfw3.h>
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "shader.hpp"
#include "controls.hpp"
#include "utils.hpp"
#include "nut.h"
#include "wrench.h"
#include "Controller.h"

int main( void )
{
	// GLFW Init
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);  // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window
	window = glfwCreateWindow( 1024, 768, "Tutorial 0 - Keyboard and Mouse", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}

	// GLEW Init
    glfwMakeContextCurrent(window);
	glewExperimental = true; 
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Mouse and keyboard
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// BG color
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Load Shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

	//"MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// textures
	GLuint NutTexture = loadBMP_custom("textures/metal.bmp");
	GLuint SceneTexture = loadBMP_custom("textures/workshop.bmp");
	GLuint WrenchTexture = loadBMP_custom("textures/metal2.bmp");
	GLuint BlockTexture = loadBMP_custom("textures/wood.bmp");
	GLuint ScrewTexture = loadBMP_custom("textures/screw2.bmp");

	//"myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");


	//BLOCK VERTICES
	static GLfloat g_vertex_block[] = {
		-3.0f,-3.0f,3.0f,
		-3.0f,-3.0f,-3.0f,
		-3.0f,-2.0f,3.0f,
		-3.0f,-3.0f,-3.0f,
		-3.0f,-2.0f,-3.0f,
		-3.0f,-2.0f,3.0f,

		-3.0f,-3.0f,-3.0f,
		3.0f,-3.0f,-3.0f,
		-3.0f,-2.0f,-3.0f,
		3.0f,-3.0f,-3.0f,
		3.0f,-2.0f,-3.0f,
		-3.0f,-2.0f,-3.0f,

		3.0f,-3.0f,3.0f,
		3.0f,-3.0f,-3.0f,
		3.0f,-2.0f,3.0f,
		3.0f,-3.0f,-3.0f,
		3.0f,-2.0f,-3.0f,
		3.0f,-2.0f,3.0f,

		-3.0f,-3.0f,3.0f,
		3.0f,-3.0f,3.0f,
		-3.0f,-2.0f,3.0f,
		3.0f,-3.0f,3.0f,
		3.0f,-2.0f,3.0f,
		-3.0f,-2.0f,3.0f,

		-3.0f,-2.0f,3.0f,
		3.0f,-2.0f,3.0f,
		-3.0f,-2.0f,-3.0f,
		3.0f,-2.0f,3.0f,
		3.0f,-2.0f,-3.0f,
		-3.0f,-2.0f,-3.0f,

		-3.0f,-3.0f,3.0f,
		3.0f,-3.0f,3.0f,
		-3.0f,-3.0f,-3.0f,
		3.0f,-3.0f,3.0f,
		3.0f,-3.0f,-3.0f,
		-3.0f,-3.0f,-3.0f,
	};

	static GLfloat g_uv_block[36 * 2];
	for (int i = 0; i < 12; i++)
	{
		g_uv_block[12 * i] = 0.0f;
		g_uv_block[12 * i + 1] = 0.0f;
		g_uv_block[12 * i + 2] = 1.0f;
		g_uv_block[12 * i + 3] = 0.0f;
		g_uv_block[12 * i + 4] = 0.0f;
		g_uv_block[12 * i + 5] = 1.0f;

		g_uv_block[12 * i + 6] = 1.0f;
		g_uv_block[12 * i + 7] = 0.0f;
		g_uv_block[12 * i + 8] = 1.0f;
		g_uv_block[12 * i + 9] = 1.0f;
		g_uv_block[12 * i + 10] = 0.0f;
		g_uv_block[12 * i + 11] = 1.0f;
	}

	//NUT VERTICES 
	const int nut_outer_sides = 6;
	const int nut_inner_sides = nut_outer_sides * 4;
	const int nut_triangles = (nut_inner_sides + nut_outer_sides) * 4;
	Nut * nut = new Nut(nut_inner_sides, 0.5, nut_outer_sides, 1, 1);
	static GLfloat g_vertex_nut[nut_triangles *3*3];
	for (int i = 0; i < nut_triangles *3; i++)
	{
		g_vertex_nut[3 * i] = GLfloat(std::get<0>(nut->vert_vector[i]));
		g_vertex_nut[3 * i + 1] = GLfloat(std::get<1>(nut->vert_vector[i]));
		g_vertex_nut[3 * i + 2] = GLfloat(std::get<2>(nut->vert_vector[i]));
	}
	delete nut;

	//NUT TEXTURE UV
	static GLfloat g_uv_nut[nut_triangles * 3*3];
	for (int i = 0; i < nut_triangles *2; i++)
	{
		g_uv_nut[3 * i] = 0.0f;
		g_uv_nut[3 * i + 1] = 0.3f;
	}
	
	//WRENCH VERTICES
	Wrench * wrench = new Wrench(1, 4, 1);
	static GLfloat g_vertex_wrench[52 * 3 * 3];
	for (int i = 0; i < 52 * 3; i++)
	{
		g_vertex_wrench[3 * i] = GLfloat(std::get<0>(wrench->vert_vector[i]));
		g_vertex_wrench[3 * i + 1] = GLfloat(std::get<1>(wrench->vert_vector[i]));
		g_vertex_wrench[3 * i + 2] = GLfloat(std::get<2>(wrench->vert_vector[i]));
	}
	delete wrench;

	static GLfloat g_uv_wrench[52*3 * 2];
	for (int i = 0; i < 52*3; i++)
	{
		g_uv_wrench[3 * i] = 0.0f;
		g_uv_wrench[3 * i + 1] = 1.0f;
	}

	//SCENE VERTICES 
	static GLfloat g_vertex_scene[] = {
		-10.0f,-3.0f,10.0f,
		-10.0f,-3.0f,-10.0f,
		-10.0f,10.0f,10.0f,
		-10.0f,-3.0f,-10.0f,
		-10.0f,10.0f,-10.0f,
		-10.0f,10.0f,10.0f,

		-10.0f,-3.0f,-10.0f,
		10.0f,-3.0f,-10.0f,
		-10.0f,10.0f,-10.0f,
		10.0f,-3.0f,-10.0f,
		10.0f,10.0f,-10.0f,
		-10.0f,10.0f,-10.0f,

		10.0f,-3.0f,10.0f,
		10.0f,-3.0f,-10.0f,
		10.0f,10.0f,10.0f,
		10.0f,-3.0f,-10.0f,
		10.0f,10.0f,-10.0f,
		10.0f,10.0f,10.0f,

		-10.0f,-3.0f,10.0f,
		10.0f,-3.0f,10.0f,
		-10.0f,10.0f,10.0f,
		10.0f,-3.0f,10.0f,
		10.0f,10.0f,10.0f,
		-10.0f,10.0f,10.0f,

		-10.0f,10.0f,10.0f,
		10.0f,10.0f,10.0f,
		-10.0f,10.0f,-10.0f,
		10.0f,10.0f,10.0f,
		10.0f,10.0f,-10.0f,
		-10.0f,10.0f,-10.0f,

		-10.0f,-3.0f,10.0f,
		10.0f,-3.0f,10.0f,
		-10.0f,-3.0f,-10.0f,
		10.0f,-3.0f,10.0f,
		10.0f,-3.0f,-10.0f,
		-10.0f,-3.0f,-10.0f,
	};

	//SCENE TEXTURE UV
	static GLfloat g_uv_scene[36*2];
	for (int i = 0; i < 12; i++)
	{
		g_uv_scene[12 * i] = 0.0f;
		g_uv_scene[12 * i + 1] = 0.0f;
		g_uv_scene[12 * i + 2] = 1.0f;
		g_uv_scene[12 * i + 3] = 0.0f;
		g_uv_scene[12 * i + 4] = 0.0f;
		g_uv_scene[12 * i + 5] = 1.0f;
		g_uv_scene[12 * i + 6] = 1.0f;
		g_uv_scene[12 * i + 7] = 0.0f;
		g_uv_scene[12 * i + 8] = 1.0f;
		g_uv_scene[12 * i + 9] = 1.0f;
		g_uv_scene[12 * i + 10] = 0.0f;
		g_uv_scene[12 * i + 11] = 1.0f;
	}

	//SCREW VERTICES
	const int screw_sides = 96;
	Cylinder * cylinder = new Cylinder(screw_sides, 0.482, 5);
	static GLfloat g_vertex_screw[screw_sides*4*3*3];
	for (int i = 0; i < screw_sides *4*3; i++)
	{
		g_vertex_screw[3 * i] = GLfloat(std::get<0>(cylinder->vert_vector[i]));
		g_vertex_screw[3 * i + 1] = GLfloat(std::get<1>(cylinder->vert_vector[i]));
		g_vertex_screw[3 * i + 2] = GLfloat(std::get<2>(cylinder->vert_vector[i]));
	}
	delete cylinder;

	static GLfloat g_uv_screw[screw_sides *4* 3 * 2];
	for (int i = 0; i < screw_sides *2; i++)
	{
		g_uv_screw[12 * i] = 0.0f;
		g_uv_screw[12 * i + 1] = 0.2f;
		g_uv_screw[12 * i + 2] = 0.0f;
		g_uv_screw[12 * i + 3] = 0.8f;
		g_uv_screw[12 * i + 4] = 10.0f;
		g_uv_screw[12 * i + 5] = 0.2f;
		g_uv_screw[12 * i + 6] = 10.0f;
		g_uv_screw[12 * i + 7] = 0.8f;
		g_uv_screw[12 * i + 8] = 0.0f;
		g_uv_screw[12 * i + 9] = 0.8f;
		g_uv_screw[12 * i + 10] = 10.0f;
		g_uv_screw[12 * i + 11] = 0.2f;
	}

	GLuint nutbuffer;
	glGenBuffers(1, &nutbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, nutbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_nut), g_vertex_nut, GL_STATIC_DRAW);

	GLuint blockbuffer;
	glGenBuffers(1, &blockbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, blockbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_block), g_vertex_block, GL_STATIC_DRAW);

	GLuint scenebuffer;
	glGenBuffers(1, &scenebuffer);
	glBindBuffer(GL_ARRAY_BUFFER, scenebuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_scene), g_vertex_scene, GL_STATIC_DRAW);

	GLuint screwbuffer;
	glGenBuffers(1, &screwbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, screwbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_screw), g_vertex_screw, GL_STATIC_DRAW);

	GLuint uvscrew;
	glGenBuffers(1, &uvscrew);
	glBindBuffer(GL_ARRAY_BUFFER, uvscrew);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_screw), g_uv_screw, GL_STATIC_DRAW);

	GLuint wrenchbuffer;
	glGenBuffers(1, &wrenchbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, wrenchbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_wrench), g_vertex_wrench, GL_STATIC_DRAW);

	GLuint uvnut;
	glGenBuffers(1, &uvnut);
	glBindBuffer(GL_ARRAY_BUFFER, uvnut);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_nut), g_uv_nut, GL_STATIC_DRAW);

	GLuint uvscene;
	glGenBuffers(1, &uvscene);
	glBindBuffer(GL_ARRAY_BUFFER, uvscene);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_scene), g_uv_scene, GL_STATIC_DRAW);

	GLuint uvwrench;
	glGenBuffers(1, &uvwrench);
	glBindBuffer(GL_ARRAY_BUFFER, uvwrench);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_wrench), g_uv_wrench, GL_STATIC_DRAW);

	GLuint uvblock;
	glGenBuffers(1, &uvblock);
	glBindBuffer(GL_ARRAY_BUFFER, uvblock);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_block), g_uv_block, GL_STATIC_DRAW);

	Controller controller;

	glm::mat4 WrenchModelMatrix(1.0);
	glm::vec3 tr(0, 0, -5);
	const glm::vec3 rot(0, 1, 0);
	WrenchModelMatrix = glm::rotate(WrenchModelMatrix, 0.52358f, rot);
	WrenchModelMatrix = glm::translate(WrenchModelMatrix, tr);
	do{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);


		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			controller.moveControl();

		else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		{
			std::thread th(&Controller::rotateControl, &controller, -1);
			th.detach();
		}
		else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		{
			std::thread th(&Controller::rotateControl, &controller, 1);
			th.detach();
		}

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		glm::mat4 MVPWrench, NutModelMatrix, MVPNut;

		if (controller.isMoving())
			controller.computeDistance();
		else if (controller.isRotating())
			controller.computePosition();

		WrenchModelMatrix = controller.getWrench();
		NutModelMatrix = controller.getNut();
		MVPWrench = ProjectionMatrix * ViewMatrix * WrenchModelMatrix;
		MVPNut = ProjectionMatrix * ViewMatrix * NutModelMatrix;


		glActiveTexture(GL_TEXTURE0);
		glUniform1i(TextureID, 0);

		//NUT
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVPNut[0][0]);
		bind_texture(uvnut, NutTexture);
		bind_buffer(0, nutbuffer);
		glDrawArrays(GL_TRIANGLES, 0, nut_triangles * 3);
												  
		// SCENE
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		bind_texture(uvscene, SceneTexture);
		bind_buffer(0, scenebuffer);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		// SCREW
		//glDisableVertexAttribArray(1);
		bind_buffer(0, screwbuffer);
		bind_texture(uvscrew, ScrewTexture);
		glDrawArrays(GL_TRIANGLES, 0, screw_sides *4*3);
		
		// BLOCK
		glEnableVertexAttribArray(1);
		bind_texture(uvblock, BlockTexture);
		bind_buffer(0, blockbuffer);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

		//WRENCH
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVPWrench[0][0]);
		bind_texture(uvwrench, WrenchTexture);
		bind_buffer(0, wrenchbuffer);
		glDrawArrays(GL_TRIANGLES, 0, 52 * 3);

		glDisableVertexAttribArray(1);	
		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup 
	glDeleteBuffers(1, &nutbuffer);
	glDeleteBuffers(1, &uvnut);
	glDeleteBuffers(1, &screwbuffer);
	glDeleteBuffers(1, &scenebuffer);
	glDeleteBuffers(1, &uvscene);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
