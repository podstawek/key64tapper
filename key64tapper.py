#!/usr/bin/env python
# -*- coding: utf-8 -*-

import time
import serial
import serial.tools.list_ports
import argparse

parser = argparse.ArgumentParser(description='key64tapper, a C64 keyboard emulator.')

specifyDevices = parser.add_mutually_exclusive_group(required=True)
specifyDevices.add_argument('-l', '--list', action='store_true',
                            help='List available USB devices and exit. Use this option to find a device for the -d / --device option.')
specifyDevices.add_argument('-d', '--device', action='store', type=str, dest='usbDevice',
                            help='Specify an Arduino-like USB device to use.')

parser.add_argument('-s', action='store', type=str, dest='cmdstring', required=True, help='User-supplied string of keys to send.')

parserResults = parser.parse_args()

serialDevice = None

print parserResults.cmdstring

if parserResults.list:
    for p in serial.tools.list_ports.comports():
        print "Device: " + p.device + "; description: " + p.description
    exit()

elif parserResults.usbDevice:
    print "Using device: " + parserResults.usbDevice
    serialDevice = parserResults.usbDevice

arduino = serial.Serial(serialDevice, 9600, timeout=.1)
time.sleep(1)

rawKeys = {'DEL': '000000', '3': '000001', '5': '000010', '7': '000011', '9': '000100', '+': '000101', '£': '000110',
           '1': '000111', 'Return': '001000', 'W': '001001', 'R': '001010', 'Y': '001011', 'I': '001100',
           'P': '001101', '*': '001110', '<-': '001111', '⇄': '010000', 'A': '010001', 'D': '010010', 'G': '010011',
           'J': '010100', 'L': '010101', ';': '010110', 'CTRL': '010111', 'F7': '011000', '4': '011001', '6': '011010',
           '8': '011011', '0': '011100', '-': '011101', 'Home': '011110', '2': '011111', 'F1': '100000', 'Z': '100001',
           'C': '100010', 'B': '100011', 'M': '100100', '.': '100101', 'Right Shift': '100110', 'Space': '100111',
           'F3': '101000', 'S': '101001', 'F': '101010', 'H': '101011', 'K': '101100', ':': '101101', '=': '101110',
           'Commodore': '101111', 'F5': '110000', 'E': '110001', 'T': '110010', 'U': '110011', 'O': '110100',
           '@': '110101', '↑': '110110', 'Q': '110111', '⇅': '111000', 'Left Shift': '111001', 'X': '111010',
           'V': '111011', 'N': '111100', ',': '111101', '/': '111110', 'Run/Stop': '111111'}

# Now that we have the connection open, write to it

arduino.write(','.join(list('111111')) + '\n')
print rawKeys['X']
arduino.write(','.join(list(rawKeys['X'])) + '\n')
time.sleep(3)
print rawKeys['U']
arduino.write(','.join(list(rawKeys['U'])) + '\n')


while True:
    data = arduino.readline()
    if data:
        print data.rstrip('\n')  # strip out the new lines for now