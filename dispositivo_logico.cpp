#include"dispositivo_logico.h"
#include<vector>
#include<vulkan/vulkan.h>
void Dispositivo::crear(DispositivosFisicos &dispositivos){


	
	
	//Extenciones de dispostivo logico
	const std::vector<const char*> extenciones_de_dispositivo_logico = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME

	};

	uint32_t cantidad_de_extenciones;
	vkEnumerateDeviceExtensionProperties(dispositivos.dispositivo_fisico,nullptr,&cantidad_de_extenciones,nullptr);

	std::vector<VkExtensionProperties> extenciones_disponibles(cantidad_de_extenciones);

	vkEnumerateDeviceExtensionProperties(dispositivos.dispositivo_fisico,nullptr,&cantidad_de_extenciones,extenciones_disponibles.data());
	
	for (unsigned i = 0;i<cantidad_de_extenciones;i++){
		//std::cout << arreglo_d_caracteres_extenciones[i] << std::endl;
		//extenciones.push_back(arreglo_de_caracteres_extenciones[i]);
		//std::cout << extenciones_disponibles[i].extensionName << std::endl;
	}

	
	//fin extenciones
	crear_estructura_de_colas(dispositivos.dispositivo_fisico);
	
	VkDeviceCreateInfo informacion_de_creacion_de_dispositivo = {};
	informacion_de_creacion_de_dispositivo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	informacion_de_creacion_de_dispositivo.queueCreateInfoCount = 1;
	informacion_de_creacion_de_dispositivo.pQueueCreateInfos = &informacion_de_creacion_de_colas;
	
	informacion_de_creacion_de_dispositivo.pEnabledFeatures = &caracteristicas_del_dispositivo_fisico;
	
	informacion_de_creacion_de_dispositivo.enabledLayerCount = 0;
	

	informacion_de_creacion_de_dispositivo.enabledExtensionCount = static_cast<uint32_t>(extenciones_de_dispositivo_logico.size());
	informacion_de_creacion_de_dispositivo.ppEnabledExtensionNames = extenciones_de_dispositivo_logico.data();

	VkResult resultado = vkCreateDevice(dispositivos.dispositivo_fisico,&informacion_de_creacion_de_dispositivo,nullptr,&dispositivo_logico);

	if (resultado != VK_SUCCESS){
	std::cout << "Error al crear dispostivo logico" << std::endl;
	}
	if (resultado == VK_SUCCESS){
	std::cout << "Se creo un dispositvo logico" << std::endl;
	}
	
	vkGetDeviceQueue(dispositivo_logico,indice_de_familia_de_colas,0,&cola_de_graficos);
	vkGetDeviceQueue(dispositivo_logico,indice_de_familia_de_colas,0,&cola_de_presentacion);
}

void Dispositivo::crear_estructura_de_colas(VkPhysicalDevice &gpu){
	{
		uint32_t cantidad_de_familia_de_colas = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(gpu,&cantidad_de_familia_de_colas,nullptr);
		std::vector<VkQueueFamilyProperties> lista_de_propiedades(cantidad_de_familia_de_colas);
		vkGetPhysicalDeviceQueueFamilyProperties(gpu,&cantidad_de_familia_de_colas,lista_de_propiedades.data());
		
		
		bool encontrado = false;
		
		for (uint32_t i = 0 ;i < cantidad_de_familia_de_colas ; i++){
				if(lista_de_propiedades[i].queueCount > 0 && lista_de_propiedades[i].queueFlags & VK_QUEUE_GRAPHICS_BIT){
						encontrado = true;
						indice_de_familia_de_colas = i;
				}
		}
		if(!encontrado){
			throw std::runtime_error("No se enconto la cola compatible");
		}else{
			std::cout << "Indice de familia de colas = " << indice_de_familia_de_colas << std::endl;
		}
		
	}
	
	
	informacion_de_creacion_de_colas = {};
	informacion_de_creacion_de_colas.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	informacion_de_creacion_de_colas.queueFamilyIndex = indice_de_familia_de_colas;
	informacion_de_creacion_de_colas.queueCount = 1;
	
	float prioridad_de_cola[] {1.0f};
	
	informacion_de_creacion_de_colas.pQueuePriorities = prioridad_de_cola;

	caracteristicas_del_dispositivo_fisico = {};

	
}
void Dispositivo::destruir(){
	vkDestroyDevice(dispositivo_logico,nullptr);
}
