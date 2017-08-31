#include <Platform/Window.h>
#include <Platform/OpenGL.h>
#include <Graphics/Texture2D.h>
#include <Input/Keyboard.h>

#include "Shaders.h"
#include "ObjectFactory.h"
#include "Renderer.h"
GLSLShader *Standard_g;

int main()
{
	using namespace Gene::Platform;
	using namespace Gene::Graphics;
	using namespace Gene::Input;

	WindowInfo info;
	info.Width = 600;
	info.Height = 400;
	info.Title = "Minecraft Clone!";
	info.Borderless = false;

	Window *window = Window::CreateWindow(info);
	window->Create();
	window->CreateGLContext();

	window->SetWindowResizeCallback([](int w, int h) {
		glViewport(0, 0, w, h);
		float w1 = w / 100;
		float w2 = h / 100;
		Matrix4 matrix = Matrix4::Perpective(w1 / w2, 90.f, 1000.f, 0.1f);
		Standard_g->LoadUniformMatrix4f("u_Projection", matrix);
	});

	Shaders shaders;
	shaders.CompileAll();
	GLSLShader *shader = shaders.Standard;
	Standard_g = shader;
	shader->Enable();
	shader->BindAttributeIndex(0, "position");
	shader->BindAttributeIndex(1, "uv");
	Matrix4 matrix = Matrix4::Perpective(6.f / 4.f, 90.f, 1000.f, 0.1f);
	shader->LoadUniformMatrix4f("u_Projection", matrix);

	ObjectFactory *objFactory = ObjectFactory::Get();
	objFactory->InitAllTypes();
	Cube cube = objFactory->CreateCube(Vector3(0, 0, -10));
	
	Renderer renderer(shaders);
	renderer.SubmitMesh(&cube);

	Texture2D texture;
	texture.Filtering = Texture2D::FilteringOptions::Nearest;
	texture.Load("Data/textures.png");
	texture.Enable();

	window->SetClearColor(Color::CornflowerBlue);
	window->Show();
	glEnable(GL_DEPTH_TEST);
	Vector3 camPos(0, 0, -5);

	while (window->Running())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		renderer.Draw();
		KeyboardState state = Keyboard::GetState();
		if (state.IsKeyDown(Keys::W)) { 
			cube.Position.Z += .5f;
		}
		if (state.IsKeyDown(Keys::S)) { 
			cube.Position.Z -= .5f; 
		}

		window->SwapBuffers();
		window->PollEvents();
	}

	return 0;
}
