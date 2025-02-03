#include "map_matrix.hpp"

float matrix_hight_from_pos(glm::ivec3 pos){
    int alpha = 5;
    float cos_pos = abs(std::cos(std::tan((pos.x*alpha + pos.z*alpha*alpha)*std::pow(pos.x + pos.z, 2))));
    return cos_pos * (MAX_BLOCK_HIGHT - MIN_BLOCK_HIGHT) + MIN_BLOCK_HIGHT;
}
float matrix_width_from_pos(glm::ivec3 pos){
    int beta = 3;
    float sin_pos = abs(std::sin(pos.x*beta + pos.z*beta*beta));
    return (sin_pos * (MAX_BLOCK_WIDTH - MIN_BLOCK_WIDTH) + MIN_BLOCK_WIDTH);
}

bool Maze_map::Is_next_to_aVoid(glm::ivec3 coord){
    for (int x = -1; x <= 1; x += 2){
        for (int z = -1; z <= 1; z += 2){
            if (this->Map.find(glm::ivec3(coord.x + x, coord.y, coord.z + z)) == this->Map.end()){return true;}
        }
    }
    return false;
}
void Maze_map::reneration_map_matrix(){
    // crate a base map
    for (int x = 0; x < this->width_map; x++){
        for (int z = 0; z < this->length_map; z++){
            glm::ivec3 pos = glm::ivec3(x,0,z);
            if (pos == this->start || pos == this->end){continue;}
            this->Map[pos] = 1;
        }
    }

    // create way go
}