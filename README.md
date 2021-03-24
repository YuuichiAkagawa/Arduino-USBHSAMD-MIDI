# Arduino USB Host Library SAMD MIDI Transport
Pre-release of USB Host Library SAMD MIDI transport layer for the [FortySevenEffects Arduino MIDI Library](https://github.com/FortySevenEffects/arduino_midi_library) and uses the underlying [USB Host Library SAMD](https://github.com/gdsports/USB_Host_Library_SAMD).
This library is based on the [Arduino-USBMIDI](https://github.com/lathoub/Arduino-USBMIDI).

__This libraries is EXTREMELY ALPHA!__

## Installation
copy it in "libraries" directory.

## Usage
### Basic / Default
```cpp
#include <USBHSAMD-MIDI.h>
USBHost UsbH;
...
USBHSAMDMIDI_CREATE_DEFAULT_INSTANCE(&UsbH);
...
void setup()
{
   MIDI.begin();
...
void loop()
{
   UsbH.Task();
   MIDI.read();
```
will create a instance named `MIDI` (transport instance named `__usbhsamdMIDI`) and is by default connected to cable number 0 - and listens to incoming MIDI on channel 1.

### Modified
```cpp
#include <USBHSAMD-MIDI.h>
...
USBHSAMDMIDI_CREATE_INSTANCE(&UsbH, 4, MIDI);
```
will create a instance named `MIDI` (transport instance named `__usbhsamdMIDI`) and is connected to cable number 4.

### Advanced
```cpp
#include <USBHSAMD-MIDI.h>
...
USBHSAMDMIDI_NAMESPACE::usbhsamdMidiTransport usbhsamdMIDI2(&Usb, 5);
MIDI_NAMESPACE::MidiInterface<USBHSAMDMIDI_NAMESPACE::usbhsamdMidiTransport> MIDI2((UHS2MIDI_NAMESPACE::uhlsdMidiTransport&)usbhsamdMIDI2);
```
will create a instance named `usbhsamdMIDI2` (and underlaying MIDI object `MIDI2`) and is by default connected to cable number 5.

## Tested boards / modules
- Arduino M0 Pro



## Other Transport protocols:
The libraries below  the same calling mechanism (API), making it easy to interchange the transport layer.
- [Arduino USB-MIDI  Transport](https://github.com/lathoub/USB-MIDI)
- [Arduino AppleMIDI Transport](https://github.com/lathoub/Arduino-AppleMIDI-Library)
- [Arduino ipMIDI  Transport](https://github.com/lathoub/Arduino-ipMIDI)
- [Arduino BLE-MIDI  Transport](https://github.com/lathoub/Arduino-BLE-MIDI)
- [Arduino USB Host Shield 2.0 MIDI Transport](https://github.com/YuuichiAkagawa/Arduino-UHS2MIDI)
