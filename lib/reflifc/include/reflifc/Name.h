﻿#pragma once

#include <ifc/FileFwd.h>
#include <ifc/Name.h>

#include <string_view>

namespace reflifc
{
    struct SpecializationName;
    struct TupleExpressionView;

    struct Name
    {
        Name(ifc::File const* ifc, ifc::NameIndex index)
            : ifc_(ifc)
            , index_(index)
        {
        }

        explicit operator bool() const
        {
            return !index_.is_null();
        }

        bool        is_identifier() const;
        char const* as_identifier() const;

        bool        is_operator() const;
        char const* operator_name() const;

        ifc::Operator get_operator() const;

        bool        is_literal() const;
        char const* as_literal() const;

        bool                is_specialization() const;
        SpecializationName  as_specialization() const;

        ifc::NameSort sort() const { return index_.sort(); }

        bool operator==(Name other) const
        {
            assert(ifc_ == other.ifc_);
            return index_ == other.index_;
        }

    private:
        ifc::File const* ifc_;
        ifc::NameIndex index_;
    };

    struct SpecializationName
    {
        SpecializationName(ifc::File const* ifc, ifc::SpecializationName const& specialization)
            : ifc_(ifc)
            , specialization_(&specialization)
        {
        }

        Name                primary()               const;
        TupleExpressionView template_arguments()    const;

    private:
        ifc::File const* ifc_;
        ifc::SpecializationName const* specialization_;
    };

    inline bool is_identifier(Name name, std::string_view s)
    {
        return name.is_identifier() && name.as_identifier() == s;
    }

    template<typename Declaration>
    bool has_name(Declaration declaration, std::string_view s)
    {
        return is_identifier(declaration.name(), s);
    }
}