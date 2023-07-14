import serial
import time

while(1):
    sr=serial.Serial("COM9",115200)
    st=str(sr.readline(),'utf-8')
    st = st.split()
    print("st ", st)
    sr.close()
    # sensor_val=str(''.join(st[:]))
    # print("sens", sensor_val)
    time.sleep(1)
    # if(sensor_val):
    #     sensor_data.append(str(sensor_val)+','+ok_date)
    # else:
    #     sensor_data.append(str(sensor_val)+','+ok_date)
