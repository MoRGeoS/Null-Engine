#pragma once

#include <Core/Logger.hpp>
#include <ECS/System.hpp>

#include <Components/Transform.h>

#include <glm/gtx/string_cast.hpp>

namespace NullEngine
{
	class TestSystem : public System
	{
	public:
		int value;

		void Awake() override
		{
			s_Logger.Info("TestSystem Awake");
		}

		void Start(entt::registry& registry) override
		{
			s_Logger.Info("TestSystem Start");
		}

		void Update(entt::registry& registry) override
		{
			s_Logger.Info("Value: {}", value);
		}

		void Stop(entt::registry& registry) override
		{
			s_Logger.Info("TestSystem Stop");
		}
	};
}