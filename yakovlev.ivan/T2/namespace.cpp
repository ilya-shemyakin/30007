#include "namespace.h"

namespace yakovlev
{
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char symbol = '0';
    in >> symbol;
    if (in && (symbol != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, SLLIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref;
  }

  std::istream& operator>>(std::istream& in, RatIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> dest.ref.first >> DelimiterIO{ ':' } >> LabelIO{ "D" } >> dest.ref.second >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string temp;
    in >> temp;
    if (temp != dest.exp)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using SLL = SLLIO;
      using RAT = RatIO;
      using str = StringIO;
      using label = LabelIO;

      in >> sep{ '(' };
      bool flag1 = false, flag2 = false, flag3 = false;
      while (true)
      {
        if (flag1 && flag2 && flag3)
          break;
        std::string key;
        char symbol;
        in >> symbol;
        if (!in)
          break;
        //(:key1 10ll:key2 (:N -2:D 3:):key3 "Data":)
        if (symbol == ':' && (in >> key))
        {
          if (key == "key1")
          {
            in >> SLL{ input.key1 } >> sep{ 'l' } >> sep{ 'l' };
            flag1 = true;
          }
          else if (key == "key2")
          {
            in >> label{ "(:N" } >> RAT{ input.key2 };
            flag2 = true;
          }
          else if (key == "key3")
          {
            in >> str{ input.key3 };
            flag3 = true;
          }
        }
      }
      in >> sep{ ':' } >> sep{ ')' };
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(";
    out << ":key1 " << src.key1 << "ll";
    out << ":key2 (:N " << src.key2.first << ":D " << src.key2.second << ":)";
    out << ":key3 \"" << src.key3 << "\"";
    out << ":)";
    return out;
  }

  bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second)
  {
    if (ds_first.key1 < ds_second.key1)
    {
      return true;
    }
    else if (ds_first.key1 == ds_second.key1)
    {
      if (ds_first.key2 < ds_second.key2)
      {
        return true;
      }
      else if (ds_first.key2 == ds_second.key2)
      {
        return ds_first.key3.length() < ds_second.key3.length();
      }
    }
    return false;
  }

  iofmtguard::iofmtguard(std::basic_ios<char>& s) :
    s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
