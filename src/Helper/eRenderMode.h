#pragma once
#include <cstdint>

enum eRenderMode :uint8_t {
	SkyBox,
	NoLights,
	DebugMode,
	DepthTestMode,
	FullRender, //Lit, texture, etc
	RenderNormals_GeometryShader,
	FullRender_Instanced,
	Outline, //Mask shader
	WiredOn, //Wire only shader
	PostProcessing,
	PostProcessingOnModel
};
