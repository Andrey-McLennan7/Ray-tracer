cmake_minimum_required(VERSION ${CMAKE_VERSION})
project(RAYTRACER)

include_directories(
	src
	contrib/cl-windows-x86_64/include
	contrib/include
)

link_directories(
	contrib/cl-windows-x86_64/lib/x64
	contrib/cl-windows-x86_64/lib/x86
)

add_executable(raytracer
	src/Main.cpp
	src/Camera.h
	src/Camera.cpp
	src/Diffuse.h
	src/Diffuse.cpp
	src/GCP_GFX_Framework.h
	src/GCP_GFX_Framework.cpp
	src/Material.h
	src/Object.h
	src/Object.cpp
	src/PBR.h
	src/PBR.cpp
	src/Plane.h
	src/Plane.cpp
	src/PointLight.h
	src/PointLight.cpp
	src/random_floats.h
	src/Ray.h
	src/RayTracer.h
	src/RayTracer.cpp
	src/Specular.h
	src/Specular.cpp
	src/Sphere.h
	src/Sphere.cpp
)

target_link_libraries(raytracer SDL2 glew32 opengl32)