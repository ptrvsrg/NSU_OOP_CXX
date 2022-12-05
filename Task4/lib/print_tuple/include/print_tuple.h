#ifndef TASK4_PRINT_TUPLE_H
#define TASK4_PRINT_TUPLE_H

#include <ostream>
#include <tuple>

namespace
{
    template<typename CharT,
             typename Traits,
             typename Type,
             size_t First,
             size_t Last>
    struct tuple_printer
    {
        static void print(std::basic_ostream<CharT, Traits> & out,
                          const Type & value)
        {
            out << std::get<First>(value) << ", ";
            tuple_printer<CharT,
                          Traits,
                          Type,
                          First + 1,
                          Last>::print(out,
                                       value);
        }
    };

    template<typename CharT,
             typename Traits,
             typename Type,
             size_t Last>
    struct tuple_printer<CharT,
                         Traits,
                         Type,
                         Last,
                         Last>
    {
        static void print(std::basic_ostream<CharT, Traits> & out,
                          const Type & value)
        {
            out << std::get<Last>(value);
        }

    };
}

template<typename CharT,
         typename Traits,
         typename... Types>
std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os,
                                               const std::tuple<Types...> & tuple)
{
    tuple_printer<CharT,
                  Traits,
                  std::tuple<Types...>,
                  0,
                  sizeof...(Types) - 1>::print(os,
                                               tuple);
    return os;
}

#endif //TASK4_PRINT_TUPLE_H
