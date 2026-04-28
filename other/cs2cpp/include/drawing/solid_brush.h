/// @file drawing/solid_brush.h
#ifndef _aspose_system_drawing_solid_brush_h_
#define _aspose_system_drawing_solid_brush_h_

#include "drawing/brush.h"
#include "drawing/color.h"

#include <cstdint>

#ifdef ASPOSECPPLIB_BEING_BUILT
#include "core/SkColor.h"
#endif

/// Ensures that SkColor is an alias for uint32_t.
ASPOSECPP_3RD_PARTY_TYPEDEF(SkColor, std::uint32_t);
/// Forward declaration of SkPaint class.
ASPOSECPP_3RD_PARTY_CLASS(SkPaint);


namespace System { namespace Drawing {
/// Represents single-color brush.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS SolidBrush: public Brush
{
    RTTI_INFO(System::Drawing::SolidBrush, ::System::BaseTypesInfo<System::Drawing::Brush>);

public:
    /// Constructs a new SolidBrush object and initalizes it with the specified color.
    /// @param color The color of the brush
    ASPOSECPP_SHARED_API SolidBrush(const Color & color);

    /// Returns this brush's color.
    ASPOSECPP_SHARED_API Color get_Color() const;
    /// Sets the color of this brush.
    /// @param color A color to set
    ASPOSECPP_SHARED_API void set_Color(Color color);

    /// Creates a copy of the current object.
    /// @returns A shared pointer to the copy of the current object.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> Clone() override;

protected:
    /// Constructs a new instance of SolidBrush class.
    ASPOSECPP_SHARED_API SolidBrush();
    MEMBER_FUNCTION_MAKE_OBJECT(SolidBrush, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    /// Sets the properties of the current brush on the specified SkPaint object.
    /// @param paint An object set the properties on
    /// @param matrix Graphics world transformation matrix
    /// @param apply_shift Is used to make a small brush's texture position shift
    virtual ASPOSECPP_SHARED_API void Apply(SkPaint &paint, const SharedPtr<Drawing2D::Matrix>& matrix, bool apply_shift) override;

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override
    {
        System::Object::DBG_for_each_member(visitor);

        visitor.add_self(this);
    }
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "SolidBrush"; }
#endif

private:
    /// The color of this SolidBrush object.
    SkColor m_sk_color;
};

}}

#endif // _aspose_system_drawing_solid_brush_h_
