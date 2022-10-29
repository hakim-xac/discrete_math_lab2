#include "Interface.h"
#include <unordered_set>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>

namespace KHAS {


    void Interface::loop()
    {
        system("cls");
        printHeader();             


        selectPower();
        initSet();
        tablePrinting();

        
        push(delimiter('-'));
        push(stringGeneration(' ', TypeGenerateString::Center, "Выход из программы выполнен!"));
        push(delimiter('-'));
        flush();
    }



    void Interface::printMenu()
    {
        
    }


    void Interface::selectPower() noexcept {

        push(delimiter('-'));
        push(stringGeneration(' ', TypeGenerateString::Center, "Введите мощность множества: (число)"));
        push(delimiter('-'));
        flush();

        int64_t n;
        while (!(std::cin >> n) || n < 0 || !isClamp(n, 1, 26)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            push(delimiter('-'));
            push(stringGeneration(' ', TypeGenerateString::Center, "Ошибка ввода! Повторите ввод!"));
            push(delimiter('-'));
            flush();
        }
        power_ = n;
    }


    void Interface::initSet() noexcept {

        std::unordered_set<char> uset;
        uset.reserve(power_);

        push(delimiter('-'));
        push(stringGeneration(' ', TypeGenerateString::Center, "Всего элементов: " + std::to_string(power_)));
        push(delimiter('-'));
        flush();

        char n;
        char left{'a'};
        char right{'z'};

        for (size_t i{}, ie{ power_ }; i != ie;) {

            push(delimiter('-'));
            push(stringGeneration(' ', TypeGenerateString::Center, "Введите элемент номер " + std::to_string(i + 1)
                , "диапазон: [" + std::string(1, left) + ".." + std::string(1, right) + "]"));
            push(delimiter('-'));
            flush();

            if (std::cin >> n && isClamp(n, left, right)) {
                if (uset.find(n) == uset.end()) {
                    ++i;
                    uset.emplace(n);
                    push(delimiter('-'));
                    push(stringGeneration(' ', TypeGenerateString::Center, "Вы ввели элемент: " + std::string(1, n)));
                    push(delimiter('-'));

                }
                else {
                    push(delimiter('-'));
                    push(stringGeneration(' ', TypeGenerateString::Center, "Ошибка ввода! Данный элемент уже существует! Введите другой!"));
                    push(delimiter('-'));
                }
            }
            else {
                push(delimiter('-'));
                push(stringGeneration(' ', TypeGenerateString::Center, "Ошибка ввода!Повторите ввод элемента!"));
                push(delimiter('-'));
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            flush();
        }

        base_set_.clear();
        base_set_.reserve(uset.size());

        std::copy(uset.begin(), uset.end(), std::back_inserter(base_set_));
        std::sort(base_set_.begin(), base_set_.end());

    }


    size_t Interface::codeGray(size_t n) const noexcept {
        return n ^ (n >> 1);
    }

    std::string Interface::toBinary(size_t n) const noexcept {

        std::string str;
        for (; n; n >>= 1) str = (n & 1 ? "1" : "0") + str;

        std::stringstream ss;
        ss << std::setfill('0') << std::setw(power_) << str;
        return ss.str();
    }

    size_t Interface::definifedElementToAddOrRemove(size_t number) const noexcept {
        number &= (~number + 1);
        size_t n{};
        for (; number; number >>= 1, ++n);
        return n;
    }

    std::string Interface::printSet(const std::vector<char>& base, size_t code_gray) const noexcept {
        std::string tmp, result;
        size_t count_delimiter{};
        for (size_t count{ base.size() - 1 }; code_gray; code_gray >>= 1, --count) {
            if ((code_gray & 1) == 1) {
                if (count_delimiter) tmp += ",";
                tmp += std::string(1, base[count]);
                ++count_delimiter;
            }
        }
        std::move(tmp.rbegin(), tmp.rend(), std::back_inserter(result));
        return "{" + result + "}";
    }

    void Interface::tablePrinting() noexcept
    {
        push(delimiter('='));
        push(stringGeneration(' ', TypeGenerateString::Center, "Вывод таблицы"));
        push(delimiter('-'));
        flush();

        std::string_view head_set{ "множества" };
        std::string general_width(general_width_, ' ');
        push(stringGeneration(' '
            , TypeGenerateString::Justifly
            , "i", general_width
            , "p", general_width
            , "B", general_width
            , head_set.data()));
        push(delimiter('-'));

        for (size_t i{}, ie{ (2ull << (power_ - 1)) }; i != ie; ++i) {
            auto cg{ codeGray(i) };
            push(stringGeneration(' '
                , TypeGenerateString::Justifly
                , std::to_string(i), general_width
                , std::to_string(definifedElementToAddOrRemove(i)), general_width
                , toBinary(cg), general_width
                , printSet(base_set_, cg)));
        }
        flush();
    }
}