#pragma once

#include <iostream>
#include <sstream>
#include "Enums.h"


namespace KHAS {
    class CommonInterface
    {
    protected:

        //* reset to output */
        void flush();

        //* clear out_buffer_ */
        void clearOutBuffer();

        //* creates a string of length table_width_ and */
        std::string delimiter(char del) const;

        //* prints the header to a stream */
        void printHeader();

        //* prints the menu to a stream */
        virtual void printMenu() = 0;

        //*  */
        void printUnknown();

        //* forwards a string "str" to a temporary buffer "out_buffer_" */
        template <typename TString>
        void push(TString&& str);

        //* generates a string of length table_width_ from the given arguments */
        template <typename ... TString>
        std::string stringGeneration(char aggregate, TypeGenerateString tgs, TString&& ... rest_str);

        //*  */
        template <typename TInput>
        std::pair<TInput, bool> dataInput(ActionWithInputValue awiv = ActionWithInputValue::ErrorReturn) const noexcept;

        //*  */
        template <typename TValue, typename TLower, typename THight>
        constexpr auto clamp(TValue&& v, TLower&& lo, THight&& hi);

        //*  */
        template <typename TValue, typename TLower, typename THight, typename Compare>
        constexpr auto clamp(TValue&& v, TLower&& lo, THight&& hi, Compare comp);

        //*  */
        template <typename TValue, typename TLower, typename THight>
        constexpr bool isClamp(TValue&& v, TLower&& lo, THight&& hi) const;



    public: // public section

        CommonInterface() = delete;
        virtual ~CommonInterface() {};

        //* params */
        // first:   size_t          table_width_    | not default
        // second:  std::ostream&   out_            | default: std::cout
        CommonInterface(std::size_t table_width, std::ostream& out = std::cout);

        //* main program loop */
        virtual void loop() = 0;


    protected:
        const size_t general_width_{ 8 };

    private:    // section for fields

        //* stream buffer */
        std::ostream& cout_;

        //* temprory buffer */
        std::stringstream out_buffer_;

        //* output table width */
        const std::size_t table_width_;
        const std::size_t min_table_width_{ 100 };
    };
}

#include "CommonInterface.hpp"
