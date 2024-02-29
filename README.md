---
author: Adam Sarhan
date: 20240219
due-date: 20240301
class: SMT303
grade:
---
[[SMT303]]
# Projet Handicap
## Organisation of the connections
<u>Available I/O Pins: 10, 11, 12, A4, A5</u>
- 1 Central breadboard that relays information to the Arduino
	- Data for each sensor
		- `sensorFront1` → `pin A0`
		- `sensorFront2` → `pin A1`
		- `sensorBack1` → `pin A2`
		- `sensorBack2` → `pin A3`
		- `sensorRight`
			- `TRIG` → `pin 1`
			- `ECHO` → `pin 2`
		- `sensorLeft`
			- `TRIG` → `pin 3`
			- `ECHO` → `pin 4`
	- Notification of detected object
		- `buzzer` → `pin 5`
		- `vibratorFront` → `pin 6`
		- `vibratorRight` → `pin 7`
		- `vibratorLeft` → `pin 8`
		- `vibratorBack` → `pin 9`

## TODO
- Assure the sensor and according beeping/vibration is working as expected
- Find a way to connect all the sensors to a central breadboard
- Figure out optimal frequency to beep/vibrate at
	- Current: $distance/5 * distance$
- Take into account temperature to ensure accurate measurements

---
# Related & References