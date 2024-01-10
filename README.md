# EarthMotion: Real-Time Earthquake Activity Monitoring

## Project Theme
**Earthquakes - Climate Force**

Earthquakes on Earth are a natural phenomenon, but they can have significant impacts on human life and property. Timely access to earthquake information is crucial for disaster management, early warnings, and public safety. IoT (Internet of Things) technology provides a new way for us to monitor seismic activity in real-time and convey information. By connecting to seismic monitoring data APIs, we can establish a real-time, global monitoring system for earthquake activities, enhancing our understanding of geological events.

<div align="center">
    <img width="650px" src="./Src/Overall.jpg" alt="Final Device">
</div>

## Project Introduction
**EarthMotion** is an innovative project aiming to achieve real-time monitoring and visualization of global earthquake activities through seismic monitoring data APIs.

We access APIs from external websites and upload real-time data to MQTT. Users can view raw data through MQTT Explorer at `mqtt.cetools.org` with credentials `student/CASA0019/G4`. The Arduino Uno Wi-Fi Rev2 board enables data to flow to each terminal hardware.

We have implemented two methods for real-time seismic data visualization:
1. A 16*2 LCD displays location and magnitude information. The first line shows the exact location through scrolling text due to the length of the text, while the second line displays the magnitude figure.
2. The rotation of two SG-90 servos drives gears and sectors, exposing the baseplate and allowing users to see the corresponding magnitude levels and intensity on the baseplate.

Additionally, we offer two ways to alert users in the event of a significant earthquake:
1. The operation of a buzzer provides an auditory warning of strong earthquakes.
2. A visually based alert using the color of an LED light strip indicates the severity. Green for magnitudes less than 3.0, yellow for levels between 3.0 and 5.0, and red if the magnitude exceeds 5.0.

*Earthquakes on Earth are a natural phenomenon, but they have significant impacts on human life and property. Timely access to earthquake information is crucial for disaster management, early warnings, and public safety.*


Hardware
| Components   | Description |
|--------|--------|
| Arduino Uno Wi-Fi Rev2   | The board features a total of 14 digital input/output pins (including 6 PWM outputs) and 6 analog input pins, allowing connections to various sensors, actuators, and peripherals. It has a built-in Wi Fi module that enables it to connect to the Internet through Wi Fi, obtain real-time seismic data, and transmit it to various hardware for data visualization.   |
| LCD (16*2)   | The first line shows the location of seismic activities, the second line display the magnitude of earthquake.   |
| SG-90 Servo * 2   | These servos will rotate based on real-time seismic data and bring gears to rotate together to achieve device baseplate data visualization.   |
| Buzzer   | If the magnitude level is exceeding the set threshold(in the case is 5.0), buzzer will start for alarming.   |
| LED light strip   | If the magnitude level is below 3.0 it will be green; if the level is between 3.0 and 5.0 it turns to yellow; if the level  is higher than 5.0 it changes to red.   |

 
Circuit Diagram
![Circuit Diagram](/Src/circuit_diagram.png)

 

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

## AR Twin: 
### Digital Twin Development
Integration with Blender: Importing gauge FBX files into Blender for dial image integration and texture adjustments.
Panel Rotation Mechanics: Manipulating semi-circular panels along y and z axes for accurate alignment.
### AR Postcard with Image Tracking
World Map Layout: Creation of a precisely laser-cut postcard for image tracking in AR.
Dynamic Alignment: Auto-alignment of the AR object with the postcard for a seamless global view.

![image](https://github.com/casa0016-group4/EarthMotion/assets/146333771/d12c13a6-2247-419e-9839-fca2867c5a8a)
![image](https://github.com/casa0016-group4/EarthMotion/assets/146333771/7b4502ea-8762-4bf4-8219-22fdc2f6b046)


### Informative Leaflet
Data Presentation: Display of the latest global earthquake events and information from the past 24 hours.
Enhanced Information: Detailed data feed including Earthquake Magnitude, Location, and Time.

![image](https://github.com/casa0016-group4/EarthMotion/assets/146333771/34bc1804-8ce9-4b3d-99ab-ff608728c6ae)

### Virtual Globe Feature
Earthquake Visualization: Integration of earthquake data into a virtual globe model (sourced from Unity3D-Globe).
Real-Time Updates: Dynamic representation of seismic activities globally.

![image](https://github.com/casa0016-group4/EarthMotion/assets/146333771/6a6f0e37-ca30-47e7-9e68-764d2d845043)

### Interactive AR Features
Object Interaction: User capabilities include double-tapping to place an object, dragging, rotating, and scaling using multi-touch gestures.

![image](https://github.com/casa0016-group4/EarthMotion/assets/146333771/162f6525-cbd8-49ec-9972-76135bb9e0f2)

### Technologies Used
1. Unity: For AR application development.
2. Visual Studio Code: For coding and scripting.
3. Blender 3.6 LTS: For design and texture modifications.

In conclusion, Our Augmented Digital Counterpart project represents a significant leap in digital data presentation, providing users with an enriched and interactive experience. The integration of advanced technologies and user-friendly interactive features makes this project a standout in the field of AR applications.



### Further Development:

Physical Device:

Redesign the internal structure of the enclosure to entails the incorporation of internal partitions and fixed slots to systematically organize and secure the wiring. This modification aims to enhance the durability and stability of the device.

Replace the current chip to a Raspberry Pi chip to enable the device to record and analyze seismic data over extended periods to generate comprehensive data reports and trend analyse for research and educational purpose.

AR twin:

Add a filter function for users to select their preferred specific time periods or location.

Apply texture mapping of the Earth to the already existed black sphere that represented the Earth.

Add noticing to users if earthquakes occured in forms of buzzer sounds, mobile texts and emails.
