#include <iostream>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/composite_key.hpp>

struct Phonebook
{
	std::string first_name;
	std::string second_name;
	std::string phone_number;

	Phonebook() = default;
};

using namespace boost::multi_index;

using pnonebook_MultiIndex = multi_index_container
<
	Phonebook, indexed_by
	<
		ordered_non_unique
			<
		    	composite_key
			    	<
		        		Phonebook,
		        		member < Phonebook, std::string, &Phonebook::second_name >,
		        		member < Phonebook, std::string, &Phonebook::first_name >
					>
        	>,
		random_access
			< >,
		hashed_non_unique
			< member < Phonebook, std::string, &Phonebook::first_name > >,
		hashed_non_unique
			< member < Phonebook, std::string, &Phonebook::second_name > >,
		hashed_unique
			< member < Phonebook, std::string, &Phonebook::phone_number > >,
		hashed_unique
			<
				composite_key
			    	<
						Phonebook,
						member < Phonebook, std::string, &Phonebook::second_name >,
						member < Phonebook, std::string, &Phonebook::first_name >,
						member < Phonebook, std::string, &Phonebook::phone_number >
					>
			>
	>
>;

int main()
{
	pnonebook_MultiIndex phonebook;

	phonebook.insert({ "Ivan", "Ivanov", "89990019972" });
	phonebook.insert({ "Petr", "Petrov", "89131122330" });
	phonebook.insert({ "Vasily", "Vasiliev", "89141710605" });
	phonebook.insert({ "Nilolay", "Nikolaev", "89994576231" });
	phonebook.insert({ "Alexey", "Alexeev", "89247676401" });

	// City Printing House

	auto& sorted_by_name_interface = phonebook.get < 0 > ();

	for (const auto& record : sorted_by_name_interface)
		std::cout << record.second_name << ": " << record.phone_number << std::endl;

	std::cout << std::endl;

	// Advertising Agency

	auto& random_access_interface = phonebook.get < 1 > ();

	std::cout << random_access_interface[2].second_name << std::endl;
	std::cout << std::endl;

	for (auto i = 0; i < random_access_interface.size(); ++i)
		std::cout << random_access_interface[i].first_name << ": "
			<< random_access_interface[i].phone_number << std::endl;

	std::cout << std::endl;

	// Regular user

	auto& quick_search_by_first_name = phonebook.get < 2 > ();
	auto& quick_search_by_second_name = phonebook.get < 3 > ();
	auto& quick_search_by_phone_number = phonebook.get < 4 > ();
	auto& quick_search_by_all_params = phonebook.get < 5 > ();

	std::cout << "Alexeev: " << quick_search_by_first_name.find("Alexey")->second_name << std::endl;
	std::cout << "Nikolaev: " << quick_search_by_second_name.find("Nikolaev")->phone_number << std::endl;
	std::cout << "Who has the phone number 89141710605? " << quick_search_by_phone_number.find("89141710605")->second_name << std::endl;
	//std::cout << quick_search_by_all_params.find({ "Nilolay", "Nikolaev", "89994576231" })->phone_number << std::endl;
	
	try
	{
		auto it = quick_search_by_all_params.find(
			boost::make_tuple("Petr", "Petrov", "89131122330"));
		auto number = it->phone_number;
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what();
	}
	
	system("pause");

	return EXIT_SUCCESS;
}