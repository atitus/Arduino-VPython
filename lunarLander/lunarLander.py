from __future__ import division
from visual import *
import serial, sys, time

#Aaron Titus, Physics for Video Games
#
#Lunar Lander
#
#Use the up arrow key to fire the thruster.
#
#Try to land the spaceship as gently as possible.

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
scene.range=20

ground = box(pos=vector(0,-10.05,0), size=(40.0,1,1), color=color.white)
spaceship = box(pos=vector(-10,8,0), size=(2,5,2), color=color.yellow)
target=box(pos=vector(10,-10.05,0), size=(5.0,1,1), color=color.red)

spaceship.m = 1
spaceship.v = vector(0,0,0)
g=1/6*vector(0,-10,0)
Fthrust=vector(0,0,0)
F=vector(0,0,0)

dt = 0.01
t = 0

scale=5.0
FgravArrow = arrow(pos=spaceship.pos, axis=scale*spaceship.m*g, color=color.red)
FthrustArrow = arrow(pos=spaceship.pos, axis=Fthrust, color=color.cyan)

voltage=[]

while 1:
        rate(100)
        voltage=getData()
        F.x=scale*(voltage[0]-1023/2)/512
        F.y=scale*(voltage[1]-1023/2)/512
        Fthrust=vector(F.x,F.y)
        Fgrav=spaceship.m*g
        Fnet=Fgrav+Fthrust
        spaceship.v = spaceship.v + (Fnet/spaceship.m)*dt
        spaceship.pos = spaceship.pos + spaceship.v*dt
        if(spaceship.pos.y-spaceship.height/2<ground.pos.y+ground.height/2):
                print("spaceship has landed, v= ", mag(spaceship.v))
                break
        t = t+dt
        FgravArrow.pos=spaceship.pos
        FgravArrow.axis=scale*Fgrav
        FthrustArrow.pos=spaceship.pos
        FthrustArrow.axis=scale*Fthrust
