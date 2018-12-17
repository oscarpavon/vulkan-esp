#include"bufer.h"

void Bufer::crear(VkDevice &dispositivo, VkBuffer &bufer){
    this->dispositivo = dispositivo;
    this->vk_bufer = bufer;

    asignar_memoria(bufer);

}

uint32_t Bufer::encontrar_tipo_de_memoria(uint32_t filtro_de_tipo, VkMemoryPropertyFlags propiedades){

    for (uint32_t i = 0; i < propiedades_de_memoria.memoryTypeCount; i++){
        if(filtro_de_tipo & (1 << i) && (propiedades_de_memoria.memoryTypes[i].propertyFlags & propiedades) == propiedades ){
            return i;
        }
   }
    std::cout << "No se encontro una memoria compatible" << std::endl;
}

void Bufer::conseguir_propiedades_de_momoria_fisica(VkPhysicalDevice &gpu){
    
    vkGetPhysicalDeviceMemoryProperties(gpu,&propiedades_de_memoria);

}

void Bufer::asignar_memoria(VkBuffer bufer){
    VkMemoryRequirements requerimiento_de_memoria;
	vkGetBufferMemoryRequirements(dispositivo,bufer,&requerimiento_de_memoria);

	VkMemoryAllocateInfo informacion_de_asignacion_de_memoria = {};
	informacion_de_asignacion_de_memoria.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	informacion_de_asignacion_de_memoria.allocationSize = requerimiento_de_memoria.size;
    informacion_de_asignacion_de_memoria.memoryTypeIndex = encontrar_tipo_de_memoria(
                                                                requerimiento_de_memoria.memoryTypeBits,
                                                                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | 
                                                                VK_MEMORY_PROPERTY_HOST_COHERENT_BIT );                                                                

    VkResult resultado = vkAllocateMemory(dispositivo,&informacion_de_asignacion_de_memoria ,nullptr,&memoria_de_dispostivo);
    
    vkBindBufferMemory(dispositivo,vk_bufer,memoria_de_dispostivo,0);
}

void Bufer::destruir(){
    vkDestroyBuffer(dispositivo,vk_bufer,nullptr);
    vkFreeMemory(dispositivo,memoria_de_dispostivo,nullptr);
}