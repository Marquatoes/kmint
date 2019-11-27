#include "sim/SteeringBehaviors.hpp"
#include "main.cpp";

kmint::math::vector2d sim::SteeringBehavoirs::Seek(kmint::math::vector2d TargetPos)
{
	Vector2D DesiredVelocity = Vec2DNormalize(TargetPos - m_pVehicle->Pos())
		* m_pVehicle->MaxSpeed();
	return (DesiredVelocity - m_pVehicle->Velocity());
}

kmint::math::vector2d sim::SteeringBehavoirs::Flee(kmint::math::vector2d TargetPos)
{
	Vector2D DesiredVelocity = Vec2DNormalize(m_pVehicle->Pos() - TargetPos)
		* m_pVehicle->MaxSpeed();
	return (DesiredVelocity - m_pVehicle->Velocity());
}

kmint::math::vector2d sim::SteeringBehavoirs::Pursuit(const perceptive_actor* evader)
{
	kmint::math::vector2d ToEvader = evader->Pos() - m_pVehicle->Pos();
	double RelativeHeading = m_pVehicle->Heading().Dot(evader->Heading());
	if ((ToEvader.Dot(m_pVehicle->Heading()) > 0) &&
		(RelativeHeading < -0.95)) //acos(0.95)=18 degs
	{
		return Seek(evader->Pos());
	}
	//Not considered ahead so we predict where the evader will be.
	//the look-ahead time is proportional to the distance between the evader
	//and the pursuer; and is inversely proportional to the sum of the
	//agents' velocities
	double LookAheadTime = ToEvader.Length() /
		(m_pVehicle->MaxSpeed() + evader->Speed());
	//now seek to the predicted future position of the evader
	return Seek(evader->Pos() + evader->Velocity() * LookAheadTime);
}
