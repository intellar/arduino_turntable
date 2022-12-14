import serial,time
#Arduino table control
#Copyright 2022 intellar@intellar.ca
#Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

class Turntable:
    #cmd = input("Command (F10: forward steps, R10: reverse steps,  D10: delay in ms between steps, 1 to inf ) :")
    #self.turntable.write(bytes(cmd, 'utf-8'))

    def __init__(self, port="COM3", baudrate=115200) -> None:
        
        self.baudrate = baudrate
        self.port = port        
        self.turntable = serial.Serial(self.port, self.baudrate, timeout=.1)
        time.sleep(1)

    
    def setDelay(self, delay):
        cmd = 'D'+str(int(delay))
        cmdByte = bytes(cmd, 'utf-8')
        self.turntable.write(cmdByte)
        print(cmdByte)
        time.sleep(0.1)
        data = self.turntable.readline()
        print("Turntable received:"+str(data))
        time.sleep(0.1)

    def reverseTurn(self,steps):
        cmd = 'R'+str(int(steps))
        self.turntable.write(bytes(cmd, 'utf-8'))
        print(cmd)
        time.sleep(0.1)
        data = self.turntable.readline()
        print("Turntable received:"+str(data))
        time.sleep(0.1)

    def forwardTurn(self,steps):
        cmd = 'F'+str(int(steps))
        self.turntable.write(bytes(cmd, 'utf-8'))
        print(cmd)
        time.sleep(0.1)
        data = self.turntable.readline()
        print("Turntable received:"+str(data))
        time.sleep(0.1)

    def interativeCommand(self):
        cte = True
        while(cte):
            cmd = input("Command (F10: forward steps, R10: reverse steps,  D10: delay in ms between steps, 1 to inf , q to quit) :")
            if cmd=="q":
                cte = False
                return

            self.turntable.write(bytes(cmd, 'utf-8'))
            print(cmd)
            time.sleep(0.1)
            data = self.turntable.readline()
            print("Turntable received:"+str(data))
            time.sleep(0.1)


      



