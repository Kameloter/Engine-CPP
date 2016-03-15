#ifndef COLLISION_H
#define COLLISION_H

class GameObject;

class Collision
{
    public:
        Collision( bool pCollides,  float pCollisionDistance):
            _collides(pCollides),
            _collisionDistance(pCollisionDistance) {}
      //  virtual ~Collision() {}
    inline bool getIsColliding() { return _collides; }
    inline float getCollisionDistance()  { return _collisionDistance; }
	
	inline GameObject * getHitBy() 
	{ 
		if (_hitBy != NULL)
			return _hitBy;
		else
			return NULL;
	}
	/*inline bool OnTriggerEnter(std::string ifHitBy)
	{
		if (_hitBy == "")
		{
			_enteredTrigger = false;
			return false;
		}

		if (_enteredTrigger) return false;

		if (ifHitBy == _hitBy)
		{
			_enteredTrigger = true;
			return true;
		}
		else
		{
			return false;
		}
	}*/

	inline void setInfo(bool pColliding, GameObject * pHitBy) { _collides = pColliding; _hitBy = pHitBy; }
    protected:
    private:
       bool _collides;
       float _collisionDistance;

	   bool _enteredTrigger = false;

	   GameObject * _hitBy;
		//std::string _hitBy;


};

#endif // COLLISION_H
