# hotronics-heater-battery
Arduino project to power a ski boot insole heater 

Hotronics makes batteries and heated clothing, but gosh darn, their batteries 
sure are expensive. We decided to spend almost as much money on parts and way 
too much time to make our own! 

For the power source, 18650's are cheap and abundant. An Arduino Pro Mini was 
chosen for the controller due to already having some on hand, and the small 
footprint. The Arduino can output a PWM signal that drives a MOSFET controlling
power to the heating element. There is one digital input pushbutton to select the 
heating power, and one latching switch to control power to the board. A .91in 
OLED display was used for lower power consumption to show the user which mode it
is in. It stays illuminated for ~5s after a button press. 

The Anatomic sole seemed like a better option than a sticky heating pad because
it comes put together already and includes a flat cable to reduce pressure felt
from it. This heating element resistance was measured at 8.5 Ohms. To generate
enough heat, ~12V was needed for power. Widely available 12V UPS boards that
run off 18650's were a good source that include a booster up to 12V. This also
includes a charging port although it is quite slow. 

Throw all this together in a 3d printed case and strap it to your ski boot to 
keep the toes warm and toasty all winter long!
