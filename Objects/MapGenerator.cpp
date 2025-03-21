/**
 * @file   MapGenerator.cpp
 *
 * @brief  マップジェネレーターのソースファイル
 *
 * @author CatCode
 */

#include "pch.h"
#include "MapGenerator.h"

#include "../Managers/ObjectManager.h"
#include "Box.h"
#include "Wall.h"
#include "Cylinder.h"
#include "Floor.h"

#include "../Components/Transform.h"

 // パネルのデータを作成
int Datas[][PanelWidth][PanelWidth]
{
	// 0:十字路のパネル
	{
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},
	// 1~4:L字型のパネル
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{1, 1, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},
	{
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 1, 1},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{1, 1, 1, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
	// 5~6:I字型のパネル
	{
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
	// 7~10:イベント部屋のパネル
	{
		{0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 0},
		{0, 0, 1, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 1},
		{0, 1, 1, 1, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{0, 0, 1, 0, 0},
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 0},
		{0, 1, 1, 1, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 1, 1, 1, 0},
		{1, 1, 1, 1, 0},
		{0, 1, 1, 1, 0},
		{0, 0, 0, 0, 0}
	},
	// 11~14:T字のパネル
	{
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{1, 1, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},
	{
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 1, 1},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},
	{
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
};

/// <summary>
/// Constructor
/// </summary>
MapGenerator::MapGenerator(SceneBace* pScene, int width) noexcept
	: ObjectBace(pScene)
	, m_Width{ width }
{
}

/// <summary>
/// Destructor
/// </summary>
MapGenerator::~MapGenerator() noexcept = default;

/// <summary>
/// 初期化処理
/// </summary>
void MapGenerator::Initialize()
{
	/*マップの自動生成*/
	GenerateMap();

	/*オブジェクトの生成*/
	GenerateObject();
}

/// <summary>
/// 更新処理
/// </summary>
void MapGenerator::Process(float elapsedTime)
{
	// 警告回避用
	elapsedTime;
}

/// <summary>
/// マップデータの自動生成
/// </summary>
void MapGenerator::GenerateMap()
{
	// パネルデータの読み込み
	std::vector<PanelData> PanelDatas;
	// 0:十字路のパネル
	PanelDatas.push_back(PanelData(Datas[0], 300));
	// 1~4:L字型のパネル
	PanelDatas.push_back(PanelData(Datas[1], 350));
	PanelDatas.push_back(PanelData(Datas[2], 380));
	PanelDatas.push_back(PanelData(Datas[3], 430));
	PanelDatas.push_back(PanelData(Datas[4], 480));
	// 5~6:I字型のパネル
	PanelDatas.push_back(PanelData(Datas[5], 580));
	PanelDatas.push_back(PanelData(Datas[6], 680));
	// 7~10:イベント部屋のパネル
	PanelDatas.push_back(PanelData(Datas[7], 710));
	PanelDatas.push_back(PanelData(Datas[8], 740));
	PanelDatas.push_back(PanelData(Datas[9], 770));
	PanelDatas.push_back(PanelData(Datas[10], 800));
	// 11~14:T字のパネル
	PanelDatas.push_back(PanelData(Datas[11], 850));
	PanelDatas.push_back(PanelData(Datas[12], 900));
	PanelDatas.push_back(PanelData(Datas[13], 950));
	PanelDatas.push_back(PanelData(Datas[14]));

	std::vector<PanelData> MapDataA;

	while (true)
	{
		// マップデータの生成
		for (int i{ 0 }; i < m_Width * m_Width; i++)
		{
			bool next{ false };

			while (!next)
			{
				int randomNumber = rand() % 1000;

				for (int j{ 0 }; j < PanelDatas.size(); j++)
				{
					if (randomNumber < PanelDatas[j].GetParcent())
					{
						// パネルを当てはまられる条件を確認
						if (i == m_Width * m_Width - 1)
						{
							// ゴールのパネル
							int GoalPanel[PanelWidth][PanelWidth]
							{
								{0, 0, 1, 0, 0},
								{0, 1, 1, 1, 0},
								{1, 1, 1, 1, 0},
								{0, 1, 1, 1, 0},
								{0, 0, 0, 0, 0}
							};
							MapDataA.push_back(PanelData(GoalPanel));
							next = true;
						}
						else if (i > 0)
						{
							// マップ右上の角
							if (i + 1 == m_Width)
							{
								if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (PanelDatas[j].GetHoalData().up == false) && (PanelDatas[j].GetHoalData().right == false))
								{
									MapDataA.push_back(PanelDatas[j]);
									next = true;
								}
							}
							// マップ最上部
							else if (i < m_Width)
							{
								if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (PanelDatas[j].GetHoalData().up == false))
								{
									MapDataA.push_back(PanelDatas[j]);
									next = true;
								}
							}
							// マップ最下部
							else if (i >= m_Width * (m_Width - 1))
							{
								if (i % m_Width == 0)
								{
									if ((PanelDatas[j].GetHoalData().left == false) && (MapDataA[MapDataA.size() - m_Width].GetHoalData().down == PanelDatas[j].GetHoalData().up) && (PanelDatas[j].GetHoalData().down == false))
									{
										MapDataA.push_back(PanelDatas[j]);
										next = true;
									}
								}
								else if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (MapDataA[MapDataA.size() - m_Width].GetHoalData().down == PanelDatas[j].GetHoalData().up) && (PanelDatas[j].GetHoalData().down == false))
								{
									MapDataA.push_back(PanelDatas[j]);
									next = true;
								}
							}
							// マップ最右部
							else if ((i + 1) % m_Width == 0)
							{
								if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (MapDataA[MapDataA.size() - m_Width].GetHoalData().down == PanelDatas[j].GetHoalData().up) && (PanelDatas[j].GetHoalData().right == false))
								{
									MapDataA.push_back(PanelDatas[j]);
									next = true;
								}
							}
							else
							{
								if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (MapDataA[MapDataA.size() - m_Width].GetHoalData().down == PanelDatas[j].GetHoalData().up))
								{
									MapDataA.push_back(PanelDatas[j]);
									next = true;
								}
							}
						}
						else
						{
							// スタート地点のパネル
							int StartPanel[PanelWidth][PanelWidth]
							{
								{0, 0, 0, 0, 0},
								{0, 1, 1, 1, 0},
								{0, 1, 2, 1, 1},
								{0, 1, 1, 1, 0},
								{0, 0, 1, 0, 0}
							};
							MapDataA.push_back(PanelData(StartPanel));
							next = true;
						}

						break;
					}
				}
			}
		}

		// マップデータをINT型のマトリックス変数のマップデータに変換
		for (int i{ 0 }; i < m_Width; i++)
		{
			for (int j{ 0 }; j < PanelWidth; j++)
			{
				std::vector<int> MapWidthData;
				for (int k{ 0 }; k < m_Width; k++)
				{
					for (int l{ 0 }; l < PanelWidth; l++)
					{
						MapWidthData.push_back(MapDataA[i * m_Width + k].GetTileData(l, j));
					}
				}
				m_MapData.push_back(MapWidthData);
			}
		}

		// マップの正規化
		if (GetNormalizedPathMap(&m_MapData, 0, 2, 2, m_Width * PanelWidth - 3, m_Width * PanelWidth - 3))
			break;
		else
		{
			MapDataA.clear();
			m_MapData.clear();
		}
	}
}

/// <summary>
/// マップデータからオブジェクトを生成する
/// </summary>
void MapGenerator::GenerateObject()
{
	// マップ上のオブジェクトを生成する
	for (int i{ 0 }, c{ 0 }; i < m_MapData.size(); i++)
	{
		for (int j{ 0 }; j < m_MapData[i].size(); j++)
		{
			if (m_MapData[i][j] == 0)
			{
				// 空間がある場合はコライダーを生成する
				if ((i - 1 >= 0 && m_MapData[i - 1][j] != 0) || (i + 1 < m_MapData.size() && m_MapData[i + 1][j] != 0) || (j - 1 >= 0 && m_MapData[i][j - 1] != 0) || (j + 1 < m_MapData[i].size() && m_MapData[i][j + 1] != 0))
					mp_ObjectManager->AddObject
					(std::string("WallCollider") + std::to_string(c++),
						std::make_unique<Box>
						(
							mp_Scene,
							DirectX::SimpleMath::Vector3((i - m_MapData.size() / 2.f) * 3.5f, 0.f, (j - m_MapData.size() / 2.f) * 3.5f)
						)
					);

				// モデルのY座標
				static constexpr float ModelPosY{ 1.3f };

				// 空間のある方向に壁を設置する
				if (i - 1 >= 0 && m_MapData[i - 1][j] != 0)
				{
					mp_ObjectManager->AddObject
					(std::string("WallModel") + std::to_string(c++),
						std::make_unique<Wall>
						(
							mp_Scene,
							DirectX::SimpleMath::Vector3((i - 0.5f - m_MapData.size() / 2.f) * 3.5f, ModelPosY, (j - m_MapData.size() / 2.f) * 3.5f),
							DirectX::SimpleMath::Vector3(0.f, DirectX::XM_PI, 0.f)
						)
					);
				}

				if (i + 1 < m_MapData.size() && m_MapData[i + 1][j] != 0)
				{
					mp_ObjectManager->AddObject
					(std::string("WallModel") + std::to_string(c++),
						std::make_unique<Wall>
						(
							mp_Scene,
							DirectX::SimpleMath::Vector3((i + 0.5f - m_MapData.size() / 2.f) * 3.5f, ModelPosY, (j - m_MapData.size() / 2.f) * 3.5f)
						)
					);
				}

				if (j - 1 >= 0 && m_MapData[i][j - 1] != 0)
				{
					mp_ObjectManager->AddObject
					(std::string("WallModel") + std::to_string(c++),
						std::make_unique<Wall>
						(
							mp_Scene,
							DirectX::SimpleMath::Vector3((i - m_MapData.size() / 2.f) * 3.5f, ModelPosY, (j - 0.5f - m_MapData.size() / 2.f) * 3.5f),
							DirectX::SimpleMath::Vector3(0.f, DirectX::XM_PI / 2.f, 0.f)
						)
					);
				}

				if (j + 1 < m_MapData[i].size() && m_MapData[i][j + 1] != 0)
				{
					mp_ObjectManager->AddObject
					(std::string("WallModel") + std::to_string(c++),
						std::make_unique<Wall>
						(
							mp_Scene,
							DirectX::SimpleMath::Vector3((i - m_MapData.size() / 2.f) * 3.5f, ModelPosY, (j + 0.5f - m_MapData.size() / 2.f) * 3.5f),
							DirectX::SimpleMath::Vector3(0.f, DirectX::XM_PI / -2.f, 0.f)
						)
					);
				}

				// 角となる部分に柱を設置
				if (i - 1 >= 0 && m_MapData[i - 1][j] != 0)
				{
					if (j - 1 >= 0 && m_MapData[i][j - 1] != 0)
					{
						mp_ObjectManager->AddObject
						(std::string("CylinderModel") + std::to_string(c++),
							std::make_unique<Cylinder>
							(
								mp_Scene,
								DirectX::SimpleMath::Vector3((i - 0.5f - m_MapData.size() / 2.f) * 3.5f, ModelPosY, (j - 0.5f - m_MapData.size() / 2.f) * 3.5f)
							)
						);
					}

					if (j + 1 < m_MapData[i].size() && m_MapData[i][j + 1] != 0)
					{
						mp_ObjectManager->AddObject
						(std::string("CylinderModel") + std::to_string(c++),
							std::make_unique<Cylinder>
							(
								mp_Scene,
								DirectX::SimpleMath::Vector3((i - 0.5f - m_MapData.size() / 2.f) * 3.5f, ModelPosY, (j + 0.5f - m_MapData.size() / 2.f) * 3.5f)
							)
						);
					}
				}


				if (i + 1 < m_MapData.size() && m_MapData[i + 1][j] != 0)
				{
					if (j - 1 >= 0 && m_MapData[i][j - 1] != 0)
					{
						mp_ObjectManager->AddObject
						(std::string("CylinderModel") + std::to_string(c++),
							std::make_unique<Cylinder>
							(
								mp_Scene,
								DirectX::SimpleMath::Vector3((i + 0.5f - m_MapData.size() / 2.f) * 3.5f, ModelPosY, (j - 0.5f - m_MapData.size() / 2.f) * 3.5f)
							)
						);
					}

					if (j + 1 < m_MapData[i].size() && m_MapData[i][j + 1] != 0)
					{
						mp_ObjectManager->AddObject
						(std::string("CylinderModel") + std::to_string(c++),
							std::make_unique<Cylinder>
							(
								mp_Scene,
								DirectX::SimpleMath::Vector3((i + 0.5f - m_MapData.size() / 2.f) * 3.5f, ModelPosY, (j + 0.5f - m_MapData.size() / 2.f) * 3.5f)
							)
						);
					}
				}
			}
			else 
			{
				// 床の作成
				mp_ObjectManager->AddObject
				(std::string("FloorModel") + std::to_string(c++),
					std::make_unique<Floor>
					(
						mp_Scene,
						DirectX::SimpleMath::Vector3((i - m_MapData.size() / 2.f) * 3.5f, -0.5f, (j - m_MapData.size() / 2.f) * 3.5f)
					)
				);

				if (m_MapData[i][j] == 2)
				{
					Transform* pPlayer = static_cast<Transform*>(mp_ObjectManager->GetObjectPtr("Player")->GetComponentPtr("Transform"));

					pPlayer->SetPosition(DirectX::SimpleMath::Vector3((i - m_MapData.size() / 2.f) * 3.5f, 0.f, (j - m_MapData.size() / 2.f) * 3.5f));
				}

			}
		}
	}
}



/*Panel Data*/

/// <summary>
/// Constructor
/// </summary>
PanelData::PanelData(int data[PanelWidth][PanelWidth], int popParcent)
	: m_tileDatas{}
	, m_hoal     {}
	, m_parcent  { popParcent }
{
	// パネルデータの読み込み
	for (int i{ 0 }; i < PanelWidth; i++)
	{
		for (int j{ 0 }; j < PanelWidth; j++)
		{
			m_tileDatas[i][j] = data[i][j];
		}
	}

	// パネルの「穴」を保存する
	m_hoal.up = (m_tileDatas[0][PanelWidth / 2] != 0);
	m_hoal.down = (m_tileDatas[PanelWidth - 1][PanelWidth / 2] != 0);
	m_hoal.left = (m_tileDatas[PanelWidth / 2][0] != 0);
	m_hoal.right = (m_tileDatas[PanelWidth / 2][PanelWidth - 1] != 0);
}

/// <summary>
/// Destructor
/// </summary>
PanelData::~PanelData() = default;

/// <summary>
/// タイルデータの読み取り
/// </summary>
int PanelData::GetTileData(int x, int y)
{
	return m_tileDatas[y][x];
}





/// <summary>
/// マップの正規化とゴール到達が可能かを行う
/// </summary>
/// <param name="_map">正規化するマップ</param>
/// <returns>ゴールにたどり着けるかどうか</returns>
bool GetNormalizedPathMap(std::vector<std::vector<int>>* _map, const int _wallNumber, const int _startX, const int _startY, const int _goalX, const int _goalY)
{
	// 座標の構造体
	struct Point
	{
		int x;
		int y;
	};

	// 引数の座標を構造体へ変換
	Point startPoint{ _startX, _startY };
	Point goalPoint{ _goalX , _goalY };

	// もし、スタート座標かゴール座標が壁だったらfalseで終了
	if ((*_map)[startPoint.x][startPoint.y] == _wallNumber || (*_map)[goalPoint.x][goalPoint.y] == _wallNumber)
		return false;

	// マップデータをコピーする
	std::vector<std::vector<int>> PaintMap{ *_map };

	// スタート地点を塗り、それ以外を無色の状態にする
	static constexpr int NONE{ 0 };
	static constexpr int PAINT{ 1 };

	for (int i{ 0 }; i < PaintMap.size(); i++)
		for (int j{ 0 }; j < PaintMap[i].size(); j++)
			PaintMap[i][j] = NONE;

	PaintMap[startPoint.x][startPoint.y] = PAINT;

	// マップを見ながら通れる部分に塗りを広げていく
	std::vector<Point> Paintings{ startPoint };

	while (true)
	{
		// 次に塗る予定の座標
		std::vector<Point> NextPaintings;

		// 次に塗る予定の座標を保存する
		for (int i{ 0 }; i < Paintings.size(); i++)
		{
			NextPaintings.push_back({ Paintings[i].x - 1, Paintings[i].y });
			NextPaintings.push_back({ Paintings[i].x + 1, Paintings[i].y });
			NextPaintings.push_back({ Paintings[i].x    , Paintings[i].y - 1 });
			NextPaintings.push_back({ Paintings[i].x    , Paintings[i].y + 1 });
		}

		// マップの情報と塗りマップを見ながら塗れない座標を省きながら塗っていく
		for (int i{ 0 }; i < NextPaintings.size(); i++)
		{
			bool isDelete = (
				// すでに塗られていた
				PaintMap[NextPaintings[i].x][NextPaintings[i].y] == PAINT ||
				// 壁だった
				(*_map)[NextPaintings[i].x][NextPaintings[i].y] == _wallNumber);

			// 省く処理
			if (isDelete)
			{
				NextPaintings.erase(NextPaintings.begin() + i);
				i--;
			}
			// 塗る処理
			else
			{
				PaintMap[NextPaintings[i].x][NextPaintings[i].y] = PAINT;
			}
		}

		// 塗った座標を保存
		Paintings = NextPaintings;
		NextPaintings.clear();

		// 塗った座補油が無ければ終了
		if (Paintings.size() <= 0)
			break;
	}

	// ゴールが塗られていなかったらfalseで終了
	if (PaintMap[goalPoint.x][goalPoint.y] == NONE)
		return false;

	// 塗られていない部分をすべて壁に置き替えながらマップを正規化
	for (int i{ 0 };i < _map->size(); i++)
		for (int j{ 0 }; j < (*_map)[i].size(); j++)
			if (PaintMap[i][j] == NONE)
				(*_map)[i][j] = _wallNumber;

	// 正常終了
	return true;
}
