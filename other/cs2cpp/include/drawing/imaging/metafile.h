/// @file drawing/imaging/metafile.h
#ifndef _aspose_system_drawing_metafile_h_
#define _aspose_system_drawing_metafile_h_

#include "fwd.h"

#include "drawing/image.h"
#include "drawing/imaging/emf_type.h"
#include "drawing/imaging/metafile_header.h"
#include "drawing/imaging/metafile_frame_unit.h"
#include "drawing/imaging/emf_plus_record_type.h"
#include "drawing/rectangle.h"
#include "system/io/stream.h"

#include <memory>

#if defined(ASPOSECPPLIB_BEING_BUILT) || defined(ASPOSECPP_SKIA_EXTERNAL_USAGE)
#include <core/SkBitmap.h>
#include <core/SkCanvas.h>
#endif

/// Forward declaration of SkBitmap class.
ASPOSECPP_3RD_PARTY_CLASS(SkBitmap);
/// Forward declaration of SkCanvas class.
ASPOSECPP_3RD_PARTY_CLASS(SkCanvas);
/// Forward declaration of SkData class.
ASPOSECPP_3RD_PARTY_CLASS(SkData);
/// Forward declaration of SkImageInfo struct.
ASPOSECPP_3RD_PARTY_STRUCT(SkImageInfo);

#if defined(ASPOSECPPLIB_BEING_BUILT) || !defined(ASPOSECPP_SKIA_EXTERNAL_USAGE)
// Static checks of SkEncodedImageFormat enum.
ASPOSECPP_3RD_PARTY_ENUM_CLASS(SkEncodedImageFormat);
#endif 

namespace System { namespace Drawing { class Bitmap; } }

namespace System { namespace Drawing { namespace Imaging {
/// Represents a graphic metafile.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS Metafile : public Image
{
    RTTI_INFO(System::Drawing::Imaging::Metafile, ::System::BaseTypesInfo<System::Drawing::Image>)

public:
    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    ASPOSECPP_SHARED_API Metafile(const System::String& filename);
    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    ASPOSECPP_SHARED_API Metafile(const SharedPtr<System::IO::Stream>& stream);
    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    ASPOSECPP_SHARED_API Metafile(const SharedPtr<System::IO::Stream>& stream, IntPtr hdc, EmfType type);
    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    ASPOSECPP_SHARED_API Metafile(const SharedPtr<System::IO::Stream>& stream, IntPtr hdc);
    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    ASPOSECPP_SHARED_API Metafile(const SharedPtr<System::IO::Stream>& stream, IntPtr hdc, Rectangle rect, MetafileFrameUnit frameUnit, EmfType type);
    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    ASPOSECPP_SHARED_API Metafile(const SharedPtr<System::IO::Stream>& stream, IntPtr hdc, RectangleF rect, MetafileFrameUnit frameUnit, EmfType type);
    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    ASPOSECPP_SHARED_API Metafile(IntPtr, EmfType);
    /// Destructor.
    virtual ASPOSECPP_SHARED_API ~Metafile();

    /// Returns a header associated with the current object.
    ASPOSECPP_SHARED_API SharedPtr<MetafileHeader> GetMetafileHeader();
    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    ASPOSECPP_SHARED_API IntPtr GetHenhmetafile();
    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    ASPOSECPP_SHARED_API void PlayRecord(EmfPlusRecordType, int32_t, int32_t, System::ByteArrayPtr);

    /// Returns the width of the image in pixels.
    virtual ASPOSECPP_SHARED_API int get_Width() const override;
    /// Returns the heights of the image in pixels.
    virtual ASPOSECPP_SHARED_API int get_Height() const override;

    /// Returns a value the indicates the image format.
    virtual ASPOSECPP_SHARED_API Imaging::ImageFormatPtr get_RawFormat() const override;
    /// Returns a value the indicates the pixel format.
    virtual ASPOSECPP_SHARED_API Imaging::PixelFormat get_PixelFormat() const override;
    /// Returns a copy of the current object.
    virtual ASPOSECPP_SHARED_API SharedPtr<Image> Clone() override;

protected:
    friend class Image;
    friend class System::Drawing::Bitmap;

    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    virtual ASPOSECPP_SHARED_API std::unique_ptr<SkCanvas> GetDrawingCanvas() const override;
    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    virtual ASPOSECPP_SHARED_API sk_sp<SkData> GetRawBytes(SkEncodedImageFormat encoder_type, int quality) override;

    /// Returns an underlying SkBitmap object.
    virtual ASPOSECPP_SHARED_API const SkBitmap* GetSkBitmap() const override;
    /// Returns an underlying SkEncodedFormat object.
    virtual ASPOSECPP_SHARED_API const SkEncodedImageFormat GetSkEncodedFormat() const override;

    /// Draws the specified region of the image to the specified region on the specified canvas.
    /// The source bitmap region is scaled and translated to fill the destination region.
    /// @param sk_canvas The canvas to draw on
    /// @param dest_rect The rectangle on the canvas to draw to
    /// @param src_rect The rectangle specifying the portion of the image to draw
    /// @param matrix The matrix that specifies how to traslate and scale the source image region
    /// @param quality The quality of image interpolation
    /// @param blend_mode Specifies how the source colors are combined with the background colors
    virtual void Draw(SkCanvas* sk_canvas, const SkRect& dest_rect, const SkRect&src_rect, SkMatrix* matrix, SkFilterQuality quality, SkBlendMode blend_mode) const override;
    /// Draws the the image to the specified region on the specified canvas.
    /// The source image is scaled and translated to fill the destination region.
    /// @param sk_canvas The canvas to draw on
    /// @param dest_rect The rectangle in the canvas to draw to
    /// @param matrix The matrix that specifies how to traslate and scale the source image region
    /// @param quality The quality of image interpolation
    /// @param blend_mode Specifies how the source colors are combined with the background colors
    virtual void Draw(SkCanvas* sk_canvas, const SkRect& dest_rect, SkMatrix* matrix, SkFilterQuality quality, SkBlendMode blend_mode) const override;
    /// Draws the specified region of the image to the specified region on the specified canvas.
    /// The source bitmap region is scaled and translated to fill the destination region.
    /// @param sk_canvas The canvas to draw on
    /// @param dest_points Array of 3 PointF objects representing points that define the rectangular region on the canvas to draw to
    /// @param src_rect The rectangle specifying the portion of the image to draw
    /// @param matrix The matrix that specifies how to traslate and scale the source image region
    /// @param quality The quality of image interpolation
    /// @param blend_mode Specifies how the source colors are combined with the background colors
    virtual void Draw(SkCanvas* sk_canvas, ArrayPtr<PointF> dest_points, const SkRect& src_rect, SkMatrix* matrix, SkFilterQuality quality, SkBlendMode blend_mode) const override;
    /// Draws the specified region of the image to the specified region on the specified canvas.
    /// The source bitmap region is scaled and translated to fill the destination region.
    /// @param sk_canvas The canvas to draw on
    /// @param dest_points ArrayView of 3 PointF objects representing points that define the rectangular region on the canvas to draw to
    /// @param src_rect The rectangle specifying the portion of the image to draw
    /// @param matrix The matrix that specifies how to traslate and scale the source image region
    /// @param quality The quality of image interpolation
    /// @param blend_mode Specifies how the source colors are combined with the background colors
    virtual void Draw(SkCanvas* sk_canvas, const System::Details::ArrayView<PointF>& dest_points, const SkRect& src_rect, SkMatrix* matrix, SkFilterQuality quality, SkBlendMode blend_mode) const override;
    /// Returns the original image format.
    virtual ASPOSECPP_SHARED_API Imaging::PixelFormat GetOriginalFormat() const override;

#ifdef ASPOSE_DUMMY_META_FILE
    /// Constructs a new instance of Metafile class.
    /// @param stream A stream object to read the metafile from
    /// @param image_format The original image format
    ASPOSECPP_SHARED_API Metafile(const SharedPtr<System::IO::Stream>& stream, const Drawing::Imaging::ImageFormatPtr& image_format);
    MEMBER_FUNCTION_MAKE_OBJECT(Metafile, CODEPORTING_ARGS(const SharedPtr<System::IO::Stream>& stream, const Drawing::Imaging::ImageFormatPtr& image_format), CODEPORTING_ARGS(stream, image_format));
    /// Image format.
    Drawing::Imaging::ImageFormatPtr m_image_format;
    /// A bounding rectangle of the image.
    Rectangle m_bounds;
    /// The width of the image.
    int m_width;
    /// The hegiht of the image.
    int m_height;
    /// An SkBitmap object representing the image.
    mutable std::unique_ptr<SkBitmap> m_dummy_sk_bitmap;
    ArrayPtr<uint8_t> m_metafile_data;
#endif
};

}}}

#endif
