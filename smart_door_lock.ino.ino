#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// LCD Pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Servo
Servo lockServo;

// Password
String password = "1234";
String inputPassword = "";

// Keypad Setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {A0, A1, A2, A3};
byte colPins[COLS] = {A4, A5, 6, 7};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {

  lcd.begin(16, 2);

  lockServo.attach(9);

  lockServo.write(0); // Locked position

  lcd.setCursor(0,0);
  lcd.print("Smart Door Lock");

  delay(2000);

  lcd.clear();
  lcd.print("Enter Password");
}

void loop() {

  char key = keypad.getKey();

  if (key) {

    // Display *
    if (key != '#') {
      inputPassword += key;

      lcd.setCursor(inputPassword.length()-1,1);
      lcd.print("*");
    }

    // Check Password
    if (key == '#') {

      lcd.clear();

      if (inputPassword == password) {

        lcd.print("Access Granted");

        lockServo.write(90); // Unlock

        delay(5000);

        lockServo.write(0); // Lock again

        lcd.clear();
        lcd.print("Door Locked");

        delay(2000);

      } else {

        lcd.print("Wrong Password");

        delay(2000);
      }

      // Reset
      inputPassword = "";

      lcd.clear();
      lcd.print("Enter Password");
    }
  }
}
