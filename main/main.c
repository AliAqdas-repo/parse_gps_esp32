#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "../include/parse_gps_data.h"


int app_main()
{
    static ESP_GPS_Data_t s_parsed_data ;
    printf("Hello World\n");
    while (1) {
        static char *msg = "$GPGGA,202530.00,5109.0262,N,11401.8407,W,5,40,0.5,1097.36,M,-17.00,M,18,TSTR*61";
        s_parsed_data = esp_parse_gps_data(msg);
        printf("Valid: %d\n" ,s_parsed_data.is_valid);
        printf("UTC Time: %f\n" ,s_parsed_data.utc_time);
        printf("Longitude: %f\n",s_parsed_data.longitude);
        printf("Latitude: %f\n" ,s_parsed_data.latitude);
        printf("Fix Quality: %d\n", s_parsed_data.fix_quality);
        printf("No. of Satelites: %d\n", s_parsed_data.number_of_satelities);
        printf("HDOP: %f\n", s_parsed_data.hdop);
        printf("Altitude: %f\n", s_parsed_data.altitude);
        printf("Altitude Units: %c\n", s_parsed_data.altitude_units);
        printf("Undulation: %f\n", s_parsed_data.undulation);
        printf("Undulation Units: %c\n", s_parsed_data.undulation_units);
        printf("Age: %d\n", s_parsed_data.age);
        printf("Station ID: %s\n", s_parsed_data.station_id);
    }
    return 0;
}
