#ifndef STRING_HPP
#define STRING_HPP
#include "CORE.hpp"
#include "random.hpp"

namespace DATA_MAKER
{
    MAKE__NamedType(sentence_terminators, std::string_view)
    MAKE__NamedType(word_separators, std::string_view)
    MAKE__NamedType(charset, std::string_view)
    MAKE__NamedType(first_letter_uppercase, bool)
    MAKE__NamedType_TWO(word_length_range, unsigned int)
    struct String
    {
        static std::string random(int l, int r, std::string_view str = ALPHABET_SMALL)
        {
            std::string __t = "";
            auto ___size = RND(l, r);
            for (int i = 1; i <= ___size; ++i)
            {
                __t.push_back(str[RND(
                    static_cast<decltype(str.length())>(0), str.length() - 1)]);
            }
            return __t;
        }

        static std::string random(int n, std::string_view str = ALPHABET_SMALL)
        {
            return random(n, n, str);
        }

        static std::string random(std::string_view str = ALPHABET_SMALL)
        {
            return random(1, str);
        }
        static std::string random(const std::vector<std::string> &v_str)
        {
            return std::string(v_str[RND(
                static_cast<decltype(v_str.size())>(0), v_str.size() - 1)]);
        }
    };

    template <
        typename Integer,
        typename... Args,
        std::enable_if_t<std::is_integral<Integer>::value, bool> = true>
    static std::string random_sentence(Integer l, Integer r, Args &&...args)
    {
        if (l < 0 || r < 0 || l > r)
        {
            throw std::invalid_argument("DATA_MAKER ERROR!");
        }

        std::string_view _M_sentence_terminators = ".!";
        std::string_view _M_word_separators = " ";
        std::string_view _M_charset = ALPHABET_SMALL;
        bool _M_first_letter_uppercase = true;
        std::pair<unsigned int, unsigned int> _M_word_length_range = std::make_pair(3, 8);

        auto __args_tuple = std::make_tuple(std::forward<Args>(args)...);
        if constexpr (__has_type<sentence_terminatorsType, std::remove_reference_t<Args>...>::value)
            _M_sentence_terminators = __pick<sentence_terminatorsType>(__args_tuple);

        if constexpr (__has_type<word_separatorsType, std::remove_reference_t<Args>...>::value)
            _M_word_separators = __pick<word_separatorsType>(__args_tuple);

        if constexpr (__has_type<charsetType, std::remove_reference_t<Args>...>::value)
            _M_charset = __pick<charsetType>(__args_tuple);

        if constexpr (__has_type<first_letter_uppercaseType, std::remove_reference_t<Args>...>::value)
            _M_first_letter_uppercase = __pick<first_letter_uppercaseType>(__args_tuple);

        if constexpr (__has_type<word_length_rangeType, std::remove_reference_t<Args>...>::value)
            _M_word_length_range = __pick<word_length_rangeType>(__args_tuple);

        unsigned int __count = RND(l, r);

        std::stringstream ss;
        __count--;
        std::string __tmp = random(_M_word_length_range.first, _M_word_length_range.second, _M_charset);
        if (_M_first_letter_uppercase)
            __tmp[0] = std::toupper(__tmp[0]);
        ss << __tmp;
        std::string _real_word_separator = random(1, 1, _M_word_separators);

        while (__count--)
        {
            ss << _real_word_separator;
            ss << random(_M_word_length_range.first, _M_word_length_range.second, _M_charset);
        }
        if (_M_sentence_terminators.length() != 0)
            ss << random(1, 1, _M_sentence_terminators);
        return ss.str();
    }
}

#endif // STRING_HPP