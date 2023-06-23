#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "driver/uart.h"
#include "esp_log.h"
#include "../include/parse_gps_data.h"



static const char *TAG = "example";


int app_main()
{
    gps_parameters parsed_data ;
    printf("Hello World\n");
    while (1) {
        static char *msg = "$GPGGA,202530.00,5109.0262,N,11401.8407,W,5,40,0.5,1097.36,M,-17.00,M,18,TSTR*61";
        parsed_data = parse_gps_data(msg);
        printf("Valid: %d\n" ,parsed_data.is_valid);
        printf("UTC Time: %f\n" ,parsed_data.utc_time);
        printf("Longitude: %f\n",parsed_data.longitude);
        printf("Latitude: %f\n" ,parsed_data.latitude);
        printf("Fix Quality: %f\n", parsed_data.fix_quality);
        printf("No. of Satelites: %f\n", parsed_data.number_of_satelities);
        printf("HDOP: %f\n", parsed_data.hdop);
        printf("Altitude: %f\n", parsed_data.altitude);
        printf("Altitude Units: %c\n", parsed_data.altitude_units);
        printf("Undulation: %f\n", parsed_data.undulation);
        printf("Undulation Units: %c\n", parsed_data.undulation_units);
        printf("Age: %f\n", parsed_data.age);
        printf("Station ID: %s\n", parsed_data.station_id);
    }
    return 0;
}
