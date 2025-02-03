#include "materials.hpp"

Material::Material(const char* specular_path[],const char* defuse_path[], glm::vec3 ob_ambient, float shiny){
    this->ambient = ob_ambient;
    this->shininess = shiny;
    for (int i = 0; i < 6; i++){
        load_image(this->defuse[i], defuse_path[i]);
        load_image(this->specular[i], specular_path[i]);}
}

void set_material_uniform(ShaderProgram shader, Material info_material){
    shader.uniformVec3("material.ambient", info_material.ambient);
    shader.uniformFloat("material.shininess", info_material.shininess);

    shader.uniformInt("material.texture_defuse_1", 0);
    shader.uniformInt("material.texture_defuse_2", 1);
    shader.uniformInt("material.texture_defuse_3", 2);
    shader.uniformInt("material.texture_defuse_4", 3);
    shader.uniformInt("material.texture_defuse_5", 4);
    shader.uniformInt("material.texture_defuse_6", 5);

    shader.uniformInt("material.texture_specular_1", 6);
    shader.uniformInt("material.texture_specular_2", 7);
    shader.uniformInt("material.texture_specular_3", 8);
    shader.uniformInt("material.texture_specular_4", 9);
    shader.uniformInt("material.texture_specular_5", 10); 
    shader.uniformInt("material.texture_specular_6", 11);

    for (int tex = 0; tex < 6; tex ++){
        glActiveTexture(GL_TEXTURE0 + tex);
        glBindTexture(GL_TEXTURE_2D, info_material.defuse[tex]);
    }
    for (int tex = 6; tex < 12; tex ++){
        glActiveTexture(GL_TEXTURE0 + tex);
        glBindTexture(GL_TEXTURE_2D, info_material.specular[tex - 6]);
    }

    shader.uniformFloat("material.Contant", 1);
    shader.uniformFloat("material.linear", 0.14);
    shader.uniformFloat("material.quadratic", 0.007);
}

void set_light_uniform(ShaderProgram shader, Light light_info, glm::vec3 Light_pos, glm::vec3 Look_vec){
    shader.uniformVec3("light.specular", light_info.specular);
    shader.uniformVec3("light.defuse", light_info.defuse);
    shader.uniformVec3("light.ambient", light_info.ambient);

    shader.uniformFloat("light.CutOff", glm::cos(glm::radians(light_info.Cutoffangle)));
    shader.uniformFloat("light.outerCutOff", glm::cos(glm::radians(light_info.OuterCutoffangle)));
    shader.uniformVec3("light_pos", Light_pos);
    shader.uniformVec3("light.Look_vec", Look_vec);

}