#include "Interface.h"
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

namespace KHAS {


    void Interface::loop()
    {
        system("cls");
        printHeader();


        /////////////
        
        constexpr size_t width{ 4 };
        std::string_view head_set{ "множества" };


        auto power{ selectPower() };
        auto base{ initSet(power) };


        format(FormatStruct<std::string>{ width, power, head_set.length() + power, "i", "p", "B", head_set.data(), TypeFormat::isHead });

        for (size_t i{}, ie{ (2ull << (power - 1)) }; i != ie; ++i) {
            auto cg{ codeGray(i) };
            format(FormatStruct<std::string>{
                width
                    , power
                    , head_set.length() + power
                    , std::to_string(i)
                    , std::to_string(definifedElementToAddOrRemove(i))
                    , toBinary(cg)
                    , printSet(base, cg)
                    , TypeFormat::isBody });
        }
        
        
        
        ///////////////////


            
        printMenu();
        
        push(delimiter('-'));
        push(stringGeneration(' ', "Выход из программы выполнен!"));
        push(delimiter('-'));
        flush();
    }



    void Interface::printMenu()
    {
        
    }


    size_t Interface::selectPower() const noexcept {
        std::cout << "Введите мощность множества: (число)\n";
        int64_t n;
        while (!(std::cin >> n) || n < 0) {
            std::cout << "Ошибка ввода! Повторите ввод!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        return n;
    }


    std::vector<char> Interface::initSet(size_t power) const noexcept {

        std::unordered_set<char> uset;
        uset.reserve(power);

        std::cout << "Всего элементов: " << power << "\n";
        char n;
        for (size_t i{}, ie{ power }; i != ie;) {
            std::cout << "Введите элемент номер " << i + 1 << "\n";
            if (std::cin >> n && isValidityElements(n)) {
                if (uset.find(n) == uset.end()) {
                    ++i;
                    uset.emplace(n);
                    std::cout << "Вы ввели элемент: " << n << "\n";
                }
                else std::cout << "Ошибка ввода! Данный элемент уже существует! Введите другой!\n";
            }
            else std::cout << "Ошибка ввода! Повторите ввод элемента!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::vector<char> result;
        result.reserve(uset.size());

        std::copy(uset.begin(), uset.end(), std::back_inserter(result));
        std::sort(result.begin(), result.end());

        return result;
    }


    bool Interface::isValidityElements(char c) const noexcept {
        return std::tolower(c) >= 'a' && std::tolower(c) <= 'z';
    }


    size_t Interface::codeGray(size_t n) const noexcept {
        return n ^ (n >> 1);
    }

    std::string Interface::toBinary(size_t n) const noexcept {
        std::string r;
        for (; n; n >>= 1) r = (n & 1 ? "1" : "0") + r;
        return r;
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
}