#ifndef CHUNK_PART_HPP
#define CHUNK_PART_HPP

#include "vertex.hpp"
#include "map_matrix.hpp"
#include <iostream>

struct Chunk{
    glm::ivec3 Pos_chunk;
    std::vector<int> Block_map;

    Chunk(glm::ivec3 mPos_chunk):Pos_chunk(mPos_chunk) {
        for (int i = 0; i < CHUNK_LENGTH*CHUNK_LENGTH; i ++){Block_map.insert(Block_map.end(), 0);}
    };

    glm::vec3 take_block_coord(int index_block);
    glm::ivec3 take_local_coord(glm::ivec3 world_coor);
    int take_block_index(glm::ivec3 block_coord);

    bool Is_east_block(glm::ivec3 pos_block, Chunk* east_chunk);
    bool Is_west_block(glm::ivec3 pos_block, Chunk* west_chunk);
    bool Is_north_block(glm::ivec3 pos_block, Chunk* north_chunk);
    bool Is_south_block(glm::ivec3 pos_block, Chunk* south_chunk);

    void build_chunk(std::vector<Vertex> &Vertices_map, std::vector<GLuint> &element_map, Chunk* east_chunk, Chunk* west_chunk, Chunk* north_chunk, Chunk* south_chunk);
};

#endif