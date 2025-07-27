#pragma once

#include <Core/Logger.hpp>
#include <ECS/System.hpp>
#include <entt/entt.hpp>
#include <memory>
#include <unordered_set>

namespace NullEngine
{
	class ECS
	{
	public:
		ECS() : m_Registry() {}
		~ECS() = default;

		entt::entity Create()
		{
			return m_Registry.create();
		}

		template <typename T>
		void SetComponent(entt::entity entity, T component)
		{
			m_Registry.emplace_or_replace<T>(entity, std::forward<T>(component));
		}

		template <typename T>
		void RemoveComponent(entt::entity entity)
		{
			m_Registry.remove<T>(entity);
		}

		template <typename T>
		void AddSystem(T&& system)
		{
			static_assert(std::is_base_of<System, T>::value, "System must inherit from System class");
			auto sysPtr = std::make_unique<T>(std::move(system));
			sysPtr->Awake();
			m_Systems.insert(std::move(sysPtr));
		}

		void Start()
		{
			for (auto& system : m_Systems)
			{
				system->Start(m_Registry);
			}
		}

		void Update()
		{
			for (auto& system : m_Systems)
			{
				system->Update(m_Registry);
			}
		}

		void Stop()
		{
			for (auto& system : m_Systems)
			{
				system->Stop(m_Registry);
			}
		}

	private:
		Logger m_Logger{ "ECS" };
		entt::registry m_Registry;

		std::unordered_set<std::unique_ptr<System>> m_Systems;
	};
}