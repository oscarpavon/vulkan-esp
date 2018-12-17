
#ifndef vkpavon_h
#define vkpavon_h
#include<iostream>

#include<cstdlib>
#include<stdexcept>
#include<vector>
#include <limits>
#include<glm/glm.hpp>
#include"vertice.h"

#include"capas_de_validacion.h"
#include"instancia_vulkan.h"
#include"dispositivo_fisico.h"
#include"dispositivo_logico.h"
#include"cadena_de_intercambio.h"
#include"archivos.h"
#include"tuberia_de_graficos.h"
#include"bufer.h"


class Aplicacion{

public:
	void andar();
	Ventana ventana_principal;
	InstanciaVulkan instancia_vulkan_nueva;	
	std::vector<VkImage> imagenes_en_cadena_de_intercambio;
	std::vector<VkImageView> vistas_de_imagenes_en_cadena_de_intercambio;
	VkRenderPass paso_de_representacion;
	VkDevice dispositivo;
	Dispositivo dispositivo_nuevo;
	std::vector<VkFramebuffer> bufer_de_cuadros;
	VkPipeline tuberias_de_graficos;
	VkPipelineLayout capa_de_tuberia;
	VkCommandPool pozo_de_comandos;

	CadenaDeIntercambio cadena_nueva;
	std::vector<VkCommandBuffer> bufer_de_comandos;
	TuberiaDeGraficos tuberia_de_graficos;
	
private:
	void iniciar_ventana();
	void iniciar_vulkan();
	CapasDeValidacion capas;
	void bucle_principal();
	void limpiar();
	void crear_vista_de_imagenes_en_cadena_de_intercambio(
				VkDevice dispositivo, 
				VkFormat formato);
	
	VkPipelineShaderStageCreateInfo* crear_etapas_de_sombreadores(VkPipelineShaderStageCreateInfo etapas[]);

	void crear_paso_de_representacion(VkDevice dispositivo);
	VkShaderModule crear_modulo_sombreador(VkDevice dispositivo, const std::vector<char> & codigo);

	
	VkShaderModule modulo_sombreador_de_vertices;
	VkShaderModule modulo_sombreador_de_pixeles;
	
	void crear_bufer_de_comandos(int indice_de_familia_de_colas);

	void dibujar_cuadro();
	void crear_semaforos();
	const int cuadros_maximos_en_vuelo = 2;
	//std::vector<VkSemaphore> semaforo_para_imagenes_disponibles;
	//std::vector<VkSemaphore> semaforo_para_representacion_finalizada;

	VkSemaphore semaforo_para_imagenes_disponibles;
	VkSemaphore semaforo_para_representacion_finalizada;

	void crear_bufer_de_vertices();
	Bufer bufer_de_vertice;
	VkBuffer bufer_de_vertices;

	const std::vector<Vertice> vertices = {
		{{0.5f,-0.5f}},
		{{0.5f,0.5f}},
		{{-0.5f,0.5f}}
		
	};

	

};
#endif
