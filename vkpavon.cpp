#include"vkpavon.h"

void Aplicacion::andar(){
	
	
	std::cout << "Se va crear una ventana" << std::endl;
	iniciar_ventana();

	iniciar_vulkan();
	
	bucle_principal();
	
	limpiar();
	
}
void Aplicacion::iniciar_vulkan(){
	
	
	capas.verificar();

	instancia_vulkan_nueva.crear();

	capas.configuar(instancia_vulkan_nueva.instancia);

	ventana_principal.crear_superficie_de_ventana(instancia_vulkan_nueva.instancia);

	DispositivosFisicos nuevo_dispositivo_fisico;
	nuevo_dispositivo_fisico.seleccionar_dispositivo(instancia_vulkan_nueva);
	nuevo_dispositivo_fisico.obtener_familia_de_colas();
	
	
	
	dispositivo_nuevo.crear(nuevo_dispositivo_fisico);
	dispositivo = dispositivo_nuevo.dispositivo_logico;
	
	VkBool32 soporte_de_presentacion = false;
	vkGetPhysicalDeviceSurfaceSupportKHR(nuevo_dispositivo_fisico.dispositivo_fisico,
										dispositivo_nuevo.indice_de_familia_de_colas,
										ventana_principal.superficie, 
										&soporte_de_presentacion);	

	
	
	cadena_nueva.crear(	dispositivo_nuevo.dispositivo_logico,
						nuevo_dispositivo_fisico.dispositivo_fisico,
						ventana_principal.superficie );

	//Conseguir imagenes en cadena de intercambio
	uint32_t cantidad_de_imagenes_en_cadena = 0;
	vkGetSwapchainImagesKHR(dispositivo_nuevo.dispositivo_logico,cadena_nueva.cadena,&cantidad_de_imagenes_en_cadena,nullptr);
	imagenes_en_cadena_de_intercambio.resize(cantidad_de_imagenes_en_cadena);
	vkGetSwapchainImagesKHR(dispositivo_nuevo.dispositivo_logico,cadena_nueva.cadena,&cantidad_de_imagenes_en_cadena,imagenes_en_cadena_de_intercambio.data() );

	crear_vista_de_imagenes_en_cadena_de_intercambio(
			dispositivo_nuevo.dispositivo_logico,
			cadena_nueva.formatos[0].format	);

	
	VkPipelineShaderStageCreateInfo etapas_de_sombreado[2];
	crear_etapas_de_sombreadores(etapas_de_sombreado);
	tuberia_de_graficos.crear(dispositivo_nuevo.dispositivo_logico,
					cadena_nueva.capacidades_de_superfice,
					cadena_nueva.formatos[0].format,
					etapas_de_sombreado);
	this->tuberias_de_graficos = tuberia_de_graficos.tuberia;
	this->capa_de_tuberia = tuberia_de_graficos.capa;
	this->paso_de_representacion = tuberia_de_graficos.paso_de_representacion;
	vkDestroyShaderModule(dispositivo,modulo_sombreador_de_pixeles,nullptr);
	vkDestroyShaderModule(dispositivo,modulo_sombreador_de_vertices,nullptr);
		


	
	bufer_de_cuadros.resize(vistas_de_imagenes_en_cadena_de_intercambio.size());
	for(size_t i = 0; i < imagenes_en_cadena_de_intercambio.size(); i++){
		VkImageView adjuntos[] = {
			vistas_de_imagenes_en_cadena_de_intercambio[i]
		};

		VkFramebufferCreateInfo bufer_de_cuadros_Informacion_de_creacion = {};
		bufer_de_cuadros_Informacion_de_creacion.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		bufer_de_cuadros_Informacion_de_creacion.renderPass = paso_de_representacion;
		bufer_de_cuadros_Informacion_de_creacion.attachmentCount = 1;
		bufer_de_cuadros_Informacion_de_creacion.pAttachments = adjuntos;
		bufer_de_cuadros_Informacion_de_creacion.width = cadena_nueva.capacidades_de_superfice.currentExtent.width;
		bufer_de_cuadros_Informacion_de_creacion.height = cadena_nueva.capacidades_de_superfice.currentExtent.height;
		bufer_de_cuadros_Informacion_de_creacion.layers = 1;

		VkResult resutlado = vkCreateFramebuffer(	dispositivo_nuevo.dispositivo_logico,
						&bufer_de_cuadros_Informacion_de_creacion,
						nullptr,
						&bufer_de_cuadros[i]);		
	}
	bufer_de_vertice.conseguir_propiedades_de_momoria_fisica(nuevo_dispositivo_fisico.dispositivo_fisico);
	crear_bufer_de_vertices();
	crear_bufer_de_comandos(dispositivo_nuevo.indice_de_familia_de_colas);

	//crear_semaforos();
	
}

void Aplicacion::bucle_principal(){
	
	while(!glfwWindowShouldClose(ventana_principal.ventana_creada)){
		glfwPollEvents();
		dibujar_cuadro();
	}
	vkDeviceWaitIdle(dispositivo);
}
void Aplicacion::iniciar_ventana(){
	ventana_principal.crear_ventana();
	
}
void Aplicacion::dibujar_cuadro(){
	

	VkSemaphoreCreateInfo semaforo_Informacion_de_creacion = {};
	semaforo_Informacion_de_creacion.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	vkCreateSemaphore(dispositivo,&semaforo_Informacion_de_creacion,nullptr,&semaforo_para_imagenes_disponibles);
	vkCreateSemaphore(dispositivo,&semaforo_Informacion_de_creacion,nullptr,&semaforo_para_representacion_finalizada);

	uint32_t indice_de_imagen;
	vkAcquireNextImageKHR(dispositivo,cadena_nueva.cadena,std::numeric_limits<uint64_t>::max(),
						semaforo_para_imagenes_disponibles,
						VK_NULL_HANDLE,
						&indice_de_imagen);
	
	VkSubmitInfo informacion_para_suministrar = {};
	informacion_para_suministrar.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore semaforos_de_espera[] = {semaforo_para_imagenes_disponibles};
	VkPipelineStageFlags estapas_de_espera[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
	
	informacion_para_suministrar.waitSemaphoreCount = 1;
	informacion_para_suministrar.pWaitSemaphores = semaforos_de_espera;
	informacion_para_suministrar.pWaitDstStageMask = estapas_de_espera;
	informacion_para_suministrar.commandBufferCount = 1;
	informacion_para_suministrar.pCommandBuffers = &bufer_de_comandos[indice_de_imagen];

	VkSemaphore semafores_de_senyales[] = {semaforo_para_representacion_finalizada};
	informacion_para_suministrar.signalSemaphoreCount = 1;
	informacion_para_suministrar.pSignalSemaphores = semafores_de_senyales;

	vkQueueSubmit(dispositivo_nuevo.cola_de_graficos,1,&informacion_para_suministrar,VK_NULL_HANDLE);


	VkPresentInfoKHR presentacion_Informacion;
	presentacion_Informacion.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentacion_Informacion.waitSemaphoreCount = 1;
	presentacion_Informacion.pWaitSemaphores = semafores_de_senyales;

	VkSwapchainKHR cadenas[] = {cadena_nueva.cadena};
	presentacion_Informacion.swapchainCount = 1;
	presentacion_Informacion.pSwapchains = cadenas;
	presentacion_Informacion.pImageIndices = &indice_de_imagen;
	presentacion_Informacion.pResults = nullptr;

	vkQueuePresentKHR(dispositivo_nuevo.cola_de_presentacion, &presentacion_Informacion);
	
	vkQueueWaitIdle(dispositivo_nuevo.cola_de_presentacion);
}

void Aplicacion::crear_semaforos(){
	// VkSemaphoreCreateInfo semaforo_Informacion_de_creacion = {};
	// semaforo_Informacion_de_creacion.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	// for(size_t i = 0; i < cuadros_maximos_en_vuelo; i++){		
	// 	vkCreateSemaphore(dispositivo,&semaforo_Informacion_de_creacion,nullptr,&semaforo_para_imagenes_disponibles[i]);
	// 	vkCreateSemaphore(dispositivo,&semaforo_Informacion_de_creacion,nullptr,&semaforo_para_representacion_finalizada[i]);

	// }
}

void Aplicacion::crear_vista_de_imagenes_en_cadena_de_intercambio(
		VkDevice dispostivo, 
		VkFormat formato ){
			
	vistas_de_imagenes_en_cadena_de_intercambio.resize(imagenes_en_cadena_de_intercambio.size());
	
	
	for(size_t i = 0; i < imagenes_en_cadena_de_intercambio.size() ; i++){
		VkImageViewCreateInfo informacion_de_creacion;
		informacion_de_creacion.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		informacion_de_creacion.pNext = NULL;
		informacion_de_creacion.flags = 0;
		informacion_de_creacion.image = imagenes_en_cadena_de_intercambio[i];
		informacion_de_creacion.viewType = VK_IMAGE_VIEW_TYPE_2D;
		informacion_de_creacion.format = formato;
		informacion_de_creacion.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		informacion_de_creacion.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;	
		informacion_de_creacion.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;	
		informacion_de_creacion.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;		
		informacion_de_creacion.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		informacion_de_creacion.subresourceRange.baseMipLevel = 0;
		informacion_de_creacion.subresourceRange.levelCount = 1;
		informacion_de_creacion.subresourceRange.baseArrayLayer = 0;
		informacion_de_creacion.subresourceRange.layerCount = 1;

		vkCreateImageView(dispostivo,&informacion_de_creacion,nullptr,&vistas_de_imagenes_en_cadena_de_intercambio[i]);
	}
}


VkPipelineShaderStageCreateInfo* Aplicacion::crear_etapas_de_sombreadores(VkPipelineShaderStageCreateInfo etapas[]){
	auto codigo_sombreador_vertices = leer_archivo("sombreadores/vert.spv");
	auto codigo_sombreador_pixel = leer_archivo("sombreadores/frag.spv");	


	modulo_sombreador_de_pixeles = crear_modulo_sombreador(dispositivo,codigo_sombreador_pixel);
	modulo_sombreador_de_vertices = crear_modulo_sombreador(dispositivo,codigo_sombreador_vertices);

	VkPipelineShaderStageCreateInfo inforomacion_creacion_estapa_vertices = {};
	inforomacion_creacion_estapa_vertices.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	inforomacion_creacion_estapa_vertices.pNext = NULL;
	inforomacion_creacion_estapa_vertices.flags = 0;
	inforomacion_creacion_estapa_vertices.stage = VK_SHADER_STAGE_VERTEX_BIT;
	inforomacion_creacion_estapa_vertices.module = modulo_sombreador_de_vertices;
	inforomacion_creacion_estapa_vertices.pName = "main";

	VkPipelineShaderStageCreateInfo inforomacion_creacion_estapa_pixeles = {};
	inforomacion_creacion_estapa_pixeles.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	inforomacion_creacion_estapa_pixeles.pNext = NULL;
	inforomacion_creacion_estapa_pixeles.flags = 0;
	inforomacion_creacion_estapa_pixeles.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	inforomacion_creacion_estapa_pixeles.module = modulo_sombreador_de_pixeles;
	inforomacion_creacion_estapa_pixeles.pName = "main";


	etapas[0] = inforomacion_creacion_estapa_vertices;
	etapas[1] = inforomacion_creacion_estapa_pixeles;


	return etapas;
}


VkShaderModule Aplicacion::crear_modulo_sombreador(VkDevice dispositivo, const std::vector<char> & codigo){
	VkShaderModule modulo_sombreador;
	VkShaderModuleCreateInfo informacion_de_creacion = {};
	informacion_de_creacion.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	informacion_de_creacion.pNext = NULL;
	informacion_de_creacion.flags = 0;
	informacion_de_creacion.codeSize = codigo.size();
	informacion_de_creacion.pCode = reinterpret_cast<const uint32_t*>(codigo.data());

	vkCreateShaderModule(dispositivo,&informacion_de_creacion,nullptr,&modulo_sombreador);

	return modulo_sombreador;
}


void Aplicacion::crear_bufer_de_comandos(int indice_de_familia_de_colas){
	
	VkCommandPoolCreateInfo pozo_de_comandos_Informacion_de_creacion = {};
	pozo_de_comandos_Informacion_de_creacion.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	pozo_de_comandos_Informacion_de_creacion.queueFamilyIndex = indice_de_familia_de_colas;

	vkCreateCommandPool(dispositivo,&pozo_de_comandos_Informacion_de_creacion,nullptr,&pozo_de_comandos);


	
	bufer_de_comandos.resize( bufer_de_cuadros.size() );

	VkCommandBufferAllocateInfo posicionamiento_de_bufer_Informacion;
	posicionamiento_de_bufer_Informacion.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	posicionamiento_de_bufer_Informacion.pNext = NULL;
	posicionamiento_de_bufer_Informacion.commandPool = pozo_de_comandos;
	posicionamiento_de_bufer_Informacion.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	posicionamiento_de_bufer_Informacion.commandBufferCount = (uint32_t) bufer_de_comandos.size();

	vkAllocateCommandBuffers(dispositivo,&posicionamiento_de_bufer_Informacion,bufer_de_comandos.data() );

	for(size_t i = 0;i < bufer_de_comandos.size() ; i++){
		VkCommandBufferBeginInfo informacion_de_inicio_de_bufer_de_comandos = {};
		informacion_de_inicio_de_bufer_de_comandos.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		informacion_de_inicio_de_bufer_de_comandos.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		
		vkBeginCommandBuffer(bufer_de_comandos[i],&informacion_de_inicio_de_bufer_de_comandos);
			
			VkRenderPassBeginInfo comienzo_de_paso_de_representacion_Informacion = {};
			comienzo_de_paso_de_representacion_Informacion.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			comienzo_de_paso_de_representacion_Informacion.renderPass = paso_de_representacion;
			comienzo_de_paso_de_representacion_Informacion.framebuffer = bufer_de_cuadros[i];
			comienzo_de_paso_de_representacion_Informacion.renderArea.offset = {0,0};
			comienzo_de_paso_de_representacion_Informacion.renderArea.extent = cadena_nueva.capacidades_de_superfice.currentExtent;

			VkClearValue color_de_limpieza = {0.0f , 0.0f , 0.0f , 1.0f };
			comienzo_de_paso_de_representacion_Informacion.clearValueCount = 1;
			comienzo_de_paso_de_representacion_Informacion.pClearValues = & color_de_limpieza;

			vkCmdBeginRenderPass(bufer_de_comandos[i], &comienzo_de_paso_de_representacion_Informacion, VK_SUBPASS_CONTENTS_INLINE);
				vkCmdBindPipeline(bufer_de_comandos[i], VK_PIPELINE_BIND_POINT_GRAPHICS, tuberias_de_graficos );
				VkBuffer buferes_de_vertices[] = {this->bufer_de_vertices};
				VkDeviceSize offsets[] = {0};
				vkCmdBindVertexBuffers(bufer_de_comandos[i],0,1,buferes_de_vertices,offsets);
				uint32_t cantidad_de_vertices = static_cast<uint32_t>( vertices.size() );
				vkCmdDraw(bufer_de_comandos[i], cantidad_de_vertices , 1, 0 ,0);
			vkCmdEndRenderPass(bufer_de_comandos[i]);
		vkEndCommandBuffer(bufer_de_comandos[i]);
	}


}


void Aplicacion::limpiar(){
	// for(size_t i = 0; i < cuadros_maximos_en_vuelo; i++){	
	// 	vkDestroySemaphore(dispositivo,semaforo_para_imagenes_disponibles[i],nullptr);
	// 	vkDestroySemaphore(dispositivo,semaforo_para_imagenes_disponibles[i],nullptr);
	// }
	
	

	vkDestroySemaphore(dispositivo,semaforo_para_imagenes_disponibles,nullptr);
	vkDestroySemaphore(dispositivo,semaforo_para_representacion_finalizada,nullptr);

	vkDestroyCommandPool(dispositivo,pozo_de_comandos,nullptr);
	
	for(auto bufer_de_cuadro : bufer_de_cuadros){
		vkDestroyFramebuffer(dispositivo,bufer_de_cuadro,nullptr);
	}
	


	vkDestroyPipeline(dispositivo,tuberias_de_graficos,nullptr);
	vkDestroyRenderPass(dispositivo,paso_de_representacion,nullptr);
	vkDestroyPipelineLayout(dispositivo,capa_de_tuberia,nullptr);

	

	for(auto vista_de_imagen : vistas_de_imagenes_en_cadena_de_intercambio){
		vkDestroyImageView(dispositivo,vista_de_imagen,nullptr);
	}
	
	cadena_nueva.destruir();
	tuberia_de_graficos.destruir_descriptor_de_disenyo();
	bufer_de_vertice.destruir();

	capas.destruir();
	ventana_principal.cerrar();	
	instancia_vulkan_nueva.destruir();
	
	
}

void Aplicacion::crear_bufer_de_vertices(){	


	VkBufferCreateInfo bufer_de_vertices_Informacion_de_creacion = {};
	bufer_de_vertices_Informacion_de_creacion.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufer_de_vertices_Informacion_de_creacion.size = sizeof(vertices[0]) * vertices.size();
	bufer_de_vertices_Informacion_de_creacion.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufer_de_vertices_Informacion_de_creacion.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	vkCreateBuffer(dispositivo,&bufer_de_vertices_Informacion_de_creacion,nullptr,&bufer_de_vertices);

	bufer_de_vertice.crear(dispositivo,bufer_de_vertices);
	void *datos;
	vkMapMemory(dispositivo,bufer_de_vertice.memoria_de_dispostivo,0,bufer_de_vertices_Informacion_de_creacion.size,0,&datos);
		memcpy(datos,vertices.data(),(size_t)bufer_de_vertices_Informacion_de_creacion.size);
	vkUnmapMemory(dispositivo,bufer_de_vertice.memoria_de_dispostivo);
	

}