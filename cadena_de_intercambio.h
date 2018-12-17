#ifndef cadena_h
#define cadena_h
#include<vulkan/vulkan.h>
#include<vector>
#include<iostream>

class CadenaDeIntercambio{
public:
	VkSwapchainKHR cadena;
	
	VkSurfaceCapabilitiesKHR capacidades_de_superfice;
	void crear(VkDevice &dispositivo_logico,VkPhysicalDevice &dispositivo_fisico, VkSurfaceKHR &superficie_de_ventana);
	void destruir();
	VkSwapchainCreateInfoKHR info_de_creacion;

	std::vector<VkSurfaceFormatKHR> formatos;
private:
	VkDevice dispositivo_logico;
	
	VkPhysicalDevice dispositivo_fisico;
	VkSurfaceKHR superficie;

	VkExtent2D extencion_de_la_ventana_donde_dibujar;	
	
	std::vector<VkPresentModeKHR> modos_de_presentacion;
	
	void obtener_los_formatos_de_superfice();
	void obtener_los_modos_de_presentacion();	

	void obtener_y_mostrar_capacidades_de_superficie();

};


#endif
