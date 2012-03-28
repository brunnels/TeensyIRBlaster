#include <IRremote.h>
#include <avr/pgmspace.h>
#include "keyconfigs.h"
#define FNV_PRIME_32 16777619
#define FNV_BASIS_32 2166136261
#define GLOBAL_RECEIVE_DELAY 25

#define KEY_CONFIG_COUNT 38
PROGMEM const char *key_config_table[KEY_CONFIG_COUNT] = {
  key_config_0,
  key_config_1,
  key_config_2,
  key_config_3,
  key_config_4,
  key_config_5,
  key_config_6,
  key_config_7,
  key_config_8,
  key_config_9,
  key_config_10,
  key_config_11,
  key_config_12,
  key_config_13,
  key_config_14,
  key_config_15,
  key_config_16,
  key_config_17,
  key_config_18,
  key_config_19,
  key_config_20,
  key_config_21,
  key_config_22,
  key_config_23,
  key_config_24,
  key_config_25,
  key_config_26,
  key_config_27,
  key_config_28,
  key_config_29,
  key_config_30,
  key_config_31,
  key_config_32,
  key_config_33,
  key_config_34,
  key_config_35,
  key_config_36,
  key_config_37,
//  key_config_38,
//  key_config_39,
//  key_config_40,
//  key_config_41,
//  key_config_42,
//  key_config_43,
//  key_config_44,
//  key_config_45,
//  key_config_46,
};

extern volatile uint8_t usb_configuration; //  0 when the USB is not configured by the host, and 1 when it is
unsigned int REPEAT_DELAY = 175; // best if evenly divisible by 25
unsigned int CYCLE_COUNTER = 6000;
String oldIrCode = "";
unsigned int offRepeatCount = 0;

const int RECV_PIN = 14;
const int PC_POWER_SWITCH_PIN = 9;
IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;

void setup() {
//  Serial.begin(9600);

  // power switch pin setup
  pinMode(PC_POWER_SWITCH_PIN, OUTPUT);
  digitalWrite(PC_POWER_SWITCH_PIN, LOW);

  // enable IR receive
  irrecv.enableIRIn();
  
  //blinks the onboard LED on IR receive
  irrecv.blink13(true);
}

void lookupIRConfig(String receivedCode, String &irCode, unsigned int &keyboardKeyConstantValue, boolean &repeat,
  String &modifierKeyName, unsigned int &modifierKeyValue, String &remoteButtonName);

/**
* Loops through the keyConfig strings to match the received IR code and sets the config variables
* when it finds a match
*/
void lookupIRConfig(String receivedCode, String &irCode, unsigned int &keyboardKeyConstantValue, boolean &repeat,
  String &modifierKeyName, unsigned int &modifierKeyValue, String &remoteButtonName) {
  char stringBuffer[100];

  // loop through our IR code config array to get the settings for the receiver IR code
  for (int i = 0; i < KEY_CONFIG_COUNT; i++) {
    int counter = 0;
    char *str;
    char *p;
    strcpy_P(stringBuffer, (char*)pgm_read_word(&(key_config_table[i])));

    // tokenize the comma delimited config array line
    for( str = strtok_r(stringBuffer, ",", &p); str; str = strtok_r(NULL, ",", &p)) {
      // trim off the whitespace added for readability
      String configPart = String(str).trim();

      // check if the received IR code matches the code in our config line
      if(configPart.equals(receivedCode) || counter > 0 ) {

        // we have a match so set our variables to the config line values
        switch (counter) {
          // IR Code
          case 0:
            irCode = configPart;
            break;

          // Keyboard Key Constant Value
          case 1:
            keyboardKeyConstantValue = configPart.toInt();
            break;

          // Repeat
          case 2:
            repeat = (configPart.equalsIgnoreCase("Yes")) ? true : false;
            break;

          // Modifier Key Value
          case 3:
            // if the modifier key is No then clear the value
            if(configPart.equalsIgnoreCase("No")) {
              modifierKeyValue = 0;
              break;
            }
            else {
              modifierKeyName = configPart;
              if(configPart.equalsIgnoreCase("Ctrl")) {
                modifierKeyValue = MODIFIERKEY_CTRL;
                break;
              }
              if(configPart.equalsIgnoreCase("Shft")) {
                modifierKeyValue = MODIFIERKEY_SHIFT;
                break;
              }
              if(configPart.equalsIgnoreCase("Alt")) {
                modifierKeyValue = MODIFIERKEY_ALT;
                break;
              }
            }
            break;

          // Remote Button Name
          case 4:
            remoteButtonName = configPart;
            break;
        }
        counter++;
      }
      else {
        // go on to the next line in the config
        break;
      }
    }
    // stop looping, we have a match
    if(irCode != "") return;
  }
}

/**
 * Compare two tick values, returning 0 if newval is shorter,
 * 1 if newval is equal, and 2 if newval is longer
 * Use a tolerance of 20%
 */
int compare(unsigned int oldval, unsigned int newval) {
  if (newval < oldval * .8) {
    return 0;
  }
  else if (oldval < newval * .8) {
    return 2;
  }
  else {
    return 1;
  }
}

/**
 * Returns the decoded IR code for supported IR protocls or 
 * converts the raw code values into a 32-bit hash code.
 * Hopefully the 32-bit hash code will be unique for each button.
 */
unsigned long decodeHash(decode_results *results) {
  unsigned long hash;
  int codeType = results->decode_type;

  if (codeType == UNKNOWN) {
    hash = FNV_BASIS_32;
    for (int i = 1; i+2 < results->rawlen; i++) {
      int value =  compare(results->rawbuf[i], results->rawbuf[i+2]);
      // Add value into the hash
      hash = (hash * FNV_PRIME_32) ^ value;
    }
  }
  else {
    if (codeType == NEC) {
      // Don't record a NEC repeat value as that's useless.
      if (results->value == REPEAT) {
        return NULL;
      }
    }
    hash = results->value;
  }

//  if (codeType == UNKNOWN) {
//    Serial.print("Received UNKNOWN: ");
//  }
//  else if (codeType == NEC) {
//      Serial.print("Received NEC ");
//  }
//  else if (codeType == SONY) {
//      Serial.print("Received SONY ");
//  }
//  else if (codeType == RC5) {
//      Serial.print("Received RC5 ");
//  }
//  else if (codeType == RC6) {
//      Serial.print("Received RC6: ");
//  }
//  
//  if(codeType != UNKNOWN) {
//    Serial.print("(");
//    Serial.print(results->bits, DEC);
//    Serial.print(" bits) : ");    
//  }

  return hash;
}

/**
* Presses a specified keyboard key
*/
void sendKeyboardKey(unsigned int key, unsigned int modifier = 0) {
  Keyboard.set_key1(key);
  Keyboard.set_modifier(modifier);
  Keyboard.send_now();

  delay(5);

  Keyboard.set_key1(0);
  Keyboard.set_modifier(0);
  Keyboard.send_now();
}

/**
* Powers on the PC
*/
void powerOnPC() {        
  // Push PC power button only if the USB driver isn't loaded.  The will turn on the computer or wake it from sleep.
  if(usb_configuration == 0) {
    digitalWrite(PC_POWER_SWITCH_PIN, HIGH);
    delay(500);
    digitalWrite(PC_POWER_SWITCH_PIN, LOW);
  }
}

/**
* Sends the TV IR codes to turn it on
*/
void powerOnTV() {
  irsend.sendRaw(cmd_tv_power_on, sizeof(cmd_tv_power_on), 38);
  delay(50);
  irsend.sendRaw(cmd_tv_power_on, sizeof(cmd_tv_power_on), 38);
  delay(50);
  irsend.sendRaw(cmd_tv_power_on, sizeof(cmd_tv_power_on), 38);      
  
  //must always turn IR back on after sending
  irrecv.enableIRIn();  
}

/**
* Sends the Receiver IR codes to turn it on
*/
void powerOnReceiver() {
  irsend.sendNEC(0x4bb620df, 32);
  delay(50);
  irsend.sendNEC(0x4bb620df, 32);
  delay(50);
  irsend.sendNEC(0x4bb620df, 32);
  
  //must always turn IR back on after sending
  irrecv.enableIRIn();    
}

/**
* Sends the XBMC keyboard command to turn shutdown or sleep.
* @var boolean pushPowerButton will press the PC power button instead of
* sending the keyboard command if true
*/
void powerOffPC(boolean pushPowerButton = false) {
  // Push PC power button
  if(pushPowerButton) {
    digitalWrite(PC_POWER_SWITCH_PIN, HIGH);
    delay(500);
    digitalWrite(PC_POWER_SWITCH_PIN, LOW);
  }
  else
  {
    // Send XBMC Power OFF keyboard command      
    sendKeyboardKey(KEY_F11, 0);
  }
}

/**
* Sends the TV IR codes to turn it off
*/
void powerOffTV() {
  irsend.sendRaw(cmd_tv_power_off, sizeof(cmd_tv_power_off), 38);
  delay(50);
  irsend.sendRaw(cmd_tv_power_off, sizeof(cmd_tv_power_off), 38);
  delay(50);
  irsend.sendRaw(cmd_tv_power_off, sizeof(cmd_tv_power_off), 38);   
  
  //must always turn IR back on after sending
  irrecv.enableIRIn();  
}

/**
* Sends the Receiver IR codes to turn it off
*/
void powerOffReceiver() {
  irsend.sendNEC(0x4b36e21d, 32);
  delay(50);
  irsend.sendNEC(0x4b36e21d, 32);
  delay(50);
  irsend.sendNEC(0x4b36e21d, 32);
  
  //must always turn IR back on after sending
  irrecv.enableIRIn(); 
}

void loop() {
  if (irrecv.decode(&results)) {
    // get the value of the raw received string or the decoded value if using a supported protocol
    String receivedCode = String(decodeHash(&results), HEX);
//    Serial.println(receivedCode);

    // if we get back a null received code (like NEC repeat) don't try to process it
    if(receivedCode != "0") {
      String irCode = "";
      unsigned int keyboardKeyConstantValue = 0;
      boolean repeat = false;
      String modifierKeyName = "";
      unsigned int modifierKeyValue = 0;
      String remoteButtonName = "";
      
      // Don't try to get a config for ON or OFF
      if(receivedCode != "73fcaa47" && receivedCode != "42b17343") {  
        lookupIRConfig(receivedCode, irCode, keyboardKeyConstantValue, repeat, modifierKeyName, modifierKeyValue, remoteButtonName);
      }
      else if(receivedCode == "42b17343") {
        // OFF can repeat
        repeat = true;
      }
      
      if(receivedCode != oldIrCode) {
        // Received IR code matched a config
        if(irCode != "") {
//          Serial.print("Remote button ");
//          Serial.print(remoteButtonName);
//          Serial.println(" was pressed.");
        
          sendKeyboardKey(keyboardKeyConstantValue, modifierKeyValue);
        }
        else if(receivedCode == "73fcaa47") {
//          Serial.println("ON button was pushed");            
          powerOnPC();
          powerOnReceiver();
          powerOnTV();
        }
        else if(receivedCode == "42b17343") {
//          Serial.println("OFF button was pushed");
          powerOffPC();
          powerOffReceiver();
          powerOffTV();
          // reset the off repeate couunter
          offRepeatCount = 0;
        }
        
        REPEAT_DELAY = 175;
        delay(REPEAT_DELAY);
      }
      
      /**
      * if the recieved IR code is the same and they key config repeat is on, then reduce the delay by 25
      * until it is 25 less than the global receive delay threshold
      */
      else if(repeat && irCode == oldIrCode) {
        if(REPEAT_DELAY >= GLOBAL_RECEIVE_DELAY && REPEAT_DELAY >= 25) {
          REPEAT_DELAY = REPEAT_DELAY - 25;
        }
        
        // Received IR code matched a config
        if(irCode != "") {
//          Serial.print("Remote button ");
//          Serial.print(remoteButtonName);
//          Serial.println(" was pressed.");

          sendKeyboardKey(keyboardKeyConstantValue, modifierKeyValue);
        }
        else if(receivedCode == "42b17343") {
//          Serial.println("OFF button repeating");
          //increment the of repeat counter
          offRepeatCount++;
          if(offRepeatCount == 20) {
            // power off button repeated for a long time so push the pc power switch
            powerOffPC(true);
            // reset the off repeate couunter
            offRepeatCount = 0;
          }          
        }
        
        delay(REPEAT_DELAY);
      }  

      oldIrCode = receivedCode;
    }

    delay(GLOBAL_RECEIVE_DELAY);
    // reset the cycle counter if we received an IR signal
    CYCLE_COUNTER = 6000;

    irrecv.resume();
  }
  else
  {
    /**
    * clear the oldIrCode after 6000 cycles of not receiving any IR signals.
    * This lets us hit the same remote key multiple times but not hold it down to repeat
    * if it's repeat config is disabled.  You may need to play around with this value
    * depending on how fast your remote repeats.
    */
    if(CYCLE_COUNTER == 0) {
      CYCLE_COUNTER = 6000;
      oldIrCode = "";
    }
    CYCLE_COUNTER--;
  }
}
