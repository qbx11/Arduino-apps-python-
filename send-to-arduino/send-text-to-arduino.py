import serial

ser = serial.Serial('COM5',19200,timeout=1)#add timeout


try:
    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8', errors='ignore').strip()
            if data:
                #fstring
                print(f"Arduino: {data}")

                if "Podaj litere" in data:
                    user_input = input()
                    if len(user_input) > 0:
                        ser.write((user_input[0] + "\n").encode('utf-8'))



except KeyboardInterrupt:
    print("Terminated")


finally:
    ser.close()
    print("Serial port closed")


