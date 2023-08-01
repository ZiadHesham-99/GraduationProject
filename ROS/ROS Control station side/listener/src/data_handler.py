
from optparse import Values


class Data_Handler:
    def String_parser(string):
        delimiter = '@'
        string = str(string)
        values = string.split(delimiter)
        print(values)

        #!SEND@MPU@G@-128@-091@-075@A@+0995@+0874@+0410@CO@+45%@!
        iterator = 0
        MQ7 = 0
        Acc_x = 0
        Acc_z = 0
        Acc_y = 0
        Gyroscope_x =0
        Gyroscope_y = 0
        Gyroscope_z =0
        ENC_DIR_R=0
        ENC_DIR_L=0
        ENC_VAL_L=0
        ENC_VAL_R=0


        for iterator,word in enumerate(values):
            if values[iterator] == '!!SEND':
                iterator+=1
                if values[iterator] == 'MPU':
                    iterator+=1
                    if values[iterator] == 'G':
                        Gyroscope_x = int(values[iterator+1])
                        Gyroscope_y = int(values[iterator+2])
                        Gyroscope_z = int(values[iterator+3])
                        iterator+=4
                    if values[iterator] == 'A':
                        Acc_x = int(values[iterator+1])/1000
                        Acc_y = int(values[iterator+2])/1000
                        Acc_z = int(values[iterator+3])/1000
                        iterator = iterator + 3
                elif values[iterator] == 'CO':
                    MQ7 = int(values[iterator+1][1]+values[iterator+1][2])/100
                    iterator+=1
                elif values[iterator] == 'ENC':
                    iterator+=1
                    if values[iterator] == '_L':
                        ENC_DIR_L = values[iterator+1]
                        ENC_VAL_L = int(values[iterator+1]+values[iterator+2])
                    elif values[iterator] == '_R':
                        ENC_DIR_R = values[iterator+1]
                        ENC_VAL_R = int(values[iterator+1]+values[iterator+2])
                    iterator+=2
                elif values[iterator] == '!!':
                    break
                    #data = "!!SEND@MPU@G@-211@-091@-075@A@+9950@+8740@+8740@CO@+45%@!!"

        return MQ7,Gyroscope_x,Gyroscope_y,Gyroscope_z,Acc_x,Acc_y,Acc_z,ENC_DIR_L,ENC_VAL_L,ENC_DIR_R,ENC_VAL_R


# !!SEND@ENC_L@+XXX@ENC_R@+XXX@!!  --- 31 BYTE






    
		
