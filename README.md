# Parse GPS Function
The repository contains a library developed for ESP32 to parse GPS data, based on NMEA-0183 standard. The function can currently parse **GPGGA** string from the packet and returns the data in a data structure that contains the following GPS Parameters.
1. UTC Time (HHMMSS.SS)
2. Latitude
3. Longitude
4. Number of Satelites
5. Fix Quality
6. Altitude
7. Altitude Units
8. Undulation
9. Undulation Units
10. Horizontal Dilution of Precision
11. Differential Age
12. Station ID
13. Validity (based on checksum)
