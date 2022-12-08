#ifndef TASK4_CSV_PARSER_H
#define TASK4_CSV_PARSER_H

#include <fstream>
#include <memory>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

#include "tuple_utility.h"
#include "CSV_parser_errors.h"

template<typename... Types>
class CSVParser
{
public:
    class InputIterator;

    explicit CSVParser(std::ifstream & ifs,
                       size_t line_offset = 0,
                       const std::string & column_delim = ",",
                       const std::string & row_delim = "\n")
        : m_ifs(ifs),
          m_line_offset(line_offset),
          m_column_delim(column_delim),
          m_line_delim(row_delim),
          m_current_line(0)
    {
        if (!m_ifs.is_open())
            throw std::ifstream::failure("File is not open");

        // enable logical error and read/writing error on i/o operation
        m_ifs.exceptions(std::ifstream::badbit);
    }

    CSVParser(const CSVParser<Types...> & src) = delete;

    InputIterator begin()
    {
        // Set goodbit error state flags
        m_ifs.clear();
        // Set the position of the next extracted character at the beginning of the stream
        m_ifs.seekg(0, std::ifstream::beg);

        // Skip first lines
        for (int i = 0; i < m_line_offset; ++i)
            GetLine();

        return InputIterator(*this, InputIterator::Mode::begin);
    }

    InputIterator end()
    {
        return InputIterator(*this, InputIterator::Mode::end);
    }

private:
    std::ifstream & m_ifs;
    std::regex m_column_delim;
    std::regex m_line_delim;
    size_t m_line_offset;
    size_t m_current_line;

    std::string GetLine()
    {
        std::string buffer;
        char sym;

        while (m_ifs.get(sym) && !std::regex_search(buffer + sym, m_line_delim))
            buffer += sym;

        ++m_current_line;
        return buffer;
    }

    std::vector<std::string> RowToVector(const std::string & line)
    {
        std::sregex_token_iterator first(line.begin(), line.end(),
                                         m_column_delim, -1);
        std::sregex_token_iterator last;
        std::vector<std::string> values(first, last);

        if (values.size() < sizeof...(Types))
            throw CSVException(m_current_line, values.size() + 1, "Few columns");
        if (values.size() > sizeof...(Types))
            throw CSVException(m_current_line, sizeof...(Types) + 1, "Many columns");

        return values;
    }

    void EscapeCharacters(std::string & line)
    {
//        std::regex pattern("\0\a\r\n\t\v\'\"\?\\");
//        line = std::regex_replace(line, pattern, "\\t");
    }
};

template<typename... Types>
class CSVParser<Types...>::InputIterator
{
public:
    using value_type = std::tuple<Types...>;
    using reference = std::tuple<Types...> &;
    using pointer = std::shared_ptr<std::tuple<Types...>>;
    enum class Mode
    {
        begin,
        end
    };

    InputIterator(CSVParser<Types...> & parent,
                  Mode mode)
        :  m_parent(parent)
    {
        switch (mode)
        {
            case Mode::begin:
                UpdatePtr();
                break;
            case Mode::end:
                m_ptr = nullptr;
                break;
        }
    }

    reference operator*() const
    {
        return *m_ptr;
    }

    const InputIterator operator++()
    {
        UpdatePtr();
        return *this;
    }

    const InputIterator operator++(int)
    {
        const InputIterator tmp = *this;
        UpdatePtr();
        return tmp;
    }

    bool operator==(const InputIterator & a) const
    {
        return a.m_ptr == m_ptr;
    }

    bool operator!=(const InputIterator & a) const
    {
        return a.m_ptr != m_ptr;
    };

private:
    pointer m_ptr;
    CSVParser<Types...> & m_parent;

    void UpdatePtr()
    {
        std::string buff = m_parent.GetLine();
        if (buff.empty())
            m_ptr = nullptr;
        else
        {
            try
            {
                m_ptr = std::make_shared<value_type>(MakeTuple<Types...>(m_parent.RowToVector(buff)));
            }
            catch (size_t idx)
            {
                throw CSVException(m_parent.m_current_line, idx + 1, "Data type mismatch");
            }
        }
    }
};

#endif //TASK4_CSV_PARSER_H
