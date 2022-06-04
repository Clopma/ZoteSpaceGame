#pragma once
#include "Core.h"
#include <functional>
#include <vector>

namespace Zote
{
	#define ADD_LISTENER(Class, Func) AddListener(&Class::Func); 

	template<typename TClass, typename TArgs>
	class Event
	{
		using EventFunc = std::function<void(const TClass&, TArgs)>;
	;	std::vector<EventFunc> functions;
		int count;

	public:

		Event() : count(0) {}
		~Event() { RemoveAllListeners(); }

		int AddListener(EventFunc function)
		{
			count++;
			functions.push_back(function);
			return count - 1;
		}

		void RemoveListener(int index)
		{
			if (index < 0 || index >= count) return;
			functions.erase(functions.begin() + index);
		}
		void RemoveAllListeners() 
		{
			if (functions.size() == 0) return;
			functions.clear();
		}

		void Invoke(const TClass& sender, TArgs args)
		{
			if (functions.size() == 0) return;
			for (EventFunc function : functions)
				function(sender, args);
		}
	};
}

