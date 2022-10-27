#pragma once

#include "CommonInterface.h"
#include <iostream>
#include <unordered_set>
#include <sstream>

namespace KHAS {

    class Interface final : public CommonInterface
    {
        using Type = size_t;


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

    private:

        template <typename TString, typename = std::enable_if_t<std::is_convertible_v<TString, FormatStruct<std::string>>>>
        inline void format(TString&& str) const noexcept;

        size_t selectPower() const noexcept;

        std::vector<char> initSet(size_t power) const noexcept;

        bool isValidityElements(char c) const noexcept;

        size_t codeGray(size_t n) const noexcept;

        size_t definifedElementToAddOrRemove(size_t number) const noexcept;

        std::string toBinary(size_t n) const noexcept;

        std::string printSet(const std::vector<char>& umap, size_t code_gray) const noexcept;



    public:
        void loop() override;
        void printMenu() override;

        //* params */
        // first:   size_t          table_width_    | not default
        // second:  std::ostream&   out_            | default: std::cout
        Interface(std::size_t table_width, std::ostream& out = std::cout)
            : CommonInterface(table_width, out) {};

    private:

    };

}

#include "Interface.hpp"