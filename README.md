# 3D Rendering Framework (Space3D)

Lightweight OpenGL-based 3D rendering demo and small framework showcasing instanced rendering, a simple camera, projectile logic and utility helpers.

## Features
- Instanced rendering (layout and uniform-based shaders)
- Free-flight camera (mouse + keyboard)
- Projectile spawning and lifetime management
- Minimal content/ shader manager
- FPS counter and timing utilities

## Dependencies
- Visual Studio 2022 (C++ workload)
- OpenGL (GPU drivers)
- [GLFW] (windowing & input)
- [GLAD] (OpenGL loader)
- [GLM] (math library)

Third-party headers/libraries should be available in the project include and library paths or installed system-wide.

## Build (Windows / Visual Studio)
1. Open the solution or project in Visual Studio 2022 (open `3D_Rendering_Framework.vcxproj` or the solution file).
2. Set the target architecture: __Platform__ -> `x64` if your dependencies are 64-bit.
3. Verify include and library paths under Project Properties:
   - __VC++ Directories__ for include/lib paths
   - __Linker > General__ for additional library directories
4. Link required libraries: `glfw3.lib`, `opengl32.lib`, and your GLAD library if applicable.
5. Place any required DLLs (e.g., `glfw3.dll`) beside the built executable or in your PATH.
6. Build: use __Build > Build Solution__.
7. Run: use __Debug > Start Debugging__ or __Debug > Start Without Debugging__.

Notes:
- If GLAD is not present, generate a loader for the desired OpenGL version and add its headers/libs to the project.
- If using prebuilt GLFW binaries, ensure the DLLs are available at runtime.

## Running
- Launch the built executable. A window opens showing instanced objects and an aiming dot.
- FPS and timing information are exposed via the console/overlay (see `Source/Helper/TimeHelper.cpp`).

## Controls
- Mouse: look around
- W / A / S / D: move camera forward / left / back / right
- Space: spawn a projectile from the camera position in the camera forward direction
- Esc: close the application

## Project Layout
- `Source/` — implementation files
- `Header/` — public headers
- `Shader/` — shader source files used by the demo
- Project & build files: `.sln`, `.vcxproj`, etc.

Important files:
- `Source/Source.cpp` — program entry + main loop
- `Source/Render/Renderer.cpp` — rendering and instance setup
- `Source/Game/Camera.cpp` — camera handling
- `Source/Game/Projectile.cpp` — projectile logic
- `Source/Helper/ContentManager.cpp` — shader & color loading utilities

## License
No license file is included. Add a `LICENSE` (for example MIT) to clarify reuse and distribution terms.

---
If you want, I can add this `README.md` to the repository now. Confirm and I will create the file.
