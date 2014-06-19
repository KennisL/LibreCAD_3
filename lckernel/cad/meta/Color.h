#ifndef COLOR_H
#define COLOR_H

#include <algorithm>
#include <cmath>

namespace lc {

    /**
      * Represents a Color
      *
      */
    class Color {
        public:
            Color() : _r(0.), _g(0.), _b(0.), _a(1.) {}
            Color(double r, double g, double b, double a = 1.) : _r(std::min(std::max(0.,r), 1.)), _g(std::min(std::max(0.,g), 1.)), _b(std::min(std::max(0.,b), 1.)), _a(std::min(std::max(0.,a), 1.)) {}
            Color(const Color& other) : _r(other._r), _g(other._g), _b(other._b), _a(other._a) {}

            Color& operator = (const Color& other) {
                if (this != &other) {
                    _r = other._r;
                    _g = other._g;
                    _b = other._b;
                    _a = other._a;
                }

                return *this;
            }

            ~Color() {}

            inline double red() const {
                return _r;
            }
            inline double green() const {
                return _g;
            }
            inline double blue() const {
                return _b;
            }
            inline double alpha() const {
                return _a;
            }

            inline unsigned char redI() const {
                return std::round(_r * 255);
            }
            inline unsigned char greenI() const {
                return std::round(_g * 255);
            }
            inline unsigned char blueI() const {
                return std::round(_b * 255);
            }
            inline unsigned char alphaI() const {
                return std::round(_a * 255);
            }

        private:
            double _r;
            double _g;
            double _b;
            double _a;
    };


}

#endif // Color_H
