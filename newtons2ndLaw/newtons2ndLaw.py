from __future__ import division
from visual import *
import serial, sys, time

def getData():
    ser.write(chr(1))
    line = ser.readline()
    #print(line)
    data = line.split()
    LR = int(data[0])
    UD = int(data[1])
    #print(str(LR)+"\t"+str(UD))
    return [LR,UD]
    

port = '/dev/cu.usbmodem1421'

#start the serial port
ser = serial.Serial(port, 9600, timeout=2)

# The following line is necessary to give the arduino time to start
# accepting stuff.

time.sleep(2)

scene.width=700
scene.height=700

t=0
dt=0.01

L=1
W=0.01
scale=1
arrowScale=0.2

scene.range=L

#track=box(pos=vector(0,0,-2*W), width=W, length=L, height=L, color=color.green)
ball=sphere(pos=vector(0,0,0), radius=L/20, color=color.red)
Farrow=arrow(pos=ball.pos, axis=vector(0,0,0), color=color.yellow)

ball.v=vector(0,0,0)
ball.m=1
F=vector(0,0,0)

voltage=[]

while 1:
    rate(100)
    voltage=getData()
    F.x=scale*(voltage[0]-1023/2)/512
    F.y=scale*(voltage[1]-1023/2)/512
    Farrow.pos=ball.pos
    Farrow.axis=F*arrowScale

    ball.v = ball.v + F/ball.m*dt
    ball.pos = ball.pos + ball.v*dt

    if ball.pos.x > L:
        ball.pos.x=-L
    elif ball.pos.x<-L:
        ball.pos.x=L

    if ball.pos.y>L:
        ball.pos.y=-L
    elif ball.pos.y<-L:
        ball.pos.y=L
