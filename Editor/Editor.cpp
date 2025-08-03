#include <Engine.h>


int main()
{
	try
	{
		NullEngine::Engine engine;
		engine.Run();
	}
	catch (const std::exception& e)
	{
		NullEngine::logger.Error("An error occurred: {}", e.what());
		return EXIT_FAILURE;
	}
}