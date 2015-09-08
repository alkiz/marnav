#ifndef __NMEA__VTG__HPP__
#define __NMEA__VTG__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief VTG - Track made good and Ground speed
///
/// @code
///         1  2  3  4  5  6  7  8 9
///         |  |  |  |  |  |  |  | |
/// $--VTG,x.x,T,x.x,M,x.x,N,x.x,K,m*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Track Degrees true
/// 2. Track degrees true reference
///    - T = True
/// 3. Track Degrees magnetic
/// 4. Track Degrees magnetic reference
///    - M = Magnetic
/// 5. Speed Knots
/// 6. Speed knots unit
///    - N = Knots
/// 7. Speed Kilometers Per Hour
/// 8. speed Kilometers per hour unit
///    - K = Kilometers Per Hour
/// 9. FAA mode indicator (NMEA 2.3 and later)
///
class vtg : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::VTG;
	constexpr static const char * TAG = "VTG";

	vtg();
	vtg(const vtg &) = default;
	vtg & operator=(const vtg &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, const std::vector<std::string> & fields);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> track_true;
	utils::optional<reference> type_true; // T:true
	utils::optional<double> track_magn;
	utils::optional<reference> type_magn; // M:magnetic
	utils::optional<double> speed_kn;
	utils::optional<unit::velocity> speed_kn_unit; // N:knots
	utils::optional<double> speed_kmh;
	utils::optional<unit::velocity> speed_kmh_unit; // K:kilometers per hour
	utils::optional<positioning_system_mode_indicator> mode_indicator; // NMEA 2.3 or newer

public:
	NMEA_GETTER(track_true)
	NMEA_GETTER(type_true)
	NMEA_GETTER(track_magn)
	NMEA_GETTER(type_magn)
	NMEA_GETTER(speed_kn)
	NMEA_GETTER(speed_kn_unit)
	NMEA_GETTER(speed_kmh)
	NMEA_GETTER(speed_kmh_unit)
	NMEA_GETTER(mode_indicator)

	void set_track_true(double t) noexcept;
	void set_track_magn(double t) noexcept;
	void set_speed_kn(double t) noexcept;
	void set_speed_kmh(double t) noexcept;
	void set_mode_indicator(positioning_system_mode_indicator t) noexcept
	{
		mode_indicator = t;
	}
};
}
}

#endif
