/*
Copyright (c) 2017-2021,
Battelle Memorial Institute; Lawrence Livermore National Security, LLC; Alliance for Sustainable
Energy, LLC.  See the top-level NOTICE for additional details. All rights reserved.
SPDX-License-Identifier: BSD-3-Clause
*/
#pragma once

#include "ValueConverter.hpp"
#include "helics/helics-config.h"
#include "helicsTypes.hpp"
#include "helics_cxx_export.h"

#include <cmath>
#include <complex>
#include <cstdint>
#include <string>
#include <utility>
#include <variant>
#include <vector>
/** @file
@brief naming a set of types that are interchangeable and recognizable inside the HELICS application
API and core
*/
namespace helics {
/** define a variant with the different types*/

using defV = std::variant<double,
                          int64_t,
                          std::string,
                          std::complex<double>,
                          std::vector<double>,
                          std::vector<std::complex<double>>,
                          NamedPoint>;

/**enumeration of the order inside the variant so the Which function returns match the enumeration*/
enum type_location {
    double_loc = 0,
    int_loc = 1,
    string_loc = 2,
    complex_loc = 3,
    vector_loc = 4,
    complex_vector_loc = 5,
    named_point_loc = 6
};
/** detect a change from the previous values*/
HELICS_CXX_EXPORT bool changeDetected(const defV& prevValue, const std::string& val, double deltaV);
HELICS_CXX_EXPORT bool changeDetected(const defV& prevValue, std::string_view val, double deltaV);
HELICS_CXX_EXPORT bool
    changeDetected(const defV& prevValue, const std::vector<double>& val, double deltaV);
HELICS_CXX_EXPORT bool changeDetected(const defV& prevValue,
                                      const std::vector<std::complex<double>>& val,
                                      double deltaV);
HELICS_CXX_EXPORT bool
    changeDetected(const defV& prevValue, const double* vals, size_t size, double deltaV);
HELICS_CXX_EXPORT bool
    changeDetected(const defV& prevValue, const std::complex<double>& val, double deltaV);
HELICS_CXX_EXPORT bool changeDetected(const defV& prevValue, double val, double deltaV);
HELICS_CXX_EXPORT bool changeDetected(const defV& prevValue, int64_t val, double deltaV);
HELICS_CXX_EXPORT bool changeDetected(const defV& prevValue, Time val, double deltaV);
HELICS_CXX_EXPORT bool changeDetected(const defV& prevValue, const NamedPoint& val, double deltaV);
HELICS_CXX_EXPORT bool changeDetected(const defV& prevValue, bool val, double deltaV);

/** directly convert the boolean to integer*/
inline int64_t make_valid(bool obj)
{
    return (obj) ? 1LL : 0LL;
}

/** directly convert the boolean to integer*/
inline int64_t make_valid(uint64_t val)
{
    return static_cast<int64_t>(val);
}
inline int64_t make_valid(int16_t val)
{
    return static_cast<int64_t>(val);
}
inline int64_t make_valid(uint16_t val)
{
    return static_cast<int64_t>(val);
}
inline int64_t make_valid(char val)
{
    return static_cast<int64_t>(val);
}
inline int64_t make_valid(unsigned char val)
{
    return static_cast<int64_t>(val);
}
inline int64_t make_valid(int32_t val)
{
    return static_cast<int64_t>(val);
}
inline int64_t make_valid(uint32_t val)
{
    return static_cast<int64_t>(val);
}
inline int64_t make_valid(Time val)
{
    return val.getBaseTimeCode();
}

inline double make_valid(float val)
{
    return static_cast<double>(val);
}

inline std::complex<double> make_valid(const std::complex<float>& val)
{
    return {val.real(), val.imag()};
}

/** this template should do nothing for most classes the specific overloads are the important ones*/
template<class X>
decltype(auto) make_valid(X&& obj)
{
    return std::forward<X>(obj);
}
/** extract the value from a variant to a string*/
HELICS_CXX_EXPORT void valueExtract(const defV& dv, std::string& val);

/** extract the value from a variant to a complex number*/
HELICS_CXX_EXPORT void valueExtract(const defV& dv, std::complex<double>& val);

/** extract the value from a variant to a vector of doubles*/
HELICS_CXX_EXPORT void valueExtract(const defV& dv, std::vector<double>& val);

/** extract the value from a variant to a complex vector of doubles*/
HELICS_CXX_EXPORT void valueExtract(const defV& dv, std::vector<std::complex<double>>& val);

/** extract the value from a variant to a named point*/
HELICS_CXX_EXPORT void valueExtract(const defV& dv, NamedPoint& val);

/** extract the value from a variant to a named point*/
HELICS_CXX_EXPORT void valueExtract(const defV& dv, Time& val);

/** extract the value from a variant to a character*/
HELICS_CXX_EXPORT void valueExtract(const defV& dv, char& val);

/** extract the value from a variant to a bool*/
HELICS_CXX_EXPORT void valueExtract(const defV& dv, bool& val);

HELICS_CXX_EXPORT defV readJsonValue(const data_view& dv);

HELICS_CXX_EXPORT void valueExtract(const data_view& dv, DataType baseType, std::string& val);

HELICS_CXX_EXPORT void
    valueExtract(const data_view& dv, DataType baseType, std::vector<double>& val);

HELICS_CXX_EXPORT void
    valueExtract(const data_view& dv, DataType baseType, std::complex<double>& val);

HELICS_CXX_EXPORT void
    valueExtract(const data_view& dv, DataType baseType, std::vector<std::complex<double>>& val);

HELICS_CXX_EXPORT void valueExtract(const data_view& dv, DataType baseType, NamedPoint& val);

HELICS_CXX_EXPORT void valueExtract(const data_view& dv, DataType baseType, Time& val);

HELICS_CXX_EXPORT void valueExtract(const data_view& dv, DataType baseType, bool& val);

HELICS_CXX_EXPORT void valueExtract(const data_view& dv, DataType baseType, defV& val);

/** extract the value from a variant to a numerical type*/
template<class X>
std::enable_if_t<std::is_arithmetic<X>::value && (!std::is_same<X, char>::value)>
    valueExtract(const defV& dv, X& val)
{
    switch (dv.index()) {
        case double_loc:  // double
            val = static_cast<X>(std::get<double>(dv));
            break;
        case int_loc:  // int64_t
            val = static_cast<X>(std::get<int64_t>(dv));
            break;
        case string_loc:  // string
        default:
            val = static_cast<X>(getDoubleFromString(std::get<std::string>(dv)));
            break;
        case complex_loc:  // complex
            val = static_cast<X>(std::abs(std::get<std::complex<double>>(dv)));
            break;
        case vector_loc:  // vector
        {
            const auto& vec = std::get<std::vector<double>>(dv);
            val = static_cast<X>(vectorNorm(vec));
            break;
        }
        case complex_vector_loc:  // complex vector
        {
            const auto& vec = std::get<std::vector<std::complex<double>>>(dv);
            val = static_cast<X>(vectorNorm(vec));
            break;
        }
        case named_point_loc: {
            const auto& np = std::get<NamedPoint>(dv);
            if (std::isnan(np.value)) {
                val = static_cast<X>(getDoubleFromString(np.name));
            } else {
                val = static_cast<X>(np.value);
            }
            break;
        }
    }
}

/** assume it is some numeric type (int or double)*/
template<class X>
std::enable_if_t<std::is_arithmetic<X>::value>
    valueExtract(const data_view& dv, DataType baseType, X& val)
{
    switch (baseType) {
        case DataType::HELICS_ANY: {
            defV val_dv;
            valueExtract(dv, baseType, val_dv);
            valueExtract(val_dv, val);
            break;
        }
        case DataType::HELICS_STRING:
        default:
            val = static_cast<X>(
                getDoubleFromString(ValueConverter<std::string_view>::interpret(dv)));
            break;
        case DataType::HELICS_BOOL:
            val = static_cast<X>((ValueConverter<std::string_view>::interpret(dv) != "0"));
            break;
        case DataType::HELICS_NAMED_POINT: {
            auto npval = ValueConverter<NamedPoint>::interpret(dv);
            if (std::isnan(npval.value)) {
                try {
                    val = static_cast<X>(getDoubleFromString(npval.name));
                }
                catch (const std::invalid_argument&) {
                    val = static_cast<X>(
                        invalidValue<
                            std::conditional_t<std::is_integral<X>::value, int64_t, double>>());
                }
            } else {
                val = static_cast<X>(npval.value);
            }

            break;
        }
        case DataType::HELICS_DOUBLE: {
            auto V = ValueConverter<double>::interpret(dv);
            val = static_cast<X>(V);
            break;
        }
        case DataType::HELICS_INT:
        case DataType::HELICS_TIME: {
            auto V = ValueConverter<int64_t>::interpret(dv);
            val = static_cast<X>(V);
            break;
        }

        case DataType::HELICS_VECTOR: {
            auto V = ValueConverter<std::vector<double>>::interpret(dv);
            val = static_cast<X>(vectorNorm(V));
            break;
        }
        case DataType::HELICS_COMPLEX: {
            auto V = ValueConverter<std::complex<double>>::interpret(dv);
            val = static_cast<X>(std::abs(V));
            break;
        }
        case DataType::HELICS_COMPLEX_VECTOR: {
            auto V = ValueConverter<std::vector<std::complex<double>>>::interpret(dv);
            val = static_cast<X>(vectorNorm(V));
            break;
        }
        case DataType::HELICS_JSON:
            valueExtract(readJsonValue(dv), val);
            break;
        case DataType::HELICS_CUSTOM:
            throw(std::invalid_argument("unrecognized helics type"));
    }
}

HELICS_CXX_EXPORT void valueConvert(defV& val, DataType newType);

}  // namespace helics
