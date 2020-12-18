#pragma once
#include "SceneObject.h"

class CubeSceneObject : public SceneObject {

public:

	CubeSceneObject(Shader shader) : SceneObject(
		std::vector<float> { 
			//face frontal
			0.5, 0.5, 0.5,
			0.5, -0.5, 0.5,
			- 0.5, -0.5, 0.5,
			- 0.5, 0.5, 0.5, 
			0.5, 0.5, 0.5,
			-0.5, -0.5, 0.5,
			//face traseira
			0.5, 0.5, -0.5, 
			0.5, -0.5, -0.5,
			- 0.5, -0.5, -0.5,
			- 0.5, 0.5, -0.5, 
			0.5, 0.5, -0.5,
			-0.5, -0.5, -0.5,
			//face esquerda
			- 0.5, -0.5, 0.5,
			-0.5, 0.5, 0.5,
			-0.5, -0.5, -0.5,
			-0.5, -0.5, -0.5,
			-0.5, 0.5, -0.5,
			-0.5, 0.5, 0.5,
			//face direita
			0.5, -0.5, 0.5,
			0.5, 0.5, 0.5,
			0.5, -0.5, -0.5,
			0.5, -0.5, -0.5,
			0.5, 0.5, -0.5,
			0.5, 0.5, 0.5,
			//face baixo
			- 0.5, -0.5, 0.5,
			0.5, -0.5, 0.5,
			0.5, -0.5, -0.5,
			0.5, -0.5, -0.5,
			-0.5, -0.5, -0.5,
			-0.5, -0.5, 0.5,
			//face cima
			- 0.5, 0.5, 0.5,
			0.5, 0.5, 0.5,
			0.5, 0.5, -0.5,
			0.5, 0.5, -0.5,
			-0.5, 0.5, -0.5,
			-0.5, 0.5, 0.5,
		}, std::vector<float>{
			//face frontal
			0.0, 0.0, 1.0, //apontado para frente
			0.0, 0.0, 1.0, //apontado para frente
			0.0, 0.0, 1.0, //apontado para frente
			0.0, 0.0, 1.0, //apontado para frente
			0.0, 0.0, 1.0, //apontado para frente
			0.0, 0.0, 1.0, //apontado para frente
			//face traseira
			0.0, 0.0, -1.0, //apontado para trás
			0.0, 0.0, -1.0, //apontado para trás
			0.0, 0.0, -1.0, //apontado para trás
			0.0, 0.0, -1.0, //apontado para trás
			0.0, 0.0, -1.0, //apontado para trás
			0.0, 0.0, -1.0, //apontado para trás
			//face esquerda
			- 1.0, 0.0, 0.0, //apontado para esquerda e para frente
			- 1.0, 0.0, 0.0, //apontado para esquerda e para frente
			- 1.0, 0.0, 0.0, //apontado para esquerda e para frente
			- 1.0, 0.0, 0.0, //apontado para esquerda e para frente
			- 1.0, 0.0, 0.0, //apontado para esquerda e para frente
			- 1.0, 0.0, 0.0, //apontado para esquerda e para frente
			//face direita
			1.0, 0.0, 0.0, //apontado para direita e para frente
			1.0, 0.0, 0.0, //apontado para direita e para frente
			1.0, 0.0, 0.0, //apontado para direita e para frente
			1.0, 0.0, 0.0, //apontado para direita e para frente
			1.0, 0.0, 0.0, //apontado para direita e para frente
			1.0, 0.0, 0.0, //apontado para direita e para frente
			//face inferior
			0.0, -1.0, 0.0, //apontado para baixo e para frente
			0.0, -1.0, 0.0, //apontado para baixo e para frente
			0.0, -1.0, 0.0, //apontado para baixo e para frente
			0.0, -1.0, 0.0, //apontado para baixo e para frente
			0.0, -1.0, 0.0, //apontado para baixo e para frente
			0.0, -1.0, 0.0, //apontado para baixo e para frente
			//face superior
			0.0, 1.0, 0.0, //apontado para cima e para frente
			0.0, 1.0, 0.0, //apontado para cima e para frente
			0.0, 1.0, 0.0, //apontado para cima e para frente
			0.0, 1.0, 0.0, //apontado para cima e para frente
			0.0, 1.0, 0.0, //apontado para cima e para frente
			0.0, 1.0, 0.0, //apontado para cima e para frente

		}, shader, STATIC)
	{
		// nothing
	}
	
};

