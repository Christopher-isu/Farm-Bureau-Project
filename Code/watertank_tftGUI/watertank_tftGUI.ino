#include <UTFT.h>
#include <URTouch.h>

// --- UART CONFIGURATION ---
// Using Serial1 (Pins 18 TX / 19 RX on Mega) for PIC communication
#define PIC_SERIAL Serial1 
const int BAUD_RATE = 9600;

// Abstract Packet Definitions
// We define a "Word" as a 16-bit unsigned integer (uint16_t)
const int PACKET_LENGTH = 8; 
uint16_t rxPacket[PACKET_LENGTH]; // Buffer for data received FROM PIC
uint16_t txPacket[PACKET_LENGTH]; // Buffer for data sent TO PIC

// Timing variables for non-blocking loop
unsigned long previousMillis = 0;
const long interval = 750; // Refresh rate (750ms)

// --- DISPLAY & TOUCH CONFIG ---
// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];

// Initialize UTFT
// Model: ITDB32S, Pins: 38, 39, 40, 41
UTFT myGLCD(ITDB32S, 38, 39, 40, 41); 

// Initialize URTouch
// Pins: 6, 5, 4, 3, 2
URTouch myTouch(6, 5, 4, 3, 2); 

// --- STATE VARIABLES ---
// These variables represent the state of the system as reported by the PIC.
// We also toggle these locally to indicate "User Request" until the next sync.
bool waterPumpOn = false; 
bool recirculationPumpOn = false; 

// Environmental variables (Updated only via UART)
int temperatureF = 0; 
bool heaterStatus = false; 

// Variables to keep track of previous states for efficient redrawing
bool prevWaterPumpOn = false;
bool prevRecirculationPumpOn = false;
int prevTemperatureF = 0;
bool prevHeaterStatus = false; 

void setup() {
  // 1. Init UI Hardware
  myGLCD.InitLCD();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  myGLCD.setFont(SmallFont);

  // 2. Init UART for PIC Communication
  PIC_SERIAL.begin(BAUD_RATE); 

  // 3. Draw Initial UI
  drawUI();
}

void drawUI() {
  myGLCD.clrScr();

  // Draw Reservoir (70% full mimic)
  myGLCD.setColor(0, 0, 128); 
  myGLCD.fillRect(50, 110, 100, 200);
  myGLCD.setColor(255, 255, 255); 
  myGLCD.drawRoundRect(50, 50, 100, 200);
  myGLCD.print("Reservoir", 50, 30); 
  
  // Draw Tank (30% full mimic)
  myGLCD.setColor(0, 128, 0); 
  myGLCD.fillRect(150, 170, 200, 200);
  myGLCD.setColor(255, 255, 255); 
  myGLCD.drawRoundRect(150, 50, 200, 200);
  myGLCD.print("Tank", 150, 30); 

  // Pump UI
  myGLCD.setColor(0, 255, 0); 
  myGLCD.setFont(BigFont); 
  myGLCD.print("Pump: OFF", 230, 120); 

  // Water Pump Button
  myGLCD.setColor(0, 0, 255); 
  myGLCD.fillRoundRect(230, 140, 250, 150); 
  myGLCD.setColor(255, 255, 255); 
  myGLCD.setFont(SmallFont); 
  myGLCD.print("TOG", 233, 142); 

  // Recirc UI
  myGLCD.setColor(0, 255, 0); 
  myGLCD.setFont(BigFont);
  myGLCD.print("Recirc: OFF", 230, 160); 

  // Recirc Pump Button
  myGLCD.setColor(0, 0, 255); 
  myGLCD.fillRoundRect(230, 180, 250, 190); 
  myGLCD.setColor(255, 255, 255); 
  myGLCD.setFont(SmallFont); // Reset to small font
  myGLCD.print("TOG", 233, 182); 

  // Temp & Heater UI
  myGLCD.setColor(255, 255, 0); 
  myGLCD.print("Temp: ", 240, 10); 
  myGLCD.printNumI(temperatureF, 290, 10); 
  myGLCD.print("*F", 320, 10); 

  myGLCD.setColor(0, 255, 0); 
  myGLCD.print("Heater: ", 240, 30); 
  myGLCD.setColor(255, 0, 0); 
  myGLCD.print("OFF", 290, 30); 
}

// --- FUNCTION: READ FROM PIC (SYSTEM FEEDBACK) ---
void checkIncomingSerial() {
  // We expect 8 words (16 bytes total)
  if (PIC_SERIAL.available() >= (PACKET_LENGTH * 2)) {
    
    // Read 8 integers from the buffer
    for (int i = 0; i < PACKET_LENGTH; i++) {
       byte high = PIC_SERIAL.read();
       byte low = PIC_SERIAL.read();
       rxPacket[i] = (high << 8) | low; 
    }

    // --- PARSE RX PACKET ---
    // Word 0: Temperature
    // Word 1: Heater Status (0 = OFF, 1 = ON)
    // Word 2: Water Pump ACTUAL Status (0 = OFF, 1 = ON)
    // Word 3: Recirc Pump ACTUAL Status (0 = OFF, 1 = ON)

    temperatureF = (int)rxPacket[0];
    heaterStatus = (rxPacket[1] == 1);
    
    // SYNC: We update our local variables to match what the PIC is actually doing.
    // If we requested ON, but PIC said NO (safety), this will flip it back to OFF.
    waterPumpOn = (rxPacket[2] == 1);
    recirculationPumpOn = (rxPacket[3] == 1);
    
    // Clear buffer of any junk to stay synced
    while(PIC_SERIAL.available()) PIC_SERIAL.read();
  }
}

// --- FUNCTION: WRITE TO PIC (USER REQUEST) ---
void sendStatusPacket() {
  // --- ASSEMBLE TX PACKET ---
  // Word 0: Water Pump REQUEST
  // Word 1: Recirculation Pump REQUEST
  // Word 2-7: Reserved/Placeholder
  
  txPacket[0] = waterPumpOn ? 1 : 0;
  txPacket[1] = recirculationPumpOn ? 1 : 0;
  // Fill remaining words with 0
  for(int j=2; j<PACKET_LENGTH; j++) txPacket[j] = 0;

  // Send 8 Integers as raw bytes (High byte first)
  for (int i = 0; i < PACKET_LENGTH; i++) {
    PIC_SERIAL.write(highByte(txPacket[i]));
    PIC_SERIAL.write(lowByte(txPacket[i]));
  }
}

void loop() {
  // --- 1. CONTINUOUS TOUCH MONITORING ---
  // We check this every single loop cycle for responsiveness
  if (myTouch.dataAvailable()) {
    myTouch.read();
    int x = myTouch.getX();
    int y = myTouch.getY();

    // Water Pump Toggle Button Hitbox
    if ((x >= 230 && x <= 250) && (y >= 140 && y <= 150)) {
      waterPumpOn = !waterPumpOn; // Toggle Request Flag
      delay(300); // Simple debounce for user interaction
    }

    // Recirc Pump Toggle Button Hitbox
    if ((x >= 230 && x <= 250) && (y >= 180 && y <= 190)) {
      recirculationPumpOn = !recirculationPumpOn; // Toggle Request Flag
      delay(300); // Simple debounce
    }
  }

  // --- 2. CONTINUOUS SERIAL LISTENING ---
  // Check for feedback packets from PIC every cycle
  checkIncomingSerial();

  // --- 3. TIMED UI UPDATE & TRANSMISSION ---
  // This executes every 750ms
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // A. Send User Request to PIC
    sendStatusPacket();

    // B. Refresh Screen Elements (Only if changed)
    
    // Update Water Pump UI
    if (waterPumpOn != prevWaterPumpOn) {
      if (waterPumpOn) {
        myGLCD.setColor(255, 0, 0); 
        myGLCD.print("Pump: ON", 230, 120);
      } else {
        myGLCD.setColor(0, 255, 0); 
        myGLCD.print("Pump: OFF", 230, 120);
      }
      prevWaterPumpOn = waterPumpOn;
    }

    // Update Recirc Pump UI
    if (recirculationPumpOn != prevRecirculationPumpOn) {
      if (recirculationPumpOn) {
        myGLCD.setColor(255, 0, 0); 
        myGLCD.print("Recirc: ON", 230, 160);
      } else {
        myGLCD.setColor(0, 255, 0); 
        myGLCD.print("Recirc: OFF", 230, 160);
      }
      prevRecirculationPumpOn = recirculationPumpOn;
    }

    // Update Temperature UI
    if (temperatureF != prevTemperatureF) {
      myGLCD.setColor(255, 255, 0); 
      myGLCD.setFont(SmallFont); 
      myGLCD.print("Temp: ", 240, 10); 
      myGLCD.printNumI(temperatureF, 290, 10); 
      myGLCD.print("*F", 320, 10); 
      prevTemperatureF = temperatureF;
    }

    // Update Heater Status UI
    if (heaterStatus != prevHeaterStatus) {
      myGLCD.setColor(0, 255, 0); 
      myGLCD.print("Heater: ", 240, 30); 
      if(heaterStatus) {
         myGLCD.setColor(255, 0, 0);
         myGLCD.print("ON ", 290, 30); 
      } else {
         myGLCD.setColor(255, 0, 0); 
         myGLCD.print("OFF", 290, 30); 
      }
      prevHeaterStatus = heaterStatus;
    }
  }
}