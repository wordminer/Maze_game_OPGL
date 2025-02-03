#ifndef CONST
#define CONST

#include "glm.hpp"

extern const float WIDTH_WIN;
extern const float HIGHT_WIN;
extern const glm::vec4 SKY_COLOR;

extern const char* vshader_path;
extern const char* fshader_path;

extern const int face_create_key[];

extern glm::vec3 vector_rotate[];

extern glm::fvec3 normal_face_vector[6];
extern glm::fvec2 Texture_coord_face[6];

extern const int CHUNK_LENGTH;
extern const int HIGHT_MAP;
extern const int BASE_AREA_CHUNK;
extern const int CHUNK_VALUME;

extern const float MIN_BLOCK_WIDTH, MAX_BLOCK_WIDTH;
extern const float MIN_BLOCK_HIGHT, MAX_BLOCK_HIGHT;

extern const int ELEMENT_INDEX_BLOCK_FACE[];

#endif