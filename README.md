# sz_ref

A sometimes handy alternative to boost::string_ref.

## What is it?

Like boost::string_ref&dagger; (and built on top of it), but...

* Does have a c_str function.
* Can only be constructed from a NUL-terminated string. (Note that std::string counts.)
* Cannot be constructed from a pointer and a length.
* Lacks substr.
* Lacks remove_suffix.

&dagger;Or std::experimental::string_view. Not much like gsl::string_view.

## Why?

Because I want most of the benefits of boost::string_ref, but with the ability to write...

    void legacy_function(const char*);

    void my_function(zstring_ref z)
    {
        legacy_function(z.c_str());
    }

## How?

It is just a header: sz_ref.hpp. It requires boost::string_ref.
