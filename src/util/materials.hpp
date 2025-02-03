#ifndef MATERIALS_HPP
#define MATERIALS_HPP

#include "shader.hpp"
#include "glm.hpp"
#include "texture.hpp"

struct Material {
    unsigned int specular[6];
    unsigned int defuse[6];
    glm::vec3 ambient;
    float shininess;

    Material(const char* specular_path[],const char* defuse_path[], glm::vec3 ob_ambient, float shiny);
};
struct Light {
    glm::vec3 specular;
    glm::vec3 defuse;
    glm::vec3 ambient;

    float Cutoffangle;
    float OuterCutoffangle;
};

void set_material_uniform(ShaderProgram shader, Material info_material);
void set_light_uniform(ShaderProgram shader, Light light_info, glm::vec3 Light_pos, glm::vec3 Look_vec);

#endif 