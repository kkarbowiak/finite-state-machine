all:
	g++ source/main.cpp source/testBasicState.cpp source/testEvent.cpp source/testEventBase.cpp source/testfsmStateBase.cpp source/testfsmStateBaseBasic.cpp source/testfsmStateMachine.cpp source/testState.cpp -o unittest -I . -I ../.. -Wall -Wextra -pedantic

.PHONY: clean

clean:
	rm -f unittest
