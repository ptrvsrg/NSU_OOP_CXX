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
                       char column_delim = ',',
                       char row_delim = '\n',
                       char escape_sym = '\"')
        : m_ifs(ifs),
          m_line_offset(line_offset),
          m_column_delim(column_delim),
          m_line_delim(row_delim),
          m_escape_sym(escape_sym),
          m_current_line(0)
    {
        // Check file opening
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
        for (size_t i = 0; i < m_line_offset; ++i)
            GetLine();

        return InputIterator(*this, InputIterator::Mode::begin);
    }

    InputIterator end()
    {
        return InputIterator(*this, InputIterator::Mode::end);
    }

private:
    std::ifstream & m_ifs;
    char m_column_delim;
    char m_line_delim;
    char m_escape_sym;
    size_t m_line_offset;
    size_t m_current_line;

    std::string GetLine()
    {
        std::string buffer;
        char sym;

        // If end of file or line delim symbol is found, finish reading
        while (m_ifs.get(sym) && !std::regex_search(buffer + sym, std::regex({m_line_delim})))
            buffer += sym;

        ++m_current_line;
        return buffer;
    }

    std::vector<std::string> RowToVector(const std::string & line)
    {
        // Split string into columns with column delim symbol
        std::regex column_delim_regex({m_column_delim});
        std::vector<std::string> values(std::sregex_token_iterator(line.begin(), line.end(),
                                                                   column_delim_regex, -1),
                                        std::sregex_token_iterator());

        for (size_t i = 0; i < values.size(); ++i)
            EscapeCharacters(values[i], i);

        if (values.size() < sizeof...(Types))
            throw FewColumnsException(m_current_line, values.size() + 1);
        if (values.size() > sizeof...(Types))
            throw ManyColumnsException(m_current_line, sizeof...(Types) + 1);

        return values;
    }

    void EscapeCharacters(std::string & line, size_t idx)
    {
        // Count number of escaping characters
        std::regex escape_sym_regex({m_escape_sym});
        size_t escape_sym_count = 0;
        for (std::sregex_iterator begin(line.begin(), line.end(), escape_sym_regex), end;
             begin != end; ++begin)
            ++escape_sym_count;

        if (escape_sym_count & 1)
            throw EscapeCharactersException(m_current_line, idx + 1);

        // Split string into substrings with escape symbol
        std::vector<std::string> values(std::sregex_token_iterator(line.begin(), line.end(),
                                                                   escape_sym_regex, -1),
                                        std::sregex_token_iterator());

        // Escape character at the beginning of line is checked
        bool begin_escape_sym = line[0] == m_escape_sym;

        // Merge processed substrings
        line.clear();
        for (size_t i = 0; i < values.size(); ++i)
        {
            if (begin_escape_sym ^ (i % 2 == 1))
            {
                values[i] = std::regex_replace(values[i], std::regex("\a"), "\\a");
                values[i] = std::regex_replace(values[i], std::regex("\n"), "\\n");
                values[i] = std::regex_replace(values[i], std::regex("\r"), "\\r");
                values[i] = std::regex_replace(values[i], std::regex("\t"), "\\t");
                values[i] = std::regex_replace(values[i], std::regex("\v"), "\\v");
            }

            line += values[i];
        }
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
                throw TypeMismatchException(m_parent.m_current_line, idx + 1);
            }
        }
    }
};

#endif //TASK4_CSV_PARSER_H
