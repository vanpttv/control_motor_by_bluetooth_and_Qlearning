#!/usr/bin/python

import numpy as np
import random
import serial  # Serial imported for Serial communication
import time  # Required to use delay functions
SERIAL_PORT = 'COM4'
SERIAL_RATE = 9600
time.sleep(1)
# ArduinoSerial = serial.Serial("COM4", 9600, timeout = 1)


#setting
row = 6
column = 2
iteration = 100
targetsym = 9
trapsym = 1
playersym = 7
lrate = 0.2
discount = 0.9
epsilon = 1.0
minepsilon = 0.01
maxstep = 100
decay_epsilon = 0.005
# actchoice = ['Down', 'Up', 'Right', 'Left']
actchoice = ['MOVE_DOWN', 'MOVE_UP', 'MOVE_RIGHT', 'MOVE_LEFT']
#target
target = np.asarray([5,1]) #convert input (lists, tuples) to an array

trap = []
# make a board
trap.append([2,0])
trap.append([0,1])
trap.append([4,0])#[[7, 6], [7, 4], [9, 0], [8, 6]]
trap = np.asarray(trap)
	# [[7 6]
	# [7 4]
	# [9 0]
	# [8 6]]

def init_board(player):
	#make a board
	board = np.zeros((row, column)) #Return a new array of given shape and type, filled with zeros.

	#init board
	board[target[0], target[1]] = targetsym # target[0]=9, target[1]=6, gán targetsym=9 vào hàng 9 cột 6
	for j in range(len(trap)):		#len(trap)=4
		board[trap[j,0], trap[j,1]] = trapsym	#trapsym = 1
	board[player[0], player[1]] = playersym		#playersym = 7
	return board

def calcreward(posplayer1, posplayer2, postarget):
	jarak1 = np.absolute(posplayer1-postarget)
	jarak2 = np.absolute(posplayer2-postarget)

	trapped = False
	#check if trapped
	for i in range(len(trap)):	#len(trap)=4
		if np.array_equal(posplayer2, trap[i]):		#return True/False
			trapped = True
	if np.sum(jarak1-jarak2) > 0:
		reward = 1.
	else:
		reward = -1.
	if np.array_equal(posplayer2, target):
		reward = 100.
	elif trapped:
		reward = -100.
	return reward

def action(qtable, posplayer):
	global epsilon
	chance = random.uniform(0,1)
	if chance < epsilon:
		while True:
			choice = random.randrange(len(actchoice))
			if actchoice[choice] == 'MOVE_DOWN':
				cnt = posplayer[0]
				cnt += 1
				if cnt < row:
					posplayer[0] = cnt
					break
			elif actchoice[choice] == 'MOVE_UP':
				cnt = posplayer[0]
				cnt -= 1
				if cnt > 0:
					posplayer[0] = cnt
					break
			elif actchoice[choice] == 'MOVE_RIGHT':
				cnt = posplayer[1]
				cnt += 1
				if cnt < column:
					posplayer[1] = cnt
					break
			elif actchoice[choice] == 'MOVE_LEFT':
				cnt = posplayer[1]
				cnt -= 1
				if cnt > 0:
					posplayer[1] = cnt
					break
	else:
		choice = np.argmax(qtable[posplayer[0], posplayer[1]])
		if actchoice[choice] == 'MOVE_DOWN':
			cnt = posplayer[0]
			cnt += 1
			if cnt < row:
				posplayer[0] = cnt
		elif actchoice[choice] == 'MOVE_UP':
			cnt = posplayer[0]
			cnt -= 1
			if cnt > 0:
				posplayer[0] = cnt
		elif actchoice[choice] == 'MOVE_RIGHT':
			cnt = posplayer[1]
			cnt += 1
			if cnt < column:
				posplayer[1] = cnt
		elif actchoice[choice] == 'MOVE_LEFT':
			cnt = posplayer[1]
			cnt -= 1
			if cnt > 0:
				posplayer[1] = cnt
	#decaying epsilon
	epsilon -= decay_epsilon
	return choice, posplayer

def realaction(qtable, posplayer):
	choice = np.argmax(qtable[posplayer[0], posplayer[1]])
	if actchoice[choice] == 'MOVE_DOWN':
		cnt = posplayer[0]
		cnt += 1
		if cnt < row:
			posplayer[0] = cnt
	elif actchoice[choice] == 'MOVE_UP':
		cnt = posplayer[0]
		cnt -= 1
		if cnt > 0:
			posplayer[0] = cnt
	elif actchoice[choice] == 'MOVE_RIGHT':
		cnt = posplayer[1]
		cnt += 1
		if cnt < column:
			posplayer[1] = cnt
	elif actchoice[choice] == 'MOVE_LEFT':
		cnt = posplayer[1]
		cnt -= 1
		if cnt > 0:
			posplayer[1] = cnt
	return actchoice[choice], posplayer

############
#init board#
############
def get_robot_route(self, direction_rb):
    # """

    # """
    robot_route = [];

    direction = direction_rb
    optimal_route = self
    if optimal_route != None:
        for index, i in enumerate(optimal_route):
            if direction == 'DOWN':
                if i == "MOVE_LEFT":  # LEFT
                    robot_route.append("GO RIGHT")
                    robot_route.append("GO FORWARD")
                    direction = 'LEFT'
                if i == "MOVE_RIGHT":  # RIGHT
                    robot_route.append("GO LEFT")
                    robot_route.append("GO FORWARD")
                    direction = 'RIGHT'
                if i == "MOVE_DOWN":  # DOWN
                    robot_route.append("GO FORWARD")
                    direction = 'DOWN'
                if i == "MOVE_UP":  # UP
                    robot_route.append("GO BACKWARD")
                    direction = 'UP'
            elif direction == 'LEFT':
                if i == "MOVE_LEFT":  # LEFT
                    robot_route.append("GO BACKWARD")
                    direction = 'LEFT'
                if i == "MOVE_RIGHT":  # RIGHT
                    robot_route.append("GO FORWARD")
                    direction = 'RIGHT'
                if i == "MOVE_DOWN":  # DOWN
                    robot_route.append("GO RIGHT")
                    robot_route.append("GO FORWARD")
                    direction = 'DOWN'
                if i == "MOVE_UP":  # UP
                    robot_route.append("GO RIGHT")
                    robot_route.append("GO FORWARD")
                    direction = 'UP'

            elif direction == 'RIGHT':
                if i == "MOVE_LEFT":  # LEFT
                    robot_route.append("GO FORWARD")
                    direction = 'LEFT'
                if i == "MOVE_RIGHT":  # RIGHT
                    robot_route.append("GO BACKWARD")
                    direction = 'RIGHT'
                if i == "MOVE_DOWN":  # DOWN
                    robot_route.append("GO RIGHT")
                    robot_route.append("GO FORWARD")
                    direction = 'DOWN'
                if i == "MOVE_UP":  # UP
                    robot_route.append("GO LEFT")
                    robot_route.append("GO FORWARD")
                    direction = 'UP'

            elif direction == 'UP':
                if i == "MOVE_LEFT":  # LEFT
                    robot_route.append("GO RIGHT")
                    robot_route.append("GO FORWARD")
                    direction = 'LEFT'
                if i == "MOVE_RIGHT":  # RIGHT
                    robot_route.append("GO LEFT")
                    robot_route.append("GO FORWARD")
                    direction = 'RIGHT'
                if i == "MOVE_DOWN":  # DOWN
                    robot_route.append("GO FORWARD")
                    direction = 'DOWN'
                if i == "MOVE_UP":  # UP
                    robot_route.append("GO BACKWARD")
                    direction = 'UP'
        return (robot_route)
    else:
        print("Can not find route state invalid")
        return

# def get_robot_route(direction):
# 	robot_route = []
# 	optimal_route = direction
# 	if optimal_route != None:
# 		for i in range (len(optimal_route)):
# 			if optimal_route[i] == "MOVE_DOWN":
# 				robot_route.append("GO UP")
# 			if optimal_route[i] == "MOVE_RIGHT":
# 				robot_route.append("GO LEFT")
# 				robot_route.append("GO UP")
# 			if optimal_route[i] == "MOVE_LEFT":
# 				robot_route.append("GO RIGHT")
# 				robot_route.append("GO UP")
# 			if optimal_route[i] == "MOVE_UP":
# 				robot_route.append("GO DOWN")
# 		return (robot_route)
# 	else:
# 		print("Can not find route state invalid")
# 		return



def send_to_arduino(steps_robot):
    robot_route = steps_robot
    # send_bytes = []
    for each_move in robot_route:
        if each_move == 'GO FORWARD':
            # send_bytes.append(b'51')
                ArduinoSerial.write(b'3')
                print("MOVE_FORWARD")
                time.sleep(0.752)
            #ArduinoSerial.write(b'6')
            #time.sleep(2)
        elif each_move == 'GO LEFT':
                ArduinoSerial.write(b'1')
                time.sleep(0.605)
                #ArduinoSerial.write(b'1')
                print("TURN_LEFT")
        elif each_move == 'GO RIGHT':
                ArduinoSerial.write(b'4')
                time.sleep(0.672)
                print("TURN_RIGHT")
            #rduinoSerial.write(b'6')
            #Qtime.sleep(2)
        elif each_move == 'GO BACKWARD':
            # send_bytes.append(b'52')
            # send_bytes.append('3')
            ArduinoSerial.write(b'2')
            print("TURN_BACKWARD")
            time.sleep(1)

#make q table
qtab = np.zeros((row, column, 4))	#tạo row mảng với colunm hàng, 4 cột

hasil = 'belum'
for i in range(iteration):
	if hasil == 'menang':
		break

	#start player
	player = np.asarray([0,0])
	board = init_board(player)

	for j in range(maxstep):	# maxstep = 100
		poslama = np.zeros((2))
		poslama[:] = player
		choice, player = action(qtab, player)
		R = calcreward(poslama, player, target)

		#update q table
		qtab[int(poslama[0]), int(poslama[1]), choice] =  qtab[int(poslama[0]), int(poslama[1]), choice] + lrate*(R + \
		(discount**j)*(np.max(qtab[int(poslama[0]), int(poslama[1])] -  qtab[int(poslama[0]), int(poslama[1]), choice])))

		#update board
		#print 'cek posisi lama', poslama, player
		board[int(poslama[0]), int(poslama[1])] = 0
		board[player[0], player[1]] = playersym
		print (board)
		#break if landed in trap
		trapped = False
		#check if trapped
		for k in range(len(trap)):
			if np.array_equal(player, trap[k]):
				trapped = True
		if trapped:
			break
print (np.max(qtab))
#print ('the q-table:')
#print (qtab)

#check solution

#start player
player = np.asarray([0,0])
board = init_board(player)
move = []

for j in range(maxstep):
	poslama = np.zeros((2))
	poslama[:] = player
	nextmove, player = realaction(qtab, player)
	move.append(nextmove)

	#update board
	board[int(poslama[0]), int(poslama[1])] = 0
	board[player[0], player[1]] = playersym
	#print (board)

	trapped = False
	#check if trapped
	for i in range(len(trap)):
		if np.array_equal(player, trap[i]):
			trapped = True
	if trapped:
		print ('FAILED')
		break
	if np.array_equal(player, target):
		break

print ('success in step to:', j)
print ('the details of the move are:')
print (move)
print(get_robot_route(move,'UP'))
ArduinoSerial = serial.Serial(SERIAL_PORT, SERIAL_RATE)
time.sleep(1)
send_to_arduino(get_robot_route(move,'UP'))
ArduinoSerial.write(b'6')
print("dung")


