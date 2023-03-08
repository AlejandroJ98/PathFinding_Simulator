#pragma once

#include "State.h"

namespace AI
{
	template <class AgentType>
	class StateMachine
	{
	public:
		using StateType = State<AgentType>;

		StateMachine(AgentType& agent)
			: mAgent(agent)
		{}

		template <class NewStateType>
		void AddState(std::string stateName)
		{
			static_assert(std::is_base_of<StateType, NewStateType>::value, "[StateMachine] Can only add state for AgentType.");
			auto [iter, success] = mStates.emplace(std::move(stateName), std::make_unique<NewStateType>());
			if (!mCurrentState)
			{
				mCurrentState = iter->second.get();
				mCurrentState->Enter(mAgent);
			}
		}

		void Update(float deltaTime)
		{
			mCurrentState->Update(mAgent, deltaTime);
		}

		void ChangeState(const std::string& stateName)
		{
			auto iter = mStates.find(stateName);
			if (iter == mStates.end())
				return;

			mCurrentState->Exit(mAgent);
			mCurrentState = iter->second.get();
			mCurrentState->Enter(mAgent);
		}

	private:
		using StateMap = std::unordered_map<std::string, std::unique_ptr<StateType>>;

		AgentType& mAgent;
		StateType* mCurrentState = nullptr;
		StateMap mStates;
	};
}