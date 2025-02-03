#include "block.hpp"

Block::Block(){
}

void Block::Create_block(const int face_key[], glm::vec3 Color,glm::fvec3 face_vector[], glm::fvec2 Tex_coord[], glm::fvec3 mPosition, float x_side, float y_side, float z_side){
    int cout = 0 ;
    Block_coord.clear();
   
    for (int z_axis = -1; z_axis <= 1; z_axis += 2){
    for (int y_axis = -1; y_axis <= 1; y_axis += 2){
    for (int x_axis = -1; x_axis <= 1; x_axis += 2){
        float x_coord = x_axis * x_side/2;
        float y_coord = y_axis * y_side/2;
        float z_coord = z_axis * z_side/2;
        Block_coord.insert(Block_coord.end(),glm::vec3(x_coord, y_coord, z_coord));
        cout ++;
        //std::cout<< x_coord<< y_coord<< z_coord << std::endl;
    }}}
    
    for (int face = 0; face < 6; face++) {
        for (int triangle = 0; triangle < 2; triangle ++){
            int start_key = face * 6 + triangle * 3;
            //std::cout<<start_key;
            Vertex v0, v1, v2;
            v0 = Vertex(Block_coord[face_key[start_key]], Color, face   , face_vector[face], Tex_coord[triangle*3]);
            v1 = Vertex(Block_coord[face_key[start_key+ 1]], Color, face, face_vector[face], Tex_coord[triangle*3 + 1]);
            v2 = Vertex(Block_coord[face_key[start_key+ 2]], Color, face, face_vector[face], Tex_coord[triangle*3 + 2]);
            Block_vertices.insert(Block_vertices.end(),{v0, v1, v2});
            // std::cout<< v0.m_pos.x<< v0.m_pos.y<< v0.m_pos.z<< std::endl;
            // std::cout<< v1.m_pos.x<< v1.m_pos.y<< v1.m_pos.z<< std::endl;
            // std::cout<< v2.m_pos.x<< v2.m_pos.y<< v2.m_pos.z<< std::endl;
        }
    }
    // std::cout << (GLsizeiptr)(Block_vertices.size() * sizeof(Vertex));
    // std::cout<< Block_vertices.data();
    
}

