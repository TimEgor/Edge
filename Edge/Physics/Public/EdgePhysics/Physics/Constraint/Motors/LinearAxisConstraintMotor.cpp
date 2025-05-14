#include "LinearAxisConstraintMotor.h"

void Edge::LinearAxisConstraintMotor::preSolve(
	const ComputeVector3& anchor1,
	const ComputeVector3& anchor2,
	const ComputeVector3& axis1,
	const ComputeVector3& axis2
) {}

void Edge::LinearAxisConstraintMotor::warmUp() {}
void Edge::LinearAxisConstraintMotor::solveVelocity() {}
void Edge::LinearAxisConstraintMotor::solvePosition() {}
bool Edge::LinearAxisConstraintMotor::isActive() const { return true; }
