#ifndef CHUNK_CTR_HPP
#define CHUNK_CTR_HPP

#include "glm.hpp"
#include "const.hpp"
#include <cmath>
#include <iostream>

glm::ivec3 getChunkPos(glm::ivec3 world_pos);
int take_block_index(glm::ivec3 chunk_pos, glm::ivec3 block_world_pos);
void getWorldPosFromLocalPos(glm::vec3 local_pos);

int take_block_info(int block_index, int block_type);
int take_block_index_from_info(int block_info);
int take_block_type_from_info(int block_info);


#endif