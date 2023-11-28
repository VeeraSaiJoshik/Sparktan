from globalData import *

class Coordinate:
    def __init__(self, x = 0, y = 0, isFieldCoordinate = True):
        self.x = x
        self.y = y
        self.standardize()
        self.isFieldCoordinate = isFieldCoordinate
    def moveX(self, deltaX):
        self.x += deltaX
        self.standardize()
    def moveY(self, deltaY):
        self.y += deltaY
        self.standardize()
    def moveCoordinate(self, deltaX, deltaY):
        self.moveX(deltaX)
        self.moveY(deltaY)
    def changeCoordinate(self, deltaCoordinate):
        self.x = deltaCoordinate[0]
        self.y = deltaCoordinate[1]
        self.standardize()
    def standardize(self):
        if self.isFieldCoordinate : 
            # Standardize the x values
            if self.x >= GAME_AREA_WIDTH//2 : self.x = GAME_AREA_WIDTH//2
            elif self.x <= GAME_AREA_WIDTH//-2 : self.x = GAME_AREA_WIDTH//-2
            # Standardize the y values
            if self.y >= GAME_AREA_HEIGHT//2 : self.y = GAME_AREA_HEIGHT//2
            elif self.y <= GAME_AREA_HEIGHT//-2 : self.y = GAME_AREA_HEIGHT//-2
        else : 
            # Standardize the x values
            if self.x >= OPTION_AREA_WIDTH//2 : self.x = OPTION_AREA_WIDTH//2
            elif self.x <= OPTION_AREA_WIDTH//-2 : self.x = OPTION_AREA_WIDTH//-2
            # Standardize the y values
            if self.y >= OPTION_AREA_HEIGHT//2 : self.y = OPTION_AREA_HEIGHT//2
            elif self.y <= OPTION_AREA_WIDTH//-2 : self.y = OPTION_AREA_WIDTH//-2