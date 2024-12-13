#pragma once
#include <platform-gpio.hh>

/**
 * Override the & operator for the Joystick to a bool so we can tell if it's been pressed or not.
 */
inline constexpr bool
operator&(SonataJoystick x, SonataJoystick y)
{
	return static_cast<bool>(static_cast<int>(x) & static_cast<int>(y));
}
  
