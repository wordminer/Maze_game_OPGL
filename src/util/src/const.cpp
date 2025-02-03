#include "const.hpp"

const float WIDTH_WIN = 1000;
const float HIGHT_WIN = 600;
const glm::vec4 SKY_COLOR = glm::vec4(0.8f, 0.8f, 1.0f, 1.0f);

const char* vshader_path = "resources/shader_source/vshader.vert";
const char* fshader_path = "resources/shader_source/fshader.frag";

// const int face_create_key[] = {
//     6, 7, 5,    6, 5, 4,
//     3, 2, 0,    3, 0, 1,
//     7, 3, 1,    7, 1, 5,
//     2, 6, 4,    2, 4, 0,
//     2, 3, 7,    2, 7, 6,
//     0, 1, 5,    0, 5, 4
// };

const int face_create_key[] = {
    3, 7, 6, 2,
    1, 5, 4, 0,
    2, 6, 5, 1,
    0, 4, 7, 3,
    4, 5, 6, 7,
    3, 2, 1, 0
};

glm::vec3 vector_rotate[] = {
    glm::vec3(1,0,0), 
    glm::vec3(0,1,0), 
    glm::vec3(0,0,1)
};

glm::fvec3 normal_face_vector[6] = {
    glm::fvec3( 0,  0,  1),
    glm::fvec3( 0,  0, -1),
    glm::fvec3( 1,  0,  0),
    glm::fvec3(-1,  0,  0),
    glm::fvec3( 0,  1,  0),
    glm::fvec3( 0, -1,  0)
};

glm::fvec2 Texture_coord_face[6] = {
    glm::fvec2(0,1), glm::fvec2(1,1), glm::fvec2(1,0),
    glm::fvec2(0,1), glm::fvec2(1,0), glm::fvec2(0,0)
};

const int CHUNK_LENGTH = 16;
const int HIGHT_MAP = 100;
const int BASE_AREA_CHUNK = CHUNK_LENGTH*CHUNK_LENGTH;
const int CHUNK_VALUME = BASE_AREA_CHUNK*HIGHT_MAP;


const float MIN_BLOCK_WIDTH = 0.2, MAX_BLOCK_WIDTH = 0.5;

const float MIN_BLOCK_HIGHT = 0.5, MAX_BLOCK_HIGHT = 0.75;

const int ELEMENT_INDEX_BLOCK_FACE[] = {
    1, 2, 3,   
    1, 3, 0
}; 