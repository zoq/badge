#/usr/bin/python

"""
@file pingpong.py
@author Marcus Edel
Implementation of the ping/pong routine.
"""

import usb # 1.0 not 0.4
import sys, time, urllib2, re

try:
    import tty, termios
except ImportError:
    # Probably Windows.
    try:
        import msvcrt
    except ImportError:
        # FIXME what to do on other platforms?
        # Just give up here.
        raise ImportError('getch not available')
    else:
        getch = msvcrt.getch
else:
    def getch():
        """getch() -> key character

        Read a single keypress from stdin and return the resulting character.
        Nothing is echoed to the console. This call will block if a keypress
        is not already available, but will not wait for Enter to be pressed.

        If the pressed key was a modifier key, nothing will be detected; if
        it were a special function key, it may return the first character of
        of an escape sequence, leaving additional characters in the buffer.
        """
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            ch = sys.stdin.read(1)
        except KeyboardInterrupt:
            sys.exit(0)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch

sys.path.append("..")
from arduino.usbdevice import ArduinoUsbDevice

if __name__ == "__main__":
    try:
        theDevice = ArduinoUsbDevice(idVendor=0x16c0, idProduct=0x05df)

        print "Found: 0x%04x 0x%04x %s %s" % (theDevice.idVendor,
                                              theDevice.idProduct,
                                              theDevice.productName,
                                              theDevice.manufacturer)
    except:
        print("Couldn't find device.")
        sys.exit(0)

    # Switch mode (PlayPingPong).
    theDevice.write(ord('p'))
    time.sleep(0.1)

    while True:
        key = getch()

        if ord(key) == 3:
            sys.exit(0)
        elif key == 'a':
            theDevice.write(ord('a'))
        elif key == 'd':
            theDevice.write(ord('d'))
        elif key == 'j':
            theDevice.write(ord('j'))
        elif key == 'l':
            theDevice.write(ord('l'))
