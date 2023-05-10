const int FSR_PIN = A0;  // Pin analog FSR terhubung ke pin A0 Arduino

void setup() {
  Serial.begin(9600);  // Inisialisasi komunikasi serial dengan kecepatan baud rate 9600
}

void loop() {
  // Membaca nilai tegangan analog dari FSR
  int sensorValue = analogRead(FSR_PIN);

  // Mengubah nilai tegangan menjadi nilai tekanan (dalam range 0-100)
  int pressure = map(sensorValue, 0, 1023, 0, 100);

  // Tampilkan nilai tekanan pada Serial Monitor
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println("%");

  delay(1000);  // Delay 1 detik antara pembacaan
}
