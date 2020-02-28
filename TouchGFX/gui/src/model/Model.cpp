#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
#include <tuple>

std::tuple<uint8_t, uint8_t, uint8_t> rtc_get (void);
void rtc_set (uint8_t h, uint8_t m, uint8_t s);
#endif

Model::Model() : modelListener(0), hour(0), minute(0), second(0), setup_flag(0)
{

}

void Model::tick()
{
#ifndef SIMULATOR
	if (setup_flag == 2){

		auto time = rtc_get();

		hour = std::get<0>(time);
		minute = std::get<1>(time);
		second = std::get<2>(time);
	} else if (setup_flag == 1){
		rtc_set (hour, minute, second);
		setup_flag = 2;
	}
#endif
}
