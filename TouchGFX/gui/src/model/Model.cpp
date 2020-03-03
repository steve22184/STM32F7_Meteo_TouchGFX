#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
#include <tuple>
#include "ds18b20.hpp"
#include "dht11.hpp"

std::tuple<uint8_t, uint8_t, uint8_t> rtc_get (void);
void rtc_set (uint8_t h, uint8_t m, uint8_t s);

#endif

Model::Model() : modelListener(0), hour(0), minute(0), second(0), setup_flag(0), humidity(0),
		eeprom_flag(0), temp_mantissa(0), temp_fraction(0), qx(270), qy(-230), csx(270), csy(45),
slider_val(0)
{

}

void Model::tick()
{
#ifndef SIMULATOR
	using namespace app;

	if (setup_flag == 2){

		auto time = rtc_get();

		hour = std::get<0>(time);
		minute = std::get<1>(time);
		second = std::get<2>(time);
	} else if (setup_flag == 1){
		rtc_set (hour, minute, second);
		setup_flag = 2;
	}

	auto temp = DS18B20::get_temp();
	temp_mantissa = std::get<0>(temp);
	temp_fraction = std::get<1>(temp);

	humidity = dht11_get().humidity();

	eeprom_flag = eeprom().get_flag();

#endif
}
