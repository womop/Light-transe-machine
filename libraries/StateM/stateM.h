#pragma once
#include "Arduino.h"
#include <LinkedList.h>

//#define DEBUGSM
#define MAXSTATE 255

/**
* State machine (StateM) et Queue de com (QueueNB) et StateMQueue (StateM + QueueNB)
* adapté de Scheduler/QueueNB.
* La lib n'est plus bloquante et n'a pas donc besoin de Scheduler.
* Si une Queue est pleine, push renvoie false au lieu de bloquer
* Si une Queue est vide, pull renvoie false au lieu de bloquer
* Push et Pull renvoient true dans tous les autres cas
*/

/**
* Template class for ring-buffer of QueueNBing data elements.
* @param[in] T element class.
* @param[in] nmemb number of elements in QueueNB.
*/
template <class T, uint8_t NMEMB>
class QueueNB {
	static_assert(NMEMB && !(NMEMB & (NMEMB - 1)), "QueueNB::NMEMB should be power of 2");
public:
	/**
* Construct a ring-buffer QueueNB with given number of members and
* member type.
*/
	QueueNB() :
	m_put(0),
	m_get(0)
	{}

	/**
* Return number of elements in QueueNB.
* @return available elements.
*/
	unsigned int available() const
	__attribute__((always_inline))
	{
		return ((NMEMB + m_put - m_get) & MASK);
	}

	/**
* Number of elements room in QueueNB.
* @return room for elements.
*/
	unsigned int room() const
	__attribute__((always_inline))
	{
		return ((NMEMB - m_put + m_get - 1) & MASK);
	}

	/**
* Push given data into QueueNB. Return true if room available, else if not.
* @param[in] data pointer to data buffer.
*/
	bool push(const T* data)
	{
		if(room()) {
			unsigned int next = (m_put + 1) & MASK;
			m_buffer[next] = *data;
			m_put = next;
			return true;
		}
		else return false;
	}

	/**
* Push given data in program memory into QueueNB.  Return true if room available, else if not.
* @param[in] data pointer to data buffer in program memory.
*/
	bool push_P(const T* data)
	{
		if(room()) {
			unsigned int next = (m_put + 1) & MASK;
			memcpy_P(&m_buffer[next], data, sizeof(T));
			m_put = next;
			return true;
		}
		else return false;
	}

	/** JYL 
* Peak at data without removing it from the QueueNB. Return true if a value is available, will update *data. Return false if no value available to peek at.
* @param[in,out] data pointer to data buffer.
*/
	bool peak(T* data)
	{
		if(available()) {
			unsigned int next = (m_get + 1) & MASK;
			*data = m_buffer[next];
			return true;
		}
		else return false;
	}

	/**
* Pull data from QueueNB to given buffer. Return true if a value is available, will update *data. Return false if no value available to read.
* @param[in,out] data pointer to data buffer.
*/
	bool pull(T* data)
	{
		if(available()) {
			unsigned int next = (m_get + 1) & MASK;
			m_get = next;
			*data = m_buffer[next];
			return true;
		}
		else return false;
	}

	/** JYL 
* Empty the queue.
*/
	void clear()
	{
		m_get = m_put;
	}

private:
	static const unsigned int MASK = (NMEMB - 1);
	volatile unsigned int m_put;
	volatile unsigned int m_get;
	T m_buffer[NMEMB];
};


class StateM {
	public :
	StateM () : m_firstRun(true) {};
	enum actions {ENTER, LOOP, EXIT};

	// initial state, autoRun
	/* must be called once to set the machine initial state. autoRun = true means 
	 * machine will be called when runAll is called. 
	 * It is usefull to set autoRun to false to control manually 
	 * machine run (for machines embedded or inherited into other machines) 
	 */
	void init( uint8_t, bool = true); 
	uint8_t getState( void );
	void setState(uint8_t state);
	uint8_t run(); // return current state
	virtual uint8_t loop(uint8_t state, uint8_t action, uint8_t cycle) = 0;
	void nextCycle(); // force state machine process to exit 
	virtual void printID();
	
	
	static void runAll();
	
	private :
	void setWorkToDo();
	uint8_t toLoop(uint8_t state, uint8_t action, uint8_t cycle);
	void clearWorkToDo();
	bool isWorkToDo();
	uint8_t m_state;
	bool m_workToDo;
	bool m_firstRun;
	bool m_nextCycle {false};
	static LinkedList<StateM*> machines;
};

template <class T, uint8_t NMEMB> 
class StateMQueue : public StateM {
public:
	StateMQueue () : StateM() {}
protected:
	QueueNB<T,NMEMB> m_msgQueue;
};

class TimerMillis {
	public :
	TimerMillis() :m_timerValue(0), m_clockRef(0), m_StateRef(0) {};
	TimerMillis(uint32_t val) :m_timerValue(val), m_clockRef(0), m_StateRef(MAXSTATE), m_expiry(false) {};
	
	void set (uint32_t val);
	void run(StateM *);
	void reset ();
	bool expired ();
private:
	uint32_t m_timerValue, m_clockRef;
	uint8_t m_StateRef;
	bool m_expiry;
};

