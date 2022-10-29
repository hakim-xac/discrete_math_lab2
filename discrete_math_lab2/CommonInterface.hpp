#pragma once
#include "CommonInterface.h"
#include <algorithm>
#include <numeric>
#include <string>
#include <cassert>
#include <limits>
#include <functional>

namespace KHAS {

    template <typename TString>
    inline void CommonInterface::push(TString&& str) {
        out_buffer_ << std::forward<TString>(str);
        out_buffer_ << '\n';
    }

    template<typename ...TString>
    inline std::string CommonInterface::stringGeneration(char aggregate, TypeGenerateString tgs, TString&& ... str)
    {
        static_assert(sizeof...(str) > 0);

        std::initializer_list forward_str{ std::string(std::forward<TString>(str))... };

        std::string result{ std::accumulate(
            forward_str.begin()
            , forward_str.end()
            , std::string{}
            , [](auto&& lhs, auto&& rhs) {
                auto result{ lhs + rhs };
                return result;
            }) };
        
        size_t diff_len{};
        switch (tgs)
        {
        case KHAS::TypeGenerateString::Center:
            diff_len = (table_width_ - result.size()) >> 1;
            result = "#" + std::string(diff_len, aggregate) + result;
            result += std::string(table_width_ - result.size() - 1, aggregate) + "#";
            break;
        case KHAS::TypeGenerateString::Justifly:
            diff_len = general_width_;
            result = "#" + std::string(diff_len, aggregate) + result;

            assert(table_width_ - diff_len - 1 >= result.size());   // assert
            result += std::string(table_width_ - result.size() - diff_len - 1, aggregate) + std::string(diff_len, aggregate) + "#";
            break;
        }

        assert(result.size() == table_width_);  // assert
        return result;
    }

    template<typename TInput>
    inline std::pair<TInput, bool> CommonInterface::dataInput(ActionWithInputValue awiv) const noexcept
    {
        using T = std::decay_t<TInput>;

        T tmp;
        std::cin >> tmp;

        if (awiv == ActionWithInputValue::ErrorReturn) {

            bool is_good{ std::cin.good() };

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (is_good) return { tmp, true };
            return { T(), false };
        }

        while (awiv == ActionWithInputValue::LoopIsError && std::cin.fail()) {

            std::cout << "Повторите ввод!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> tmp;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return { tmp, true };        
    }

    template <typename TValue, typename TLower, typename THight>
    inline constexpr auto CommonInterface::clamp(TValue&& v, TLower&& lo, THight&& hi) {
        return clamp(std::forward<TValue>(v), std::forward<TLower>(lo), std::forward<THight>(hi), std::less{});
    }

    template <typename TValue, typename TLower, typename THight, typename Compare>
    inline constexpr auto CommonInterface::clamp(TValue&& v, TLower&& lo, THight&& hi, Compare comp) {
        auto value{ std::forward<TValue>(v) };
        auto lower{ std::forward<TLower>(lo) };
        auto hight{ std::forward<THight>(hi) };
        return comp(value, lower) ? lower : comp(hight, value) ? hight : value;
    }

    template <typename TValue, typename TLower, typename THight>
    inline constexpr bool CommonInterface::isClamp(TValue&& v, TLower&& lo, THight&& hi) const {
        auto value{ std::forward<TValue>(v) };
        auto lower{ std::forward<TLower>(lo) };
        auto hight{ std::forward<THight>(hi) };
        return value >= lower && value <= hight;
    }    
    
    
}