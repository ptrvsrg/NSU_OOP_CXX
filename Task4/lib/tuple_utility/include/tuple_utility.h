#ifndef TASK4_TUPLE_UTILITY_H
#define TASK4_TUPLE_UTILITY_H

#include <ostream>
#include <sstream>
#include <tuple>

namespace
{
    template<typename CharT,
             typename Traits,
             size_t First,
             size_t Last,
             typename... Types>
    struct TuplePrinter
    {
        static void print(std::basic_ostream<CharT, Traits> & out,
                          const std::tuple<Types...> & value)
        {
            out << std::get<First>(value) << ", ";
            TuplePrinter<CharT,
                         Traits,
                         First + 1,
                         Last,
                         Types...>::print(out,
                                          value);
        }
    };

    template<typename CharT,
             typename Traits,
             size_t Last,
             typename... Types>
    struct TuplePrinter<CharT,
                         Traits,
                         Last,
                         Last,
                         Types...>
    {
        static void print(std::basic_ostream<CharT, Traits> & out,
                          const std::tuple<Types...> & value)
        {
            out << std::get<Last>(value);
        }
    };

    template<size_t First,
        size_t Last,
        typename... Types>
    struct TupleMaker
    {
        static void make(std::vector<std::string> & params,
                         std::tuple<Types...> & tuple)
        {
            std::istringstream iss(params[0]);
            iss >> std::get<First>(tuple);
            params.erase(params.cbegin());
            TupleMaker<First + 1,
                       Last,
                       Types...>::make(params,
                                       tuple);
        }
    };

    template<size_t Last,
             typename... Types>
    struct TupleMaker<Last,
                      Last,
                      Types...>
    {
        static void make(std::vector<std::string> & params,
                         std::tuple<Types...> & tuple)
        {
            std::istringstream iss(params[0]);
            iss >> std::get<Last>(tuple);
        }
    };
}

template<typename CharT,
         typename Traits,
         typename... Types>
std::basic_ostream<CharT, Traits> & operator<<(std::basic_ostream<CharT, Traits> & os,
                                               const std::tuple<Types...> & tuple)
{
    TuplePrinter<CharT,
                  Traits,
                  0,
                  sizeof...(Types) - 1,
                  Types...>::print(os,
                                   tuple);
    return os;
}

template<typename... Types>
std::tuple<Types...> MakeTuple(std::vector<std::string> params)
{
    std::tuple<Types...> tuple;
    TupleMaker<0,
               sizeof...(Types) - 1,
               Types...>::make(params,
                               tuple);
    return tuple;
}

#endif //TASK4_TUPLE_UTILITY_H
