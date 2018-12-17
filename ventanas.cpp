#include"ventanas.h"
Ventana::Ventana(){

}
Ventana::~Ventana(){

}
void Ventana::crear_ventana(){
	glfwInit();
	
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE,GLFW_FALSE);
	
	ventana_creada = glfwCreateWindow(100,100,"Ventana1",nullptr,nullptr);
	
	manejar_entrada();
}
void Ventana::cerrar(){
	glfwDestroyWindow(ventana_creada);
	
	glfwTerminate();
}
void Ventana::crear_superficie_de_ventana(VkInstance &instancia_proporcionada){
	VkResult resultado =  glfwCreateWindowSurface(instancia_proporcionada,ventana_creada,NULL,&superficie);
	if (resultado != VK_SUCCESS){
		std::cout << "No se creo la superficie"<< std::endl;
	}
}

void Ventana::manejar_entrada(){
	glfwSetKeyCallback(this->ventana_creada,llamada_a_tecla);
}


