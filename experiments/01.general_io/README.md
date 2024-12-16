General IO Example
==================

This example shows how to access and use the GPIO and RGB LED via the MMIO_CAPABILITY() macro. The RGB LED slowly changes colours, the user LEDs wil play a simple scrolling pattern and using the Joystick will create an output on the UART saying which direction is being selected and if the button is pressed.
This uses the debug facilities to write a message directly to the UART.

The [`xmake.lua`](xmake.lua) file contains the build instructions for this example.

When looking to access the IO for the Sonata Board you need to do 2 things:
1. Look in the "devices" section of ['../../sdk/boards/sonata.json'](../../sdk/boards/sonata.json) to get the list of devices that can be accessed.
2. Look in ['../../sdk/include/platform/sunburst'](../../sdk/include/platform/sunburst) to find the header files for those devices. Each header file has a name beginning "platform-".
Note: I agree that it is a little confusing that the board is called "sonata" and the platform is called "sunburst". I'm sure there's a historical reason for it.

In this example we control:
* The RGB LED using the "SonataRgbLedController" class, defined in ['../../sdk/include/platform/sunburst/platform-rgbctrl.hh'](../../sdk/include/platform/sunburst/platform-rgbctrl.hh) pointing to "rgbled" as defined in ['../../sdk/boards/sonata.json'](../../sdk/boards/sonata.json).
* The Joystick using the "SonataGPIO" class, defined in ['../../sdk/include/platform/sunburst/platform-gpio.hh'](../../sdk/include/platform/sunburst/platform-gpio.hh) pointing to "gpio" as defined in ['../../sdk/boards/sonata.json'](../../sdk/boards/sonata.json).

We've also created a simple ['gpio_helper.hh'](gpio_helper.hh) file to assist with somethings. In this case we have overidden the "&" operator so that we can do a Boolean compare of the SonataJoystick values that are returned.
