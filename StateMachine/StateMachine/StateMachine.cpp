// StateMachine.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

#include <iostream>

class StateMachine
{
public:
	StateMachine() : state_(StateA) {}
	void event(int Num)
	{
		(this->*handler_[state_][Num])();
	}
private:
	enum State {
		StateA = 0,
		StateB = 1
	};
	void A0() {
		std::cout << "StateA-Event0" << std::endl;
		std::cout << "Goto StateB" << std::endl;
		state_ = StateB;
	}
	void A1() {
		std::cout << "StateA-Event1" << std::endl;
	}
	void B0() {
		std::cout << "StateB-Event0" << std::endl;
	}
	void B1() {
		std::cout << "StateB-Event1" << std::endl;
		std::cout << "Goto StateA" << std::endl;
		state_ = StateA;
	}
	State state_;
	static void (StateMachine::*const handler_[2][2])();
};

void (StateMachine::*const StateMachine::handler_[2][2])() = {
	{ &StateMachine::A0, &StateMachine::A1 },
	{ &StateMachine::B0, &StateMachine::B1 },
};

int main()
{
	StateMachine fsm;
	fsm.event(1);
	fsm.event(0);
	fsm.event(0);
	fsm.event(1);

    return 0;
}

