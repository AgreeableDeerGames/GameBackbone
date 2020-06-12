#pragma once

#include <GameBackbone/Core/Updatable.h>
#include <GameBackbone/UserInput/InputHandler.h>

#include <SFML/Window/Event.hpp>

#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>
#include <chrono>
#include <cassert>
#include <string>
#include <iostream>

namespace GB
{
	// FROM: https://blog.tartanllama.xyz/exploding-tuples-fold-expressions/

	template <std::size_t... Idx>
	auto make_index_dispatcher(std::index_sequence<Idx...>) {
		return [](auto&& f) { (f(std::integral_constant<std::size_t, Idx>{}), ...); };
	}

	template <std::size_t N>
	auto make_index_dispatcher() {
		return make_index_dispatcher(std::make_index_sequence<N>{});
	}

	template <typename Tuple, typename Func>
	void for_each(Tuple&& t, Func&& f) {
		constexpr auto n = std::tuple_size<std::decay_t<Tuple>>::value;
		auto dispatcher = make_index_dispatcher<n>();
		dispatcher([&f, &t](auto idx) { f(std::get<idx>(std::forward<Tuple>(t))); });
	}

	// TODO: add deduction guide to type decay everything here
	template <class... Handlers>
	class InputRouter : public InputHandler
	{
	public:

		InputRouter(Handlers... inputHandlers)
		{
			m_handlers = std::tie(std::move(inputHandlers)...);
		}

		// return true if any input handler handled the event
		bool handleEvent(const sf::Event& event) override
		{
			bool eventHandled = false;
			// TODO: use custom for loop here to enforce order of elements and exit early
			for_each(
				m_handlers,
				[&event, &eventHandled](auto& handler)
			{
				if (handler.handleEvent(event))
				{
					eventHandled = true;
				}
			}
			);
			return eventHandled;
		}

	private:
		std::tuple<Handlers...> m_handlers;
	};
}