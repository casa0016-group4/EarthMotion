const axios = require('axios');
const mqtt = require('mqtt');
const moment = require('moment');

const mqttOptions = {
    username: 'YourUsernameHere', // Replace with your username
    password: 'YourPasswordHere', // Replace with your password
    port: 1884
  };

// MQTT Broker URL and Port
const client = mqtt.connect('mqtt://mqtt.cetools.org', mqttOptions);

// Function to fetch data from the API
async function fetchData() {
  // Get the current date and the next day's date
  const today = moment().format('YYYY-MM-DD');
  const tomorrow = moment().add(1, 'days').format('YYYY-MM-DD');

  // Construct the API URL with dynamic dates
  const dynamicApiURL = `https://earthquake.usgs.gov/fdsnws/event/1/query?format=geojson&starttime=${today}&endtime=${tomorrow}&minmagnitude=1`;

  try {
    const response = await axios.get(dynamicApiURL);
    return response.data;
  } catch (error) {
    console.error('Error fetching data:', error);
    return null;
  }
}

// Function to filter and get the latest earthquake data
function getLatestEarthquakeData(data) {
  if (!data || !data.features || data.features.length === 0) {
    return null;
  }

  // Sort earthquakes by time in descending order
  const sortedEarthquakes = data.features.sort((a, b) => b.properties.time - a.properties.time);

  // Get the latest earthquake
  const latestEarthquake = sortedEarthquakes[0];

  // Extract and return relevant information
  return {
    magnitude: latestEarthquake.properties.mag,
    location: latestEarthquake.properties.place,
    time: moment(latestEarthquake.properties.time).format('YYYY-MM-DD HH:mm:ss')
  };
}

// Function to publish data to different MQTT topics
function publishData(data) {
    if (client.connected) {
      // Publish magnitude to a specific topic
      client.publish('student/CASA0019/G4/magnitude', JSON.stringify(data.magnitude));
  
      // Publish location to a specific topic
      client.publish('student/CASA0019/G4/location', JSON.stringify(data.location));
  
      // Publish time to a specific topic
      client.publish('student/CASA0019/G4/time', JSON.stringify(data.time));
    }
  }

client.on('connect', () => {
  console.log('Connected to MQTT Broker');
  setInterval(async () => {
    const apiData = await fetchData();
    const latestEarthquakeData = getLatestEarthquakeData(apiData);
    if (latestEarthquakeData) {
      publishData(latestEarthquakeData);
    }
  }, 10000); // Fetch and publish data every 10 seconds
});
