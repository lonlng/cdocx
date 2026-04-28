/**
 * @file convert_util.cpp
 * @brief ConvertUtil implementation
 * @since 0.8.0
 */

#include <cdocx/convert_util.h>

#include <cmath>

namespace cdocx {

// Points per inch (standard typographic measure)
static constexpr double kPointsPerInch = 72.0;

// Millimeters per inch
static constexpr double kMmPerInch = 25.4;

// Default screen resolution in dpi
static constexpr double kDefaultDpi = 96.0;

// Twips per point
static constexpr double kTwipsPerPoint = 20.0;

double ConvertUtil::point_to_pixel(double points) {
    return point_to_pixel(points, kDefaultDpi);
}

double ConvertUtil::point_to_pixel(double points, double resolution) {
    return points / kPointsPerInch * resolution;
}

double ConvertUtil::pixel_to_point(double pixels) {
    return pixel_to_point(pixels, kDefaultDpi);
}

double ConvertUtil::pixel_to_point(double pixels, double resolution) {
    return pixels / resolution * kPointsPerInch;
}

int ConvertUtil::pixel_to_new_dpi(double pixels, double old_dpi, double new_dpi) {
    return static_cast<int>(std::round(pixels * new_dpi / old_dpi));
}

double ConvertUtil::inch_to_point(double inches) {
    return inches * kPointsPerInch;
}

double ConvertUtil::point_to_inch(double points) {
    return points / kPointsPerInch;
}

double ConvertUtil::millimeter_to_point(double millimeters) {
    return millimeters / kMmPerInch * kPointsPerInch;
}

double ConvertUtil::point_to_millimeter(double points) {
    return points / kPointsPerInch * kMmPerInch;
}

double ConvertUtil::centimeter_to_point(double centimeters) {
    return millimeter_to_point(centimeters * 10.0);
}

double ConvertUtil::point_to_centimeter(double points) {
    return point_to_millimeter(points) / 10.0;
}

int ConvertUtil::point_to_twips(double points) {
    return static_cast<int>(std::round(points * kTwipsPerPoint));
}

double ConvertUtil::twips_to_point(int twips) {
    return static_cast<double>(twips) / kTwipsPerPoint;
}

}  // namespace cdocx
