# ESP32-now-for-flsh-on-by-Broadcast
this code is example for broadcasting with ESP32 Cam module (now) to turn on flashlight which is embedded in ESP32 Cam module (pin no.4)
you can use different modules of esp32, but according to this code this will turn on the flsh led of esp32 cam module
# Note 
for this you require minimum of 2 esp32 cam module's 
if you're using different modules of esp32 then chage the pin configuration in the code and add one led light 
# uploading
upload the same code for both of the modules
# connections
pin no.4 of esp32 cam is for flsh led no need of connecting 
give the power to both modules
ESP32        |    Push button 🔳 
pin no. 12 ------> pin 1
GND--------------> pin 4

# layout of general push button 🔳
pin1  ____ |----------| _____ pin2
           |    O     | 
pin3 _____ |__________| ______ pin4
