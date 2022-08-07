import speech_recognition as sr
from pyfirmata import Arduino, util
import time

recording = sr.Recognizer()

board = Arduino('COM3')

it = util.Iterator(board)
it.start()

with sr.Microphone() as source:
    recording.adjust_for_ambient_noise(source)
    print("Please Say your name :")
    audio =  recording.listen(source)
    name = recording.recognize_google(audio)
    print("your name : ",name)


def voice_recog(dir):
    if dir == 1:
        direct = 'front'
    elif dir == 2:
        direct = 'behind'
    elif dir == 3:
        direct = 'right'
    elif dir == 4:
        direct = 'left'

    with sr.Microphone() as source:
        recording.adjust_for_ambient_noise(source)
        # print("Please Say something:")
        audio = recording.listen(source)

    try:
        s = recording.recognize_google(audio)
        if name in s:
            print("direction = ", direct)
    except Exception as e:
        print(e)

sampleWindow = 50
leftLedPin = 12
rightLedPin = 13
sensorA = 0
sensorB = 0
sensorC = 0
sensorD = 0

analog_input1 = board.get_pin('a:0:i')
analog_input2 = board.get_pin('a:1:i')
analog_input3 = board.get_pin('a:2:i')
analog_input4 = board.get_pin('a:3:i')

while True:
    startMillis = time.time()

    peakToPeakA = 0
    maxA = 0
    minA = 1024

    peakToPeakB = 0
    maxB = 0
    minB = 1024

    peakToPeakC = 0
    maxC = 0
    minC = 1024

    peakToPeakD = 0
    maxD = 0
    minD = 1024

    while (time.time() - startMillis < sampleWindow):
        time.sleep(0.5)
        sensorA = board.analog[0].read()
        time.sleep(0.5)
        sensorB = board.analog[1].read()
        time.sleep(0.5)
        sensorC = board.analog[2].read()
        time.sleep(0.5)
        sensorD = board.analog[3].read()
        time.sleep(0.5)

        if (sensorA < 1024):
            if (sensorA > maxA):
                maxA = sensorA
            elif (sensorA < minA):
                minA = sensorA

        if (sensorB < 1024):
            if (sensorB > maxB):
                maxB = sensorB
            elif (sensorB < minB):
                minB = sensorB

        if (sensorC < 1024):
            if (sensorC > maxC):
                maxC = sensorC
            elif (sensorC < minC):
                minC = sensorC

        if (sensorD < 1024):
            if (sensorD > maxD):
                maxD = sensorD
            elif (sensorD < minD):
                minD = sensorD

    peakToPeakA = maxA - minA
    voltA = (peakToPeakA * 5.0) / 1024

    peakToPeakB = maxB - minB
    voltB = (peakToPeakB * 5.0) / 1024

    peakToPeakC = maxC - minC
    voltC = (peakToPeakC * 5.0) / 1024

    peakToPeakD = maxD - minD
    voltD = (peakToPeakD * 5.0) / 1024

    if (voltA + voltB + voltC + voltD > 0.09):
        if (voltA > voltB and voltA > voltC and voltA > voltD):
            board.digital[leftLedPin]. write(0)
            board.digital[rightLedPin]. write(1)
            # digitalWrite(leftLedPin, LOW)
            # digitalWrite(rightLedPin, HIGH)
            # print("A  voltA ->", voltA, "  voltB -> ", voltB, "voltC -> ", voltC, "  voltD ->", voltD)
            voice_recog(1)

        elif (voltB > voltA and voltB > voltC and voltB > voltD):
            board.digital[leftLedPin]. write(1)
            board.digital[rightLedPin]. write(0)
            # digitalWrite(leftLedPin, HIGH)
            # digitalWrite(rightLedPin,   LOW)
            # print("B  voltA ->", voltA, "  voltB -> ", voltB, "voltC -> ", voltC, "  voltD ->", voltD)
            voice_recog(2)

        elif (voltC > voltA and voltC > voltB and voltC > voltD):
            # print("C  voltA ->", voltA, "  voltB -> ", voltB, "voltC -> ", voltC, "  voltD ->", voltD)
            voice_recog(3)

        else:
            # print("D  voltA ->", voltA, "  voltB -> ", voltB, "voltC -> ", voltC, "  voltD ->", voltD)
            voice_recog(4)
    time.sleep(0.2)
