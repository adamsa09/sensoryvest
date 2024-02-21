---
author: Adam Sarhan
date: 20240219
due-date: 20240301
class: SMT303
grade:
---
[[SMT303]]
[[Projects]]
# Projet Handicap
## TODO
- Assure the sensor and according beeping/vibration is working as expected
- Find a way to connect all the sensors to a central breadboard
- Figure out optimal frequency to beep/vibrate at
	- Current: $distance/5 * distance$
- Take into account temperature to ensure accurate measurements

## General Info
- The vibration motor and the buzzer are connected inversely: the ground is the I/O pin and the + is the 3.5v

## Organisation of the connections
<u>Available I/O Pins: 10, 11, 12, A4, A5</u>
- 1 Central breadboard that relays information to the Arduino
	- Data for each sensor
		- `sensorFront1` → `pin 1`
		- `sensorFront2` → `pin 2`
		- `sensorBack1` → `pin 3`
		- `sensorBack2` → `pin 4`
		- `sensorRight`
			- `TRIG` → `pin A0`
			- `ECHO` → `pin A1`
		- `sensorLeft`
			- `TRIG` → `pin A2`
			- `ECHO` → `pin A3`
	- Notification of detected object
		- `buzzer` → `pin 5`
		- `vibratorFront` → `pin 6`
		- `vibratorBack` → `pin 7`
		- `vibratorRight` → `pin 8`
		- `vibratorLeft` → `pin 9`



---
# Related & References