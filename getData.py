#script python
import serial   
import time
import os   

arduino_port = "COM8" 
baud = 9600
ser=serial.Serial(arduino_port, baud)
time.sleep(2)
while True:
    data = ser.readline()
    print(data.decode('utf-8').rstrip())
    if data:
        humidity, temperature = data.split(b',')
        print(f"humedad: {humidity}%, temperatura: {temperature}%")
        time.sleep(1)
        #rstirp:elimmina espacios en blanco y saltos de linea
        #timeout: tiempo de espera para la lectura del puerto serial
        
