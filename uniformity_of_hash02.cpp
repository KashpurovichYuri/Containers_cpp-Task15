#include <iostream>
#include <chrono>
#include <random>
#include <set>
#include <string>
#include <array>
#include <functional>
#include <unordered_set>

std::set < std::string > make_random_words(std::size_t N, std::size_t length) // length = 10 - good enough
{
	std::uniform_int_distribution <> letter(97, 122);
	std::default_random_engine e(static_cast <std::size_t> (
		std::chrono::system_clock::now().time_since_epoch().count()));

	std::set < std::string > words;

	for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
		for (auto& c : s)
			c = letter(e);

	return words;
}

// http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html

template < typename T >
void hash_combine(std::size_t& seed, const T& value) noexcept
{
	seed ^= std::hash < T >()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template < typename T >
void hash_value(std::size_t& seed, const T& value) noexcept
{
	hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t& seed, const T& value, const Types & ... args) noexcept
{
	hash_combine(seed, value);
	hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types & ... args) noexcept
{
	std::size_t seed = 0;
	hash_value(seed, args...);
	return seed;
}

int main()
{	
	const auto N = 100000000;
	const auto length = 6;
	//const auto NI = 1000000;
	auto set_of_unique_strings = make_random_words(N, length);

	std::set < std::size_t > collisions;
	auto num_of_collisions = 0;
	auto i = 0;
	for (const auto& string : set_of_unique_strings)
	{
		//auto integral = rand() % NI;
		auto [useless, flag] = collisions.insert(hash_value(string));
		if (!flag)
		{
			std::cout << flag;
			num_of_collisions++;
			std::cout << i << " " << num_of_collisions << std::endl;
		}
		++i;
	}

	system("pause");

	return EXIT_SUCCESS;
}