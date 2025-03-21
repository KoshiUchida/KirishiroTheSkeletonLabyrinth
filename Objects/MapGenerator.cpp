/**
 * @file   MapGenerator.cpp
 *
 * @brief  �}�b�v�W�F�l���[�^�[�̃\�[�X�t�@�C��
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

 // �p�l���̃f�[�^���쐬
int Datas[][PanelWidth][PanelWidth]
{
	// 0:�\���H�̃p�l��
	{
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0}
	},
	// 1~4:L���^�̃p�l��
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
	// 5~6:I���^�̃p�l��
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
	// 7~10:�C�x���g�����̃p�l��
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
	// 11~14:T���̃p�l��
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
/// ����������
/// </summary>
void MapGenerator::Initialize()
{
	/*�}�b�v�̎�������*/
	GenerateMap();

	/*�I�u�W�F�N�g�̐���*/
	GenerateObject();
}

/// <summary>
/// �X�V����
/// </summary>
void MapGenerator::Process(float elapsedTime)
{
	// �x�����p
	elapsedTime;
}

/// <summary>
/// �}�b�v�f�[�^�̎�������
/// </summary>
void MapGenerator::GenerateMap()
{
	// �p�l���f�[�^�̓ǂݍ���
	std::vector<PanelData> PanelDatas;
	// 0:�\���H�̃p�l��
	PanelDatas.push_back(PanelData(Datas[0], 300));
	// 1~4:L���^�̃p�l��
	PanelDatas.push_back(PanelData(Datas[1], 350));
	PanelDatas.push_back(PanelData(Datas[2], 380));
	PanelDatas.push_back(PanelData(Datas[3], 430));
	PanelDatas.push_back(PanelData(Datas[4], 480));
	// 5~6:I���^�̃p�l��
	PanelDatas.push_back(PanelData(Datas[5], 580));
	PanelDatas.push_back(PanelData(Datas[6], 680));
	// 7~10:�C�x���g�����̃p�l��
	PanelDatas.push_back(PanelData(Datas[7], 710));
	PanelDatas.push_back(PanelData(Datas[8], 740));
	PanelDatas.push_back(PanelData(Datas[9], 770));
	PanelDatas.push_back(PanelData(Datas[10], 800));
	// 11~14:T���̃p�l��
	PanelDatas.push_back(PanelData(Datas[11], 850));
	PanelDatas.push_back(PanelData(Datas[12], 900));
	PanelDatas.push_back(PanelData(Datas[13], 950));
	PanelDatas.push_back(PanelData(Datas[14]));

	std::vector<PanelData> MapDataA;

	while (true)
	{
		// �}�b�v�f�[�^�̐���
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
						// �p�l���𓖂Ă͂܂���������m�F
						if (i == m_Width * m_Width - 1)
						{
							// �S�[���̃p�l��
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
							// �}�b�v�E��̊p
							if (i + 1 == m_Width)
							{
								if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (PanelDatas[j].GetHoalData().up == false) && (PanelDatas[j].GetHoalData().right == false))
								{
									MapDataA.push_back(PanelDatas[j]);
									next = true;
								}
							}
							// �}�b�v�ŏ㕔
							else if (i < m_Width)
							{
								if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (PanelDatas[j].GetHoalData().up == false))
								{
									MapDataA.push_back(PanelDatas[j]);
									next = true;
								}
							}
							// �}�b�v�ŉ���
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
							// �}�b�v�ŉE��
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
							// �X�^�[�g�n�_�̃p�l��
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

		// �}�b�v�f�[�^��INT�^�̃}�g���b�N�X�ϐ��̃}�b�v�f�[�^�ɕϊ�
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

		// �}�b�v�̐��K��
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
/// �}�b�v�f�[�^����I�u�W�F�N�g�𐶐�����
/// </summary>
void MapGenerator::GenerateObject()
{
	// �}�b�v��̃I�u�W�F�N�g�𐶐�����
	for (int i{ 0 }, c{ 0 }; i < m_MapData.size(); i++)
	{
		for (int j{ 0 }; j < m_MapData[i].size(); j++)
		{
			if (m_MapData[i][j] == 0)
			{
				// ��Ԃ�����ꍇ�̓R���C�_�[�𐶐�����
				if ((i - 1 >= 0 && m_MapData[i - 1][j] != 0) || (i + 1 < m_MapData.size() && m_MapData[i + 1][j] != 0) || (j - 1 >= 0 && m_MapData[i][j - 1] != 0) || (j + 1 < m_MapData[i].size() && m_MapData[i][j + 1] != 0))
					mp_ObjectManager->AddObject
					(std::string("WallCollider") + std::to_string(c++),
						std::make_unique<Box>
						(
							mp_Scene,
							DirectX::SimpleMath::Vector3((i - m_MapData.size() / 2.f) * 3.5f, 0.f, (j - m_MapData.size() / 2.f) * 3.5f)
						)
					);

				// ���f����Y���W
				static constexpr float ModelPosY{ 1.3f };

				// ��Ԃ̂�������ɕǂ�ݒu����
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

				// �p�ƂȂ镔���ɒ���ݒu
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
				// ���̍쐬
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
	// �p�l���f�[�^�̓ǂݍ���
	for (int i{ 0 }; i < PanelWidth; i++)
	{
		for (int j{ 0 }; j < PanelWidth; j++)
		{
			m_tileDatas[i][j] = data[i][j];
		}
	}

	// �p�l���́u���v��ۑ�����
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
/// �^�C���f�[�^�̓ǂݎ��
/// </summary>
int PanelData::GetTileData(int x, int y)
{
	return m_tileDatas[y][x];
}





/// <summary>
/// �}�b�v�̐��K���ƃS�[�����B���\�����s��
/// </summary>
/// <param name="_map">���K������}�b�v</param>
/// <returns>�S�[���ɂ��ǂ蒅���邩�ǂ���</returns>
bool GetNormalizedPathMap(std::vector<std::vector<int>>* _map, const int _wallNumber, const int _startX, const int _startY, const int _goalX, const int _goalY)
{
	// ���W�̍\����
	struct Point
	{
		int x;
		int y;
	};

	// �����̍��W���\���̂֕ϊ�
	Point startPoint{ _startX, _startY };
	Point goalPoint{ _goalX , _goalY };

	// �����A�X�^�[�g���W���S�[�����W���ǂ�������false�ŏI��
	if ((*_map)[startPoint.x][startPoint.y] == _wallNumber || (*_map)[goalPoint.x][goalPoint.y] == _wallNumber)
		return false;

	// �}�b�v�f�[�^���R�s�[����
	std::vector<std::vector<int>> PaintMap{ *_map };

	// �X�^�[�g�n�_��h��A����ȊO�𖳐F�̏�Ԃɂ���
	static constexpr int NONE{ 0 };
	static constexpr int PAINT{ 1 };

	for (int i{ 0 }; i < PaintMap.size(); i++)
		for (int j{ 0 }; j < PaintMap[i].size(); j++)
			PaintMap[i][j] = NONE;

	PaintMap[startPoint.x][startPoint.y] = PAINT;

	// �}�b�v�����Ȃ���ʂ�镔���ɓh����L���Ă���
	std::vector<Point> Paintings{ startPoint };

	while (true)
	{
		// ���ɓh��\��̍��W
		std::vector<Point> NextPaintings;

		// ���ɓh��\��̍��W��ۑ�����
		for (int i{ 0 }; i < Paintings.size(); i++)
		{
			NextPaintings.push_back({ Paintings[i].x - 1, Paintings[i].y });
			NextPaintings.push_back({ Paintings[i].x + 1, Paintings[i].y });
			NextPaintings.push_back({ Paintings[i].x    , Paintings[i].y - 1 });
			NextPaintings.push_back({ Paintings[i].x    , Paintings[i].y + 1 });
		}

		// �}�b�v�̏��Ɠh��}�b�v�����Ȃ���h��Ȃ����W���Ȃ��Ȃ���h���Ă���
		for (int i{ 0 }; i < NextPaintings.size(); i++)
		{
			bool isDelete = (
				// ���łɓh���Ă���
				PaintMap[NextPaintings[i].x][NextPaintings[i].y] == PAINT ||
				// �ǂ�����
				(*_map)[NextPaintings[i].x][NextPaintings[i].y] == _wallNumber);

			// �Ȃ�����
			if (isDelete)
			{
				NextPaintings.erase(NextPaintings.begin() + i);
				i--;
			}
			// �h�鏈��
			else
			{
				PaintMap[NextPaintings[i].x][NextPaintings[i].y] = PAINT;
			}
		}

		// �h�������W��ۑ�
		Paintings = NextPaintings;
		NextPaintings.clear();

		// �h�����������������ΏI��
		if (Paintings.size() <= 0)
			break;
	}

	// �S�[�����h���Ă��Ȃ�������false�ŏI��
	if (PaintMap[goalPoint.x][goalPoint.y] == NONE)
		return false;

	// �h���Ă��Ȃ����������ׂĕǂɒu���ւ��Ȃ���}�b�v�𐳋K��
	for (int i{ 0 };i < _map->size(); i++)
		for (int j{ 0 }; j < (*_map)[i].size(); j++)
			if (PaintMap[i][j] == NONE)
				(*_map)[i][j] = _wallNumber;

	// ����I��
	return true;
}
