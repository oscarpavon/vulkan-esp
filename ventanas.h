#ifndef _VentanasIncluida_

#define _VentanasIncluida_

#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>
#include"instancia_vulkan.h"
#include<iostream>

class Ventana{

public:
	VkSurfaceKHR superficie;
	Ventana();
	~Ventana();
	GLFWwindow* ventana_creada;
	
	void cerrar();

	void crear_ventana();
	
	void crear_superficie_de_ventana(VkInstance &instancia_proporcionada);

private:
	void manejar_entrada();

	
};

static void llamada_a_tecla(GLFWwindow * ventana, int tecla, int codigo_escaneado, int accion, int modificador){
	std::cout << "Tecla presionada" << std::endl;
}

#endif
