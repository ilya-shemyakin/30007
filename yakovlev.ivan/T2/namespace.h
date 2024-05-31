#ifndef NAMESPACE_H
#define NAMESPACE_H

#include "local.h"

namespace yakovlev
{
  struct DataStruct
  {
    long long key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct SLLIO
  {
    long long& ref;
  };

  struct RatIO
  {
    std::pair<long long, unsigned long long>& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct LabelIO
  {
    std::string exp;
  };

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
  private:
    std::basic_ios<char>& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
  };

  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, SLLIO&& dest);
  std::istream& operator>>(std::istream& in, RatIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);

  bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second);
}

#endif
