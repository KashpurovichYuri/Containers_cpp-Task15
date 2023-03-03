#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <random>
#include <algorithm>
#include "timer/timer.cpp"

template <typename AC, typename C>
auto time_measure_associate_container(AC ass_container, const C& container)
{
    Timer time{ "start filling of set", std::cout };
    for (const auto& elem : container)
        ass_container.emplace(elem);
    time.stop();

    return time.get_time();
}

template <typename Conteiner>
auto time_measure_by_std_sort(Conteiner conteiner)
{
    Timer time{ "start sort of vector", std::cout };
    std::sort(conteiner.begin(), conteiner.end());
    time.stop();

    return time.get_time();
}

auto test_result(std::vector< std::vector<double> >& seria)
{
    std::vector<double> res;

    for (size_t j = 0; j < seria[0].size(); j++)
    {
        double sum = 0;
        for (size_t i = 0; i < seria.size(); i++)
        {
            sum += seria[i][j];
            std::cout << seria[i][j] << " ";
        }
        std::cout << std::endl << std::endl;
        res.push_back(sum / seria.size());
    }

    return res;
}

int main()
{
    const auto N = 1000;

    std::uniform_int_distribution<int> distribution(0, 100 * N);
    std::mt19937 engine; //  Mersenne twister MT19937

    std::vector<int> vector(N);
    for (auto& elem : vector)
    {
        auto new_elem = distribution(engine);
        if (std::find(vector.begin(), vector.end(), new_elem) == vector.end())
            elem = new_elem;
    }

    std::set < int > set;

    std::vector< std::vector<double> > seria(50);
    for (auto& current : seria)
    {
        current.push_back(time_measure_associate_container(set, vector)); // #0
        current.push_back(time_measure_by_std_sort(vector));              // #1
    }

    auto result = test_result(seria);
    std::cout << std::endl << std::endl;
    for (auto& elem : result)
        std::cout << elem << " ";

    system("pause");

    return EXIT_SUCCESS;
}

/*
-----------
N == 100000

set:    0.178788 | 0.145017 0.146847 0.142947 0.157437 0.155807 0.156883 0.158974 0.164481 0.161834 0.166590 0.163396 0.150666 0.143503 0.142517 0.148793 0.142090 0.158475 0.159222 0.157147 0.156605 0.386238 0.217926 0.244426 0.199638 0.238870 0.241543 0.217089 0.235481 0.158589 0.178958 0.158725 0.144252 0.162783 0.204057 0.213631 0.145674 0.160119 0.174097 0.205991 0.212599 0.168450 0.227031 0.176677 0.178998 0.172414 0.145560 0.149007 0.153786 0.198321 0.189223 

vector: 0.052003 | 0.058308 0.057303 0.046071 0.045909 0.046138 0.046155 0.045356 0.047798 0.046468 0.047000 0.046247 0.046365 0.059272 0.059957 0.056982 0.046612 0.045955 0.046061 0.046086 0.047791 0.055665 0.046680 0.046131 0.073372 0.048048 0.051085 0.046728 0.059164 0.047011 0.063056 0.058569 0.062806 0.047898 0.062732 0.046155 0.045978 0.047687 0.051082 0.049868 0.056766 0.089694 0.064543 0.048104 0.049401 0.046038 0.047404 0.047577 0.050569 0.047324 0.055164 

-----------
N == 1000

set:    0.004854 | 0.003547 0.001614 0.003452 0.003203 0.003778 0.003193 0.004789 0.003442 0.003750 0.003479 0.003493 0.003253 0.003411 0.018180 0.005075 0.003253 0.003190 0.003406 0.008776 0.005918 0.003555 0.003177 0.003205 0.003850 0.003919 0.005224 0.005176 0.003479 0.003777 0.003253 0.003561 0.006540 0.005172 0.006372 0.003535 0.003183 0.003240 0.006901 0.007661 0.006472 0.005135 0.005551 0.003309 0.003210 0.002837 0.005924 0.005500 0.005143 0.018775 0.003843


vector: 0.003343 | 0.001127 0.002236 0.002509 0.004894 0.005493 0.003965 0.004616 0.004478 0.005144 0.004553 0.004117 0.004785 0.002184 0.002093 0.003332 0.006677 0.002310 0.002086 0.002142 0.002157 0.006928 0.005167 0.004171 0.003790 0.002142 0.002680 0.002126 0.004549 0.004122 0.004010 0.002633 0.002100 0.002052 0.002069 0.004287 0.006309 0.002134 0.002172 0.002123 0.002096 0.002105 0.002322 0.005366 0.004045 0.002090 0.002146 0.002790 0.002075 0.002269 0.003404

*/