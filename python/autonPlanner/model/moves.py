from enum import Enum

class ActionType(Enum):
    Move = 1
    Rotate = 2
    Catapult = 3
    Intake = 4
    Outake = 5
    Wings = 6
    Shove = 7

class Action:  
    def __init__(self, move = ActionType.Move, previousMove = ActionType.Move, x = 0, y = 0, theta = 0, parameter = 0):
        self.move = move
        self.previousMove = previousMove
        self.x = x
        self.y = y
        self.theta = theta
        self.parameter = parameter
    def encode(self):
        if self.move == ActionType.Move :
            # do math to see what angle and how much distance we have to travel
            pass
        elif self.move == ActionType.Rotate :
            
            pass
        elif self.move == ActionType.Catapult :
            return "Ca"
        elif self.move == ActionType.Intake :
            return "In|" + str(self.parameter)
        elif self.move == ActionType.Outake :
            return "Ot|" + str(self.parameter)
        elif self.move == ActionType.Wings :
            if self.parameter : return "Wo"
            return "Wi"
        elif self.move == ActionType.Shove :
            return 'Sh'
    def decode(self):
        pass