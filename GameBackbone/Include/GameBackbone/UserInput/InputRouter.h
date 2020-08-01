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
#include <type_traits>

namespace GB
{
	namespace Detail
	{
		// FROM: https://blog.tartanllama.xyz/exploding-tuples-fold-expressions/

		template <std::size_t... Idx>
		auto make_index_dispatcher(std::index_sequence<Idx...>)
		{
			return [](auto&& f) { (f(std::integral_constant<std::size_t, Idx>{}), ...); };
		}

		template <std::size_t N>
		auto make_index_dispatcher()
		{
			return make_index_dispatcher(std::make_index_sequence<N>{});
		}

		template <typename Tuple, typename Func>
		void for_each(Tuple&& t, Func&& f)
		{
			constexpr auto n = std::tuple_size<std::decay_t<Tuple>>::value;
			auto dispatcher = make_index_dispatcher<n>();
			dispatcher( [&f, &t] (auto idx) { f(std::get<idx>(std::forward<Tuple>(t))); } );
		}


		/// <summary> Checks if all types fulfill the requirements of a CompoundSprite component. (Drawable and Transformable) </summary>
		template <class... InTypes>
		inline constexpr bool are_all_input_handlers_v = (std::is_base_of_v<InputHandler, InTypes> && ...);
	}

	template <class... Handlers>
	class InputRouter final : public InputHandler
	{
	public:

		template < std::enable_if_t<Detail::are_all_input_handlers_v<Handlers...>, bool> = true>
		InputRouter(Handlers... inputHandlers) :
			m_handlers(std::make_tuple(std::move(inputHandlers)...))
		{
		}

		// return true if any input handler handled the event
		bool handleEvent(sf::Int64 elapsedTime, const sf::Event& event) final
		{
			bool eventHandled = false;

			// Loop through all sub-handlers until handles the event
			Detail::for_each(
				m_handlers,
				[&event, &eventHandled, elapsedTime](auto& handler)
				{
					// Only attempt to handle an event that has not been handled yet
					if (!eventHandled)
					{
						if (handler.handleEvent(elapsedTime, event))
						{
							eventHandled = true;
						}
					}
				}
			);
			return eventHandled;
		}

	private:
		std::tuple<Handlers...> m_handlers;
	};
}