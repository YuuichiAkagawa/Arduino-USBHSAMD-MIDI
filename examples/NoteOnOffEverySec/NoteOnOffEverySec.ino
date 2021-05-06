#include <USBHSAMD-MIDI.h>
#include <usbhub.h>

USBHost UsbH;
USBHSAMDMIDI_CREATE_DEFAULT_INSTANCE(&UsbH);

unsigned long t1 = millis();

void handleNoteOn(byte inChannel, byte inNumber, byte inVelocity)
{
  Serial.print("NoteOn  ");
  Serial.print(inNumber);
  Serial.print("\tvelocity: ");
  Serial.println(inVelocity);
}

void handleNoteOff(byte inChannel, byte inNumber, byte inVelocity)
{
  Serial.print("NoteOff ");
  Serial.print(inNumber);
  Serial.print("\tvelocity: ");
  Serial.println(inVelocity);
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  MIDI.begin();
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);

  if (UsbH.Init() == -1) {
    while (1); //halt
  }//if (Usb.Init() == -1...
  delay( 200 );

  Serial.println("Arduino ready.");
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
void loop()
{
  UsbH.Task();
  MIDI.read();

  if ((millis() - t1) > 500)
  {
    t1 = millis();

    MIDI.sendNoteOn(27, 55, 1);
    MIDI.sendNoteOff(27, 55, 1);
  }
}
