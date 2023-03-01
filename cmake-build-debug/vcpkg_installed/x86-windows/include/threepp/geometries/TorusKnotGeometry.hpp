// https://github.com/mrdoob/three.js/blob/r129/src/geometries/TorusKnotGeometry.js

#ifndef THREEPP_TORUSKNOTGEOMETRY_HPP
#define THREEPP_TORUSKNOTGEOMETRY_HPP

#include "threepp/core/BufferGeometry.hpp"

namespace threepp {

    class TorusKnotGeometry: public BufferGeometry {

    public:
        static std::shared_ptr<TorusKnotGeometry> create(
                float radius = 1,
                float tube = 0.4f,
                unsigned int tubularSegments = 64,
                unsigned int radialSegments = 8,
                unsigned int p = 2,
                unsigned int q = 3) {

            return std::shared_ptr<TorusKnotGeometry>(new TorusKnotGeometry(radius, tube, tubularSegments, radialSegments, p, q));
        }

    protected:
        explicit TorusKnotGeometry(float radius, float tube, unsigned int tubularSegments, unsigned int radialSegments, unsigned int p, unsigned int q);
    };

}// namespace threepp

#endif//THREEPP_TORUSKNOTGEOMETRY_HPP
