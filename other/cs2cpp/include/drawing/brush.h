/// @file drawing/brush.h
#ifndef _aspose_system_drawing_brush_h_
#define _aspose_system_drawing_brush_h_

#include "system/icloneable.h"
#include "drawing2d/wrap_mode.h"
#include "drawing2d/matrix.h"

/// Forward declaration of SkPaint class.
ASPOSECPP_3RD_PARTY_CLASS(SkPaint);

namespace System { namespace Drawing {
/// A base class for classes that represent fillers used to fill the interiors of graphical shapes.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS Brush : public System::ICloneable, public System::IDisposable
{
    /// RTTI information.
    RTTI_INFO(System::Drawing::Brush, ::System::BaseTypesInfo<System::ICloneable>)

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const
    {
        System::Object::DBG_for_each_member(visitor);

        visitor.add_self(this);
    }
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "Brush"; }
#endif

protected:
    friend class Graphics;
    friend class Pen;
    /// Sets the properties of the current brush on the specified SkPaint object.
    /// @param paint An object set the properties on
    /// @param matrix Graphics world transformation matrix
    /// @param apply_shift Is used to make a small brush's texture position shift
    virtual ASPOSECPP_SHARED_API void Apply(SkPaint &paint, const SharedPtr<Drawing2D::Matrix>& matrix, bool apply_shift = false) {};
};

}}


#endif
