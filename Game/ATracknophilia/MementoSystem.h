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
		if (timeLimitOfData > 5)
		{
			lerpTime += dt;
			auto player1 = AutoList::get<Player>().at(0);
			m_currentPos = positions.at(positions.size() - 1); // last index
			for (int i = 0; i < positions.size(); i++)
			{
				player1->getComponent<DynamicBodyComponent>()->body->SetTransform(rewindData(positions.at(positions.size() - 1 - i), m_currentPos, lerpTime), 0);
			}
		}
		else
		{
			storeData();		
		}
	}

	void storeData() {
		auto player1 = AutoList::get<Player>().at(0);
		positions.push_back(player1->getComponent<DynamicBodyComponent>()->body->GetPosition());
	}


	b2Vec2 rewindData(b2Vec2 positionToGoTo, b2Vec2 currentPos, float lerpT) {
		// interpolate between previous positions
		if (currentPos != positionToGoTo)
		{
			float decelPercentage = lerpT / maxLerpTime;
			b2Vec2 initialValue = currentPos -positionToGoTo;
			b2Vec2 finalValue = b2Vec2(0,0);
			float decelRateX = (initialValue.x - finalValue.x) * decelPercentage;
			float decelRateY = (initialValue.y - finalValue.y) * decelPercentage;
			b2Vec2 position;
			position.x = currentPos.x - decelRateX;
			position.y = currentPos.y - decelRateY;
			m_currentPos = position;
			return position;
		}
	}

	void deleteData() {

	}

private:
	vector<b2Vec2>positions;
	b2Vec2 m_currentPos;
	float timeLimitOfData;
	float lerpTime;
	float maxLerpTime = 5;
};