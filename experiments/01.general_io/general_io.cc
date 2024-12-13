// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#include <compartment.h>
#include <cstdint>
#include <debug.hh>
#include <fail-simulator-on-error.h>

//#include <cstdlib>
//#include <errno.h>
//#include <locks.hh>
//#include <platform-entropy.hh>
#include <platform-rgbctrl.hh>
#include <tick_macros.h>
#include <FreeRTOS-Compat/task.h>
#include <platform-gpio.hh>
#include "gpio_helper.hh"

/// Expose debugging features unconditionally for this compartment.
using Debug = ConditionalDebug<true, "General IO tests compartment">;

auto gpio_data()
{
	return MMIO_CAPABILITY(SonataGPIO, gpio);
}

void set_rgb_led_colour(auto leds, uint8_t colours[]) {
	//auto  leds    = MMIO_CAPABILITY(SonataRgbLedController, rgbled);
	leds->rgb(SonataRgbLed::Led0, colours[0], colours[1], colours[2]);
	leds->update();
}

/// Thread entry point.
void __cheri_compartment("main_comp") main_entry()
{
	//Timeout t{MS_TO_TICKS(5000)};

	// Print hello world, along with the compartment's name to the default UART.
	Debug::log("General IO Tests -  Hello World");

	uint8_t colours[] = {255, 0, 0};
	auto  leds    = MMIO_CAPABILITY(SonataRgbLedController, rgbled);
	// leds->rgb(SonataRgbLed::Led0, colours[0], colours[1], colours[2]);
	// leds->update();
	set_rgb_led_colour(leds, colours);

	uint8_t phase = 0;
	uint8_t currentLed = 0;
	while(true) {
		//t = Timeout{MS_TO_TICKS(250)};
		vTaskDelay(MS_TO_TICKS(50));
		switch(phase) {
			default:
				phase = 0;
				colours[0] = 255;
				colours[1] = 0;
				colours[2] = 0;
				Debug::log("Phase incorrect {} resetting to 0.", phase);
				break;
			case 0:
				colours[0]--;
				colours[1]++;
				if(colours[0] == 0) {
					phase++;
				}
				break;
			case 1:
				colours[1]--;
				colours[2]++;
				if(colours[1] == 0) {
					phase++;
				}
				break;
			case 2:
				colours[2]--;
				colours[0]++;
				if(colours[2] == 0) {
					phase = 0;
				}
				break;
		}
		set_rgb_led_colour(leds, colours);

		gpio_data()->led_off(currentLed);
		currentLed++;
		if(currentLed > gpio_data()->LEDCount) {
			currentLed = 0;
		}
		gpio_data()->led_on(currentLed);

		auto js = gpio_data()->read_joystick();
		if(js & SonataJoystick::Left) {
			Debug::log("Joystick: Left");
		}
		if(js & SonataJoystick::Right) {
			Debug::log("Joystick: Right");
		}
		if(js & SonataJoystick::Up) {
			Debug::log("Joystick: Up");
		}
		if(js & SonataJoystick::Down) {
			Debug::log("Joystick: Down");
		}
		if(js & SonataJoystick::Pressed) {
			Debug::log("Joystick: Pressed");
		}
	}
}
