#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

bool compare_func(std::vector<int> a, std::vector<int> b) {
    bool a1_big = a[0] > b[0];
    bool a1_eq = a[0] == b[0];
    bool a2_big = a[1] > b[1];
    bool a2_eq = a[1] == b[1];
    bool a3_big = a[2] > b[2];
    bool a3_eq = a[2] == b[2];
    bool a4_big = a[3] > b[3];

    return a1_big || (a1_eq && a2_big) || (a1_eq && a2_eq && a3_big) || (a1_eq && a2_eq && a3_eq && a4_big);
}

bool compare_func_1(std::vector<int> a) {
    return a[0] == 1;
}

bool compare_func_2(std::vector<int> a) {
    return a[0] == 46 && a[1] == 70;
}

bool compare_func_3(std::vector<int> a) {
    return a[0] == 46 || a[1] == 46 || a[2] == 46 || a[3] == 46;
}

void printToConsole(std::string header, std::vector<std::vector<int> > ip_pool) {

    std::cout << header << std::endl;
    for(std::vector<std::vector<int> >::const_iterator ip = ip_pool.begin(); ip != ip_pool.end(); ++ip)
        {
            for(std::vector<int>::const_iterator ip_part = ip->begin(); ip_part != ip->end(); ++ip_part)
            {
                if (ip_part != ip->begin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<std::vector<int> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(split(line, '\t').at(0), '.');
            std::vector<int> res;
            
            for (std::vector<std::string>::const_iterator item = v.cbegin(); item != v.cend(); ++item) {
                try {
                    int number = std::stoi(*item);
                    res.push_back(number);    
                }
                catch (const std::exception &e) {
                    continue;
                }
            } 
            ip_pool.push_back(res);
        }

        // inverse sort vector
        std::sort(ip_pool.begin(), ip_pool.end(), compare_func);

        printToConsole("1) Inverse sort", ip_pool);

        // First byte equals 1
        std::vector<std::vector<int> > eq1;
        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(eq1), compare_func_1);
        printToConsole("2) Sort ip with 1 in first byte", eq1);

        // First byte equals 46 second 70
        std::vector<std::vector<int> > eq2;
        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(eq2), compare_func_2);
        printToConsole("3) Sort ip with 46 in first byte and 70 in second", eq2);

        // First byte equals 46 second 70
        std::vector<std::vector<int> > eq3;
        std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(eq3), compare_func_3);
        printToConsole("4) Sort ip with 46 any byte", eq3);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
