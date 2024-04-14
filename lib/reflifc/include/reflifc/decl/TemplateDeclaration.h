#pragma once

#include "reflifc/HashCombine.h"
#include "reflifc/Name.h"
#include "reflifc/ViewOf.h"
#include "reflifc/Declaration.h"

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Chart;
    struct Declaration;

    struct TemplateDeclaration
    {
        TemplateDeclaration(ifc::File const* ifc, ifc::DeclIndex index, ifc::TemplateDeclaration const& template_)
            : ifc_(ifc)
            , template_(&template_)
            , index_(index)
        {
        }

        Name name() const;
        Declaration entity() const;
        Chart chart() const;
        Declaration home_scope() const;
        ifc::Access access() const;
        ifc::BasicSpecifiers specifiers() const;

        ViewOf<Declaration> auto template_specializations() const;

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(TemplateDeclaration const& other) const = default;

    private:
        friend std::hash<TemplateDeclaration>;

        ifc::File const* ifc_;
        ifc::TemplateDeclaration const* template_;
        ifc::DeclIndex index_;
    };


    inline ViewOf<Declaration> auto TemplateDeclaration::template_specializations() const
    {
        return ifc_->declarations().slice(ifc_->trait_template_specializations(index_))
            | std::views::transform([ifc = ifc_](ifc::Declaration decl) {
            return reflifc::Declaration{ ifc, decl.index };
        });
    }
}

template<>
struct std::hash<reflifc::TemplateDeclaration>
{
    size_t operator()(reflifc::TemplateDeclaration template_decl) const noexcept
    {
        return reflifc::hash_combine(0, template_decl.ifc_, template_decl.template_);
    }
};
