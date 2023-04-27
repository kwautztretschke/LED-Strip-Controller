# MOSFETs

We have previously used:

* IXTH6N50D2 6A N-Channel depletion type


Competitor (Hardware store brand) controllers use among others:
* 09N03 25V N-Channel Enhancement Mode MOSFET
ID = 50A

* A2SHB N-Channel Enhancement mode MOSFET
ID = 2,1A
# Wiring

The fourth transistor is connected to GPIO2, which is high at boot.
This is intended, as the fourth transistor is usually for the white channel of a WRGB strip.
This leads to faster illumination when power is switched on (which should be default behaviour! Turn the damn lights on when the power is on!)

