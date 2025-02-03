#ifndef MAP_HPP
#define MAP_HPP

#include <unordered_set>
#include <gtx/hash.hpp>

#include <iostream>
#include <random>

#include "chunk_ctr.hpp"
#include "chunk_part.hpp"
#include "handle_data.hpp"

class Map{
public:
    Map(std::unordered_map<glm::ivec3, int> map);
    void regeneration_chunk(glm::ivec3 mPos_chunk);

    void build_chunk(glm::ivec3 Chunk_pos);
    void update_chunk(glm::ivec3 player_pos, int Chunk_range, Graphic_data &data);
    void render(Graphic_data &data);

    bool Is_block(glm::ivec3 mPos_chunk, glm::ivec3 local_block_coord);
    bool Is_void(glm::ivec3 Chunk_pos);

private:
    glm::ivec3 PosChunkIn = glm::vec3(0,1,0);
    std::vector<Vertex> Vertices_load;
    std::vector<GLuint> element_index_load;

    std::unordered_map<glm::ivec3, int> Block_map;
    std::unordered_map<glm::ivec3, Chunk*> Chunk_list;

    glm::ivec3 min_chunk_load;
    glm::ivec3 max_chunk_load;
};

#endif