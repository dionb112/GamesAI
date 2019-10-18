#include "NPC.h"
NPC::NPC() :
	m_velocity{ -MAX_VELOCITY, 0.0f },
	m_myPosition{ SCR_W / 2, SCR_H / 2 },
	m_orientation{ 0.0f },
	m_rotation{ 0.0f },
	m_targetPosition{ 0.0f, 0.0f } {
	srand(time(NULL));			// initialize 'random' seed
	m_generateTarget();
}
void NPC::kinematicFlee(float t_deltaTime, sf::Vector2f& t_playerPos) {
	m_targetPosition = t_playerPos;
	m_velocity = m_myPosition - m_targetPosition;
	m_velocity = m_velocity / Kinematic::vectorLength(m_velocity) * (t_deltaTime / 3);
	m_velocity *= MAX_VELOCITY;
	m_orientation = Kinematic::getNewOrientation(m_orientation, m_velocity);
}
void NPC::update(float t_deltaTime, sf::Vector2f& t_playerPos, sf::Vector2f& t_playerVelo, sf::Vector2f& t_slotPos) {
	bool isFlee = false;
	switch (m_behaviourType)
	{
	case wander:
		kinematicWander(t_deltaTime / 4.2f);
		break;
	case seek:
		kinematicSeek(t_deltaTime / 4.2f, t_playerPos);
		break;
	case arrive:
		kinematicArrive(t_deltaTime / 4.2f, t_playerPos);
		break;
	case flee:
		kinematicFlee(t_deltaTime / 4.2f, t_playerPos);
		isFlee = true;
		break;
	case pursue:
		dynamicPursue(t_deltaTime / 4.2f, t_playerPos, t_playerVelo);
		break;
	case form:
		kinematicSeek(t_deltaTime / 4.2f, t_slotPos);
	default:
		break;
	}
	m_move();
	if (!isFlee) {
		Kinematic::screenWrap(m_myPosition);
	}
}
void NPC::m_move()
{
	m_myPosition += m_velocity;
	m_sprite.setRotation(m_orientation);
	m_sprite.setPosition(m_myPosition);
}
void NPC::kinematicSeek(float t_deltaTime, sf::Vector2f& t_playerPos) {
	m_targetPosition = t_playerPos;
	m_velocity = m_targetPosition - m_myPosition;
	m_velocity = m_velocity / Kinematic::vectorLength(m_velocity) * t_deltaTime;
	m_velocity *= MAX_VELOCITY;
	m_orientation = Kinematic::getNewOrientation(m_orientation, m_velocity);
}
void NPC::kinematicArrive(float t_deltaTime, sf::Vector2f& t_playerPos) {
	float timeToTarget = 0.25f;
	float radius = SPRITE_QUARTER;
	m_targetPosition = t_playerPos;
	m_velocity = m_targetPosition - m_myPosition;
	if (Kinematic::vectorLength(m_velocity) < radius) {
		m_velocity.x = 0;
		m_velocity.y = 0;
	} else {
		m_velocity = m_velocity / timeToTarget * t_deltaTime;
		if (Kinematic::vectorLength(m_velocity)) {
			m_velocity = m_velocity / Kinematic::vectorLength(m_velocity);
			m_velocity = m_velocity * MAX_VELOCITY;
		}
		m_orientation = Kinematic::getNewOrientation(m_orientation, m_velocity);
	}
}
void NPC::m_generateTarget() {
	float x = rand() % SCR_W;
	float y = rand() % SCR_H;
	m_targetPosition = sf::Vector2f{ x, y };
}
void NPC::kinematicWander(float t_deltaTime) {
	if (m_targetPosition.x - m_myPosition.x < 50 && m_targetPosition.y - m_myPosition.y < 11.11f)
	{
		m_generateTarget();
	}
	m_orientation = Kinematic::getNewOrientation(m_orientation, m_velocity);
	m_orientation = m_orientation + ROTATION_CHANGE * ((rand() % 2) - 1); // rand 0 to 2 minus 1 gives -1 to 1 
	m_velocity = sf::Vector2f{ -sinf(m_orientation), cosf(m_orientation) } * MAX_VELOCITY ;
	m_velocity = m_targetPosition - m_myPosition;
	m_velocity = m_velocity / Kinematic::vectorLength(m_velocity) * t_deltaTime;
}
void NPC::dynamicPursue(float t_deltaTime, sf::Vector2f& t_playerPos, sf::Vector2f& t_playerVelo) {
	float timePrediction = 0.0f;
	sf::Vector2f direction = t_playerPos - m_myPosition;	//direction = target.position - my.position
	float distance = Kinematic::vectorLength(direction);	//	distance = direction.length
	float speed = Kinematic::vectorLength(m_velocity);		//	speed = my.velocity.length
	if (speed <= distance / MAX_TIME_PRED) { //	if speed <= distance / maxTimePrediction:
		timePrediction = MAX_TIME_PRED;	//timePrediction = maxTimeprediction
		}
	else {
		timePrediction = distance / speed;	//timePrediction = distance / speed
	}
	sf::Vector2f newTarget = t_playerPos + t_playerVelo * timePrediction * t_deltaTime;	//	newtarget.position = target.position + target.velocity * timePrediction
	kinematicSeek(t_deltaTime, newTarget); //	seek(me, newTarget)
}
void NPC::closestApproach() {
	float shortestTime = INFINITY;		//	shortestTime = infinity​
		//		firstTarget = None // target that will collide first​
		//		firstMinSeparation, firstDistance, firstRelativePos, firstRelativeVel​
		//		radius //collision radius​
		//		for target in targets : ​
		//			relativePos = target.position - character.position​
		//			relativeVel = target.velocity - character.velocity​
		//			relativeSpeed = relativeVel.length()​
		//			timeToCollision = (relativePos.relativeVel) / (relativeSpeed * relativeSpeed)​
		//			distance = relativePos.length()​
		//			minSeparation = distance – relativeSpeed * shortestTime​
		//			if minSeparation > 2 * radius: continue​
		//				if timeToCollision > 0 and timeToCollision < shortestTime: //Is it the shortest?​
		//	shortestTime = timeToCollision​
		//		firstTarget = target​
		//		firstMinSeparation = minSeparation​
		//		firstDistance = distance​
		//		firstRelativePos = relativePos​
		//		firstRelativeVel = relativeVel​
		//		if not firstTarget: return None​
		//			if firstMinSeparation <= 0 or distance < 2 * radius : # colliding​
		//				relativePos = firstTarget.position - character.position​
		//			else:​
		//				relativePos = firstRelativePos + firstRelativeVel * shortestTime​
		//				relativePos.normalize()​
		//				steering.linear = relativePos * maxAcceleration​
		//				return steering​
}
void NPC::render(sf::RenderWindow& t_window) {
	t_window.draw(m_sprite);
}
/// <summary>
/// 
/// </summary>
/// <param name="t_type"></param>
void NPC::setupBehaviourAndSprite(Type t_type) {	
	m_behaviourType = t_type;
	switch (m_behaviourType)
	{
	case wander:
		if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\wanderer.png"))
		{
			std::cout << "problem loading wanderer" << std::endl;
		}		
		break;
	case seek:
		if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\seeker.png"))
		{
			std::cout << "problem loading seeker" << std::endl;
		}
		break;
	case arrive:
		if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\arriver.png"))
		{
			std::cout << "problem loading arriver" << std::endl;
		}
		break;
	case flee:
		if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\scaredyCat.png"))
		{
			std::cout << "problem loading scaredy cat" << std::endl;
		}
		break;
	case pursue:
		if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\pursuir.png"))
		{
			std::cout << "problem loading pursuir" << std::endl;
		}
		break;
	case form:
		if (!m_spriteTexture.loadFromFile("ASSETS\\IMAGES\\form.png"))
		{
			std::cout << "problem loading form texture" << std::endl;
		}
	default:
		break;
	}
	m_sprite.setTexture(m_spriteTexture);
	m_sprite.setOrigin(m_spriteTexture.getSize().x / 2, m_spriteTexture.getSize().y / 2);
}
