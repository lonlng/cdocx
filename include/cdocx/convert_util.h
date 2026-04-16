/**
 * @file convert_util.h
 * @brief Measurement unit conversion utilities
 * @details Provides helper functions to convert between various measurement units
 *          commonly used in document processing (points, inches, millimeters, pixels, twips).
 *
 * @par Usage Example:
 * @code
 * double margin_in_points = cdocx::ConvertUtil::inch_to_point(1.0);   // 72.0
 * double width_in_inches = cdocx::ConvertUtil::point_to_inch(144.0);  // 2.0
 * double a4_width = cdocx::ConvertUtil::millimeter_to_point(210.0);  // ~595.3
 * int twips = cdocx::ConvertUtil::point_to_twips(72.0);              // 1440
 * @endcode
 *
 * @since 0.7.0
 */

#pragma once

#include <cstdint>

namespace cdocx {

/**
 * @class ConvertUtil
 * @brief Static utility class for measurement unit conversions
 * @since 0.7.0
 */
class ConvertUtil {
public:
    ConvertUtil() = delete;

    // ========================================================================
    // Points <-> Pixels
    // ========================================================================

    /**
     * @brief Convert points to pixels at 96 dpi
     * @param points Value in points
     * @return Value in pixels
     */
    static double point_to_pixel(double points);

    /**
     * @brief Convert points to pixels at specified resolution
     * @param points Value in points
     * @param resolution Dots per inch (dpi)
     * @return Value in pixels
     */
    static double point_to_pixel(double points, double resolution);

    /**
     * @brief Convert pixels to points at 96 dpi
     * @param pixels Value in pixels
     * @return Value in points
     */
    static double pixel_to_point(double pixels);

    /**
     * @brief Convert pixels to points at specified resolution
     * @param pixels Value in pixels
     * @param resolution Dots per inch (dpi)
     * @return Value in points
     */
    static double pixel_to_point(double pixels, double resolution);

    /**
     * @brief Convert pixels from one resolution to another
     * @param pixels Value in pixels
     * @param old_dpi Current dpi resolution
     * @param new_dpi Target dpi resolution
     * @return Value in pixels at new resolution
     */
    static int pixel_to_new_dpi(double pixels, double old_dpi, double new_dpi);

    // ========================================================================
    // Points <-> Inches
    // ========================================================================

    /**
     * @brief Convert inches to points
     * @param inches Value in inches
     * @return Value in points
     */
    static double inch_to_point(double inches);

    /**
     * @brief Convert points to inches
     * @param points Value in points
     * @return Value in inches
     */
    static double point_to_inch(double points);

    // ========================================================================
    // Points <-> Millimeters
    // ========================================================================

    /**
     * @brief Convert millimeters to points
     * @param millimeters Value in millimeters
     * @return Value in points
     */
    static double millimeter_to_point(double millimeters);

    /**
     * @brief Convert points to millimeters
     * @param points Value in points
     * @return Value in millimeters
     */
    static double point_to_millimeter(double points);

    // ========================================================================
    // Points <-> Centimeters
    // ========================================================================

    /**
     * @brief Convert centimeters to points
     * @param centimeters Value in centimeters
     * @return Value in points
     */
    static double centimeter_to_point(double centimeters);

    /**
     * @brief Convert points to centimeters
     * @param points Value in points
     * @return Value in centimeters
     */
    static double point_to_centimeter(double points);

    // ========================================================================
    // Points <-> Twips
    // ========================================================================

    /**
     * @brief Convert points to twips (1/20 of a point)
     * @param points Value in points
     * @return Value in twips
     */
    static int point_to_twips(double points);

    /**
     * @brief Convert twips to points
     * @param twips Value in twips
     * @return Value in points
     */
    static double twips_to_point(int twips);

    // ========================================================================
    // Convenience: Common paper sizes in points
    // ========================================================================

    /**
     * @brief A4 paper width in points (210 mm)
     * @return 595.276 points
     */
    static double a4_width() { return millimeter_to_point(210.0); }

    /**
     * @brief A4 paper height in points (297 mm)
     * @return 841.89 points
     */
    static double a4_height() { return millimeter_to_point(297.0); }

    /**
     * @brief Letter paper width in points (8.5 inches)
     * @return 612.0 points
     */
    static double letter_width() { return inch_to_point(8.5); }

    /**
     * @brief Letter paper height in points (11 inches)
     * @return 792.0 points
     */
    static double letter_height() { return inch_to_point(11.0); }
};

} // namespace cdocx
