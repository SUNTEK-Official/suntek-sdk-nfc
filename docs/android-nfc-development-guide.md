# SUNTEK Android NFC Development Guide

The library 'libcomPro.so' should be added to your jniLibs folder, if this folder is not exist, create it.

The package file lc.jar and jRF.jar which located in libs shall be added to your app folder.

---

# How to Test the Android NFC Demo

Open the App, and the interface will be as shown above;

This demo program supports readers and writers for both USB interfaces and serial ports (UART). If connecting to a USB interface, select USB; if connecting to a serial port, select SerialPort. Then, edit and set the corresponding Device Path and Baud parameters according to the actual serial port of the connected mainboard;

Below are explanations for each item on the test list:

- M1
Test commonly used M1 (Mifare 1K / S50 / S70) cards, including reading card numbers and conducting read-write tests

- Ultralight
Test the reading and writing of Ultralight tag cards

- CTL_CPU
Test the resetting of non-contact CPU cards and the execution of sample instructions

- FM1208
Test an application example of a commonly used contactless CPU card, FM1208 from Fudan Microelectronics

- ICODE
Test the reading and writing of the commonly used card type ICODE for the ISO15693 protocol

- CT_CPU
Test the reset of contact CPU (ISO7816 protocol) cards and the execution of example instructions

About the test button

- Test
Manually initiate a test for the specified test item

- AutoTest
Continuously and automatically execute tests for specified projects in a loop. After starting, you can also stop the test by clicking this button

- Clean
Clear the text prompt of the test results located below in real time

Length: 38mm, Width: 30.5mm, Interval: 2mm
