#ifndef MAP_MATRIX_HPP
#define MAP_MATRIX_HPP

#include <unordered_set>
#include <gtx/hash.hpp>
#include <gtc/noise.hpp>
#include "glm.hpp"
#include "const.hpp"
#include <cmath>
#include <vector>


struct Maze_map{
    int width_map;
    int length_map;
    glm::ivec3 start;
    glm::ivec3 end;
    
    std::unordered_map<glm::ivec3, int> Map;
    bool Is_have_main_way = false;

    bool Is_next_to_aVoid(glm::ivec3 coord);
    bool Is_out_of_map(glm::ivec3 coord);

    void reneration_map_matrix();
};


float matrix_hight_from_pos(glm::ivec3 pos);
float matrix_width_from_pos(glm::ivec3 pos);

#endif