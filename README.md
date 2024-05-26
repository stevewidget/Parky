This is a github  repository for Parkinsons Gloves project. You can find more details at
https://www.b4x.com/android/forum/threads/help-requuest-for-parkinsons-glove-development.160991/

This is a community project. I shall be concentrating on the hardware, which currently consists of an ESP32-C3 driving a TLC5917 LED driver to drive 8 mini vibrator motors. The motors are rated at around 60mA, and the TLC 120mA. It is hoped that with its ability to vary the current thet a few of the features of a Haptic controller can also be implemented (such as acceleration, amplitude modulation etc) First prototype used a ULN2803, but volts drop to big to use on Lipo.
The other side of the project is to monitor the usage of the device with a mobile phone using B4X and BLE
