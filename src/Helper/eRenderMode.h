#pragma once
#include <cstdint>

enum eRenderMode :uint8_t {
	SkyBox,
	NoLights,
	NoLights_NoTextures,
	DepthTestMode,
	FullRender, //Lit, texture, etc
	FullRender_Instanced,
	Outline, //Mask shader
	WiredOn, //Wire only shader
	PostProcessing,
	PostProcessingOnModel
};
