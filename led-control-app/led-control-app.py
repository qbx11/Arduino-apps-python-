import tkinter as tk
import serial

arduino = serial.Serial('COM5', 19200, timeout=1)

def center_window(window, width=300, height=150):
    screen_width = window.winfo_screenwidth()
    screen_height = window.winfo_screenheight()
    x = int((screen_width - width) / 2)
    y = int((screen_height - height) / 2)
    window.geometry(f"{width}x{height}+{x}+{y}")

# Funkcje do wysyłania danych
def led_on():
    arduino.write(b'1')

def led_off():
    arduino.write(b'0')

# Główne okno
win = tk.Tk()
win.title("LED CONTROL")
center_window(win, 300, 400)

# Konfiguracja siatki (2 kolumny, 1 rząd)
win.columnconfigure(0, weight=1)
win.columnconfigure(1, weight=1)
win.rowconfigure(0, weight=1)

# Przycisk ON
button_on = tk.Button(win, text="ON", command=led_on, width=10, height=2, font=("Arial", 12))
button_on.grid(row=0, column=0, padx=20, pady=20, sticky="e")

# Przycisk OFF
button_off = tk.Button(win, text="OFF", command=led_off, width=10, height=2, font=("Arial", 12))
button_off.grid(row=0, column=1, padx=20, pady=20, sticky="w")

win.mainloop()
