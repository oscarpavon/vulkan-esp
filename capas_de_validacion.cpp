#include"capas_de_validacion.h"
void CapasDeValidacion::verificar(){
	nombres_de_capas_de_validadcion = {
	"VK_LAYER_LUNARG_standard_validation"
	};

	const bool activar_capas_de_validacion = true;

	if(!verificar_soporte_de_capas_de_validacion()){
		throw std::runtime_error("no se encontro la capa");
	}
}


bool CapasDeValidacion::verificar_soporte_de_capas_de_validacion(){
	std::cout << "Buscando capas de validacion" << std::endl;
	uint32_t cantidad_de_capas;
	
	vkEnumerateInstanceLayerProperties(&cantidad_de_capas,nullptr);
	
	std::vector<VkLayerProperties> capas_disponibles(cantidad_de_capas);
	vkEnumerateInstanceLayerProperties(&cantidad_de_capas,capas_disponibles.data());


	for (const char* nombre_de_capa : nombres_de_capas_de_validadcion){

		bool capa_encontrada = false;
		
		for(const auto& propiedades_de_capa : capas_disponibles){
			if(strcmp(nombre_de_capa, propiedades_de_capa.layerName)==0){
				capa_encontrada = true;
				break;
			}
		}
		if(!capa_encontrada){
			return false;
		}
	}
	
	return true;	
}

VkResult CapasDeValidacion::CrearExtencionDeDepuracion(
    VkInstance                                          instancia,
    const VkDebugUtilsMessengerCreateInfoEXT*           pInformacionDeCreacion,
    const VkAllocationCallbacks*                        pPosicionador,
    VkDebugUtilsMessengerEXT*                           pLlamadaDeDepuracion
){
    auto funcion = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instancia,"vkCreateDebugUtilsMessengerEXT");
    if(funcion != nullptr){
        return funcion(instancia,pInformacionDeCreacion,pPosicionador,pLlamadaDeDepuracion);
    }else{
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

}
void CapasDeValidacion::DestruirExtencionDeDepuracion(
        VkInstance                                          instancia,
		VkDebugUtilsMessengerEXT                           	LlamadaDeDepuracion,
        const VkAllocationCallbacks*                        pAsignador
        
	){
		auto funcion = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instancia,"vkDestroyDebugUtilsMessengerEXT");
		if(funcion != nullptr){
			funcion(instancia,LlamadaDeDepuracion,pAsignador);
		}

	}

void CapasDeValidacion::configuar(VkInstance &instancia){
    
	this->instancia = instancia;
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = llamada_de_depuracion;
    createInfo.pUserData = nullptr; // Optional 
    CrearExtencionDeDepuracion(instancia,&createInfo,nullptr,&llamadas_de_depuracion);
	
	
}

void CapasDeValidacion::destruir(){
	DestruirExtencionDeDepuracion(instancia,llamadas_de_depuracion,nullptr);
}

