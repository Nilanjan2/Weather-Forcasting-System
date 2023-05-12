#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <curl/curl.h>
#include "cJSON.h"

// Define constant API key
#define API_KEY "your api key"

// Function to convert temperature from Kelvin to Celsius
float kelvin_to_celsius(float temp) {
    return temp - 273.15;
}

int main() {
    // Declare variables
    float latitude, longitude;
    char complete_api_link[200], buffer[1024];
    int response_code;
    cJSON *json, *weather, *main, *wind, *clouds, *sys, *visibility;

    // Get user input for latitude and longitude
    printf("Enter the latitude of the desired location: ");
    scanf("%f", &latitude);
    printf("Enter the longitude of the desired location: ");
    scanf("%f", &longitude);

    // Build API URL with user input and API key
    sprintf(complete_api_link, "https://api.openweathermap.org/data/2.5/weather?lat=%.2f&lon=%.2f&appid=%s", latitude, longitude, API_KEY);

    // Initialize CURL object
    CURL *curl = curl_easy_init();
    if (curl) {
        // Set the API URL as the URL to fetch
        curl_easy_setopt(curl, CURLOPT_URL, complete_api_link);

        // Set the buffer to write the response into
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buffer);

        // Perform the request
        CURLcode res = curl_easy_perform(curl);

        // Get the HTTP response code
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

        // Check if the response code indicates an error
        if (res != CURLE_OK || response_code != 200) {
            printf("Error: Could not retrieve weather information.\n");
            curl_easy_cleanup(curl);
            return 1;
        }

        // Cleanup CURL object
        curl_easy_cleanup(curl);
    }

    // Parse the JSON response
    json = cJSON_Parse(buffer);
    if (!json) {
        printf("Error: Could not parse JSON.\n");
        return 1;
    }

    // Extract information from the JSON object
    weather = cJSON_GetArrayItem(json, 0);
    main = cJSON_GetObjectItem(json, "main");
    wind = cJSON_GetObjectItem(json, "wind");
    clouds = cJSON_GetObjectItem(json, "clouds");
    sys = cJSON_GetObjectItem(json, "sys");
    visibility = cJSON_GetObjectItem(json, "visibility");

    // Convert temperature values to Celsius
    float temp = kelvin_to_celsius(cJSON_GetObjectItem(main, "temp")->valuedouble);
    float feels_like = kelvin_to_celsius(cJSON_GetObjectItem(main, "feels_like")->valuedouble);
    float temp_min = kelvin_to_celsius(cJSON_GetObjectItem(main, "temp_min")->valuedouble);
    float temp_max = kelvin_to_celsius(cJSON_GetObjectItem(main, "temp_max")->valuedouble);

    // Extract other weather information
    char *weather_desc = cJSON_GetObjectItem(weather, "description")->valuestring;
    int humidity = cJSON_GetObjectItem(main, "humidity")->valueint;
    float wind_speed = cJSON_GetObjectItem(wind, "speed")->valuedouble;
    int pressure = cJSON_GetObjectItem(main, "pressure")->valueint;
    int visibility_value = visibility->valueint;
    int clouds_all = cJSON_GetObjectItem(clouds, "all")->valueint;
	int sunrise_time = cJSON_GetObjectItem(sys, "sunrise")->valueint;
	int sunset_time = cJSON_GetObjectItem(sys, "sunset")->valueint;
	char sunrise[30];
	char sunset[30];
// Convert Unix timestamp to readable time
	strftime(sunrise, 30, "%I:%M:%S %p", localtime(&sunrise_time));
	strftime(sunset, 30, "%I:%M:%S %p", localtime(&sunset_time));

// Print weather information
	printf("--------------------------------------------------------\n");
	printf("--------------------------------------------------------\n");
	printf("Current Temperature   : %.2f deg C\n", temp_city);
	printf("Feels Like            : %.2f deg C\n", feels_like);
	printf("Minimum Temperature   : %.2f deg C\n", min_temp);
	printf("Maximum Temperature   : %.2f deg C\n", max_temp);
	printf("Current Weather Desc  : %s\n", weather_desc);
	printf("Current Humidity      : %d%%\n", humidity);
	printf("Current Wind Speed    : %.2f kmph\n", wind_speed);
	printf("Current Pressure      : %d hPa\n", pressure);
	printf("Current Visibility    : %d m\n", visibility_value);
	printf("Current Cloudiness    : %d%%\n", clouds_all);
	printf("Sunrise Time          : %s\n", sunrise);
	printf("Sunset Time           : %s\n", sunset);

return 0;
}
