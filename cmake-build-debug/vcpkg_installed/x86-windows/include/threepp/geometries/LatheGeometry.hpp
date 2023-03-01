// https://github.com/mrdoob/three.js/blob/r129/src/geometries/LatheGeometry.js

#ifndef THREEPP_LATHEGEOMETRY_HPP
#define THREEPP_LATHEGEOMETRY_HPP

#include "threepp/core/BufferGeometry.hpp"

namespace threepp {

    class LatheGeometry: public BufferGeometry {

    public:
        template<class ArrayLike>
        static std::shared_ptr<LatheGeometry> create(const ArrayLike& points, unsigned int segments = 12, float phiStart = 0, float phiLength = math::TWO_PI) {

            return std::shared_ptr<LatheGeometry>(new LatheGeometry({points.begin(), points.end()}, segments, phiStart, phiLength));

        }

    protected:
        LatheGeometry(const std::vector<Vector2>& points, unsigned int segments = 12, float phiStart = 0, float phiLength = math::TWO_PI);

    };

}

#endif//THREEPP_LATHEGEOMETRY_HPP
