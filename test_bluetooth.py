import serial

ser = serial.Serial("COM4", 9600, timeout = 1) #Change your port name COM... and your baudrate

# def retrieveData():
#     ser.write(b'1')
#     data = ser.readline().decode('ascii')
#     return data

while(True):
    uInput = input("Retrieve data? ")
    if uInput == '1':
        ser.write(b'1')
    elif uInput == '2':
        ser.write(b'2')
    elif uInput == '3':
        ser.write(b'3')
    elif uInput == '4':
        ser.write(b'4')
    else: ser.write(b'6')