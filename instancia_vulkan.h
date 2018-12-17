//#include"vkpavon.h"

#ifndef InstanciaVulkan_H
#define InstanciaVulkan_H
#include"ventanas.h"
#include<vector>
class InstanciaVulkan{
public:
	InstanciaVulkan();
	~InstanciaVulkan();
	
	VkInstance instancia;
	void crear();
	void destruir();
private:
	VkApplicationInfo informacion_aplicacion;
	VkInstanceCreateInfo informacion_de_creacion_de_instancia;
	void crear_estructuras_de_datos_de_instancia_vulkan();
	void conseguir_extenciones();
	std::vector<const char*>		lista_de_capas_de_validacion;	
	std::vector<const char*>		lista_de_extenciones;	

	void conseguir_e_imprimir_extenciones();
	std::vector<const char*> ConseguirExtenciones();

};
#endif
