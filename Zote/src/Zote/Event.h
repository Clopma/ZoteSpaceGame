#pragma once
#include <functional>
#include <vector>

namespace Zote
{
	#define DELEGATE(Args, Instance, Subscriber, Method)\
		Zote::Delegate<Args>(Instance, &Subscriber::Method)

	template<class TArgs>
	class Delegate
	{
		using Method = std::function<void(TArgs)>;
		Method method;

	public:
		
		template<class Subscriber>
		Delegate(Subscriber subscriber, void (Subscriber::*function)(TArgs))
		{
			method = std::bind(function, subscriber, std::placeholders::_1);
		}

		void Invoke(TArgs args)
		{
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