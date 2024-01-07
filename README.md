# EarthMotion
Project Theme: 

Earthquakes - Climate Force 

 

Project Background: 

Earthquakes on Earth are a natural phenomenon, but they can have significant impacts on human life and property. Timely access to earthquake information is crucial for disaster management, early warnings, and public safety. IoT (Internet of Things) technology provides a new way for us to monitor seismic activity in real-time and convey information. By connecting to seismic monitoring data APIs, we can establish a real-time, global monitoring system for earthquake activities, enhancing our understanding of geological events. 

 

Project Introduction - EarthMotion: 

EarthMotion is an innovative project aiming to achieve real-time monitoring and visualization of global earthquake activities through seismic monitoring data APIs. 

We get APIs from external website and upload real-time data to the MQTT, then users can view raw data through MQTT Explorer host: mqtt.cetools.org student/CASA0019/G4. Then Arduino Uno Wi-Fi Rev2 board enable data float to each terminal hardware.

We have two methods for real-time seismic data visualization. For one, a 16*2 LCD presents location and magnitude information directly, the first line displays the exact location through scrolling text due to text’s length while the second line shows the figure of magnitude. For another, the rotation of two SG-90 servers drives the gears and sectors to rotate together, exposing the baseplate and allowing users to see the corresponding magnitude levels and intensity on the baseplate.

We also have two ways to remind users if there is a strong earthquake happening. One way is to start the operation of buzzer, users are aware of strong earthquakes by sound. Another way is to visually based on the color of the LED light strip. If the magnitude is less than 3.0, the color is green; for levels between 3.0 and 5.0, it turns yellow; if the magnitude exceeds 5.0, it changes to red.

Earthquakes on Earth are a natural phenomenon, but they can have significant impacts on human life and property. Timely access to earthquake information is crucial for disaster management, early warnings, and public safety.
 

Hardware
| Components   | Description |
|--------|--------|
| Arduino Uno Wi-Fi Rev2   | The board features a total of 14 digital input/output pins (including 6 PWM outputs) and 6 analog input pins, allowing connections to various sensors, actuators, and peripherals. It has a built-in Wi Fi module that enables it to connect to the Internet through Wi Fi, obtain real-time seismic data, and transmit it to various hardware for data visualization.   |
| LCD (16*2)   | The first line shows the location of seismic activities, the second line display the magnitude of earthquake.   |
| SG-90 Servo * 2   | These servos will rotate based on real-time seismic data and bring gears to rotate together to achieve device baseplate data visualization.   |
| Buzzer   | If the magnitude level is exceeding the set threshold(in the case is 5.0), buzzer will start for alarming.   |
| LED light strip   | If the magnitude level is below 3.0 it will be green; if the level is between 3.0 and 5.0 it turns to yellow; if the level  is higher than 5.0 it changes to red.   |

 
Circuit Diagram
![Circuit Diagram](/circuit_diagram.png)

 

Target Users: 

Educational Institutions: Students and educators interested in geology, earth sciences, and environmental studies. 

Public Spaces: Community members, families, and individuals interested in staying informed about seismic activities globally. 

Science Enthusiasts: Visitors to science museums, exhibits, or centers with an interest in real-time data and interactive displays. 

Emergency Response Teams: Professionals involved in disaster management and emergency response. 

 

Display and User Scenarios: 

Placement: The EarthMotion device can be displayed in public spaces such as museums, educational institutions, or community centers. 

Interactive Learning: Positioned in educational settings, the device serves as an interactive learning tool for students to understand seismic activities. 

Community Awareness: Placed in community centers or public spaces, the device raises awareness about global seismic events and encourages disaster preparedness. 

Scientific Exhibits: Suitable for science museums or exhibits, providing an engaging and informative display of real-time seismic data. 

Home Use: A scaled-down version can be created for home use, offering families a way to stay informed about global earthquake activities. 

Further Development:

Physical Device:

Redesign the internal structure of the enclosure to entails the incorporation of internal partitions and fixed slots to systematically organize and secure the wiring. This modification aims to enhance the durability and stability of the device.

Replace the current chip to a Raspberry Pi chip to enable the device to record and analyze seismic data over extended periods to generate comprehensive data reports and trend analyse for research and educational purpose.

AR twin:

Add a filter function for users to select their preferred specific time periods or location.

Apply texture mapping of the Earth to the already existed black sphere that represented the Earth.

Add noticing to users if earthquakes occured in forms of buzzer sounds, mobile texts and emails.
