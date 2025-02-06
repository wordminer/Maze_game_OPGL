#include "handle_data.hpp"
#include "camera.hpp"
#include "texture.hpp"
#include "block.hpp"
#include "const.hpp"
#include "handle_data.hpp"
#include "materials.hpp"
#include "map.hpp"
#include "map_matrix.hpp"


#include "stb_image.h"


int main(int argc, char* argv[]) {
    Window screen("hello", WIDTH_WIN, HIGHT_WIN, SDL_INIT_VIDEO, SDL_WINDOW_OPENGL);
    ShaderProgram Shader_rec(vshader_path, 
                             fshader_path);
    
    glEnable(GL_DEPTH_TEST);

    Shader_rec.activate();

    bool running = true;
    SDL_Event event;

    glm::vec3 Camera_pos = { 1.0f, 0.25f, 1.0f };
    Camera Main_view(Camera_pos, 45, 0.1, 0.1, 0.1f, 300.0f);
    Main_view.set_viewrange(Shader_rec, WIDTH_WIN, HIGHT_WIN);
    screen.swap_mouse(WIDTH_WIN / 2, HIGHT_WIN / 2);

    const char* container_defuse[] = {"resources/image/container/container2.jpg","resources/image/container/container2.jpg","resources/image/container/container2.jpg","resources/image/container/container2.jpg","resources/image/container/container2.jpg","resources/image/container/container2.jpg"};
    const char* container_specular[] = {"resources/image/container/container2_specular.jpg","resources/image/container/container2_specular.jpg","resources/image/container/container2_specular.jpg","resources/image/container/container2_specular.jpg","resources/image/container/container2_specular.jpg","resources/image/container/container2_specular.jpg"};
    Material container = Material(container_specular, container_defuse,
                            glm::vec3(0.005, 0.005, 0.005), 8);
        
    Light light{
        glm::vec3(0.1, 0.1, 0.1),
        glm::vec3(1, 1, 1),
        glm::vec3(0.1, 0.1, 0.1),
        20.0f, 18.0f
    };    


    float Angle_rotate[] = {0,0,0};

    
    Maze_map Maze = {300,300,glm::ivec3(5,0,5), glm::ivec3(99,0,98)};
    Maze.reneration_map_matrix();
    Map maze_map(Maze.Map);

    // Block sunlight(light_coord, 0.5, 0.5, 0.5);
    // sunlight.Create_block(false, Block_tex, face_create_key, glm::vec3(1, 1, 1), normal_face_vector);

    Graphic_data data;
    // maze_map.update_chunk(Main_view.Camera_pos, 5, data);
    // buffer_data(test.Block_vertices, data);
    
    while (running) {
        Main_view.control_mouse(screen, WIDTH_WIN, HIGHT_WIN);
        Main_view.control_moving();
        maze_map.update_chunk(Main_view.Camera_pos, 10, data);


        //Angle_rotate[1] += 0.1;
        //SDL_GetMouseState(&mouse_current_x, &mouse_current_y);
        screen.clear_color(SKY_COLOR.x, SKY_COLOR.y, SKY_COLOR.z, SKY_COLOR.a);
        Shader_rec.activate();

        Main_view.set_camera_pos(Shader_rec);
        Shader_rec.uniformVec3("camera_pos", Main_view.Camera_pos); 
        set_light_uniform(Shader_rec, light, Main_view.Camera_pos, Main_view.Target_point);
        set_material_uniform(Shader_rec, container);
        // for (int i = 0; i < 5; i++ ){    
        Main_view.set_position(Shader_rec, glm::vec3(0,0,0), Angle_rotate, vector_rotate);
        
        maze_map.render(data);

        while (SDL_PollEvent(&event)) {
            if (SDL_QUIT == event.type) {
                running = false;
                SDL_Quit();
            }
            if (SDL_KEYDOWN == event.type) {
                if (SDL_SCANCODE_TAB == event.key.keysym.scancode) {
                    if (SDL_GetRelativeMouseMode()) {
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                    }
                    else {
                        screen.swap_mouse(WIDTH_WIN / 2, HIGHT_WIN / 2);
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                    }
                }
            }
        }        
        screen.swap_buffer();
    }

    Shader_rec.purge();
    return 0;
}

