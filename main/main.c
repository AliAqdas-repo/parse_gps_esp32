#include<stdio.h>
#include<stdlib.h>
#include "driver/uart.h"
#include "esp_log.h"


#define MAX_PACKET_LENGTH 84

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
    char* altitude_units;
    float undulation;
    char* undulation_units;
    float age;
    char* station_id;
} gps_parameters;

gps_parameters parse_gps_data(char * packet);
static const char *TAG = "example";


int app_main()
{
    gps_parameters parsed_data;
    
    while (1) {
        char *msg = "$GPGGA,202530.00,5109.0262,N,11401.8407,W,5,40,0.5,1097.36,M,-17.00,M,18,TSTR*61";
        parsed_data = parse_gps_data(msg);
        ESP_LOGI(TAG,"Goodbye!\n");
    }
    return 0;
}


gps_parameters parse_gps_data(char * packet)
{
    gps_parameters packet_parameters;
    int field_counter = 0;
    int packet_iterator = 0;
    int field_iterator = 0;
    long int checksum = 0;
    int checksum_flag = 0;
    char * field = (char *)malloc(MAX_PACKET_LENGTH);
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
            if(*(packet+packet_iterator) != ',' && *(packet+packet_iterator) != '*'
                 && *(packet+packet_iterator) != 10 && *(packet+packet_iterator) != 13 /*CR AND LF*/) {
                if (!checksum_flag){
                    checksum ^= *(packet+packet_iterator);  // Checksum does not include $ or ,
                }
                *(field+field_iterator) = *(packet+packet_iterator);
                field_iterator++;

            }
            else {
                *(field+field_iterator) = 0;
                if (*(packet+packet_iterator) == '*'){
                    checksum_flag = 1;
                }
                switch (field_counter)
                {
                    case 0:
                        while (field != NULL) {
                            packet_parameters.is_valid = 1;
                            ESP_LOGI(TAG,"%s\n",field);
                            break;
                        }
                        break;
                    case 1:
                        while (field != NULL) {
                            packet_parameters.utc_time = atof(field);
                            ESP_LOGI(TAG,"%s\n",field);
                            break;
                        }
                        break;
                    case 2: 
                        while (field != NULL) {
                            packet_parameters.latitude = atof(field);
                            ESP_LOGI(TAG,"%s\n",field);
                            break;
                        }
                        break;
                    case 3:
                        while (field != NULL) {
                            if (*field == 'S') {
                                packet_parameters.latitude = -packet_parameters.latitude;
                                ESP_LOGI(TAG,"%s\n",field);
                            }
                                break;
                        }
                        break;
                    case 4: 
                        while (field != NULL) {
                            packet_parameters.longitude = atof(field);
                            ESP_LOGI(TAG,"%s\n",field);
                            break;
                        }
                        break;
                    case 5:
                        while (field != NULL) {
                            if (*field == 'W') {
                                packet_parameters.longitude = -packet_parameters.longitude;
                                ESP_LOGI(TAG,"%s\n",field);
                            }               
                            break;
                        }
                        break;
                    case 6:
                        while (field != NULL) {
                                packet_parameters.fix_quality = atof(field);
                                ESP_LOGI(TAG,"%s\n",field);
                                break;
                        }
                        break;
                    case 7:
                        while (field != NULL) {
                                packet_parameters.number_of_satelities = atof(field);
                                ESP_LOGI(TAG,"%s\n",field);
                                break;
                        }
                        break;
                    case 8:
                        while (field != NULL) {
                                packet_parameters.hdop = atof(field);
                                ESP_LOGI(TAG,"%s\n",field);
                                break;
                        }
                        break;
                    case 9:
                        while (field != NULL) {
                                packet_parameters.altitude = atof(field);
                                ESP_LOGI(TAG,"%s\n",field);
                                break;
                        }
                        break;
                    case 10:
                        while (field != NULL) {
                                packet_parameters.altitude_units = field;
                                ESP_LOGI(TAG,"%s\n",field);
                                break;
                        }
                        break;
                    case 11:
                        while (field != NULL) {
                                packet_parameters.undulation = atof(field);
                                ESP_LOGI(TAG,"%s\n",field);
                                break;
                        }
                        break;
                    case 12:
                        while (field != NULL) {
                                packet_parameters.undulation_units = field;
                                ESP_LOGI(TAG,"%s\n",field);
                                break;
                        }
                        break;
                    case 13:
                        while (field != NULL) {
                                packet_parameters.age = atof(field);
                                ESP_LOGI(TAG,"%s\n",field);
                                break;
                        }
                        break;
                    case 14:
                        while (field != NULL) {
                                packet_parameters.station_id = field;
                                ESP_LOGI(TAG,"%s\n",field);
                                break;
                        }
                        break;
                    case 15:
                        while (field != NULL) {
                                if (checksum != strtol(field,NULL,16))
                                packet_parameters.is_valid = 0;
                                ESP_LOGI(TAG,"%s\n",field);
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


