#include "Event.h"
#include <iostream>
#include <fstream>
#include <ranges>
#include <regex>
#include <optional>

class Time;

std::vector<std::string> splitString(const std::string& input, const std::string& delim);
std::optional<Time> parseTime(const std::string& time_string);


int main(int argc, char* argv[]) {

    if (argc < 2) {
        return 0;
    }

    int tables_num;

    Time start_time;

    Time end_time;

    int rate;

    std::ifstream file(argv[1]);
    std::string line;

    if (file.is_open()) {

        getline(file, line);

        if (std::regex_match(line, std::regex("\\d+"))) {

            tables_num = std::stoi(line);
        }
        else {

            std::cout << line << std::endl;
            return -1;
        }

        getline(file, line);

        if (std::regex_match(line, std::regex("\\d{2}:\\d{2}\\s\\d{2}:\\d{2}"))) {

            auto tokens = splitString(line, " ");

            auto time_1 = parseTime(tokens[0]);
            auto time_2 = parseTime(tokens[1]);

            if (!time_1.has_value() || !time_2.has_value()) {

                std::cout << line << std::endl;
                return -1;
            }

            start_time = time_1.value();
            end_time = time_2.value();
            
        }
        else {

            std::cout << line << std::endl;
            return -1;
        }

        getline(file, line);

        if (std::regex_match(line, std::regex("\\d+"))) {

            rate = std::stoi(line);
        }
        else {

            std::cout << line << std::endl;
            return -1;
        }

        while (getline(file, line)) {



        }

    }

    else {
        std::cout << "Unable to open file" << std::endl;
    }

    return 0;
}


std::vector<std::string> splitString(const std::string& input, const std::string& delim) {

    auto split_view = input | std::views::split(delim)  
                            | std::views::transform([](auto&& range) { 
                            return std::string(range.begin(), range.end()); 
            });

            
    return std::vector<std::string> (split_view.begin(), split_view.end());

}

std::optional<Time> parseTime(const std::string& time_string) {

    Time time;

    auto tokens = splitString(time_string, ":");
    int hours = std::stoi(tokens[0]);
    int minutes = std::stoi(tokens[1]);
   
    try {
        time = Time(hours, minutes);
    }
    catch (std::invalid_argument& ex) {
        return {};
    }

    return time;

}