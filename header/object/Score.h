#pragma once

class Score : public Object
{
public:
	enum class Count
	{
		Five = 0, Ten, Twenty
	};
	
	Score(long x, long y, Count type);

	~Score();

	void Tick(const int& delta) override;

	void Render() override;

	bool CheckCollsion();

	void BonusPlayer(Player& player);

public:
	static std::array<IMAGE*, 3> img_list;
	Count type;
};

class ScoreGenerator
{
public:

	static ScoreGenerator& GetGenerator()
	{
		static ScoreGenerator generator;
		return generator;
	}

	void TryGenerate(const int& delta);

private:
	ScoreGenerator() : counter(0) {};

	~ScoreGenerator() = default;

	const int cooldown = 2000;
	int counter;
};