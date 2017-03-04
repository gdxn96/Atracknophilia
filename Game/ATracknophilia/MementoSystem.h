#pragma once
#include "ECSInterfaces.h"
#include "RaceManager.h"

typedef vector<float> vector_of_floats;

class MementoSystem : public ISystem
{
public:
	MementoSystem()
	{

	}

	void process(float dt) override {
		timeLimitOfData += dt;


		//PhysicsSystem::World().Step(dt * 4, 7, 3);

		if (timeLimitOfData > 5)
		{
			//deleteData();
			lerpTime += dt;
			auto player1 = AutoList::get<Player>().at(0);
			
				for (int i = 0; i < posX.size(); i++)
				{
					player1->getComponent<DynamicBodyComponent>()->body->SetTransform(b2Vec2(posX.at((posX.size() -1) - i), posY.at((posY.size() -1) - i)), 0);
				}
			
			
		}
		else
		{
			auto player1 = AutoList::get<Player>().at(0);
			
			/*	vector_of_floats posX;
				vector_of_floats posY;*/

				posX.push_back(player1->getComponent<DynamicBodyComponent>()->body->GetPosition().x);
				posY.push_back(player1->getComponent<DynamicBodyComponent>()->body->GetPosition().y);

			/*	xs.push_back(posX);
				ys.push_back(posY);*/



			
		}
	}

	void storeData() {

	}

	void rewindData(int start, int end, float lerpT) {
		// while the velocity is greater than original max velocity - reduce the velocity evenly over time (lerp)
		if (end > start)
		{
			/*float decelPercentage = lerpT / stamComp->boostTime;
			float initialValue = boostedVelComp->BOOSTED_VELOCITY - maxVelComp->MAX_VELOCITY;
			float finalValue = 0;
			float decelRate = (initialValue - finalValue) * decelPercentage;
			velComp->velocity = boostedVelComp->BOOSTED_VELOCITY - decelRate;
			accComp->acceleration = maxAccComp->MAX_ACCELERATION;*/
		}
	}

	void deleteData() {
		for (int i = 0; i < xs.size(); i++)
		{
			xs.erase(xs.begin() + i);
		}
		for (int j = 0; j < ys.size(); j++)
		{
			ys.erase(ys.begin() + j);
		}
	}

private:

	vector_of_floats posX;
	vector_of_floats posY;

	vector<vector_of_floats> xs;
	vector<vector_of_floats> ys;
	vector<vector_of_floats> xVelocities;
	vector<vector_of_floats> yVelocities;

	float timeLimitOfData;

	float lerpTime;

	float maxLerpTime = 5;

	//PhysicsSystem* physicsSys; // use for speeding up world for recording data
};