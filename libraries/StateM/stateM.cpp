#include "stateM.h"
#include "Streaming.h"

LinkedList<StateM*> StateM::machines = LinkedList<StateM * >();

void StateM::init(uint8_t initialState, bool autoRun) {
	setState(initialState);
	if (autoRun) machines.add(this);
}

uint8_t StateM::getState( void ) {
	return m_state;
}


void StateM::setState(uint8_t state) {
	m_state = state;
}



uint8_t StateM::toLoop(uint8_t state, uint8_t action, uint8_t cycle){
#ifdef DEBUGSM
	if (action == ENTER || action == EXIT ) {
		Serial << millis()  << F("-") << cycle<< F(" id: ");
		printID();
	}
	//  if (action == LOOP) Serial <<  F(" LOOP   state # ") << getState() << endl;
	if (action == ENTER) Serial << F(" ENTER  state # ") << getState() << endl;
	if (action == EXIT) Serial <<  F(" EXIT   state # ") << getState() << endl;

#endif	
	return loop(state,action,cycle);
}

void StateM::runAll() {
	for (int i = 0; i < machines.size(); i++) {
		/*Serial << F("Machine run :") << i << endl;
		delay(500);*/
		machines.get(i)->run();
		/*Serial << F("Machine done :") << i << endl;
		delay(500);*/
	}
}

void StateM::printID() {
	#ifdef DEBUGSM
	Serial << F("genericID");
	#endif	
}

// Usefull when end user wants us to stop chaining states in current sequence.
void StateM::nextCycle() {
	m_nextCycle = true;
}

uint8_t StateM::run(void) {
	uint8_t newState;
	uint8_t cycle=0;
	m_nextCycle = false;
	
	setWorkToDo();
	while (isWorkToDo() && cycle < 100 && !m_nextCycle) {
		clearWorkToDo();
		if (m_firstRun) {
			m_firstRun=false;
			toLoop(m_state,ENTER,cycle);
		}		
		newState = toLoop(m_state,LOOP,cycle);
		
		if (newState != 0) {
			if (newState != m_state) {
				toLoop(m_state,EXIT,cycle);
				m_state = newState;
				cycle++;
				toLoop(m_state,ENTER,cycle);
				setWorkToDo();
			}
		}
		cycle++;
	}
	// Anti loop has kicked in
	#ifdef DEBUGSM
	if (cycle >=100) Serial << F("Infinite loop detected and kicked in the ass") << endl;
	//if (m_nextCycle) Serial << F("Forcefully stepping out of state machine") << endl;
	#endif
	return m_state;
}

void StateM::setWorkToDo() {
	m_workToDo = true;
}

void StateM::clearWorkToDo() {
	m_workToDo = false;
}

bool StateM::isWorkToDo()  {
	return m_workToDo;
}

void TimerMillis::set (uint32_t val) {
	m_timerValue = val;
}


/* Automatic timer. Resets upon state change. Must be called at each StateMachine cycle, whatever the state
* else the timer won't work as expected.
*/
void TimerMillis::run (StateM *p_State) {
	if (m_StateRef != p_State->getState()) {
		m_clockRef = millis();
		m_StateRef = p_State->getState();
	}
	if (millis()-m_clockRef >= m_timerValue) {
		m_expiry = true;
	}
	else {
		m_expiry = false;
	}
}

/*
 * Reset the timer as if it was just set for the first time
 */

void TimerMillis::reset () {
	m_clockRef = millis();
}

/* 
* Return timer expiry state
*/
bool TimerMillis::expired () {
	return m_expiry;
}



