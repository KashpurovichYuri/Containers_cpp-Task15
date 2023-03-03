#include <iostream>
#include <chrono>
#include <random>
#include <set>
#include <string>
#include <array>
#include <functional>
#include <unordered_set>
#include "Hash Functions/Hash Functions.cpp"

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

template < 	unsigned int (*Function)(const char*, unsigned int) >
auto calculation_of_number_of_collisions(const std::set< std::string >& set_of_string, std::vector< std::vector< int> >& points)
{
	std::set < std::size_t > collisions;
	auto num_of_collisions = 0, i = 0;
	for (const auto& string : set_of_string)
	{
		auto pair = collisions.insert(Function(string.c_str(), string.size()));
		auto flag = pair.second;
		if (!flag)
			num_of_collisions++;

		std::vector<int> point{i, num_of_collisions};
		points.push_back(point);
		i++;

		if (!flag)
			std::cout << point[0] << " " << point[1] << std::endl;
	}
}

int main()
{
	const std::size_t N = 10000000;
	const std::size_t length = 6;
	std::set< std::string > set_of_string = make_random_words(N, length);

	//std::array< std::array< std::size_t, 2 >, N > pointsRS;
	//=> if I will do all for 2D-std::array it won't work but why? => Because there is a question about the size of set_of_strings
	
	std::cout << "RS Hash Function" << std::endl;
	std::vector < std::vector <int> > pointsRS;
	calculation_of_number_of_collisions < RSHash > (set_of_string, pointsRS);
	std::cout << std::endl;

	std::cout << "JS Hash Function" << std::endl;
	std::vector < std::vector <int> > pointsJS;
	calculation_of_number_of_collisions < JSHash >(set_of_string, pointsJS);
	std::cout << std::endl;

	std::cout << "PJW Hash Function" << std::endl;
	std::vector < std::vector <int> > pointsPJW;
	calculation_of_number_of_collisions < PJWHash >(set_of_string, pointsPJW);
	std::cout << std::endl;

	std::cout << "ELF Hash Function" << std::endl;
	std::vector < std::vector <int> > pointsELF;
	calculation_of_number_of_collisions < ELFHash >(set_of_string, pointsELF);
	std::cout << std::endl;

	std::cout << "BKDR Hash Function" << std::endl;
	std::vector < std::vector <int> > pointsBKDR;
	calculation_of_number_of_collisions < BKDRHash >(set_of_string, pointsBKDR);
	std::cout << std::endl;
	
	std::cout << "SDBM Hash Function" << std::endl;
	std::vector < std::vector <int> > pointsSDBM;
	calculation_of_number_of_collisions < SDBMHash >(set_of_string, pointsSDBM);
	std::cout << std::endl;
	
	std::cout << "DJB Hash Function" << std::endl;
	std::vector < std::vector <int> > pointsDJB;
	calculation_of_number_of_collisions < DJBHash >(set_of_string, pointsDJB);
	std::cout << std::endl;
	
	std::cout << "DEK Hash Function" << std::endl;
	std::vector < std::vector <int> > pointsDEK;
	calculation_of_number_of_collisions < DEKHash >(set_of_string, pointsDEK);
	std::cout << std::endl;
	
	std::cout << "AP Hash Function" << std::endl;
	std::vector < std::vector <int> > pointsAP;
	calculation_of_number_of_collisions < APHash >(set_of_string, pointsAP);
	std::cout << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}