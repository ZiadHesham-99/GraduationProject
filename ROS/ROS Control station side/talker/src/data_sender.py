from optparse import Values

class Data_Prep:
    @staticmethod
    def movement_data_extractor(data):
        pwm_r = data[0]
        pwm_l = data[1]
        dir_r = data[2]
        dir_l = data[3]
        frame = Data_Prep.movement_data_prepare(pwm_r, dir_r, pwm_l, dir_l)
        return frame

    @staticmethod
    def movement_data_prepare(pwm_right, dir_right, pwm_left, dir_left):
        movement_data = '!!REC@M_R@' + str(dir_right) + str(pwm_right) + '@M_L' + str(dir_left) + str(pwm_left) + '!!'
        return movement_data
