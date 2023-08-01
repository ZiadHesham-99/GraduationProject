
import time
import pyi2c

class I2C:
    def __init__ (self):
        bus = 1
        slave_address = 0x70
        self.I2C_device = pyi2c.I2C(bus)


    def recieve_sensors_data (self,data_size):
        sensors_frame = self.I2C_device.read(slave_address,data_size)
        return sensors_frame

    def send_movement_data (self,data):
        self.I2C_device.write(slave_address,data)









