#include "tuberia_de_graficos.h"

void TuberiaDeGraficos::crear( VkDevice &dispositivo,
                VkSurfaceCapabilitiesKHR &capacidades_de_superficie,
	            VkFormat &formato,
                VkPipelineShaderStageCreateInfo *etapas_sombreadores ){

    this->dispositivo = dispositivo;
    this->formato = formato;

	auto descripcion_de_enlace = Vertice::conseguir_descripcion_de_enlace();
	auto descripcion_de_atributos = Vertice::conseguir_descripcion_de_atributos();

    VkPipelineVertexInputStateCreateInfo informacion_de_entrada_de_vertices = {};
	informacion_de_entrada_de_vertices.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	informacion_de_entrada_de_vertices.vertexBindingDescriptionCount = 1;
	informacion_de_entrada_de_vertices.pVertexBindingDescriptions = &descripcion_de_enlace;
	informacion_de_entrada_de_vertices.vertexAttributeDescriptionCount = 1;
	informacion_de_entrada_de_vertices.pVertexAttributeDescriptions = &descripcion_de_atributos;
	


	VkPipelineInputAssemblyStateCreateInfo ensamblado_de_entrada = {};
	ensamblado_de_entrada.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	ensamblado_de_entrada.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	ensamblado_de_entrada.primitiveRestartEnable = VK_FALSE;


	VkViewport vista_de_ventana;
	vista_de_ventana.x = 0.0f;
	vista_de_ventana.y = 0.0f;	
	vista_de_ventana.width = (float) capacidades_de_superficie.currentExtent.width;
	vista_de_ventana.height = (float) capacidades_de_superficie.currentExtent.height;
	vista_de_ventana.minDepth = 0.0f;
	vista_de_ventana.maxDepth = 1.0f;

	VkRect2D recortado = {};
	recortado.offset = {0,0};
	recortado.extent = capacidades_de_superficie.currentExtent;

	VkPipelineViewportStateCreateInfo estado_vista_en_ventana = {};
	estado_vista_en_ventana.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	estado_vista_en_ventana.viewportCount = 1;
	estado_vista_en_ventana.pViewports = &vista_de_ventana;
	estado_vista_en_ventana.scissorCount = 1;
	estado_vista_en_ventana.pScissors = &recortado;


    

	VkPipelineRasterizationStateCreateInfo informacion_de_creacion_de_raterizacion = {};
	informacion_de_creacion_de_raterizacion.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	informacion_de_creacion_de_raterizacion.depthClampEnable = VK_FALSE;
	informacion_de_creacion_de_raterizacion.rasterizerDiscardEnable = VK_FALSE;
	informacion_de_creacion_de_raterizacion.polygonMode = VK_POLYGON_MODE_FILL;
	informacion_de_creacion_de_raterizacion.lineWidth = 1.0f;
	informacion_de_creacion_de_raterizacion.cullMode = VK_CULL_MODE_BACK_BIT;
	informacion_de_creacion_de_raterizacion.frontFace = VK_FRONT_FACE_CLOCKWISE;
	informacion_de_creacion_de_raterizacion.depthBiasEnable = VK_FALSE;


	VkPipelineMultisampleStateCreateInfo informacion_de_creacion_de_multimuestreo = {};
	informacion_de_creacion_de_multimuestreo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	informacion_de_creacion_de_multimuestreo.sampleShadingEnable = VK_FALSE;
	informacion_de_creacion_de_multimuestreo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	
	crear_descriptor_de_establecimiento_de_disenyo();
	VkPipelineLayoutCreateInfo informacion_de_creacion_de_capa_de_tuberia = {};
	informacion_de_creacion_de_capa_de_tuberia.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	informacion_de_creacion_de_capa_de_tuberia.setLayoutCount = 1;
	informacion_de_creacion_de_capa_de_tuberia.pSetLayouts = &descriptor_de_establecimiento_de_disenyo;

	vkCreatePipelineLayout(dispositivo,&informacion_de_creacion_de_capa_de_tuberia,nullptr,&capa);

    crear_paso_de_representacion();
	
	
	//Mezcla de color
	VkPipelineColorBlendAttachmentState mezcla_de_color_adjunta = {};
	mezcla_de_color_adjunta.colorWriteMask =	VK_COLOR_COMPONENT_A_BIT |
												VK_COLOR_COMPONENT_G_BIT |
												VK_COLOR_COMPONENT_B_BIT |
												VK_COLOR_COMPONENT_R_BIT;

	VkPipelineColorBlendStateCreateInfo mezcla_de_color_Informacion_de_creacion = {};
	mezcla_de_color_Informacion_de_creacion.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	mezcla_de_color_Informacion_de_creacion.logicOpEnable = VK_FALSE;
	mezcla_de_color_Informacion_de_creacion.attachmentCount = 1;
	mezcla_de_color_Informacion_de_creacion.pAttachments = &mezcla_de_color_adjunta;

	
	VkGraphicsPipelineCreateInfo informacion_de_creacion_de_tuberias_de_graficos = {};
	informacion_de_creacion_de_tuberias_de_graficos.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	informacion_de_creacion_de_tuberias_de_graficos.stageCount = 2;
	informacion_de_creacion_de_tuberias_de_graficos.pStages = etapas_sombreadores;
	informacion_de_creacion_de_tuberias_de_graficos.pVertexInputState = &informacion_de_entrada_de_vertices;
	informacion_de_creacion_de_tuberias_de_graficos.pInputAssemblyState = &ensamblado_de_entrada;
	informacion_de_creacion_de_tuberias_de_graficos.pViewportState = &estado_vista_en_ventana;
	informacion_de_creacion_de_tuberias_de_graficos.pRasterizationState = &informacion_de_creacion_de_raterizacion;
	informacion_de_creacion_de_tuberias_de_graficos.pMultisampleState = &informacion_de_creacion_de_multimuestreo;
	informacion_de_creacion_de_tuberias_de_graficos.pColorBlendState = &mezcla_de_color_Informacion_de_creacion;
	informacion_de_creacion_de_tuberias_de_graficos.layout = capa;
	informacion_de_creacion_de_tuberias_de_graficos.renderPass = paso_de_representacion;
	informacion_de_creacion_de_tuberias_de_graficos.subpass = 0;

	VkResult resultado_de_creacion = vkCreateGraphicsPipelines(dispositivo,VK_NULL_HANDLE,1,&informacion_de_creacion_de_tuberias_de_graficos,nullptr,&tuberia);

	
}
void TuberiaDeGraficos::crear_paso_de_representacion(){
    //Paso de representacion
	VkAttachmentDescription color_abjunto = {};
	color_abjunto.format = formato;
	color_abjunto.samples = VK_SAMPLE_COUNT_1_BIT;
	color_abjunto.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	color_abjunto.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

	color_abjunto.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	color_abjunto.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;




	VkAttachmentReference referencia_de_adjuncion_de_color = {};
	referencia_de_adjuncion_de_color.attachment = 0;
	referencia_de_adjuncion_de_color.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;


	VkSubpassDependency dependencia_de_subpase = {};
	dependencia_de_subpase.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependencia_de_subpase.dstSubpass = 0;
	dependencia_de_subpase.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependencia_de_subpase.srcAccessMask = 0;
	
	dependencia_de_subpase.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependencia_de_subpase.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;



	VkSubpassDescription descripcion_de_sub_pase = {};
	descripcion_de_sub_pase.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	descripcion_de_sub_pase.colorAttachmentCount = 1;
	descripcion_de_sub_pase.pColorAttachments = &referencia_de_adjuncion_de_color;


	VkRenderPass paso_de_representacion;
	VkRenderPassCreateInfo informacion_de_creacion_de_paso_de_representacion = {};
	informacion_de_creacion_de_paso_de_representacion.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	informacion_de_creacion_de_paso_de_representacion.attachmentCount = 1;
	informacion_de_creacion_de_paso_de_representacion.pAttachments = &color_abjunto;
	informacion_de_creacion_de_paso_de_representacion.subpassCount = 1;	
	informacion_de_creacion_de_paso_de_representacion.pSubpasses = &descripcion_de_sub_pase;
	informacion_de_creacion_de_paso_de_representacion.dependencyCount = 1;
	informacion_de_creacion_de_paso_de_representacion.pDependencies = &dependencia_de_subpase;
	vkCreateRenderPass(dispositivo,&informacion_de_creacion_de_paso_de_representacion,nullptr,&paso_de_representacion);
    this->paso_de_representacion = paso_de_representacion;
}

void TuberiaDeGraficos::crear_descriptor_de_establecimiento_de_disenyo(){
	
	
	VkDescriptorSetLayoutBinding enlace_al_bufer_de_objeto_uniforme;
	enlace_al_bufer_de_objeto_uniforme.binding = 0;
	enlace_al_bufer_de_objeto_uniforme.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	enlace_al_bufer_de_objeto_uniforme.descriptorCount = 1;
	enlace_al_bufer_de_objeto_uniforme.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
	enlace_al_bufer_de_objeto_uniforme.pImmutableSamplers = nullptr;

	VkDescriptorSetLayoutCreateInfo descriptor_de_establecimiento_de_disenyo_Informacion_de_creacion = {};
	descriptor_de_establecimiento_de_disenyo_Informacion_de_creacion.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptor_de_establecimiento_de_disenyo_Informacion_de_creacion.bindingCount = 1;
	descriptor_de_establecimiento_de_disenyo_Informacion_de_creacion.pBindings = &enlace_al_bufer_de_objeto_uniforme;

	vkCreateDescriptorSetLayout(dispositivo,&descriptor_de_establecimiento_de_disenyo_Informacion_de_creacion,nullptr,&descriptor_de_establecimiento_de_disenyo);

}

void TuberiaDeGraficos::destruir_descriptor_de_disenyo(){
	vkDestroyDescriptorSetLayout(dispositivo,descriptor_de_establecimiento_de_disenyo,nullptr);
}