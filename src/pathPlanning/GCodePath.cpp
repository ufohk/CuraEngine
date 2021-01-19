//Copyright (c) 2021 Ultimaker B.V.
//CuraEngine is released under the terms of the AGPLv3 or higher.

#include "GCodePath.h"
#include "../GCodePathConfig.h"

namespace cura
{
GCodePath::GCodePath(const GCodePathConfig& config, std::string mesh_id, const SpaceFillType space_fill_type, const Ratio flow, const bool spiralize, const Ratio speed_factor) :
config(&config),
mesh_id(mesh_id),
space_fill_type(space_fill_type),
flow(flow),
speed_factor(speed_factor),
retract(false),
perform_z_hop(false),
perform_prime(false),
skip_agressive_merge_hint(false),
points(std::vector<Point>()),
done(false),
spiralize(spiralize),
fan_speed(GCodePathConfig::FAN_SPEED_DEFAULT),
estimates(TimeMaterialEstimates())
{
}

bool GCodePath::isTravelPath() const
{
    return config->isTravelPath();
}

double GCodePath::getExtrusionMM3perMM() const
{
    return flow * config->getExtrusionMM3perMM();
}

double GCodePath::getExtrusionMM3perS() const
{
    //We want to know how much material is extruded per second of extrusion in this type of path.
    //So we can calculate how long the path would be if we were to travel along it at the path's speed for 1 second.
    //Multiply this by the amount of material per unit of length, and we get the amount of material extruded in 1 second.
    return getExtrusionMM3perMM() * config->getSpeed() * speed_factor;
}

coord_t GCodePath::getLineWidthForLayerView() const
{
    return flow * config->getLineWidth() * config->getFlowRatio();
}

void GCodePath::setFanSpeed(double fan_speed)
{
    this->fan_speed = fan_speed;
}

double GCodePath::getFanSpeed() const
{
    return (fan_speed >= 0 && fan_speed <= 100) ? fan_speed : config->getFanSpeed();
}

}
