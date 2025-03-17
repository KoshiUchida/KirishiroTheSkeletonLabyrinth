/**
 * @file   MapGenerator.h
 *
 * @brief  マップジェネレーターのヘッダーファイル
 *
 * @author CatCode
 */

#pragma once
#include "ObjectBace.h"

static constexpr int PanelWidth{ 5 };

class MapGenerator :
    public ObjectBace
{
private:
	static constexpr int Width{ 5 };

public:
	// Main System
	MapGenerator(SceneBace* pScene) noexcept;
	~MapGenerator() noexcept;

	void Initialize() override final;
	void Process(float elapsedTime) override final;
};

class PanelData
{
private:
	// パネルのタイル情報
	int m_tileDatas[PanelWidth][PanelWidth];

	// 「穴」の情報
	struct Hoal
	{
		bool up;
		bool down;
		bool left;
		bool right;
	} m_hoal;

	// このパネルの確率
	int m_parcent;

public:
	PanelData(int data[PanelWidth][PanelWidth], int popParcent = 1000);
	~PanelData();
	int GetTileData(int x, int y);
	int  GetParcent() const { return m_parcent; }
	Hoal GetHoalData() const { return m_hoal; }
};

bool GetNormalizedPathMap(std::vector<std::vector<int>>* _map, const int _wallNumber, const int _startX, const int _startY, const int _goalX, const int _goalY);
