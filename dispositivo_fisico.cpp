#include"dispositivo_fisico.h"
#include"iostream"
#include<vulkan/vulkan.h>
void DispositivosFisicos::seleccionar_dispositivo(InstanciaVulkan &instancia){
	uint32_t numero_del_disposito = 1;
	VkPhysicalDevice dispositivo_fisico_nuevo = VK_NULL_HANDLE;
		std::cout << "Se va selecioar un dispositvo fisico" << std::endl;

	std::vector<VkPhysicalDevice> dispositivos(numero_del_disposito);
	vkEnumeratePhysicalDevices(instancia.instancia,&numero_del_disposito,dispositivos.data());

	dispositivo_fisico = dispositivos[0];
}
void DispositivosFisicos::obtener_familia_de_colas(){
		uint32_t cantidad_de_familia_de_colas = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(dispositivo_fisico,&cantidad_de_familia_de_colas,nullptr);
		std::vector<VkQueueFamilyProperties> lista_de_propiedades(cantidad_de_familia_de_colas);
		vkGetPhysicalDeviceQueueFamilyProperties(dispositivo_fisico,&cantidad_de_familia_de_colas,lista_de_propiedades.data());

		std::cout << "Cantidad de familia de colas: " << cantidad_de_familia_de_colas << std::endl;
		for (const auto& familia_de_cola : lista_de_propiedades){
			if(familia_de_cola.queueFlags == VK_QUEUE_GRAPHICS_BIT){
				std::cout << "\tColas de graficos" << std::endl;

			}
			if(familia_de_cola.queueFlags == VK_QUEUE_COMPUTE_BIT){
				std::cout << "\tColas de computo" << std::endl;

			}
			if(familia_de_cola.queueFlags == VK_QUEUE_TRANSFER_BIT){
				std::cout << "\tColas de transferencia" << std::endl;

			}
			if(familia_de_cola.queueFlags == VK_QUEUE_FLAG_BITS_MAX_ENUM){
				std::cout << "\tColas de banderas" << std::endl;

			}
			std::cout << "\t"<< familia_de_cola.queueFlags << std::endl;

		}

		bool encontrado;
		for (uint32_t i = 0 ;i < cantidad_de_familia_de_colas ; i++){
				if(lista_de_propiedades[i].queueCount > 0 && lista_de_propiedades[i].queueFlags & VK_QUEUE_GRAPHICS_BIT){
						encontrado = true;
						//indice_de_familia_de_colas = i;
				}
		}
		if(!encontrado){
			throw std::runtime_error("No se enconto la cola compatible");
		}

}