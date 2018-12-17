#ifndef vertice_h
#define vertice_h
#include<glm/glm.hpp>
#include<vulkan/vulkan.h>

struct Vertice{
		glm::vec2 posicion;

		static VkVertexInputBindingDescription conseguir_descripcion_de_enlace(){
			VkVertexInputBindingDescription descripcion_de_enlace = {};
			descripcion_de_enlace.binding = 0;
			descripcion_de_enlace.stride = sizeof(Vertice);
			descripcion_de_enlace.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return descripcion_de_enlace;
		}
		static VkVertexInputAttributeDescription conseguir_descripcion_de_atributos(){
			VkVertexInputAttributeDescription descripcion_del_atributo = {};
			descripcion_del_atributo.binding = 0;
			descripcion_del_atributo.location = 0;
			descripcion_del_atributo.format = VK_FORMAT_R32G32_SFLOAT;
			descripcion_del_atributo.offset = offsetof(Vertice,posicion);
			return descripcion_del_atributo;
		}
	};
#endif