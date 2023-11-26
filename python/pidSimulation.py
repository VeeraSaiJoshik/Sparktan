import matplotlib.pyplot as plt
import numpy as np

def clampMotorSpeed(speed):
    if(speed > 200): return 200
    elif (speed < -200): return -200
    return speed
def robotRotationModel(currentVelocity):
    return 0.12 * currentVelocity
def simulationAlgorithm(marginOfError, angularError, kP, kI, kD):
    xData = []
    errorData = []
    throttleData = []
    time = 0
    derivative = 0
    integral = 0
    calculateIntegral = False
    error = angularError
    prevError = angularError
    throttleSpeed = 0
    passed = False
    while(time <= 60 * 500):
        if(calculateIntegral): integral += error
        derivative = error - prevError
        if(error <= marginOfError and error >= -1 * marginOfError):
            passed = True
            break
        throttleSpeed = int(kP * error + kI * integral + kD * derivative)
        calculateIntegral = ((throttleSpeed == clampMotorSpeed(throttleSpeed)) and ((throttleSpeed < 0 and error < 0) or (throttleSpeed > 0 and error > 0)))
        throttleSpeed = clampMotorSpeed(throttleSpeed)
        error = error - robotRotationModel(throttleSpeed)
        prevError = error
        #print("Error : " + str(error) + "  Time : " + str(time) + " integral : " + str(integral) )
        xData.append(time)
        errorData.append(error)
        throttleData.append(throttleSpeed)
        time = time + 20
    return time, errorData, throttleData, xData, error, passed
def getAverageTime(kP, kI, kD, marginOfError):
    average = 0
    for error in range(10, 360):
        time, _, _, _, error, _ = simulationAlgorithm(marginOfError, error, kP, kI, kD)
        print(error)
        average += time
    return average/350.0
def fitAndPlot(xData, yError, yThrottle):
    _, axis = plt.subplots(2, 1)
    axis[0].scatter(xData, yThrottle, label='raw Curve', color='red')
    axis[1].scatter(xData, yError, label='raw Curve', color='red')
    plt.show()

kP = 1
x = []
y = []
for i in range(1000) : 
    kP += 0.001
    x.append(kP)
    y.append(getAverageTime(kP, 0, 0, 1))
fitAndPlot(x, y, y)
"""print("simulation started")
time, yError, yThrotle, x, finalError, passed = simulationAlgorithm(0.1, 10, 1, 0.001, 0.0)
fitAndPlot(x, yError, yThrotle)
print("simulaiton finished : " + str(time))
print("final error : " + str(finalError))
"""