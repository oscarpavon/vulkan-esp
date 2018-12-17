#ifndef Ventans_h
#define Ventans_h
#include"ventanas.h"
#include"instancia_vulkan.h"
#include<vector>
class DispositivosFisicos{

public:
	VkPhysicalDevice dispositivo_fisico;
	void seleccionar_dispositivo(InstanciaVulkan &instancia);
	void obtener_familia_de_colas();

};
#endif
