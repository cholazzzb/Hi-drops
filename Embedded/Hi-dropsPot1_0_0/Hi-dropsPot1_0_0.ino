/**  Import Library   **/
#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>

/***** Global Variable *****/
#define FIREBASE_HOST "******"                          // database URL 
#define FIREBASE_AUTH "******"           // secret key
#define WIFI_SSID "sst"                     // Our WiFi SSID                                 
#define WIFI_PASSWORD "gak boleh"      // Our Wifi Password

int kodePot=2; // Change this later

void setup() {
/***** Inizialize pin *****/
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  
/***** Setup Internet and monitor *****/
  Serial.begin(9600);
  Serial.println("Hi!drops machine started \n\n"); 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);    //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

/** If not connected yet to WiFi **/
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase
  delay(1000);

}

void loop() {
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase
 
  // Setelah ada paket data dari arduino, barulah cek firebase
      if (Firebase.failed()) {
        delay(500);
        Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
        Serial.println(Firebase.error());
        Serial.println("Connection to firebase failed. Reconnecting...");
        delay(500);
      }

    // Cek kode status di database
    NyalaMati(cekKode(kodePot));

}

/**** Cek Kode didatabase ****/
String cekKode(int kodePot){
  String path = String(kodePot);
  String status = Firebase.getString(path + "/Status");
  Serial.println(status);
  return status;
}
/**
 * Nyalain waktu kalo state di Realtime Database nya nyala, matiin kalo mati
 * 
 * no return
 *  
 */
void NyalaMati(String Sstatus){
  if (Sstatus == "ON"){
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    digitalWrite(D5, HIGH);
    Serial.println("HIGH");
  }
  else {
    digitalWrite(D3, LOW);
    digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);
    Serial.println("LOW");
  }
  // Update data di database
   String path = "2/StatusLampu";
   Firebase.setString(path, Sstatus);  
}
