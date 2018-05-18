// This #include statement was automatically added by the Particle IDE.
#include "RelayShield.h"

//Create an instance of the RelayShield library, so we have something to talk to
RelayShield myRelays;

// Declare Local Variables
int door1_pin = D0;
int door2_pin = D1;
int door3_pin = D2;
String door1 = "1";
String door2 = "2";
String door3 = "3";

int door1_status = 99;
int door2_status = 99;
int door3_status = 99;

String sd1 = "UNKNOWN";
String sd2 = "UNKNOWN";
String sd3 = "UNKNOWN";

void setup() {
  Serial.begin(115200);
  myRelays.begin();

  // Ensure all Relays are OFF
  relayOff(door1);
  delay(250);
  relayOff(door2);
  delay(250);
  relayOff(door3);
  delay(250);

  // Set PinMode on Reed Switches
  pinMode(door1_pin, INPUT_PULLUP);
  pinMode(door2_pin, INPUT_PULLUP);
  pinMode(door3_pin, INPUT_PULLUP);

  // Define Cloud variables
  Particle.variable("DOOR_LEFT", sd1);
  Particle.variable("DOOR_MIDDLE", sd2);
  Particle.variable("DOOR_RIGHT", sd3);

  // Define Cloud Functions
  Particle.function("triggerDoor", triggerDoor);
  // Particle.function("checkDoorStatus", checkDoorStatus);
}

void loop() {
  // Check Status of Each Door
  int door1_current = checkDoorStatus(door1);
  int door2_current = checkDoorStatus(door2);
  int door3_current = checkDoorStatus(door3);

  // Look for Change in Status and Report if updated
  if (door1_current != door1_status) {
    // Convert Int to String for Cloud
    if (door1_current == 0) {
      sd1 = "CLOSED";
    }
    else if (door1_current == 1) {
      sd1 = "OPEN";
    }
    else {
      sd1 = "UNKNOWN";
    }

    Particle.publish("DOOR_LEFT", sd1, PRIVATE);
    door1_status = door1_current;
  }

  if (door2_current != door2_status) {
    // Convert Int to String for Cloud
    if (door2_current == 0) {
      sd2 = "CLOSED";
    }
    else if (door1_current == 1) {
      sd2 = "OPEN";
    }
    else {
      sd2 = "UNKNOWN";
    }

    Particle.publish("DOOR_MIDDLE", sd2, PRIVATE);
    door2_status = door2_current;
  }

  if (door3_current != door3_status) {
    // Convert Int to String for Cloud
    if (door3_current == 0) {
      sd3 = "CLOSED";
    }
    else if (door1_current == 1) {
      sd3 = "OPEN";
    }
    else {
      sd3 = "UNKNOWN";
    }

    Particle.publish("DOOR_RIGHT", sd3, PRIVATE);
    door3_status = door3_current;
  }

  // Wait for Next Execution
  delay(1000);
}

int checkDoorStatus(String doorNum) {
  // Check Status of Requested Door -- Return 0 = CLOSED, 1 = OPEN, 99 = UNKNOWN
  int doorStatus = 99;
  if (doorNum == door1) {
    doorStatus = digitalRead(door1_pin);
  }
  else if (doorNum == door2) {
    doorStatus = digitalRead(door2_pin);
  }
  else if (doorNum == door3) {
    doorStatus = digitalRead(door3_pin);
  }

  Serial.print("Door Status (");
  Serial.print(doorNum);
  Serial.print("): ");
  Serial.println(doorStatus);
  return doorStatus;
}

int triggerDoor(String doorNum) {
  if (doorNum == "1" || doorNum == "2" || doorNum == "3") {
    relayOn(doorNum);
    delay(500);
    relayOff(doorNum);

    Particle.publish("DOOR TRIGGERED", doorNum, PRIVATE);
    return 1;
  }
  else {
    Particle.publish("ERROR", "INVALID DOOR: " + doorNum, PRIVATE);
    return 0;
  }
}

int relayOn(String command){
  // Ritual incantation to convert String into Int
  char inputStr[64];
  command.toCharArray(inputStr,64);
  int i = atoi(inputStr);

  // Turn the desired relay on
  myRelays.on(i);

  // Respond
  return 1;
}

int relayOff(String command){
  // Ritual incantation to convert String into Int
  char inputStr[64];
  command.toCharArray(inputStr,64);
  int i = atoi(inputStr);

  // Turn the desired relay off
  myRelays.off(i);

  // Respond
  return 1;
}
