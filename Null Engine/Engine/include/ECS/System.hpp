#pragma once

#include <entt/entt.hpp>

namespace NullEngine
{
	class System
	{
	public:
		System() { Awake(); };
		virtual ~System() = default;
		virtual void Awake() {};
		virtual void Start(entt::registry&) {};
		virtual void Update(entt::registry&) {};
		virtual void Stop(entt::registry&) {};
	};
}