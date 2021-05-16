/*
 * fsm-defs.h
 *
 *  Created on: Mar 28, 2020
 *      Author: doitaljosh
 */

#ifndef FSM_DEFS_H_
#define FSM_DEFS_H_

// Error state machine
enum ErrorStates {
	OverCurrent,
	OverTemperature,
	NoPotDetected,
	KillSignal,
} ErrorStates;

enum ErrorEvents {
	TurnOffZones,
	ThrowErrorCode,
	BlinkLed,
};

// Normal operation state machine
enum OperatingStates {
	Zone0IsActive,
	Zone1IsActive,
	SystemIsHot,
	SystemIsIdle,
} OperatingStates;

enum OperatingEvents {
	MonitorZone0,
	MonitorZone1,
	CoolDown,
	IdleMode,
};

// PID loop
enum PidLoopStates {
	PosError,
	NegError,
} PidLoopStates;

enum PidLoopEvents {
	RampUp,
	RampDown,
};

#endif /* FSM_DEFS_H_ */
