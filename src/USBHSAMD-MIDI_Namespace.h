/*!
 *  @file       USBHSAMD-MIDI_Namespace.h
 *  Project     Arduino USBHSAMD-MIDI transport
 *  @brief      USBHSAMD-MIDI transport for the Arduino - Namespace declaration
 *  @author     Yuuichi Akagawa
 *  @date       24/3/2021
 *  @license    MIT - Copyright (c) 2021 Yuuichi Akagawa
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

#define USBHSAMDMIDI_NAMESPACE         uhlsamdMidi
#define BEGIN_USBHSAMDMIDI_NAMESPACE   namespace USBHSAMDMIDI_NAMESPACE {
#define END_USBHSAMDMIDI_NAMESPACE     }

#define USING_NAMESPACE_USBHSAMDMIDI   using namespace USBHSAMDMIDI_NAMESPACE;

BEGIN_USBHSAMDMIDI_NAMESPACE

END_USBHSAMDMIDI_NAMESPACE
