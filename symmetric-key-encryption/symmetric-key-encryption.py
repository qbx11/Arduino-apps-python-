import random
import string
import serial
import time

ser = serial.Serial('COM5',19200,timeout=1)#add timeout

chars = " " + string.digits + string.ascii_letters
print(chars)
chars = list(chars)

key = "5L0Po6s4f1tvIaFl KrjbGCepZB9zNXTVOWgdJnh3RmAkEwHQcu2iUM8qS7YyxD"
key=list(key)
cipher_text=""

try:
    while True:
        user_input = input("Message to encode: ")

        if user_input:
            cipher_text = ""

            for letter in user_input:
                index = chars.index(letter)
                cipher_text += key[index]

            ser.write((cipher_text + "\r\n").encode('utf-8'))
            time.sleep(0.2)



        while ser.in_waiting > 0:
            data = ser.readline().decode('utf-8', errors='ignore').strip()
            if data:
                print(f"Arduino: {data}")

except KeyboardInterrupt:
    print("Terminated")


finally:
    ser.close()
    print("Serial port closed")


