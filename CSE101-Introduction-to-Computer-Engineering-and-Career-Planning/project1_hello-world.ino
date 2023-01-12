

void setup() {
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("CSE 101 HW-1 Yusuf Arslan_200104004112\n");
}


void loop() {
 

  Serial.print("Hello, my name is Yusuf Arslan.\n");
  delay (100);
  exit(0);
};
