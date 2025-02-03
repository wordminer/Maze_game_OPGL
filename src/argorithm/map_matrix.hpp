#ifndef MAP_MATRIX_HPP
#define MAP_MATRIX_HPP

#include <unordered_set>
#include <gtx/hash.hpp>
#include <gtc/noise.hpp>
#include "glm.hpp"
#include "const.hpp"
#include <cmath>
#include <vector>
#include <iostream>


struct Maze_map{
    int width_map;
    int length_map;
    glm::ivec3 start_point;
    glm::ivec3 end_point;
    
    std::unordered_map<glm::ivec3, int> Map;
    std::vector<glm::ivec3> Direct = {glm::ivec3(1,0,0), glm::ivec3(-1,0,0), glm::ivec3(0,0,-1), glm::ivec3(0,0,1)};
    std::vector<glm::ivec3> CrossDirect = {glm::ivec3(1,0,1), glm::ivec3(-1,0,1), glm::ivec3(1,0,-1), glm::ivec3(-1,0,-1)};
    
    bool Is_have_main_way = false;

    int Is_next_to_aVoid(glm::ivec3 pos, glm::ivec3 before_pos);
    bool Is_next_to_block(glm::ivec3 pos_block, glm::ivec3 pos_check);
    std::vector<glm::ivec3> random_way(std::vector<glm::ivec3> way, glm::ivec3 pos);

    void reneration_map_matrix();
    void build_way(glm::ivec3 now_pos, glm::ivec3 before_pos);
    int take_maze_random(int Is_abs, glm::ivec3 pos);
};


float matrix_hight_from_pos(glm::ivec3 pos);
float matrix_width_from_pos(glm::ivec3 pos);

#endif