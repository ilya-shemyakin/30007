#ifndef tabolina_datastruct
#define tabolina_datastruct
#include <string>
#include <complex>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <exception>
#include <iterator>

namespace tabolina
{
    struct DataStruct
    {
        long long key1;
        std::complex<double> key2;
        std::string key3;
    };
    struct DelimeterIO
    {
        char exp;
    };
    struct SLL_ST
    {
        long long& ref;
    };
    struct CMPDouble_ST
    {
        std::complex<double>& ref;
    };
    struct Double_ST
    {
        double& ref;
    };
    struct String_ST
    {
        std::string& ref;
    };
    class iofmtguard
    {
    public:
        iofmtguard(std::basic_ios< char >& s);
        ~iofmtguard();
    private:
        std::basic_ios< char >& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };
    std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
    std::istream& operator>>(std::istream& in, SLL_ST&& dest);
    std::istream& operator>>(std::istream& in, CMPDouble_ST&& dest);
    std::istream& operator>>(std::istream& in, Double_ST&& dest);
    std::istream& operator>>(std::istream& in, String_ST&& dest);
    std::istream& operator>>(std::istream& in, DataStruct& dest);
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
    bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second);
}
#endif
