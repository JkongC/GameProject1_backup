#include "stdlibs.h"
#include "general/util.h"
#include "object/Animation.h"
#include "object/Object.h"
#include "object/Player.h"
#include "general/event.h"
#include "ui/Arena.h"
#include "object/Score.h"
#include "general/scene.h"

std::array<IMAGE*, 3> Score::img_list = { nullptr, nullptr, nullptr };

Score::Score(long x, long y, Count type)
	: type(type)
{
	this->width = Score::img_list[0]->getwidth();
	this->height = Score::img_list[0]->getheight();
	this->angle = 0;
	this->pos.x = x;
	this->pos.y = y;
	this->life = 1;

	Scene::GetScene().AddObject(this);
}

Score::~Score() = default;

void Score::Tick(const int& delta)
{
	if (CheckCollsion()) {
		this->should_remove = true;
		BonusPlayer(*Scene::GetScene().GetPlayer());
	}
}

void Score::Render()
{
	putimage_alpha(Score::img_list[(int)this->type], pos.x, pos.y, 0, 0, width, height);
}

bool Score::CheckCollsion()
{
	Player* player = Scene::GetScene().GetPlayer();
	if (this->GetCenter().GetDistanceFrom(player->GetCenter()) < this->width / 2 + player->width - 20) {
		return true;
	}

	return false;
}

void Score::BonusPlayer(Player& player)
{
	switch (this->type)
	{
	case Count::Five:
		player.SetScore(player.GetScore() + 5);
		break;
	case Count::Ten:
		player.SetScore(player.GetScore() + 10);
		break;
	case Count::Twenty:
		player.SetScore(player.GetScore() + 20);
		player.SetHealth(player.GetHealth() + 1);
		break;
	default:
		break;
	}
}


void ScoreGenerator::TryGenerate(const int& delta)
{
	counter += delta;
	if (counter < cooldown) return;

	counter = 0;
	static std::random_device rd;
	static std::mt19937 rand(rd());

	static std::normal_distribution<> radius_rate(0, 0.2);
	static std::uniform_int_distribution<> degree_dist(0, 359);
	static std::uniform_int_distribution<> score_type_rd(0, 10);

	double r = 1;
	double degree = degree_dist(rand);
	double angle = PI / 180 * degree;

	while (r >= 0.75)
	{
		r = radius_rate(rand);
	}

	long x = (long)sqrt(Arena::long_axis * Arena::long_axis * r);
	long y = (long)sqrt(Arena::short_axis * Arena::short_axis * r);

	int score_type_rdvalue = score_type_rd(rand);
	Score::Count score_type;

	if (score_type_rdvalue <= 5) {
		score_type = Score::Count::Five;
	}
	else if (score_type_rdvalue > 5 && score_type_rdvalue <= 8) {
		score_type = Score::Count::Ten;
	}
	else {
		score_type = Score::Count::Twenty;
	}

	new Score((long)(cos(degree) * x + Arena::center.x), (long)(sin(degree) * y + Arena::center.y), score_type);
}