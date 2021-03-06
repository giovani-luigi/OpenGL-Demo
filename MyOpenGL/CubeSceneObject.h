#pragma once
#include "SceneObject.h"

class CubeSceneObject : public SceneObject
{
public:

    CubeSceneObject(Shader shader) : SceneObject(
        std::vector<float>{
            //face frontal
            1.0, 1.0, 1.0,
            1.0, -1.0, 1.0,
            - 1.0, -1.0, 1.0,
            - 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            -1.0, -1.0, 1.0,
            //face traseira
            1.0, 1.0, -1.0,
            1.0, -1.0, -1.0,
            - 1.0, -1.0, -1.0,
            - 1.0, 1.0, -1.0,
            1.0, 1.0, -1.0,
            -1.0, -1.0, -1.0,
            //face esquerda
            - 1.0, -1.0, 1.0,
            -1.0, 1.0, 1.0,
            -1.0, -1.0, -1.0,
            -1.0, -1.0, -1.0,
            -1.0, 1.0, -1.0,
            -1.0, 1.0, 1.0,
            //face direita
            1.0, -1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0, 1.0, -1.0,
            1.0, 1.0, 1.0,
            //face baixo
            - 1.0, -1.0, 1.0,
            1.0, -1.0, 1.0,
            1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            -1.0, -1.0, -1.0,
            -1.0, -1.0, 1.0,
            //face cima
            - 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, 1.0, -1.0,
            1.0, 1.0, -1.0,
            -1.0, 1.0, -1.0,
            -1.0, 1.0, 1.0,
        }, std::vector<float>{
            //face frontal
            0.0, 0.0, 1.0, //apontado para frente
            0.0, 0.0, 1.0, //apontado para frente
            0.0, 0.0, 1.0, //apontado para frente
            0.0, 0.0, 1.0, //apontado para frente
            0.0, 0.0, 1.0, //apontado para frente
            0.0, 0.0, 1.0, //apontado para frente
            //face traseira
            0.0, 0.0, -1.0, //apontado para tr�s
            0.0, 0.0, -1.0, //apontado para tr�s
            0.0, 0.0, -1.0, //apontado para tr�s
            0.0, 0.0, -1.0, //apontado para tr�s
            0.0, 0.0, -1.0, //apontado para tr�s
            0.0, 0.0, -1.0, //apontado para tr�s
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

        }, STATIC, shader, Material::create_white_marble())
    {
        // nothing
    }
};
