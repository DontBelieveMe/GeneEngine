#include <Platform/Window.h>
#include <Platform/OpenGL.h>
#include <Graphics/Texture2D.h>

#include "Shaders.h"
#include "ObjectFactory.h"
#include "Renderer.h"

int main()
{
	using namespace Gene::Platform;
	using namespace Gene::Graphics;

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
	});

	Shaders shaders;
	shaders.CompileAll();
	GLSLShader *shader = shaders.Standard;
	shader->Enable();
	shader->BindAttributeIndex(0, "position");
	Matrix4 matrix = Matrix4::Perpective(6.f / 4.f, 90.f, 1000.f, 0.1f);
	shader->LoadUniformMatrix4f("u_Projection", matrix);

	ObjectFactory *objFactory = ObjectFactory::Get();
	objFactory->InitAllTypes();
	Cube cube = objFactory->CreateCube(Vector3(0, 0, -10));
	
	Renderer renderer(shaders);
	renderer.SubmitMesh(&cube);

	Texture2D texture("Data/textures.png");

	window->SetClearColor(Color::CornflowerBlue);
	window->Show();
	glEnable(GL_DEPTH_TEST);

	while (window->Running())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.Draw();
		window->SwapBuffers();
		window->PollEvents();
	}

	return 0;
}
