#ifndef B2_COMMON_FUNCTIONS_HPP
#define B2_COMMON_FUNCTIONS_HPP

#include <iostream>
#include <locale>
#include <boost/io/ios_state.hpp>

namespace detail
{
  template< class CharT, class Traits >
  std::basic_istream<CharT,Traits>& skipBlanks(std::basic_istream<CharT, Traits>& is)
  {
    boost::io::ios_flags_saver ifs(is);
    std::noskipws(is);
    std::istream::sentry sentry(is);
    if (sentry)
    {
      typedef std::basic_istream<CharT, Traits> istream_t;
      typedef std::basic_streambuf<CharT, Traits> streambuf_t;
      typedef typename istream_t::int_type int_t;
      typedef std::ctype<CharT> ctype_type;

      const ctype_type& ct = std::use_facet<ctype_type>(is.getloc());
      const int_t eof = Traits::eof();

      streambuf_t *sb = is.rdbuf();
      int_t c = sb->sgetc();

      while (!Traits::eq_int_type(c, eof)
          && ct.is(std::ctype_base::blank, Traits::to_char_type(c)))
      {
        c = sb->snextc();
      }

      if (c == std::char_traits<char>::eof())
      {
        is.setstate(std::ios::eofbit);
      }
    }
    return is;
  }

  bool skipSymbol(char symbol, std::istream &is = std::cin, std::ostream &os = std::cout);
}

#endif
