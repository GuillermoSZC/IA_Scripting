#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>

class SteeringDelegate;

namespace MathFunctions
{
	#define PI 3.14159265358979323846f

    void NormalizeRadianToAngles(float& _angle);
    void NormalizeDegreeToAngles(float& _angle);
    float DegreesToRadians(float _angle);
    float RadiansToDegrees(float _angle);
}

class Character: public MOAIEntity2D
{
public:
    DECL_LUA_FACTORY(Character)

protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);

public:
	virtual void DrawDebug();

	Character();
	~Character();
	
	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y;}
	void SetAngularVelocity(float angle) { mAngularVelocity = angle;}
	void SetPosition(USVec2D& _position);
	void SetAcceleration(USVec2D& _acceleration);
	void SetParams(Params& _params);
	
	USVec2D GetLinearVelocity() const { return mLinearVelocity;}
	float GetAngularVelocity() const { return mAngularVelocity;}
	USVec2D GetPosition() const;
	USVec2D GetAcceleration() const;
	const Params& GetParams() const;

private:
	USVec2D mLinearVelocity;
	float mAngularVelocity;
	USVec2D position;
	USVec2D acceleration;	
	float rotation;

	Params mParams;

	/*ArriveSteering steering;
	AlignSteering alignSteering;*/
	SteeringDelegate* steering;
	
	// Lua configuration

public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);

private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
};

#endif