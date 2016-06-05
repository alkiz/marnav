#include "zda.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * zda::TAG;

zda::zda()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

zda::zda(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in zda"};

	read(*(first + 0), time_utc);
	read(*(first + 1), day);
	read(*(first + 2), month);
	read(*(first + 3), year);
	read(*(first + 4), local_zone_hours);
	read(*(first + 5), local_zone_minutes);
}

std::unique_ptr<sentence> zda::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<zda>(new zda(talker, first, last));
}

std::vector<std::string> zda::get_data() const
{
	return {to_string(time_utc), format(day, 2), format(month, 2), format(year, 4),
		format(local_zone_hours, 2), format(local_zone_minutes, 2)};
}
}
}
