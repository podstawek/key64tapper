#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
import serial
import serial.tools.list_ports
import argparse
import readchar
from keymaps import rawKeys, defaultMap

BAUD = 19200
serialDevice = None

parser = argparse.ArgumentParser(description='key64tapper, a C64 keyboard emulator.')
specifyDevices = parser.add_mutually_exclusive_group(required=True)
specifyDevices.add_argument('-l', '--list', action='store_true',
                            help='List available USB devices and exit. Use this option to find a device for the -d / --device option.')
specifyDevices.add_argument('-d', '--device', action='store', type=str, dest='usbDevice',
                            help='Specify an Arduino-like USB device to use.')
specifyDevices.add_argument('-D', '--dummy', action='store_true',
                            help='Dummy mode. Don\'t connect to a device, print all serial output to STDOUT instead.')
parser.add_argument('-r', action='store', type=str, dest='rawString', required=False, help='User-supplied string of keys to send.')
parser.add_argument('-i', '--interactive', action='store_true', help='Interactive mode. Whatever you type is passed on to Commodore.')
parser.add_argument('-u', '--to_uppercase', action='store_true', help='In interactive mode, changes typed-in lower case letters to uppercase.')
parserResults = parser.parse_args()

if parserResults.list:
    for p in serial.tools.list_ports.comports():
        print "Device: " + p.device + "; description: " + p.description
    exit()

elif parserResults.usbDevice:
    print "Using device: " + parserResults.usbDevice

    serialDevice = parserResults.usbDevice

if not parserResults.dummy:
    try:
        arduino = serial.Serial(serialDevice, BAUD, timeout=.1)
    except:
        print "Cannot open serial device, exiting."
        exit(1)
# Give serial interface time to settle down
time.sleep(1)

# Now that we have the connection open, write to it
if parserResults.rawString:
    for k in parserResults.rawString.split(' '):
        combined = ''
        if '+' in k:
            for l in k.split('+'):
                combined += ','.join(list(rawKeys[l]))
                combined += ',_,'
            combined = combined.rstrip(',_,')
        else:
            combined = ','.join(list(rawKeys[k]))

        if parserResults.dummy:
            print(combined)
        else:
            arduino.write(combined + '\n')
        time.sleep(.05)

elif parserResults.interactive:
    print("You can start typing now :)")

    while True:
        combined = ''
        c = readchar.readchar()
        print c
        print ord(c)

        if parserResults.to_uppercase:
            c = c.upper()

        if c in rawKeys:
            print "Found in raw keys."
            combined += ','.join(list(rawKeys[c]))
        elif ord(c) in defaultMap:
            print "Found in default map."
            if '+' in defaultMap[ord(c)]:
                for l in defaultMap[ord(c)].split('+'):
                    combined += ','.join(list(rawKeys[l]))
                    combined += ',_,'
                combined = combined.rstrip(',_,')
            else:
                combined = ','.join(list(rawKeys[defaultMap[ord(c)]]))
        if parserResults.dummy:
            print(combined)
        else:
            arduino.write(combined + '\n')


# This returns over serial port whatever is sent to Arduino -- for debugging
#
# while True:
#     data = arduino.readline()
#     if data:
#         print data.rstrip('\n')  # strip out the new lines for now

if not parserResults.dummy:
    arduino.close()