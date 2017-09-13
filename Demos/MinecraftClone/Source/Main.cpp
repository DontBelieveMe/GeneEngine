#include <Platform/Window.h>
#include <Platform/OpenGL.h>
#include <Graphics/Texture2D.h>
#include <Input/Keyboard.h>
#include <Platform/Time.h>
#include <Input/Mouse.h>
#include "Shaders.h"
#include "ObjectFactory.h"
#include "Renderer.h"
#include "Player.h"
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

	Player player(Vector3(0, 0, 0));
	Matrix4 view = player.GetViewMatrix();
    GameTime gameTimer;
    gameTimer.Init(); // Kick off game clock

    float fixed60fpsMs = 1000 / 60;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glCullFace(GL_FRONT_AND_BACK);

	window->Show();

	while (window->Running())
	{
        gameTimer.StartFrame();
        player.Tick(window, gameTimer);
		Standard_g->Enable();
		Standard_g->LoadUniformMatrix4f("u_View", player.GetViewMatrix());
		Standard_g->Disable();

		KeyboardState state = Keyboard::GetState();
		if (state.IsKeyDown(Keys::Q)) break;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		renderer.Draw();
		
		window->SwapBuffers();
		window->PollEvents();

        gameTimer.EndFrame();
        gameTimer.Sleep(fixed60fpsMs);
    }
    window->Destroy();

	return 0;
}
