#include "map.hpp"

Map::Map(std::unordered_map<glm::ivec3, int> map){
    Block_map = map;
}

void Map::regeneration_chunk(glm::ivec3 mPos_chunk){
    Chunk* chunk_create = new Chunk(mPos_chunk);
    for (int x_coord = 0; x_coord < CHUNK_LENGTH; x_coord ++){
        for (int z_coord = 0; z_coord < CHUNK_LENGTH; z_coord ++){
            int x = x_coord + mPos_chunk.x*CHUNK_LENGTH;
            int z = z_coord + mPos_chunk.z*CHUNK_LENGTH;
            glm::ivec3 pos = glm::ivec3(x,0,z);
            if (Block_map.find(pos) == Block_map.end()){continue;}
    
            chunk_create->Block_map[chunk_create->take_block_index(pos)] = Block_map[pos];
        }
    }
    this->Chunk_list[mPos_chunk] = chunk_create;
}

void Map::build_chunk(glm::ivec3 Chunk_pos){
    Chunk *east_chunk = nullptr, *west_chunk = nullptr, *north_chunk = nullptr, *south_chunk = nullptr;
    if (!Is_void(Chunk_pos + glm::ivec3(1,0,0))){east_chunk = Chunk_list[Chunk_pos + glm::ivec3(1,0,0)];}
    if (!Is_void(Chunk_pos + glm::ivec3(-1,0,0))){west_chunk = Chunk_list[Chunk_pos + glm::ivec3(-1,0,0)];}
    if (!Is_void(Chunk_pos + glm::ivec3(0,0,-1))){north_chunk = Chunk_list[Chunk_pos + glm::ivec3(0,0,-1)];}
    if (!Is_void(Chunk_pos + glm::ivec3(0,0,1))){south_chunk = Chunk_list[Chunk_pos + glm::ivec3(0,0,1)];}
    
    Chunk_list[Chunk_pos]->build_chunk(Vertices_load, element_index_load, east_chunk, west_chunk, north_chunk, south_chunk);
}

bool Map::Is_block(glm::ivec3 mPos_chunk, glm::ivec3 local_block_coord){
    Chunk* chunk_choose = this->Chunk_list[mPos_chunk];
    if (chunk_choose->Block_map[chunk_choose->take_block_index(local_block_coord)] != 0){return true;}
    return false;
}


void Map::update_chunk(glm::ivec3 player_pos, int Chunk_range, Graphic_data &data){
    glm::ivec3 Chunk_in = getChunkPos(player_pos);
    if (Chunk_in == this->PosChunkIn){return;}
    PosChunkIn = Chunk_in;

    glm::ivec3 Chunk_min = Chunk_in - glm::ivec3(Chunk_range, 0, Chunk_range);
    this->min_chunk_load = Chunk_min;
    this->max_chunk_load = Chunk_min + glm::ivec3(Chunk_range*2 + 1, 0, Chunk_range*2 + 1);
    Chunk_list.clear();
    Vertices_load.clear();

    for (int x = 0; x <= Chunk_range*2; x++){
    for (int z = 0; z <= Chunk_range*2; z++){
        regeneration_chunk(Chunk_min + glm::ivec3(x, 0, z));
    }}
    for (int x = 0; x <= Chunk_range*2; x++){
    for (int z = 0; z <= Chunk_range*2; z++){
        build_chunk(Chunk_min + glm::ivec3(x, 0, z));
    }}

    data.Buffer_array_data(Vertices_load.data(), (GLsizeiptr)(Vertices_load.size()*sizeof(Vertex)), GL_STATIC_DRAW);

    data.AttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void *)getOffsetOfPos());
    data.AttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void *)getOffsetOfColor());
    data.AttribPointer(2, 3, GL_FLOAT, false, sizeof(Vertex), (void *)getOffsetOfNormal());
    data.AttribPointer(3, 2, GL_FLOAT, false, sizeof(Vertex), (void *)getOffsetOfTexCoord());
    data.AttribPointer(4, 2, GL_FLOAT, false, sizeof(Vertex), (void *)getOffsetOfFaceID());
}

void Map::render(Graphic_data &data){
    data.Bind_vertex_array();
    glDrawArrays(GL_TRIANGLES, 0, Vertices_load.size());    
}

bool Map::Is_void(glm::ivec3 Chunk_pos){
    for (int axis = 0; axis < 3; axis ++){
        if (Chunk_pos[axis] < min_chunk_load[axis] || Chunk_pos[axis] > max_chunk_load[axis]){
            return true;
        }
    }
    return false;
}