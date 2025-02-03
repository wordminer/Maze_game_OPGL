#include "chunk_ctr.hpp"

glm::ivec3 getChunkPos(glm::ivec3 world_pos){
    if (world_pos.x < 0){world_pos.x ++;}
    if (world_pos.z < 0){world_pos.z ++;}

    int x_pos = round(world_pos.x / CHUNK_LENGTH);
    int y_pos = 0;
    int z_pos = round(world_pos.z / CHUNK_LENGTH);

    if (world_pos.x < 0){x_pos --;}
    if (world_pos.z < 0){z_pos --;}

    return glm::ivec3(x_pos, y_pos, z_pos);
}

int take_block_index(glm::ivec3 chunk_pos, glm::ivec3 block_world_pos){
    glm::ivec3 local_coord;
    local_coord.x = (block_world_pos.x - chunk_pos.x * CHUNK_LENGTH);
    local_coord.y = (block_world_pos.y - chunk_pos.y * HIGHT_MAP);
    local_coord.z = (block_world_pos.z - chunk_pos.z * CHUNK_LENGTH);
    int index = (local_coord.x + local_coord.y*BASE_AREA_CHUNK + local_coord.z*CHUNK_LENGTH);
    return index;
}

int take_block_info(int block_index, int block_type){
    // for example block index is 26 (have define in chunk) and block type is 6
    // so return 266 and return 76 if index is 7;
    return block_index*10 + block_type;
}

int take_block_index_from_info(int block_info){
    return round(block_info/10);
}

int take_block_type_from_info(int block_info){
    return block_info - take_block_index_from_info(block_info)*10;
}

