#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<../include/parse_gps_data.h>

#define MAX_PACKET_LENGTH 84

ESP_GPS_Data_t esp_parse_gps_data(char * packet)
{
    ESP_GPS_Data_t packet_parameters;
    short field_counter = 0;
    short packet_iterator = 0;
    short field_iterator = 0;
    short checksum = 0;
    bool checksum_flag = 0;
    char * field = (char*)malloc(MAX_PACKET_LENGTH);
    if (*packet != '$') {
        packet_parameters.is_valid = 0;
        return packet_parameters;
    }
    else {
        while(1) {
            packet_iterator++;
            if (field_iterator == 0) {
                    field = (char*)malloc(84);
            }
            if (*(packet + packet_iterator) != ',' && *(packet + packet_iterator) != '*'
                 && *(packet + packet_iterator) != 10 && *(packet + packet_iterator) != 13 /*CR AND LF*/) {
                if (!checksum_flag) {
                    checksum ^= *(packet + packet_iterator);  // checksum does not include $ or ,
                }
                *(field + field_iterator) = *(packet + packet_iterator);
                field_iterator++;
            }
            else {
                *(field + field_iterator) = 0;
                if (*(packet + packet_iterator) == '*') {
                    checksum_flag = 1;
                }
                switch (field_counter) {
                    case 0:
                        while (field != NULL) {
                            packet_parameters.is_valid = true;
                            break;
                        }
                        break;
                    case 1:
                        while (field != NULL) {
                            packet_parameters.utc_time = atof(field);
                            break;
                        }
                        break;
                    case 2: 
                        while (field != NULL) {
                            packet_parameters.latitude = atof(field);
                            break;
                        }
                        break;
                    case 3:
                        while (field != NULL) {
                            if (*field == 'S') {
                                packet_parameters.latitude = -packet_parameters.latitude;
                            }
                            break;
                        }
                        break;
                    case 4: 
                        while (field != NULL) {
                            packet_parameters.longitude = atof(field);
                            break;
                        }
                        break;
                    case 5:
                        while (field != NULL) {
                            if (*field == 'W') {
                                packet_parameters.longitude = -packet_parameters.longitude;
                            }               
                            break;
                        }
                        break;
                    case 6:
                        while (field != NULL) {
                            packet_parameters.fix_quality = (uint8_t)atoi(field);
                            break;
                        }
                        break;
                    case 7:
                        while (field != NULL) {
                            packet_parameters.number_of_satelities = (uint8_t)atoi(field);
                            break;
                        }
                        break;
                    case 8:
                        while (field != NULL) {
                            packet_parameters.hdop = atof(field);
                            break;
                        }
                        break;
                    case 9:
                        while (field != NULL) {
                            packet_parameters.altitude = atof(field);
                            break;
                        }
                        break;
                    case 10:
                        while (field != NULL) {
                                packet_parameters.altitude_units = *field;
                            break;
                        }
                        break;
                    case 11:
                        while (field != NULL) {
                            packet_parameters.undulation = atof(field);
                            break;
                        }
                        break;
                    case 12:
                        while (field != NULL) {
                            packet_parameters.undulation_units = *field;
                            break;
                        }
                        break;
                    case 13:
                        while (field != NULL) {
                            packet_parameters.age = (uint8_t)atoi(field);
                            break;
                        }
                        break;
                    case 14:
                        while (field != NULL) {
                            strncpy(packet_parameters.station_id,field,4); 
                            break;
                        }
                        break;
                    case 15:
                        while (field != NULL) {
                                if (checksum != strtol(field,NULL,16))
                                packet_parameters.is_valid = false;
//                                ESP_LOGI(TAG,"%s\n",field);
                                break;
                        }
                        break;
                }
                if (field_counter == 15) {
                    free(field);
                    return packet_parameters;
                }
                field_counter++;
                field_iterator = 0;
                free(field);
            }
        }
    }
}


