## Inspiration
Being engineering students, we realized how in industries and several other aspects of work, a person and especially an engineer needs to use different tools for the sole purpose of measuring. Hence we thought of building a hack that is an all-in-one solution for measuring requirements, which can also come in handy to beginner electricians. Many times we hear during the drilling of holes in walls, humans get shocked by rupturing live wires. So we thought of incorporating a live wire detector that can sense live wires. Along with that, we took inspiration from theodolites that were used to measure very tall structures, to build the height measuring device.

## What it does
It is an electronic tool that can measure if a surface is leveled or not, measure pretty high heights using a laser pointer, the concept of theodolites, RPM of rotating objects using the stroboscopic effect. And a live wire detector can be useful for measuring live wires behind walls of concealing wiring.  The purpose of Laser theodolite was to give the electricians a rough Idea of how much wire to buy for tall buildings.  This can also be used by painter to estimate area of faces of buildings.

## How we built it
ElecTool contains an accelerometer to measure the inclination angles. The level meter was pretty straight forward it senses the inclination on the X-axis. Upon tilting the board, the acceleration due to the gravity vector changes at an angle phi. Along with that using some trigonometry, we find the exact angle. 
The next was the stroboscope, where it uses a potentiometer to change the flickering rate i.e how fast the LED oscillates and upon matching that with a moving or rotating object, we can see the object is still and steady, by calculating the period of oscillation and inversing it, we calculate the frequency of the object.  Here my camera's shutter speed is being approximated.
Next is the Live wire detector, where it can detect the presence of live wires. Using transistors as Darlington pairs, it was picking up very small signals. Upon bringing that near an AC supply, there's a metallic plate behind the breadboard which acts as a surface capacitor and triggers the Arduino. 
Finally, the Height measurement tool is made by a laser pointer and the inclination readings. Using basic geometry and the tan(phi)=height/base, we were able to measure the height. The phi is the inclination angle measured by the accelerometer and the base is kept unity. Thus the height equals the tan(phi). 
These were all controlled by the Arduino, and along with that, an OLED display is used for displaying the menu and a button and potentiometer for selecting. 

## Challenges we ran into
Completing the hardware prototype and making the code work for the different parts was the biggest challenge of them all. Mainly getting rid of noises that were coming from the accelerometer data. Which was resulting in very jittery measurements of the angles thus bad readings. The live wire detector was false triggering sometimes. Making the demo video finally was very constrained, as it contains a demo of 4 tools. 

## Accomplishments that we're proud of
Being able to complete the project on time was the biggest achievement of them all. Watching the height measurements was pretty amazing, as it was a very crude device giving some accurate results. Removing the false triggering of the live wire detector.

## What we learned
Learned about Theodolites and how previously people used to measure tall sculptures. 

## What's next for ElecTool
Making a perfect enclosure and a PCB for making a perfect handy tool for Engineers and as well as beginner Electricians.
