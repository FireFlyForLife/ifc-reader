﻿#pragma once

#include <ifc/FileFwd.h>
#include <ifc/DeclarationFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Name;
    struct Namespace;
    struct ClassOrStruct;
    struct Declaration;

    struct ScopeDeclaration
    {
        ScopeDeclaration(ifc::File const* ifc, ifc::ScopeDeclaration const& scope)
            : ifc_(ifc)
            , scope_(&scope)
        {
        }

        Name name() const;
        Declaration home_scope() const;

        bool        is_namespace() const;
        Namespace   as_namespace() const;

        bool            is_class_or_struct() const;
        ClassOrStruct   as_class_or_struct() const;

        ifc::BasicSpecifiers specifiers() const;
        ifc::TypeBasis kind() const;

    private:
        ifc::File const* ifc_;
        ifc::ScopeDeclaration const* scope_;
    };
}