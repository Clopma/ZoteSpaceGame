#pragma once
#include <functional>
#include <vector>

namespace Zote
{
	#define SUBSCRIBE(DelegateMethod, Subscriber, Method, Instance) \
		using std::placeholders::_1;\
		DelegateMethod = std::bind(&Subscriber::Method, Instance, _1);

	template<class TArgs>
	class Delegate
	{
	public:
		using Method = std::function<void(TArgs)>;
		Method method = nullptr;

		Delegate() {}

		void Invoke(TArgs args)
		{  
			if (method == nullptr)
				return;
			method(args);
		}
	};

	template<class TArgs>
	class Event
	{
		std::vector<Delegate<TArgs>> subscribers;
		int count;

	public:

		Event() : count(0) {}
		Event(Event& other) = delete;
		Event(Event&& other) = delete;
		~Event()
		{
			RemoveAllListeners();
		}

		int AddListener(Delegate<TArgs> subscriber)
		{
			subscribers.push_back(subscriber);
			count++;
			return count - 1;
		}

		void RemoveListener(int index)
		{
			if (index < 0 || index >= count)
				return;
			subscribers.erase(subscribers.begin() + index);
		}

		void RemoveAllListeners()
		{
			if (subscribers.size() == 0)
				return;
			subscribers.clear();
		}

		void Invoke(TArgs args)
		{
			if (subscribers.size() == 0)
				return;
			for (Delegate<TArgs> subscriber : subscribers)
				subscriber.Invoke(args);
		}
	};
}

