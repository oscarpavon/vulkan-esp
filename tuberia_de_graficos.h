#ifndef tuberias_h
#define tuberias_h
#include<vulkan/vulkan.h>
#include"vertice.h"

struct BuferDeObjetosUniformes{
		glm::mat4 modelo;
		glm::mat4 vista;
		glm::mat4 proyeccion;
	};

class TuberiaDeGraficos{
public:
    VkPipeline tuberia;
	VkPipelineLayout capa;
    VkRenderPass paso_de_representacion;
    
   
    void crear( VkDevice &dispositivo,
                VkSurfaceCapabilitiesKHR &capacidades_de_superficie,
	            VkFormat &formato,
                VkPipelineShaderStageCreateInfo *etapas_sombreadores );
    void destruir_descriptor_de_disenyo();
private:
    VkDevice dispositivo;
    VkFormat formato;
    VkDescriptorSetLayout descriptor_de_establecimiento_de_disenyo;
    void crear_paso_de_representacion();
    void crear_descriptor_de_establecimiento_de_disenyo();
};

#endif