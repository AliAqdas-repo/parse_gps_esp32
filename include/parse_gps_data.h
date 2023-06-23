typedef struct
{
    int is_valid;
    float utc_time;
    float latitude;
    float longitude;
    float fix_quality;
    float number_of_satelities;
    float hdop;
    float altitude;
    char altitude_units;
    float undulation;
    char undulation_units;
    float age;
    char station_id[4];
} gps_parameters;

extern gps_parameters parse_gps_data(char * packet);