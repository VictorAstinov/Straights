CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -Werror=vla -MMD 
EXEC = straights
OBJECTS = AbstractPlayer.o AbstractRules.o Card.o Commands.o CompStrategy.o ComputerPlayer.o  Deck.o DefaultRules.o DefaultStrat.o GameController.o GraphicObserver.o GameState.o HardStrat.o HumanPlayer.o main.o RandomStrat.o subject.o TextObserver.o window.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}