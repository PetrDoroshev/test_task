#include "Utils.h"

std::vector<std::string> splitString(const std::string& input, const std::string& delim) {

    auto split_view = input | std::views::split(delim)  
                            | std::views::transform([](auto&& range) { 
                            return std::string(range.begin(), range.end()); 
            });

            
    return std::vector<std::string> (split_view.begin(), split_view.end());
}