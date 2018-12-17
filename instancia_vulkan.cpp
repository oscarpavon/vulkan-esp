#include"instancia_vulkan.h"
#include<vector>
InstanciaVulkan::InstanciaVulkan(){
}
InstanciaVulkan::~InstanciaVulkan(){

}
void InstanciaVulkan::crear(){
	
	conseguir_e_imprimir_extenciones();
	
	//crear_estructuras_de_datos_de_instancia_vulkan();
	//conseguir_extenciones();


	informacion_aplicacion = {};
	informacion_aplicacion.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	informacion_aplicacion.pApplicationName = "Vulkan PRO";
	informacion_aplicacion.applicationVersion = VK_MAKE_VERSION(1,0,0);
	informacion_aplicacion.pEngineName = "Sin motor";
	informacion_aplicacion.engineVersion = VK_MAKE_VERSION(1,0,0);
	informacion_aplicacion.apiVersion = VK_API_VERSION_1_1; 


	const std::vector<const char*> capas_de_validacion = {
    "VK_LAYER_LUNARG_standard_validation"
    };
    std::vector<const char*> extenciones = {
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME
        };
	extenciones.push_back("VK_KHR_xcb_surface");
	extenciones.push_back("VK_KHR_surface");
	extenciones.push_back("VK_EXT_debug_report");
	
	

	VkInstanceCreateInfo informacion_de_creacion_de_instancia = {}; 
	informacion_de_creacion_de_instancia.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	informacion_de_creacion_de_instancia.pApplicationInfo = &informacion_aplicacion;
	informacion_de_creacion_de_instancia.enabledExtensionCount = static_cast<uint32_t>(extenciones.size());
    informacion_de_creacion_de_instancia.ppEnabledExtensionNames = extenciones.data();
    informacion_de_creacion_de_instancia.enabledLayerCount = static_cast<uint32_t>(capas_de_validacion.size());
    informacion_de_creacion_de_instancia.ppEnabledLayerNames = capas_de_validacion.data();
	
	VkResult resultado;
	resultado =  vkCreateInstance(&informacion_de_creacion_de_instancia , nullptr , &instancia);
		
	if(resultado != VK_SUCCESS){
		
		throw std::runtime_error("No se pudo crear la instancia vulkan");
	}
	else
		std::cout << "Se creo un instancia de vulkan" << std::endl;

}
void InstanciaVulkan::crear_estructuras_de_datos_de_instancia_vulkan(){
	
	
/* 
	informacion_aplicacion = {};
	informacion_aplicacion.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	informacion_aplicacion.pApplicationName = "Vulkan PRO";
	informacion_aplicacion.applicationVersion = VK_MAKE_VERSION(1,0,0);
	informacion_aplicacion.pEngineName = "Sin motor";
	informacion_aplicacion.engineVersion = VK_MAKE_VERSION(1,0,0);
	informacion_aplicacion.apiVersion = VK_API_VERSION_1_1; */
	
	informacion_de_creacion_de_instancia = {};
	/* informacion_de_creacion_de_instancia.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	informacion_de_creacion_de_instancia.pApplicationInfo = &informacion_aplicacion; */





	const std::vector<const char*> capas_de_validacion = {
    "VK_LAYER_LUNARG_standard_validation"
    };
    std::vector<const char*> extenciones = {
            VK_EXT_DEBUG_UTILS_EXTENSION_NAME
        };

	informacion_de_creacion_de_instancia.enabledExtensionCount = static_cast<uint32_t>(extenciones.size());
    informacion_de_creacion_de_instancia.ppEnabledExtensionNames = extenciones.data();
    informacion_de_creacion_de_instancia.enabledLayerCount = static_cast<uint32_t>(capas_de_validacion.size());
    informacion_de_creacion_de_instancia.ppEnabledLayerNames = capas_de_validacion.data();




	/* //capas de validadacion
	lista_de_capas_de_validacion.push_back("VK_LAYER_LUNARG_standard_validation");
	informacion_de_creacion_de_instancia.enabledLayerCount = lista_de_capas_de_validacion.size();	
	informacion_de_creacion_de_instancia.ppEnabledLayerNames =  lista_de_capas_de_validacion.data(); */	
}

void InstanciaVulkan::conseguir_extenciones(){
	
	uint32_t cantidad_de_extenciones_glfw = 0;
	const char** arreglo_de_caracteres_extenciones;
		
	arreglo_de_caracteres_extenciones = glfwGetRequiredInstanceExtensions(&cantidad_de_extenciones_glfw);

	std::vector<const char*> extenciones_para_agregar(cantidad_de_extenciones_glfw);
	extenciones_para_agregar.push_back("VK_KHR_surface");
	extenciones_para_agregar.push_back("VK_KHR_xcb_surface");
	//extenciones_para_agregar.push_back("VK_EXT_debug_report");
	//extenciones_para_agregar.push_back("VK_EXT_debug_utils");

	auto extenciones = ConseguirExtenciones();
	//extenciones.push_back("VK_EXT_debug_utils");
	

	informacion_de_creacion_de_instancia.enabledExtensionCount = cantidad_de_extenciones_glfw;
	informacion_de_creacion_de_instancia.ppEnabledExtensionNames = arreglo_de_caracteres_extenciones;	

	
}



void InstanciaVulkan::conseguir_e_imprimir_extenciones(){
	uint32_t cantidad_de_extenciones_de_instancia = 0;
	vkEnumerateInstanceExtensionProperties(nullptr,&cantidad_de_extenciones_de_instancia,nullptr);
	std::vector<VkExtensionProperties> extenciones_encontradas (cantidad_de_extenciones_de_instancia);
	vkEnumerateInstanceExtensionProperties(nullptr,&cantidad_de_extenciones_de_instancia,extenciones_encontradas.data());

	std::cout << "Extenciones disponibles de instancia: " << std::endl;
	for(const auto& extencion : extenciones_encontradas){
		std::cout << "\t" << extencion.extensionName << std::endl;
	}

}

void InstanciaVulkan::destruir(){
	vkDestroyInstance(instancia,nullptr);
}


std::vector<const char*> InstanciaVulkan::ConseguirExtenciones()
    {
        

        uint32_t CantidadExtencionesGLFW = 0;
        const char** ExtencionesGLFW;
        ExtencionesGLFW = glfwGetRequiredInstanceExtensions(&CantidadExtencionesGLFW);

		std::vector<const char*>extenciones(ExtencionesGLFW,ExtencionesGLFW+CantidadExtencionesGLFW);
                

       
        //extenciones.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
       
        return extenciones;
    }