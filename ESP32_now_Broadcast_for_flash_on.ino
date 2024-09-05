/*
this code is example for broadcasting with ESP32 Cam module (now) to turn on flashlight which is embedded in ESP32 Cam module (pin no.4) 
you can use different modules of esp32, but according to this code this will turn on the flsh led of esp32 cam module
its for esp32 cam module
for this you require minimum of 2 esp32 cam module's
if you're using different modules of esp32 then chage the pin configuration in the code and add one led light
*/
#include <esp_now.h>
#include <WiFi.h>

#define BUTTON_PIN 12  // Button input pin
#define LED_PIN 4     // FLASH LED output pin

typedef struct {
  bool led_status;
} esp_now_data_t;

esp_now_data_t new_msg;
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  // Broadcast MAC address

// Updated OnDataRecv function signature
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len) {
  esp_now_data_t msg;
  memcpy(&msg, incomingData, sizeof(msg));
  
  // Set LED state based on received data
  digitalWrite(LED_PIN, msg.led_status ? HIGH : LOW);
  Serial.println(msg.led_status ? "LED ON" : "LED OFF");
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Message Sent" : "Send Failed");
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  
  // Initialize GPIO
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Initialize button pin
  pinMode(LED_PIN, OUTPUT);           // Initialize LED pin

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register the send callback
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
  
  // Register the receive callback with the correct function signature
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Setup complete.");
}

void loop() {
  bool button_state = digitalRead(BUTTON_PIN) == LOW;  // Read button state (LOW when pressed)
  
  new_msg.led_status = button_state;  // Set LED status based on button state
  
  // Send message
  if (esp_now_send(broadcastAddress, (uint8_t *)&new_msg, sizeof(new_msg)) != ESP_OK) {
    Serial.println("Failed to send message");
  } else {
    Serial.println(button_state ? "Button Pressed: LED ON" : "Button Released: LED OFF");
  }
  
  delay(100);  // Add a small delay to debounce the button
}
