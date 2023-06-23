#pragma once

/**
 * @brief Structure for storing GPS parameters.
 */
typedef struct
{
    bool is_valid;
    float utc_time;
    float latitude;
    float longitude;
    uint8_t fix_quality;
    uint8_t number_of_satelities;
    float hdop;
    float altitude;
    char altitude_units;
    float undulation;
    char undulation_units;
    uint8_t age;
    char station_id[4];
} ESP_GPS_Data_t;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Parses GPS data from a packet.
 *
 * @param packet The packet containing GPS data.
 * @return The parsed GPS parameters.
 */
 ESP_GPS_Data_t esp_parse_gps_data(char * packet);

#ifdef __cplusplus
}
#endif