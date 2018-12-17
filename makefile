compilador = g++ -g 
vulkan = vkpavon.o instancia_vulkan.o dispositivo_fisico.o dispositivo_logico.o cadena_de_intercambio.o tuberia_de_graficos.o
objetos = ventanas.o 
librerias = -lvulkan -lglfw

principal: principal.cpp $(objetos) $(vulkan)
	$(compilador) -o vulkan capas_de_validacion.cpp bufer.cpp principal.cpp $(objetos) $(vulkan) $(librerias)

vkpavon.o: vkpavon.cpp vkpavon.h 
	$(compilador) -c vkpavon.cpp 


tuberia_de_graficos.o: tuberia_de_graficos.h tuberia_de_graficos.cpp
	$(compilador) -c tuberia_de_graficos.cpp 
	
cadena_de_intercambio.o: cadena_de_intercambio.cpp cadena_de_intercambio.h
	$(compilador) -c cadena_de_intercambio.cpp

dispositivo_logico.o: dispositivo_logico.cpp dispositivo_logico.h
	$(compilador) -c dispositivo_logico.cpp

dispositivo_fisico.o: dispositivo_fisico.cpp dispositivo_fisico.h
	$(compilador) -c dispositivo_fisico.cpp
ventanas.o: ventanas.cpp ventanas.h
	$(compilador) -c ventanas.cpp

instancia_vulkan.o: instancia_vulkan.cpp instancia_vulkan.h
	$(compilador) -c instancia_vulkan.cpp

limpiar:
	rm -rf *.o
