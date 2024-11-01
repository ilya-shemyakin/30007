#include "Tabolina_datastruct.h"

namespace tabolina
{
    std::istream& operator>>(std::istream& in, DelimeterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c_in = '0';
        in >> c_in;
        if (in && (c_in != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, SLL_ST&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> dest.ref >> DelimeterIO{ 'l' } >> DelimeterIO{ 'l' };
        if (!in)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, CMPDouble_ST&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        double real = 0.0;
        double imag = 0.0;
        in >> DelimeterIO{ '(' } >> real >> imag >> DelimeterIO{ ')' };
        if (in)
        {
            dest.ref = std::complex<double>(real, imag);
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, Double_ST&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> dest.ref;
    }
    std::istream& operator>>(std::istream& in, String_ST&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimeterIO{'"'}, dest.ref, '"');
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
            using sep = DelimeterIO;
            using cmp = CMPDouble_ST;
            using sll = SLL_ST;
            using str = String_ST;
            in >> sep{ '(' };
            bool flag1 = false, flag2 = false, flag3 = false;
            while (true)
            {
                if (flag1 && flag2 && flag3) break;
                std::string key;
                char c;
                in >> c;
                if (!in) break;
                if (c == ':' && (in >> key))
                {
                    if (key == "key1")
                    {
                        in >> sll{ input.key1 };
                        flag1 = true;
                    }
                    else if (key == "key2")
                    {
                        in >> sep{ '#' } >> sep{ 'c' } >> cmp{ input.key2 };
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
    std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        iofmtguard fmtguard(out);
        out << "(";
        out << ":key1 " << dest.key1 << "ll";
        out << ":key2 " << std::fixed << std::setprecision(1) << "#c(" << dest.key2.real() << " " << dest.key2.imag() << ")";
        out << ":key3 \"" << dest.key3 << "\"";
        out << ":)";
        return out;
    }
    bool compareDataStruct(const DataStruct& ds_first, const DataStruct& ds_second)
    {
        double Re_first = ds_first.key2.real(),
            Re_second = ds_second.key2.real(),
            Im_first = ds_first.key2.imag(),
            Im_second = ds_second.key2.imag(),
            R_first = 0.0,
            R_second = 0.0;
        R_first = sqrt(pow(Re_first, 2) + pow(Im_first, 2));
        R_second = sqrt(pow(Re_second, 2) + pow(Im_second, 2));
        if (ds_first.key1 < ds_second.key1)
        {
            return true;
        }
        else if (ds_first.key1 == ds_second.key1)
        {
            if (R_first < R_second)
            {
                return true;
            }
            else if (R_first == R_second)
            {
                return ds_first.key3.length() < ds_second.key3.length();
            }
        }
        return false;
    }
    iofmtguard::iofmtguard(std::basic_ios< char >& s) :
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
