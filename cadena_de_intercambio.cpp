#include"cadena_de_intercambio.h"

void CadenaDeIntercambio::crear(VkDevice &dispositivo_logico,VkPhysicalDevice &dispositivo_fisico, VkSurfaceKHR &superficie_de_ventana){

	this->dispositivo_fisico = dispositivo_fisico;
	this->superficie = superficie_de_ventana;
	this->dispositivo_logico = dispositivo_logico;

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dispositivo_fisico,superficie_de_ventana,&capacidades_de_superfice);
	obtener_y_mostrar_capacidades_de_superficie();

	obtener_los_formatos_de_superfice();
	obtener_los_modos_de_presentacion();

	VkSwapchainCreateInfoKHR informacion_de_creacion;
	VkPresentModeKHR modo_de_presentacion = VK_PRESENT_MODE_FIFO_KHR;

	informacion_de_creacion.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	informacion_de_creacion.pNext = NULL;
	informacion_de_creacion.flags = 0;
	informacion_de_creacion.surface = superficie;
	informacion_de_creacion.minImageCount = capacidades_de_superfice.minImageCount;
	informacion_de_creacion.imageFormat = formatos[0].format;
	informacion_de_creacion.imageColorSpace = formatos[0].colorSpace;
	informacion_de_creacion.imageExtent = capacidades_de_superfice.currentExtent;
	//informacion_de_creacion.imageExtent.width = capacidades_de_superfice.currentExtent.width;
	//informacion_de_creacion.imageExtent.height = capacidades_de_superfice.currentExtent.height;
	informacion_de_creacion.imageArrayLayers = 1;
	informacion_de_creacion.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	informacion_de_creacion.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	informacion_de_creacion.queueFamilyIndexCount = 0;
	informacion_de_creacion.pQueueFamilyIndices = nullptr;
	informacion_de_creacion.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
	informacion_de_creacion.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;	
	informacion_de_creacion.presentMode = modo_de_presentacion;
	informacion_de_creacion.clipped = VK_TRUE;
	informacion_de_creacion.oldSwapchain = VK_NULL_HANDLE;

	
	this->info_de_creacion = informacion_de_creacion;

  	VkResult resultado =	vkCreateSwapchainKHR(dispositivo_logico,&informacion_de_creacion,nullptr,&cadena);
	std::cout << resultado << std::endl;
	if(resultado != VK_SUCCESS){
	std::cout << "Error al crear la cadena de intercambio " << std::endl;
	}
}

void CadenaDeIntercambio::obtener_los_formatos_de_superfice(){
	
	uint32_t cantidad_de_formatos;
	
	vkGetPhysicalDeviceSurfaceFormatsKHR(dispositivo_fisico,superficie,&cantidad_de_formatos,nullptr);
	
	std::cout << "Cantidad de formatos de superfice: " << cantidad_de_formatos << std::endl;
	formatos.resize(cantidad_de_formatos);
	
	
	vkGetPhysicalDeviceSurfaceFormatsKHR(dispositivo_fisico,superficie,&cantidad_de_formatos,formatos.data());

	
}

void CadenaDeIntercambio::obtener_los_modos_de_presentacion()
{
	
	uint32_t cantidad_modos_de_presentacion;

	vkGetPhysicalDeviceSurfacePresentModesKHR(dispositivo_fisico,superficie,&cantidad_modos_de_presentacion,nullptr);
	
		std::cout << "Cantidad de modos de presentacion: " << cantidad_modos_de_presentacion << std::endl;

	modos_de_presentacion.resize(cantidad_modos_de_presentacion);
	 	
	vkGetPhysicalDeviceSurfacePresentModesKHR(dispositivo_fisico,superficie,&cantidad_modos_de_presentacion,modos_de_presentacion.data());
	
	std::cout << "Modos de presentacion:" << std::endl;
	for(uint32_t i = 0; i < cantidad_modos_de_presentacion ; i++){
		
		std::cout << modos_de_presentacion[i] << std::endl;
	}

}

void CadenaDeIntercambio::obtener_y_mostrar_capacidades_de_superficie(){
	std::cout << "\t "<< "Informacion de superficie " << std::endl;
	std::cout << "Cantidad de imagenes minimas " << capacidades_de_superfice.minImageCount << std::endl;

	

}

void CadenaDeIntercambio::destruir(){
	vkDestroySwapchainKHR(dispositivo_logico,cadena,nullptr);
}


