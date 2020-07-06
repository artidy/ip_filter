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
        std::copy_if(ip_pool.begin(), ip_pool.end(), eq1.begin(), compare_func_1);
        printToConsole("2) Sort ip with 1 in first byte", eq1);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
