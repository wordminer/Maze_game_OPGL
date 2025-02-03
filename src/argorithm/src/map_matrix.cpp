#include "map_matrix.hpp"

float matrix_hight_from_pos(glm::ivec3 pos){
    int alpha = 5;
    float cos_pos = abs(std::cos((pos.x*alpha + pos.z*alpha*alpha)*std::pow(pos.x + pos.z, 2)));
    return cos_pos * (MAX_BLOCK_HIGHT - MIN_BLOCK_HIGHT) + MIN_BLOCK_HIGHT;
}
float matrix_width_from_pos(glm::ivec3 pos){
    int beta = 3;
    float sin_pos = abs(std::sin((pos.x*beta + pos.z*beta*beta)*std::pow(pos.x + pos.z, 2)));
    return (sin_pos * (MAX_BLOCK_WIDTH - MIN_BLOCK_WIDTH) + MIN_BLOCK_WIDTH);
}

int Maze_map::take_maze_random(int Is_abs, glm::ivec3 pos){
    int alpha = 1;
    int beta = 5;
    int yeta = 8;
    int sin_pos = round(std::sin(alpha*pow(pos.x,3) + beta*pow(pos.y,2) + yeta*pos.z));
    if (Is_abs){return abs(sin_pos);}
    return sin_pos + 1;
}

int Maze_map::Is_next_to_aVoid(glm::ivec3 pos, glm::ivec3 before_pos){
    for (auto direct:this->Direct){
        glm::ivec3 direct_pos = pos + direct;

        if (direct_pos == before_pos){continue;}
        if (direct_pos == this->end_point){return -1;}
        if (this->Map.find(direct_pos) == this->Map.end()){return 1;}
    }
    // std::cout<<pos.x <<" "<<pos.y <<" "<<pos.z <<" "<<std::endl;
        
    return 0;
}
void Maze_map::reneration_map_matrix(){
    // crate a base map
    for (int x = 0; x < this->width_map; x++){
        for (int z = 0; z < this->length_map; z++){
            glm::ivec3 pos = glm::ivec3(x,0,z);
            if (pos == this->start_point || pos == this->end_point){continue;}
            this->Map[pos] = 1;
        }
    }
    build_way(start_point, start_point);

    // create way go
}

void Maze_map::build_way(glm::ivec3 now_pos, glm::ivec3 before_pos){
    std::vector<glm::ivec3> way_go;
    for (auto direct:this->Direct){
        glm::ivec3 new_pos = now_pos + direct;
        if (new_pos == before_pos){continue;}
        int Void_check = Is_next_to_aVoid(new_pos, now_pos);

        if (!Is_have_main_way && Void_check == -1){
            Is_have_main_way = true;
            this->Map.erase(this->Map.find(new_pos));
            return;
        }
        if (Void_check == 0){
            way_go.insert(way_go.end(), direct);
            //this->Map.erase(this->Map.find(new_pos));
            // build_way(new_pos, now_pos);
       }
    }
    std::vector<glm::ivec3> way_select = this->random_way(way_go, now_pos);
    for (auto x:way_select){
        glm::ivec3 new_pos = now_pos + x;
        int Void_check = Is_next_to_aVoid(new_pos, now_pos);
        if (Void_check == 0){ 
            this->Map.erase(this->Map.find(new_pos));
            build_way(new_pos, now_pos);
        }
    }
}

std::vector<glm::ivec3> Maze_map::random_way(std::vector<glm::ivec3> way, glm::ivec3 pos){
    std::vector<glm::ivec3> way_random;
    if (way.size() == 1){way_random = way;}
    else if (way.size() == 2){
        int rd_way = this->take_maze_random(true, pos);
        way_random.insert(way_random.end(), way[rd_way]);
        way_random.insert(way_random.end(), way[rd_way*(-1) + 1]);
    }
    else if (way.size() == 3) {
        int rd_way = this->take_maze_random(false, pos);
        way_random.insert(way_random.end(), way[rd_way]);
        int rd_other_way = this->take_maze_random(true, pos);
        if (rd_way == 1){
            way_random.insert(way_random.end(), way[rd_other_way*2]);
            way_random.insert(way_random.end(), way[rd_other_way*(-2) + 2]);
        }
        if (rd_way == 2){
            way_random.insert(way_random.end(), way[rd_other_way]);
            way_random.insert(way_random.end(), way[rd_other_way*(-1) + 1]);
        }
        if (rd_way == 0){
            way_random.insert(way_random.end(), way[rd_other_way + 1]);
            way_random.insert(way_random.end(), way[rd_other_way*(-1) + 2]);
        }
    }   
    return way_random;
}