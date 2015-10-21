#pragma once
/*
 * sz_ref.hpp
 * A class like (and built on) boost::string_ref,
 * but has c_str() and lacks substr().
 * A work in progress.
 */
#include <cstddef>
#include <iterator>
#include <string>
#include <stdexcept>
#include <boost/utility/string_ref.hpp>

template< typename C, typename Traits = std::char_traits<C> >
class basic_sz_ref {
public:
    typedef Traits traits_type;
    typedef C value_type;
    typedef C* pointer;
    typedef const C* const_pointer;
    typedef C& reference;
    typedef const C& const_reference;
    typedef const_pointer const_iterator;
    typedef const_iterator iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef const_reverse_iterator reverse_iterator;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    typedef boost::basic_string_ref<C, Traits> String_ref;

    BOOST_CONSTEXPR
    basic_sz_ref(): my_str("") {}

    BOOST_CONSTEXPR
    basic_sz_ref(const basic_sz_ref& that): my_str(that.my_str) {}

    BOOST_CONSTEXPR
    basic_sz_ref(const C* s): my_str(s)
    { if (!s) my_str = ""; }

    template<typename Allocator>
    basic_sz_ref(const std::basic_string<C, Traits, Allocator>& s)
    : my_str(s.c_str()) { if (!my_str) my_str = ""; }

    basic_sz_ref& operator=(const basic_sz_ref& that)
    {
        my_str = that.my_str;
        return *this;
    }

    BOOST_CONSTEXPR
    const_iterator cbegin() const { return my_str; }

    BOOST_CONSTEXPR
    const_iterator begin() const { return cbegin(); }

    BOOST_CONSTEXPR
    const_iterator cend() const { return my_str + size(); }

    BOOST_CONSTEXPR
    const_iterator end() const { return cend(); }

    //rbegin, crbegin, rend, crend

    BOOST_CONSTEXPR
    const_reference operator[](size_type pos) const { return my_str[pos]; }

    BOOST_CONSTEXPR
    const_reference at(size_type pos) const
    {
#if 0
        if (pos >= size()) {
            throw std::out_of_range(std::string("sz_ref::at(pos): \"") + my_str + "\"; pos = " + pos + "; size = " + size());
        }
        return (*this)[pos];
#else
        return String_ref(my_str).at(pos);
#endif
    }

    BOOST_CONSTEXPR
    const_reference front() const { return (*this)[0]; }

    BOOST_CONSTEXPR
    const_reference back() const { return (*this)[size() - 1]; }

    BOOST_CONSTEXPR
    const_pointer data() const { return my_str; }

    BOOST_CONSTEXPR
    const_pointer c_str() const { return my_str; }

    BOOST_CONSTEXPR
    size_type size() const { Traits::length(my_str); }

    BOOST_CONSTEXPR
    size_type length() const { return size(); }

    BOOST_CONSTEXPR
    size_type max_size() const { return String_ref(my_str).max_size(); }

    BOOST_CONSTEXPR
    bool empty() const { return '\0' == my_str[0]; }

    BOOST_CONSTEXPR
    void remove_prefix(size_type n) { my_str += n; }

    //constexpr void swap(basic_sz_ref& that);

    template< typename Allocator
#if 0
        //Default template parameters are an extension?
        = std::allocator<C>
#endif
        >
    std::basic_string<C, Traits, Allocator> to_string(const Allocator& a = Allocator()) const
    { return String_ref(my_str).to_string(); }

#if 0
    //Explicit conversion functions are an extension?
    template<typename Allocator>
    explicit operator std::basic_string<C, Traits, Allocator>() const
    { return to_string(); }
#endif

    operator String_ref() const { return String_ref(my_str); }

    size_type copy(C* destination, size_type count, size_type pos = 0) const
    { return String_ref(my_str).copy(destination, count, pos); }

    BOOST_CONSTEXPR
    int compare(String_ref that) const
    { return String_ref(my_str).compare(that); }

    BOOST_CONSTEXPR
    int compare(size_type pos, size_type count, String_ref that) const
    { return String_ref(my_str).compare(pos, count, that); }

    BOOST_CONSTEXPR
    int compare(size_type pos1, size_type count1, String_ref that,
            size_type pos2, size_type count2) const
    { return String_ref(my_str).compare(pos1, count1, that, pos2, count2); }

    BOOST_CONSTEXPR
    size_type find(String_ref that, size_type pos = 0) const
    { return String_ref(my_str).find(that, pos); }

    BOOST_CONSTEXPR
    size_type find(C c, size_type pos = 0) const
    { return String_ref(my_str).find(c, pos); }

    BOOST_CONSTEXPR
    size_type find(const C* that, size_type pos, size_type count) const
    { return String_ref(my_str).find(that, pos, count); }

private:
    const C* my_str;
};

typedef basic_sz_ref<char> sz_ref;
