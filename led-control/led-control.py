#LED changes state when 'SPACE' is pressed, debouncing is crucial!

import serial
import keyboard
import time

ser = serial.Serial('COM5',19200,timeout=1)#add timeout

print("PRESS 'SPACE' TO CHANGE LED STATE")

while True:
    try:
        if keyboard.is_pressed('SPACE'):
            ser.write(b'1') #send binary 1 to arduino
            time.sleep(0.1) #debounce

        elif keyboard.is_pressed('esc'):
            print("zamykanie programu")
            break

    except KeyboardInterrupt:
        break

ser.close()

