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

int random_int_with_seed(glm::ivec3 pos, int range_random){
    int alpha = 10;
    int beta = 6;
    int zeta = 5;
    int result = 0;
    if (range_random != 0){
        result = (pos.x*pos.x*pos.x*alpha + pos.y*pos.y*beta + pos.z*zeta)%range_random;
    }
    return result;
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

    for (auto direct:this->CrossDirect){
        glm::ivec3 direct_pos = pos + direct;
        if (this->Is_next_to_block(before_pos, direct_pos)){continue;}
        if (direct_pos == this->end_point){return 0;}
        if (this->Map.find(direct_pos) == this->Map.end()){return 1;}
    }
    // std::cout<<pos.x <<" "<<pos.y <<" "<<pos.z <<" "<<std::endl;
        
    return 0;
}

bool Maze_map::Is_next_to_block(glm::ivec3 pos_block, glm::ivec3 pos_check){
    for (auto direct:this->Direct){
        glm::ivec3 direct_pos = pos_check + direct;
        if (direct_pos == pos_block){return true;}
    }
    return false;
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
    for (auto way:way_select){
        // std::cout << now_pos.x << " "<< now_pos.y << " "<< now_pos.z << " " <<std::endl;
        // std::cout << way.x << " "<< way.y << " "<< way.z << " " <<std::endl;
        int random_insert = random_int_with_seed(now_pos + way, this->Pos_wait.size());
        this->Map.erase(this->Map.find(now_pos + way));
        this->Pos_wait.insert(this->Pos_wait.begin() + random_insert,now_pos);
        this->Way_will_go.insert(this->Way_will_go.begin() + random_insert,way);
    }
    for (int i = 0; i < this->Pos_wait.size(); i ++){
        
        glm::ivec3 build_pos = Pos_wait[0];
        glm::ivec3 new_pos = Pos_wait[0] + Way_will_go[0];
        this->Pos_wait.erase(this->Pos_wait.begin());
        this->Way_will_go.erase(this->Way_will_go.begin());
        
        int Void_check = Is_next_to_aVoid(new_pos, build_pos);
        if (Void_check == 0){ 
            //this->Map.erase(this->Map.find(new_pos));
            build_way(new_pos, build_pos);
            break;
        }
    }
}

std::vector<glm::ivec3> Maze_map::random_way(std::vector<glm::ivec3> way, glm::ivec3 pos){
    std::vector<glm::ivec3> way_random;
    if (way.size() == 1 || way.size() == 4){way_random = way;}
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