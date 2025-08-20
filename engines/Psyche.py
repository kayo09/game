from typing import List, Tuple

#Implementaton of Hardware abstraction layer, POSIX
#Questions to ask user 
#Note: lacks better accessibility yet
class Psyche:
    def __init__(self, choices: List[Tuple])-> None:
        self.choices = choices
        pass

    def anal_kind(self,):
        #logic to analyze kind
        pass

    def diff_senses(self,):
        #logic to analyze senses, treating sense count as difficulty classifier for game
        pass

    #creates a choices object
    def hi(self):
        print("You're about to make a big CHOICE, chose wisely! or don't it's just some garbage code ;)")
        print("What kind of human are you?")
        kind = str(input())
        print("How many tactile senses do you poses?")
        senses = int(input())
        print("Can i classify you while you evolve?")
        choice_0 = bool(input())
        self.choices = (kind, senses, choice_0)


