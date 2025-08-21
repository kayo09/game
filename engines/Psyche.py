from typing import List, Tuple, Optional

#Implementaton of Hardware abstraction layer, POSIX
#Questions to ask user 
#Note: lacks better accessibility yet
class Psyche:
    def __init__(self, choices: Optional[List[Tuple]] = None) -> None:
        if choices is None: 
            choices = []
        self.choices = choices

    def anal_kind(self,):
        #logic to analyze kind and create a point system to generate an avatar
        kind = self.choices[0]
        

    def diff_senses(self,):
        #logic to analyze senses, treating sense count as difficulty classifier for game
        pass

    #creates a choices object
    def hi(self) -> None:
        print("You're about to make a big CHOICE, chose wisely! or don't it's just some garbage code ;)")
        while True:
            kind = str(input("What kind of human are you? (max 280 chars)\n"))
            if len(kind)<=280:
                break
            print("⚠ Too BIG! Try again")
        senses = int(input("How many tactile senses do you poses?"))
        choice_0 = bool(input("Can i classify you while you evolve?"))
    
        self.choices = (kind, senses, choice_0)

if __name__ == "__main__":
    obj = Psyche()
    obj.hi()
    print(obj.choices)
