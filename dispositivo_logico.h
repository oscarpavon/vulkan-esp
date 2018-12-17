#ifndef dispositivo_logico_h
#define dispositivo_logico_h
#include<iostream>
#include<vulkan/vulkan.h>
#include"dispositivo_fisico.h"
class Dispositivo{

public:
//	Dispositivo();
//	~Dispositivo();	
	VkDevice dispositivo_logico;
	void crear(DispositivosFisicos &dispositivos);
	void destruir();
	int32_t indice_de_familia_de_colas = 0;
	VkQueue cola_de_graficos;
	VkQueue cola_de_presentacion;

private:
	void crear_estructura_de_colas(VkPhysicalDevice &gpu);
	VkDeviceQueueCreateInfo informacion_de_creacion_de_colas;
	VkPhysicalDeviceFeatures caracteristicas_del_dispositivo_fisico;
	
};
#endif
