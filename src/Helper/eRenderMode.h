#pragma once
#include <cstdint>

enum eRenderMode :uint8_t {
	SkyBox,
	NoLights,
	DebugMode,
	DepthTestMode,
	FullRender, //Lit, texture, etc
	FullRender_Instanced,
	Outline, //Mask shader
	WiredOn, //Wire only shader
	PostProcessing,
	PostProcessingOnModel
};
