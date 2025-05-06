#include "events/Event.h"
#include "Club.h"
#include "Utils.h"
#include "Time.h"
#include <iostream>
#include <fstream>
#include <ranges>
#include <regex>
#include <optional>

int main(int argc, char *argv[]) {

    if (argc < 2) {

        std::cout << "file not specified !" << std::endl;
        return EXIT_FAILURE;
    }

    int tables_amount;

    Time start_time;

    Time end_time;

    int rate;

    std::ifstream file(argv[1]);
    std::string line;

    if (!file.is_open()) {

        std::cout << "Unable to open file" << std::endl;
        return EXIT_FAILURE;
    }

    getline(file, line);

    if (std::regex_match(line, std::regex("\\d+"))) {

        tables_amount = std::stoi(line);
    }
    else {

        std::cout << line << std::endl;
        return EXIT_FAILURE;
    }

    getline(file, line);

    if (std::regex_match(line, std::regex("\\d{2}:\\d{2}\\s\\d{2}:\\d{2}"))) {

        auto tokens = splitString(line, " ");

        try {

            start_time = Time(tokens[0]);
            end_time = Time(tokens[1]);
        }
        catch (std::invalid_argument &ex) {

            std::cout << line << std::endl;
            return EXIT_FAILURE;
        }
    }
    else {

        std::cout << line << std::endl;
        return EXIT_FAILURE;
    }

    getline(file, line);

    if (std::regex_match(line, std::regex("\\d+"))) {

        rate = std::stoi(line);
    }
    else {

        std::cout << line << std::endl;
        return EXIT_FAILURE;
    }

    auto club = Club(tables_amount, start_time, end_time, rate);

    while (getline(file, line)) {

        if (std::regex_match(line, std::regex("\\d{2}:\\d{2}\\s\\d{1,2}\\s[a-z, 1-9,_,-]+\\s{0,1}\\d*"))) {

            try {

                club.processEvent(new ClientEvent(line));
            }
            catch(std::invalid_argument &ex) {

                std::cout << line << std::endl;
                std::cout << ex.what() << std::endl;
                return EXIT_FAILURE;
            }
        }

        else {

            std::cout << line << std::endl;
            return EXIT_FAILURE;
        }
    }

    club.closeClub();
    club.printEvents();

    for (auto& table: club.getTables()) {

        std::cout << table.getIncome(club.getRate()) << ", " << table.getTimeOccupied().toString() << std::endl;

    }

    file.close();

    return EXIT_SUCCESS;
}
