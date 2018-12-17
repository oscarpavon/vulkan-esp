#include"vkpavon.h"
#include <stdexcept>
int main(){
	Aplicacion aplicacion_uno;
	
	try{
	aplicacion_uno.andar();
	}catch (const std::exception &e){
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
