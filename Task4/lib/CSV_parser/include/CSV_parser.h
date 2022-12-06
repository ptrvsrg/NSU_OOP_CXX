#ifndef TASK4_CSV_PARSER_H
#define TASK4_CSV_PARSER_H

#include <fstream>
#include <iterator>
#include <memory>
#include <tuple>
#include <vector>
#include "tuple_utility.h"

template<typename... Types>
class CSVParser
{
public:
    explicit CSVParser(std::ifstream & ifs,
                       std::string column_delim = ",",
                       std::string row_delim = "\n",
                       size_t skip_count = 0)
        : m_ifs(ifs),
          m_column_delim(std::move(column_delim)),
          m_line_delim(std::move(row_delim)),
          m_offset(skip_count) {}

    CSVParser(const CSVParser<Types...> & src) = delete;

    class InputIterator
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

        explicit InputIterator(CSVParser<Types...> & parent,
                               Mode mode)
            :  m_parent(parent)
        {
            switch (mode)
            {
                case Mode::beg:
                {
                    for (; m_parent.m_skip_count != 0; --m_parent.m_skip_count)
                        m_parent.GetRow();
                    break;
                }
                case Mode::end:
                    m_ptr = nullptr;
                    break;
                }
            }

            SetPtr();
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
                m_ptr = std::make_shared<value_type>(MakeTuple<Types...>(m_parent.RowToVector(buff)));
        }
    };

    InputIterator begin()
    {
        m_ifs.clear();
        m_ifs.seekg(0,
                    std::ios_base::beg);
        return InputIterator(*this, InputIterator::Mode::beg);
    }

    InputIterator end()
    {
        return InputIterator(*this, InputIterator::Mode::end);
    }

private:
    std::ifstream & m_ifs;
    std::string m_column_delim;
    std::string m_line_delim;
    size_t m_offset;

    std::string GetLine()
    {
        std::string buffer;
        char sym;
        do
        {
            m_ifs.read(&sym, 1);

            if (m_ifs.eof())
                break;

            buffer += sym;
        } while (buffer.find(m_line_delim, 0) == std::string::npos);

        return buffer;
    }

    std::vector<std::string> RowToVector(const std::string & line)
    {
        std::vector<std::string> values;
        size_t prev = 0;
        size_t next;

        while ((next = line.find(m_column_delim, prev)) != std::string::npos)
        {
            values.push_back(line.substr(prev,
                                         next - prev));
            prev = next + m_column_delim.size();
        }

        values.push_back(line.substr(prev));

        if (values.size() < sizeof...(Types))
            throw std::invalid_argument("");
        if (values.size() > sizeof...(Types))
            throw std::invalid_argument("");

        return values;
    }
};

#endif //TASK4_CSV_PARSER_H
