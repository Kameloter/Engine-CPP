#ifndef COLLISION_H
#define COLLISION_H

class Collision
{
    public:
        Collision(const bool pCollides, const float pCollisionDistance):
            _collides(pCollides),
            _collisionDistance(pCollisionDistance) {}
      //  virtual ~Collision() {}
    inline bool getIsColliding() const { return _collides; }
    inline float getCollisionDistance() const { return _collisionDistance; }
	inline std::string getHitBy() 
	{ 
		if (_hitBy != "")
			return _hitBy;
		else
			return "null";
	}


	inline void setInfo(bool pColliding, std::string pHitBy) { _collides = pColliding; _hitBy = pHitBy; }
    protected:
    private:
        bool _collides;
        const float _collisionDistance;

		std::string _hitBy;


};

#endif // COLLISION_H
