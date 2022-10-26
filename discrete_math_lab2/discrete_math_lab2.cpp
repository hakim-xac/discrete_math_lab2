#include <iostream>
#include <iomanip>
#include <iterator>
#include <bitset>
#include <string>
#include <type_traits>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

//*   declarations */
enum class TypeFormat {
    isHead, isBody
};

template <typename TString, typename = std::enable_if_t<std::is_convertible_v<TString, std::string>>>
struct FormatStruct {
    size_t width_first;
    size_t width_second;
    size_t width_third;
    TString first;
    TString second;
    TString third;
    TString fourth; 
    TypeFormat is_head;
};


size_t codeGray(size_t n);
size_t definifedElementToAddOrRemove(size_t number);
size_t selectPower();
bool isValidityElements(char c);
std::string toBinary(size_t n);
std::string printSet(const std::vector<char>& umap, size_t code_gray);
std::vector<char> initSet(size_t power);

template <typename TString, typename = std::enable_if_t<std::is_convertible_v<TString, FormatStruct<std::string>>>>
inline void format(TString&& str);

//////////////////////////////////////////////////////////////////////////////
//*  Entry Point  */
int main()
{
    setlocale(LC_ALL, "Russian");

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


}
////////////////////////////////////////////////////////////////////////////////////
//*   definitions */



size_t selectPower() {
    std::cout << "Введите мощность множества: (число)\n";
    int64_t n;
    while (!(std::cin >> n) || n < 0) {
        std::cout << "Ошибка ввода! Повторите ввод!\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return n;
}

size_t codeGray(size_t n) {
    return n ^ (n >> 1);
}

std::string toBinary(size_t n) {
    std::string r;
    for (; n; n >>= 1) r = (n & 1 ? "1" : "0") + r;
    return r;
}

template <typename TString, typename>
void format(TString&& str) {
    auto str_{ std::forward<TString>(str) };
    std::stringstream ss;
    ss << std::fixed << "|" << std::setfill(' ') << std::setw(str_.width_first) << str_.first << std::setw(str_.width_first) << "|"
        << std::setfill(' ') << std::setw(str_.width_first) << str_.second << std::setw(str_.width_first) << "|"
        << std::setfill(' ') << std::setw(str_.width_first) << " "
        << std::setfill(str_.is_head == TypeFormat::isBody ? '0' : ' ') << std::setw(str_.width_second) << str_.third
        << std::setfill(' ') << std::setw(str_.width_first) << "|"
        << std::setw(str_.width_first) << std::setfill(' ') << std::setw(str_.width_third) << str_.fourth << std::setw(str_.width_first) << "|\n";

    std::cout << ss.str() <<  std::string(ss.str().length() - 1, '-') << "\n";
}

size_t definifedElementToAddOrRemove(size_t number) {
    number &= (~number + 1);
    size_t n{};
    for (; number; number >>= 1, ++n);
    return n;
}


std::vector<char> initSet(size_t power) {

    std::unordered_set<char> uset;
    uset.reserve(power);

    std::cout << "Всего элементов: " << power << "\n";
    char n;
    for (size_t i{}, ie{ power }; i != ie;) {
        std::cout << "Введите элемент номер " << i+1 << "\n";
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


bool isValidityElements(char c) {
    return std::tolower(c) >= 'a' && std::tolower(c) <= 'z';
}


std::string printSet(const std::vector<char>& base, size_t code_gray) {
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