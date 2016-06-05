#include "bwc.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/nmea/convert.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * bwc::TAG;

bwc::bwc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

bwc::bwc(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	const auto size = std::distance(first, last);
	if ((size != 12) && (size != 13))
		throw std::invalid_argument{"invalid number of fields in bwc::parse"};

	read(*(first + 0), time_utc);
	read(*(first + 1), lat);
	read(*(first + 2), lat_hem);
	read(*(first + 3), lon);
	read(*(first + 4), lon_hem);
	read(*(first + 5), bearing_true);
	read(*(first + 6), bearing_true_ref);
	read(*(first + 7), bearing_mag);
	read(*(first + 8), bearing_mag_ref);
	read(*(first + 9), distance);
	read(*(first + 10), distance_unit);
	read(*(first + 11), waypoint_id);

	if (size == 13)
		read(*(first + 12), mode_indicator);

	// instead of reading data into temporary lat/lon, let's correct values afterwards
	lat = correct_hemisphere(lat, lat_hem);
	lon = correct_hemisphere(lon, lon_hem);
}

void bwc::set_lat(const geo::latitude & t)
{
	lat = t;
	lat_hem = convert_hemisphere(t);
}

void bwc::set_lon(const geo::longitude & t)
{
	lon = t;
	lon_hem = convert_hemisphere(t);
}

void bwc::set_bearing_true(double t) noexcept
{
	bearing_true = t;
	bearing_true_ref = reference::TRUE;
}

void bwc::set_bearing_mag(double t) noexcept
{
	bearing_mag = t;
	bearing_mag_ref = reference::MAGNETIC;
}

void bwc::set_distance(double t) noexcept
{
	distance = t;
	distance_unit = unit::distance::nm;
}

void bwc::set_waypoint(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_id = id;
}

std::unique_ptr<sentence> bwc::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<bwc>(new bwc(talker, first, last));
}

std::vector<std::string> bwc::get_data() const
{
	return {to_string(time_utc), to_string(lat), to_string(lat_hem), to_string(lon),
		to_string(lon_hem), to_string(bearing_true), to_string(bearing_true_ref),
		to_string(bearing_mag), to_string(bearing_mag_ref), to_string(distance),
		to_string(distance_unit), to_string(waypoint_id), to_string(mode_indicator)};
}
}
}
