#include "chunk_part.hpp"


glm::vec3 Chunk::take_block_coord(int index_block){
    // std::cout << index_block;
    int local_x = index_block%CHUNK_LENGTH;
    int local_y = round(index_block/BASE_AREA_CHUNK);
    int local_z = round(index_block/CHUNK_LENGTH);
     
    int x_coord = CHUNK_LENGTH * this->Pos_chunk.x + local_x;
    int y_coord = HIGHT_MAP * this->Pos_chunk.y + local_y;
    int z_coord = CHUNK_LENGTH * this->Pos_chunk.z + local_z;
    return glm::vec3(x_coord, y_coord, z_coord);
}

glm::ivec3 Chunk::take_local_coord(glm::ivec3 world_coor){
    return glm::ivec3(world_coor.x - Pos_chunk.x*CHUNK_LENGTH, world_coor.y - Pos_chunk.y*CHUNK_LENGTH, world_coor.z - Pos_chunk.z*CHUNK_LENGTH);
}

int Chunk::take_block_index(glm::ivec3 block_coord){
    glm::ivec3 local_coord;
    local_coord.x = (block_coord.x - Pos_chunk.x * CHUNK_LENGTH);
    local_coord.y = (block_coord.y - Pos_chunk.y * HIGHT_MAP);
    local_coord.z = (block_coord.z - Pos_chunk.z * CHUNK_LENGTH);

    int index = (local_coord.x + local_coord.y*BASE_AREA_CHUNK + local_coord.z*CHUNK_LENGTH);
    return index;
}

bool Chunk::Is_east_block(glm::ivec3 pos_block, Chunk* east_chunk){
    if (take_local_coord(pos_block).x + 1 >= CHUNK_LENGTH){
        if (east_chunk == nullptr){return false;}
        if (east_chunk->Block_map[east_chunk->take_block_index(glm::ivec3(0 + east_chunk->Pos_chunk.x*CHUNK_LENGTH, pos_block.y, pos_block.z))] == 0){return false;}
    }
    else if (Block_map[take_block_index(glm::ivec3(pos_block.x + 1, pos_block.y, pos_block.z))] == 0){return false;}    
    
    return true;
}
bool Chunk::Is_west_block(glm::ivec3 pos_block, Chunk* west_chunk){
    // std::cout<< pos_block.x <<pos_block.y<<pos_block.z<<std::endl;
    // std::cout<< west_chunk->Pos_chunk.x <<west_chunk->Pos_chunk.y<<west_chunk->Pos_chunk.z<<std::endl;
    if (take_local_coord(pos_block).x - 1 < 0){
        if (west_chunk == nullptr){return false;}
        if (west_chunk->Block_map[west_chunk->take_block_index(glm::ivec3(CHUNK_LENGTH - 1 + west_chunk->Pos_chunk.x*CHUNK_LENGTH, pos_block.y, pos_block.z))] == 0){return false;}
    }
    else if (Block_map[take_block_index(glm::ivec3(pos_block.x - 1, pos_block.y, pos_block.z))] == 0){return false;}    

    return true;
}
bool Chunk::Is_north_block(glm::ivec3 pos_block, Chunk* north_chunk){
    if (take_local_coord(pos_block).z - 1 < 0){
        if (north_chunk == nullptr){return false;}
        if (north_chunk->Block_map[north_chunk->take_block_index(glm::ivec3(pos_block.x, pos_block.y, CHUNK_LENGTH - 1 + north_chunk->Pos_chunk.z*CHUNK_LENGTH))] == 0){
            return false;}
    }
    else if (Block_map[take_block_index(glm::ivec3(pos_block.x, pos_block.y, pos_block.z - 1))] == 0){return false;}    
    return true;
}
bool Chunk::Is_south_block(glm::ivec3 pos_block, Chunk* south_chunk){
    if (take_local_coord(pos_block).z + 1 >= CHUNK_LENGTH){
        if (south_chunk == nullptr){return false;}
        if (south_chunk->Block_map[south_chunk->take_block_index(glm::ivec3(pos_block.x, pos_block.y, 0 + south_chunk->Pos_chunk.z*CHUNK_LENGTH))] == 0){return false;}
    }
    else if (Block_map[take_block_index(glm::ivec3(pos_block.x, pos_block.y, pos_block.z + 1))] == 0){return false;}    
    return true;
}

void Chunk::build_chunk(std::vector<Vertex> &Vertices_map, std::vector<GLuint> &element_map, Chunk* east_chunk, Chunk* west_chunk, Chunk* north_chunk, Chunk* south_chunk){
    float x_east, x_west, z_north, z_south;
    std::vector<glm::fvec3> Block_coord;
    int block = 0;

    for (unsigned int block_index = 0; block_index < Block_map.size(); block_index ++){
        if (Block_map[block_index] == 0){continue;}
        block ++;
        Block_coord.clear();
        glm::fvec3 block_coord = take_block_coord(block_index);
        float block_width = matrix_width_from_pos(block_coord);
        float block_hight = matrix_hight_from_pos(block_coord);
        
        if (Is_east_block(block_coord, east_chunk))    {x_east = 0.5; } else{x_east = block_width/2;}
        if (Is_west_block(block_coord, west_chunk))   {x_west = -0.5; } else{x_west = -block_width/2;}
        if (Is_south_block(block_coord, south_chunk)) {z_south = 0.5; } else{z_south = block_width/2;}
        if (Is_north_block(block_coord, north_chunk)){z_north = -0.5; } else{z_north = -block_width/2;}
        
        Block_coord.insert(Block_coord.end(),glm::fvec3(0.5,0,0.5) + block_coord + glm::fvec3(x_west, 0, z_north));
        Block_coord.insert(Block_coord.end(),glm::fvec3(0.5,0,0.5) + block_coord + glm::fvec3(x_east, 0, z_north));
        Block_coord.insert(Block_coord.end(),glm::fvec3(0.5,0,0.5) + block_coord + glm::fvec3(x_east, 0, z_south));
        Block_coord.insert(Block_coord.end(),glm::fvec3(0.5,0,0.5) + block_coord + glm::fvec3(x_west, 0, z_south));
        Block_coord.insert(Block_coord.end(),glm::fvec3(0.5,0,0.5) + block_coord + glm::fvec3(x_west, block_hight, z_north));
        Block_coord.insert(Block_coord.end(),glm::fvec3(0.5,0,0.5) + block_coord + glm::fvec3(x_east, block_hight, z_north));
        Block_coord.insert(Block_coord.end(),glm::fvec3(0.5,0,0.5) + block_coord + glm::fvec3(x_east, block_hight, z_south));
        Block_coord.insert(Block_coord.end(),glm::fvec3(0.5,0,0.5) + block_coord + glm::fvec3(x_west, block_hight, z_south));
        for (int face = 0; face < 6; face ++){
            int start_index = face*4;
            unsigned int start_element_index = block*24 + face*4;
            Vertex v0, v1, v2, v3;
            // std::cout << "-------------------" << std::endl;
            // std::cout << face_create_key[start_index] << std::endl;
            // std::cout << Block_coord[face_create_key[start_index]].x << std::endl;
            // std::cout << Block_coord[face_create_key[start_index]].y << std::endl;
            // std::cout << Block_coord[face_create_key[start_index]].z << std::endl;
            
            v0 = Vertex(Block_coord[face_create_key[start_index]], glm::fvec3(1,1,1), face, normal_face_vector[face], glm::fvec2(0,0));
            v1 = Vertex(Block_coord[face_create_key[start_index + 1]], glm::fvec3(1,1,1), face, normal_face_vector[face], glm::fvec2(0,block_hight));
            v2 = Vertex(Block_coord[face_create_key[start_index + 2]], glm::fvec3(1,1,1), face, normal_face_vector[face], glm::fvec2(1,block_hight));
            v3 = Vertex(Block_coord[face_create_key[start_index + 3]], glm::fvec3(1,1,1), face, normal_face_vector[face], glm::fvec2(1,0));
            Vertices_map.insert(Vertices_map.end(), {v1, v2, v3, v1, v3, v0});
        }
    }
}