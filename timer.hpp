#pragma once

#include <iostream>
#include <chrono>
#include <string>

namespace jl
{
	class timer
	{
		std::ostream& out;
		const std::string message;
		std::chrono::time_point<std::chrono::high_resolution_clock> start;

	public:
		timer(const std::string& _message, std::ostream& _out = std::cerr) : message(_message), out(_out)
		{
			start = std::chrono::high_resolution_clock::now();
		}
		~timer()
		{
			std::chrono::duration<float, std::milli> life_span = std::chrono::high_resolution_clock::now() - start;
			out << message << ": " << life_span.count() << std::endl;
		}
	};
}