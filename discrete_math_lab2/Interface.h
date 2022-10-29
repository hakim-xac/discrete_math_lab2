#pragma once

#include "CommonInterface.h"
#include <iostream>
#include <unordered_set>
#include <sstream>

namespace KHAS {

    class Interface final : public CommonInterface
    {
        using Type = size_t;


    private:

        template <typename TString, typename = std::enable_if_t<std::is_convertible_v<TString, std::string>>>
        inline void format(TString&& str) const noexcept;

        void selectPower() noexcept;

        void initSet() noexcept;

        size_t codeGray(size_t n) const noexcept;

        size_t definifedElementToAddOrRemove(size_t number) const noexcept;

        std::string toBinary(size_t n) const noexcept;

        std::string printSet(const std::vector<char>& umap, size_t code_gray) const noexcept;

        void tablePrinting() noexcept;

    public:
        void loop() override;
        void printMenu() override;

        //* params */
        // first:   size_t          table_width_    | not default
        // second:  std::ostream&   out_            | default: std::cout
        Interface(std::size_t table_width, std::ostream& out = std::cout)
            : CommonInterface(table_width, out) 
            , power_()
            , base_set_() {};

    private:
        size_t power_;
        std::vector<char> base_set_;
    };

}