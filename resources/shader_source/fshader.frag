#version 330 core
out vec4 FragColor;
 
in vec3 ob_color;
in vec3 face_normal;
in vec3 light_vec;
in vec3 camera_vec;

in vec2 Face;
in vec2 TexCoord;

struct Material{
    sampler2D texture_defuse_1;
    sampler2D texture_defuse_2;
    sampler2D texture_defuse_3;
    sampler2D texture_defuse_4;
    sampler2D texture_defuse_5;
    sampler2D texture_defuse_6;
    sampler2D texture_specular_1;
    sampler2D texture_specular_2;
    sampler2D texture_specular_3;
    sampler2D texture_specular_4;
    sampler2D texture_specular_5;
    sampler2D texture_specular_6;

    vec3 ambient;
    float shininess;

    float Contant;
    float linear;
    float quadratic;
};

struct Light {
    vec3 specular;
    vec3 defuse;
    vec3 ambient;

    float CutOff;
    float outerCutOff;
    vec3 Look_vec;
};

uniform Material material;
uniform Light light;
uniform vec3 light_color;

void main()
{
    vec3 defuse_texture;
    vec3 specular_texture;

    if      (Face.x == 0){defuse_texture =  texture(material.texture_defuse_1, TexCoord).rgb; specular_texture = texture(material.texture_specular_1, TexCoord).rgb;}
    else if (Face.x == 1){defuse_texture =  texture(material.texture_defuse_2, TexCoord).rgb; specular_texture = texture(material.texture_specular_2, TexCoord).rgb;}
    else if (Face.x == 2){defuse_texture =  texture(material.texture_defuse_3, TexCoord).rgb; specular_texture = texture(material.texture_specular_3, TexCoord).rgb;}
    else if (Face.x == 3){defuse_texture =  texture(material.texture_defuse_4, TexCoord).rgb; specular_texture = texture(material.texture_specular_4, TexCoord).rgb;}
    else if (Face.x == 4){defuse_texture =  texture(material.texture_defuse_5, TexCoord).rgb; specular_texture = texture(material.texture_specular_5, TexCoord).rgb;}
    else if (Face.x == 5){defuse_texture =  texture(material.texture_defuse_6, TexCoord).rgb; specular_texture = texture(material.texture_specular_6, TexCoord).rgb;}

    float spotlight_check = dot(normalize(-light_vec), normalize(light.Look_vec));
    float epsilon = light.CutOff - light.outerCutOff;
    // float intensity = clamp((light.outerCutOff - spotlight_check)/ epsilon, 0.0, 1.0);
    // smoother edge.
    float intensity = smoothstep(0.0, 1.0, (light.outerCutOff -spotlight_check) / epsilon);


    float light_distance = length(light_vec);
    float attenuation = 1/(material.Contant + material.linear*light_distance + material.quadratic*(light_distance * light_distance));

    vec3 ambient = defuse_texture* light.ambient;

    vec3 norm = normalize(face_normal);
    float defuse_streght =  max(dot(normalize(light_vec), norm), 0);
    vec3 difuse = defuse_streght * defuse_texture * light.defuse ;

    vec3 reflect_vec = normalize(reflect(-normalize(light_vec), norm));
    float reflect_check = dot(reflect_vec, norm);
    float negative_check = max(reflect_check, 0) / reflect_check;
    float specular = pow(max(dot(reflect_vec, normalize(camera_vec)) * negative_check, 0), material.shininess);
    vec3 specular_vec = specular * specular_texture * light.specular ;

    

    vec3 ourColor = (ambient + difuse );

    FragColor = vec4(ourColor, 1.0);
}