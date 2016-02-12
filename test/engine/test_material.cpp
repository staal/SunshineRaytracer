#include <boost/test/unit_test.hpp>

#include "engine/geometry/material.h"

BOOST_AUTO_TEST_CASE(MaterialDefaults)
{
    using sunshine::engine::Material;

    Material m;

    //Test default values
    BOOST_CHECK(m.Ka == glm::vec3(0.0f));
    BOOST_CHECK(m.Kd == glm::vec3(0.0f));
    BOOST_CHECK(m.Ke == glm::vec3(0.0f));
    BOOST_CHECK(m.Ks == glm::vec3(0.0f));
    BOOST_CHECK(m.Ns == 0.0f);
}