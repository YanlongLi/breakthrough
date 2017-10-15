# =============================================================================
#      FileName: Makefile
#          Desc: Make file
#        Author: YanlongLi
#         Email: lansunlong@gmail.com
#      HomePage: http://www.yanlongli.me
#       Created: 2017-10-14 06:51:07
#       Version: 0.0.1
#    LastChange: 2017-10-14 06:51:07
#       History:
#                0.0.1 | YanlongLi | init
# =============================================================================

CPPFLAGS=-g --std=c++11

breakthrough: Board.o Agent.o MinimaxAgent.o Evaluator.o RandomAgent.o main.o utils.o
	@$(CXX) $(CPPFLAGS) $^ -o $@


%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $<

# Board.o: Board.cpp
#	@g++ -g -c -std=c++11 Board.cpp
#
# Agent.o: Agent.cpp
#	@g++ -g -c -std=c++11 Agent.cpp
#
# MinimaxAgent.o: MinimaxAgent.cpp
#	@g++ -g -c -std=c++11 MinimaxAgent.cpp
#
# RandomAgent.o: RandomAgent.cpp
#	@g++ -g -c -std=c++11 RandomAgent.cpp
#
# utils.o: utils.cpp
#	@g++ -g -c -std=c++11 utils.cpp
#
# main.o: main.cpp
# @g++ -g -c -std=c++11 main.cpp

run: breakthrough
	@./breakthrough

clean:
	@rm -f *.o breakthrough

.PHONY: run

