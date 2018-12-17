#ifndef bufer_h
#define bufer_h
#include<vulkan/vulkan.h>
#include<iostream>

class Bufer{
    public:
        void crear(VkDevice &dispositivo, VkBuffer &bufer);
        void conseguir_propiedades_de_momoria_fisica(VkPhysicalDevice &gpu);
        VkDeviceMemory memoria_de_dispostivo;
        void destruir();
    private:
        VkDevice dispositivo;
        VkBuffer vk_bufer;
        void asignar_memoria(VkBuffer bufer);
        uint32_t encontrar_tipo_de_memoria(uint32_t filtro_de_tipo, VkMemoryPropertyFlags propiedades);

        VkPhysicalDeviceMemoryProperties propiedades_de_memoria;
        
        
        void asignar_memoria();

};

#endif