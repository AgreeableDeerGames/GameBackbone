#pragma once
#include "stdafx.h"
#include "DllUtil.h"


#include <random>
#include <string>

template class libGameBackbone std::allocator<char>;
template struct libGameBackbone std::char_traits<char>;

template struct libGameBackbone std::_Simple_types<char>;

template union libGameBackbone std::_String_val<std::_Simple_types<char>>::_Bxty;

template class libGameBackbone std::_String_val<std::_Simple_types<char>>;

template class libGameBackbone std::_Compressed_pair<std::_Wrap_alloc<std::allocator<char>>, std::_String_val<std::_Simple_types<char>>, true>;
template class libGameBackbone std::basic_string<char, std::char_traits<char>, std::allocator<char>>;

template class libGameBackbone std::uniform_real_distribution<double>;
template class libGameBackbone std::mersenne_twister_engine<unsigned int,32,624,397,31,2567483615,11,4294967295,7,2636928640,15,4022730752,18,1812433253>;


//template class libGameBackbone std::_Compressed_pair<std::_Wrap_alloc<std::allocator<char>>, std::_String_val<std::_Simple_types<char>>, true>;


//template class __declspec(dllexport) std::allocator<int>;
//template class __declspec(dllexport) std::vector<int>;
//template class __declspec(dllexport) std::string;


namespace GB {

	class libGameBackbone RandGen {
	public:
		RandGen();
		RandGen(std::string seed);

		RandGen(const RandGen& generator) = default;
		RandGen(RandGen&& generator) = default;
		RandGen& operator= (const RandGen& generator) = default;
		RandGen& operator= (RandGen&& generator) = default;
		~RandGen() = default;


		std::string getSeed();
		void setSeed(std::string seed);

		double uniDist(double min, double max);

	private:
		std::string m_seedString;
		std::mt19937 m_generator;
		std::uniform_real_distribution<double> m_uniDistributor;

	};
}