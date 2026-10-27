#pragma once
#include <cstdint>

enum eInput : uint8_t
{
	None,
	Arrow_Up,
	Arrow_Down,
	Arrow_Left,
	Arrow_Right,
	Space_Bar,
	RotatePitch,
	RotateYaw,
	RotateRoll,
	RenderMode_LightsOff,
	RenderMode_Debug,
	RenderMode_DepthTest,
	RenderMode_LitAndReflection
};
