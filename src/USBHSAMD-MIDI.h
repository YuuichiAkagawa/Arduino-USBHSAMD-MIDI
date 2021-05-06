/*
 Copyright (c) 2020 lathoub

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */
/*
 *******************************************************************************
 * Original version: https://github.com/lathoub/Arduino-USBMIDI/blob/master/src/USB-MIDI.h
 *
 * Modified for the USB Host Library SAMD
 * copyright (c) 2021 Yuuichi Akagawa
 *******************************************************************************
 */
 

#pragma once

#include <MIDI.h>
#include <usbh_midi.h>


#include "USBHSAMD-MIDI_defs.h"
#include "USBHSAMD-MIDI_Namespace.h"

BEGIN_USBHSAMDMIDI_NAMESPACE
class usbhsamdMidiTransport : public USBH_MIDI
{
private:
    uint8_t mTxIndex;
    MidiType mTxStatus;
    usbMidiEventPacket_t mTxPacket;
    uint8_t mRxLength;
    uint8_t mRxIndex;
    usbMidiEventPacket_t mRxPacket;

    uint8_t cableNumber;

public:
    usbhsamdMidiTransport(USBHost *p, uint8_t cableNumber = 0) : USBH_MIDI(p)
    {
      this->cableNumber = cableNumber;
    };

    static const bool thruActivated = false;

    uint8_t SendData(usbMidiEventPacket_t &packet){
        if( !bPollEnable ) return 4;
        return USBH_MIDI::SendRawData(4, packet.buf);
    };

    uint8_t RecvData(usbMidiEventPacket_t &packet){
      uint8_t rc = USBH_MIDI::RecvData(packet.buf, true);
      if( rc == 0 ) {
        packet.p.header = 0;
      }
      return rc;
    };


    void begin()
    {
      mTxIndex = 0;
      mRxIndex = 0;
      mRxLength = 0;
    };

    bool beginTransmission(MidiType status)
    {
      mTxStatus = status;

      byte cin = 0;
      if (status < SystemExclusive) {
        // Non System messages
        cin = ((status & 0xF0) >> 4);
        mTxPacket.p.header = MAKEHEADER(cableNumber, cin);
      }
      else {
        // Only System messages
        cin = pgm_read_byte_near(Fsys2cin + (status & 0x0F));
        mTxPacket.p.header = MAKEHEADER(cableNumber, cin);
      }

      mTxPacket.p.byte1 = mTxPacket.p.byte2 = mTxPacket.p.byte3  = 0;
      mTxIndex = 0;

      return true;
    };

    void write(byte byte)
    {
      if (mTxStatus != MidiType::SystemExclusive) {
        mTxPacket.buf[mTxIndex+1] = byte;
      }
      else if (byte == MidiType::SystemExclusiveStart) {
        mTxPacket.p.header = MAKEHEADER(cableNumber, 0x04);
        mTxPacket.p.byte1 = byte;
      }
      else // SystemExclusiveEnd or SysEx data
      {
        if (byte == MidiType::SystemExclusiveEnd)
          mTxPacket.p.header = MAKEHEADER(cableNumber, (0x05 + mTxIndex));

        switch(mTxIndex){
          case 0:
            mTxPacket.p.byte1 = byte;
            mTxPacket.p.byte2 = mTxPacket.p.byte3 = 0x00;
            break;
          case 1:
            mTxPacket.p.byte2 = byte;
            mTxPacket.p.byte3 = 0x00;
            break;
          case 2:
            mTxPacket.p.byte3 = byte;
            if (byte != MidiType::SystemExclusiveEnd)
              SendData(mTxPacket);
            break;
          default:
            break;
        }
      }
      mTxIndex = (mTxIndex == 2) ? 0 : mTxIndex+1;
    };

    void endTransmission()
    {
      SendData(mTxPacket);
    };

    byte read()
    {
      auto byte = mRxPacket.buf[mRxIndex++];
      mRxLength--;
      return byte;
    };

    unsigned available()
    {
      // consume mRxBuffer first, before getting a new packet
      if (mRxLength > 0)
        return mRxLength;

      mRxIndex = 1;
      auto len = (size_t)RecvData(mRxPacket);
      if (mRxPacket.p.header != 0) {
        auto cn = (mRxPacket.p.header >> 4) & 0x0f;
        if (cn != cableNumber)
          return 0;
        mRxLength = len;
      }
      return mRxLength;
    };
};


END_USBHSAMDMIDI_NAMESPACE

#define USBHSAMDMIDI_CREATE_INSTANCE(USBH, CableNr, Name)  \
  USBHSAMDMIDI_NAMESPACE::usbhsamdMidiTransport __usbhsamd##Name(USBH, CableNr);\
  MIDI_NAMESPACE::MidiInterface<USBHSAMDMIDI_NAMESPACE::usbhsamdMidiTransport> Name((USBHSAMDMIDI_NAMESPACE::usbhsamdMidiTransport&)__usbhsamd##Name);

#define USBHSAMDMIDI_CREATE_DEFAULT_INSTANCE(USBH)  \
  USBHSAMDMIDI_CREATE_INSTANCE(USBH, 0, MIDI)
