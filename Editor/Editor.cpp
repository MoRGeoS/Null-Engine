#define GLM_ENABLE_EXPERIMENTAL

#include <Core/Logger.hpp>
#include <Window/Window.h>
#include <ECS/ECS.hpp>

#include <Systems/TestSystem.hpp>

#include <Components/Transform.h>
using namespace NullEngine;
#include <iostream>

int main()
{
	Logger logger(LogLevel::Info, "Exception");
	s_Logger.Info("Application starting...");
	try
	{
		ECS ecs;
		ecs.AddSystem(TestSystem());

		auto entity = ecs.Create();
		ecs.SetComponent(entity, Transform());

		ecs.Start();
		ecs.Update();
		ecs.Stop();
	}
	catch (const std::exception& e)
	{
		if (e.what() != nullptr)
			logger.Error("Exception caught: {}", e.what());
	}
}