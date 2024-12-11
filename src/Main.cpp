#include "GCP_GFX_Framework.h"
#include "RayTracer.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "Diffuse.h"
#include "Specular.h"
#include "PBR.h"
#include "Ray.h"

#include "random_floats.h"

#include <memory>
#include <mutex>
#include <thread>
#include <chrono>
#include <fstream>
#include <ctime>

#ifdef _DEBUG
bool debug = true;
#else
bool debug = false;
#endif

struct Cache
{
	glm::ivec2 win_size;
	glm::ivec2 start;
	glm::ivec2 end;

	GCP_Framework* framework;
	RayTracer* ray_tracer;
	Camera* camera;
};

unsigned int num_threads{ 6 };

// Utility functions
void RTrenderer(Cache cache)
{
	// Iterate through every x coordinate
	for (int x{ cache.start.x }; x < cache.end.x; ++x)
	{
		// Iterate through every y coordinate
		for (int y{ cache.start.y }; y < cache.end.y; ++y)
		{
			glm::ivec2 pixel_pos{ x, y };
			glm::vec3 pixel_colour{ 0 };

			int samples{ 5 };

			// Calculate anti-aliasing
			for (int i = 0; i < samples; i++)
			{
				float fx{ (float)pixel_pos.x + random_floats_x[i] };
				float fy{ (float)pixel_pos.y + random_floats_y[i] };

				pixel_colour += cache.ray_tracer->TraceRay(cache.camera->GetRay(glm::vec2{ fx, fy }, cache.win_size));
			}

			cache.framework->DrawPixel(pixel_pos, pixel_colour / (float)samples);
		}
	}
}

void calculate_and_store_time(std::ofstream& file, const std::string& fileName, const std::chrono::steady_clock::time_point& time1, const std::chrono::steady_clock::time_point& time2)
{
	// Calculate amount of time in milliseconds
	std::chrono::milliseconds milliseconds{ std::chrono::duration_cast<std::chrono::milliseconds>(time2 - time1) };

	// Calculate in seconds
	float seconds{ (float)milliseconds.count() / 1000.0f };

	// Print amount of time
	std::cout << "\nTime taken: " << seconds << " seconds\n" << std::endl;

	// Open/Create CSV file than can append data
	file.open(fileName, std::ofstream::out | std::ofstream::app);

	file.seekp(0, std::ios::end);

	if (file.tellp() == 0)
	{
		file << "Threads, Seconds\n";
	}

	file << num_threads << ',' << seconds << '\n';
	file.close();
}

void CPU_overload_test(RayTracer* ray_tracer)
{
	ray_tracer->enable_shadows(false);

	float radius{ 0.1f };

	float z_pos{ -2.0f };

	for (int i = 0; i < 5; i++)
	{
		float y_pos{ 0.0f };

		for (int j = 0; j < 5; j++)
		{
			float x_pos{ -2.0f };

			for (int k = 0; k < 20; k++)
			{
				std::shared_ptr<Sphere> sphere
				{
					std::make_shared<Sphere>
					(
						radius, glm::vec3
						{
							x_pos, 
							y_pos,
							z_pos
						},

						std::make_shared<Diffuse>
						(
							glm::vec3
							{
								random_float(),
								random_float(),
								random_float()
							}
						)
					)
				};

				sphere->add_material(std::make_shared<Specular>(50.0f));

				ray_tracer->add_object(sphere);

				x_pos += radius * 2;
			}

			y_pos -= radius * 2;
		}

		z_pos += radius * 2;
	}

	ray_tracer->add_light(std::make_shared<PointLight>(1.0f, glm::vec3{ 0.0f, 10.0f,  10.0f }));
	ray_tracer->add_light(std::make_shared<PointLight>(1.0f, glm::vec3{ 0.0f, 10.0f, -100.0f }));

	ray_tracer->add_object(std::make_shared<Plane>(glm::vec3{ 0.0f, -1.0f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f }, std::make_shared<Diffuse>(glm::vec3{ 0.75f })));
}

void add_objects(RayTracer* ray_tracer)
{
	// Enable shadows
	ray_tracer->enable_shadows(false);

	// Create poit lights
	std::vector<std::shared_ptr<PointLight>> point_lights;

	point_lights.push_back(std::make_shared<PointLight>(1.0f, glm::vec3{ 1.0f, 1.0f, 1.0f }));
	point_lights.push_back(std::make_shared<PointLight>(0.5f, glm::vec3{ -1.0f, 1.0f, 1.0f }));

	// Add point lights to the scene
	std::vector<std::shared_ptr<PointLight>>::const_iterator itr;
	for (itr = point_lights.begin(); itr != point_lights.end(); ++itr)
	{
		ray_tracer->add_light(*itr);
	}

	// Create sphere object(s)
	//std::shared_ptr<Sphere> red_sphere{ std::make_shared<Sphere>(0.5f, glm::vec3{ 0.0f, -0.5f, -1.0f }, std::make_shared<PBR>(0.5f, 1.0f, 0.5f, glm::vec3{ 0.8f, 0.2f, 0.1f })) };
	std::shared_ptr<Sphere> red_sphere{ std::make_shared<Sphere>(0.5f, glm::vec3{ 0.0f, -0.5f, -1.0f }, std::make_shared<Diffuse>(glm::vec3{ random_float(), random_float(), random_float() })) };

	red_sphere->add_material(std::make_shared<Specular>(50.0f));

	ray_tracer->add_object(red_sphere);

	// Add a plane
	ray_tracer->add_object(std::make_shared<Plane>(glm::vec3{ 0.0f, -1.0f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f }, std::make_shared<Diffuse>(glm::vec3{ 0.75f })));
}

#undef main
int main()
{
	srand(time(NULL));

	// Set window size
	const glm::ivec2 win_size(1240, 720);

	// This will handle rendering to screen
	GCP_Framework framework;

	// Initialises SDL and OpenGL and sets up a framebuffer
	if (!framework.Init(win_size))
	{
		return -1;
	}

	while ((unsigned int)win_size.y % num_threads != 0)
	{
		++num_threads;

		std::cout << "Theads increased to " << num_threads << std::endl;

		if (num_threads > (unsigned int)win_size.y)
		{
			return -1;
		}
	}

	std::vector<std::thread> threads;

	// Ray tracer
	RayTracer ray_tracer;

	//add_objects(&ray_tracer);
	CPU_overload_test(&ray_tracer);
	
	// Camera
	Camera camera(win_size);

	Cache cache
	{
		win_size,
		glm::ivec2{ 0, 0 },
		glm::ivec2{ win_size.x, win_size.y / num_threads },

		&framework,
		&ray_tracer,
		&camera
	};

	// ---------------------------------Start timer------------------------------------------
	std::chrono::steady_clock::time_point time1{ std::chrono::high_resolution_clock::now() };

	for (unsigned int i{ 0 }; i < num_threads; ++i)
	{
		threads.push_back(std::thread(RTrenderer, cache));

		cache.start.y = cache.end.y;
		cache.end.y += win_size.y / num_threads;
	}

	std::vector<std::thread>::iterator itr;
	for (itr = threads.begin(); itr != threads.end(); ++itr)
	{
		itr->join();
	}

	std::chrono::steady_clock::time_point time2{ std::chrono::high_resolution_clock::now() };
	// ---------------------------------End timer--------------------------------------------

	std::ofstream file;

	// Check if the compiler is in debug mode
	// 
	// Since it takes longer to run a program when it is in debug mode
	// it would be very useful to ensure that there are two different
	// files that store the amount of time it has taken to output a
	// single frame to the screen. This can help determine the optimal
	// amount of threads needed to output an image
	//
	if (debug)
	{
		// If it is, then redirect the location in the debug file
		//calculate_and_store_time(file, "../res/Measurements/Debug/data-" + std::to_string(win_size.y) + "p.csv", time1, time2);
	}
	else
	{
		// If it is NOT, then redirect the location in the release file
		//calculate_and_store_time(file, "../res/Measurements/Release/data-" + std::to_string(win_size.y) + "p.csv", time1, time2);
	}

	// Pushes the framebuffer to OpenGL and renders to screen
	// Also contains an event loop that keeps the window going until it's closed
	framework.ShowAndHold();

	return 0;
}