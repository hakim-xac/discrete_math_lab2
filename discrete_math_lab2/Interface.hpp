#pragma once

#include <sstream>
#include <iomanip>
#include "Interface.h"

namespace KHAS {

    template <typename TString, typename>
    inline void Interface::format(TString&& str) const noexcept {

        auto str_{ std::forward<TString>(str) };
        std::stringstream ss;
        ss << std::fixed << "|" << std::setfill(' ') << std::setw(str_.width_first) << str_.first << std::setw(str_.width_first) << "|"
            << std::setfill(' ') << std::setw(str_.width_first) << str_.second << std::setw(str_.width_first) << "|"
            << std::setfill(' ') << std::setw(str_.width_first) << " "
            << std::setfill(str_.is_head == TypeFormat::isBody ? '0' : ' ') << std::setw(str_.width_second) << str_.third
            << std::setfill(' ') << std::setw(str_.width_first) << "|"
            << std::setw(str_.width_first) << std::setfill(' ') << std::setw(str_.width_third) << str_.fourth << std::setw(str_.width_first) << "|\n";

        std::cout << ss.str() << std::string(ss.str().length() - 1, '-') << "\n";
    }

}