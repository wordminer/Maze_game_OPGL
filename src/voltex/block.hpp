#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <iostream>
#include <vector>
#include "glm.hpp"
#include "vertex.hpp"



class Block{
public:
    std::vector<glm::vec3> Block_coord;
    std::vector<Vertex> Block_vertices;

    Block();
    void Create_block(const int face_key[], glm::vec3 Color,glm::fvec3 face_vector[], glm::fvec2 Tex_coord[], glm::fvec3 mPosition, float x_side, float y_side, float z_side);
   
};

#endif 