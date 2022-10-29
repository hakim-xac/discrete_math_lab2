#include "CommonInterface.h"
#include <Windows.h>
#include <cassert>
#include <unordered_map>


namespace KHAS {

    void CommonInterface::printHeader()
    {
        push(delimiter('='));
        push(stringGeneration(' ', TypeGenerateString::Justifly, "Дисциплина:", std::string(50, ' '), "Дискретная математика"));
        push(stringGeneration(' ', TypeGenerateString::Justifly, "Лабораторня работа:", std::string(50, ' '), "№ 2"));
        push(delimiter('-'));
        push(stringGeneration(' ', TypeGenerateString::Justifly, "Тема:", std::string(56, ' '), "Генерация подмножеств"));
        push(stringGeneration(' ', TypeGenerateString::Justifly, "Выполнил студент:", std::string(52, ' '), "Хакимов А.С."));
        push(delimiter('='));
        flush();
    }

    void CommonInterface::printUnknown()
    {
        push(delimiter('-'));
        push(stringGeneration(' ', TypeGenerateString::Center, "Ошибка ввода! Повторите ввод!"));
        push(delimiter('-'));
        flush();
    }

    void CommonInterface::flush()
    {
        cout_ << out_buffer_.str();
        clearOutBuffer();
    }

    void CommonInterface::clearOutBuffer()
    {
        out_buffer_.str("");
    }

    std::string CommonInterface::delimiter(char del) const
    {
        assert(table_width_ >= min_table_width_);
        std::string tmp(table_width_, del);
        tmp.front() = tmp.back() = '#';
        return tmp;
    }

    CommonInterface::CommonInterface(std::size_t table_width, std::ostream& out)
        : cout_(out)
        , out_buffer_()
        , table_width_(table_width)
    {
        assert(table_width >= min_table_width_);
    }
}