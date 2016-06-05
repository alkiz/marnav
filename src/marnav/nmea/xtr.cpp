#include "xtr.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * xtr::TAG;

xtr::xtr()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

xtr::xtr(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in xtr"};

	read(*(first + 0), cross_track_error_magnitude);
	read(*(first + 1), direction_to_steer);
	read(*(first + 2), cross_track_unit);
}

std::unique_ptr<sentence> xtr::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<xtr>(new xtr(talker, first, last));
}

std::vector<std::string> xtr::get_data() const
{
	return {to_string(cross_track_error_magnitude), to_string(direction_to_steer),
		to_string(cross_track_unit)};
}
}
}
