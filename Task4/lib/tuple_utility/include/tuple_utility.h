#ifndef TASK4_TUPLE_UTILITY_H
#define TASK4_TUPLE_UTILITY_H

#include <memory>
#include <ostream>
#include <sstream>
#include <tuple>

namespace
{
    template <size_t First, size_t Last, size_t Size, typename Callback, typename... Types>
    class Iteration
    {
    public:
        // for printing
        static void Next(Callback callback, std::tuple<Types...> tuple)
        {
            callback(std::get<First>(tuple), false);
            Iteration<First + 1, Last, Size, Callback, Types...>::Next(callback, tuple);
        }

        // for making
        static void Next(Callback callback, std::unique_ptr<std::tuple<Types...>> & tuple_ptr)
        {
            callback(std::get<First>(*tuple_ptr), false);
            Iteration<First + 1, Last, Size, Callback, Types...>::Next(callback, tuple_ptr);
        }
    };

    // Last iteration
    template <size_t Last, size_t Size, typename Callback, typename... Types>
    class Iteration<Last, Last, Size, Callback, Types...>
    {
    public:
        // for printing
        static void Next(Callback callback, std::tuple<Types...> tuple)
        {
            callback(std::get<Last>(tuple), true);
        }

        // for making
        static void Next(Callback callback, std::unique_ptr<std::tuple<Types...>> & tuple_ptr)
        {
            callback(std::get<Last>(*tuple_ptr), true);
        }
    };

    // empty tuple
    template <size_t First, size_t Last, typename Callback, typename... Types>
    class Iteration<First, Last, 0, Callback, Types...>
    {
    public:
        // for printing
        static void Next(Callback callback, std::tuple<Types...> tuple) {}

        // for making
        static void Next(Callback callback, std::unique_ptr<std::tuple<Types...>> & tuple_ptr) {}
    };

    // for printing
    template <typename Callback, typename... Types>
    void ForEach(Callback callback, std::tuple<Types...> tuple)
    {
        Iteration<0, sizeof...(Types) - 1, sizeof...(Types), Callback, Types...>::Next(callback, tuple);
    }

    // for making
    template <typename Callback, typename... Types>
    void ForEach(Callback callback, std::unique_ptr<std::tuple<Types...>> & tuple_ptr)
    {
        Iteration<0, sizeof...(Types) - 1, sizeof...(Types), Callback, Types...>::Next(callback, tuple_ptr);
    }

    template<typename CharT, typename Traits>
    class PrintCallback
    {
    public:
        explicit PrintCallback(std::basic_ostream<CharT, Traits> & os)
            :   m_os(os) {}

        template<typename Type>
        void operator()(Type value, bool is_last)
        {
            m_os << value;
            if (!is_last)
                m_os << ", ";
        }
    private:
        std::basic_ostream<CharT, Traits> & m_os;
    };

    class MakeCallback
    {
    public:
        explicit MakeCallback(std::vector<std::string> params)
            :   m_params(std::move(params)) {}

        template<typename Type>
        void operator()(Type & value, bool is_last)
        {
            std::istringstream iss(m_params[m_cur_idx]);
            iss >> value;

            std::ostringstream oss;
            oss << value;

            if (oss.str() != m_params[m_cur_idx])
                throw m_cur_idx;

            ++m_cur_idx;
        }

        // Partial template specialization for std::string
        void operator()(std::string & value, bool is_last)
        {
            value = m_params[m_cur_idx];
            ++m_cur_idx;
        }

    private:
        std::vector<std::string> m_params;
        size_t m_cur_idx;
    };
}

template<typename CharT, typename Traits, typename... Types>
auto & operator<<(std::basic_ostream<CharT, Traits> & os, const std::tuple<Types...> & tuple)
{
    PrintCallback<CharT, Traits> print_callback(os);
    ForEach(print_callback, tuple);
    return os;
}

template<typename... Types>
std::tuple<Types...> MakeTuple(const std::vector<std::string> & params)
{
    auto tuple_ptr = std::make_unique<std::tuple<Types...>>();
    MakeCallback make_callback(params);
    ForEach(make_callback, tuple_ptr);
    return *tuple_ptr;
}

#endif //TASK4_TUPLE_UTILITY_H
