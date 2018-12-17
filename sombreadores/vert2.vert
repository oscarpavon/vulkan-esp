#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(binding = 0) uniform BuferDeObjetoUniforme{
    mat4 modelo;
    mat4 vista;
    mat4 proyeccion;
} bou;

layout(location = 0) in vec2 posiones_de_entrada;

out gl_PerVertex{
    vec4 gl_Position;
};


void main(){
    gl_Position = vec4(posiones_de_entrada,0.0,1.0);
}