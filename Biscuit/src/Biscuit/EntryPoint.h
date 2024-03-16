#pragma once

#ifdef BC_PLATFORM_WINDOWS

extern Biscuit::Application* Biscuit::CreateApplication();

int main(int argc, char** argv)
{
	BC_CORE_WARN("Initialized Log£¡");
	int a = 5;
	BC_INFO("Hello! Var = {0}", a);

	printf("Biscuit Engine\n");
	auto app = Biscuit::CreateApplication();
	app->Run();
	delete app;
}
#endif