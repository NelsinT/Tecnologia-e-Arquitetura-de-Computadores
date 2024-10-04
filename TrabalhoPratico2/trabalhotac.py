import serial
arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1)
def read():
    data = arduino.readline()
    return data
while True:
    value = read().decode('utf-8').strip()
    if value != "":
        print(value) 
        with open('data.txt', 'a') as arquivo:
            arquivo.write(value + "\n")