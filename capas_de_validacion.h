#ifndef _Capas_H_ 

#define _Capas_H_

#include<vector>
#include<iostream>
#include<vulkan/vulkan.h>
#include<cstring>

static VKAPI_ATTR VkBool32 VKAPI_CALL  llamada_de_depuracion(
    VkDebugUtilsMessageSeverityFlagBitsEXT          severidad_de_mensaje,
    VkDebugUtilsMessageTypeFlagsEXT                 tipo_de_mensaje,
    const VkDebugUtilsMessengerCallbackDataEXT*     pDatos_de_llamada,
    void*                                           pDatos_de_usuario
){
    if (severidad_de_mensaje & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT){
        std::cout<<"ERROR:";
    }
    
    std::cerr << "Validacion:  " << pDatos_de_llamada->pMessage << std::endl;
    return VK_FALSE;
}

class CapasDeValidacion{

public:
	bool verificar_soporte_de_capas_de_validacion();
	void verificar();

    void configuar(VkInstance &instancia);
    void destruir();

private:
    VkInstance  instancia;
    VkDebugUtilsMessengerEXT llamadas_de_depuracion;
	std::vector<const char*> nombres_de_capas_de_validadcion;
    VkResult CrearExtencionDeDepuracion(
        VkInstance                                          instancia,
        const VkDebugUtilsMessengerCreateInfoEXT*           pInformacionDeCreacion,
        const VkAllocationCallbacks*                        pPosicionador,
        VkDebugUtilsMessengerEXT*                           pLlamadaDeDepuracion
	);

    void DestruirExtencionDeDepuracion(
        VkInstance                                          instancia,
		VkDebugUtilsMessengerEXT                           	LlamadaDeDepuracion,
        const VkAllocationCallbacks*                        pAsignador        
	);
};



#endif
