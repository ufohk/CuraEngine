

#ifndef CURAENGINE_UNIT_H
#define CURAENGINE_UNIT_H

#include <units/isq/si/length.h>
#include <units/isq/si/time.h>

namespace u = units::isq::si::references;

namespace cura::unit
{
using base_length = units::isq::si::micrometre; // The base length unit, use a different prefix for more or less precision

}


#endif // CURAENGINE_UNIT_H
