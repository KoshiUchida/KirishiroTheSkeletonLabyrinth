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

/// <summary>
/// Constructor
/// </summary>
MapGenerator::MapGenerator(SceneBace* pScene) noexcept
	: ObjectBace(pScene)
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

	// �p�l���̃f�[�^���쐬
	int datas[][PanelWidth][PanelWidth]
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

	// �p�l���f�[�^�̓ǂݍ���
	std::vector<PanelData> PanelDatas;
	// 0:�\���H�̃p�l��
	PanelDatas.push_back(PanelData(datas[0], 300));
	// 1~4:L���^�̃p�l��
	PanelDatas.push_back(PanelData(datas[1], 350));
	PanelDatas.push_back(PanelData(datas[2], 380));
	PanelDatas.push_back(PanelData(datas[3], 430));
	PanelDatas.push_back(PanelData(datas[4], 480));
	// 5~6:I���^�̃p�l��
	PanelDatas.push_back(PanelData(datas[5], 580));
	PanelDatas.push_back(PanelData(datas[6], 680));
	// 7~10:�C�x���g�����̃p�l��
	PanelDatas.push_back(PanelData(datas[7], 710));
	PanelDatas.push_back(PanelData(datas[8], 740));
	PanelDatas.push_back(PanelData(datas[9], 770));
	PanelDatas.push_back(PanelData(datas[10], 800));
	// 11~14:T���̃p�l��
	PanelDatas.push_back(PanelData(datas[11], 850));
	PanelDatas.push_back(PanelData(datas[12], 900));
	PanelDatas.push_back(PanelData(datas[13], 950));
	PanelDatas.push_back(PanelData(datas[14]));

	std::vector<PanelData> MapDataA;
	std::vector<std::vector<int>> MapData;

	while (true)
	{
		// �}�b�v�f�[�^�̐���
		for (int i{ 0 }; i < Width * Width; i++)
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
						if (i == Width * Width - 1)
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
							if (i + 1 == Width)
							{
								if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (PanelDatas[j].GetHoalData().up == false) && (PanelDatas[j].GetHoalData().right == false))
								{
									MapDataA.push_back(PanelDatas[j]);
									next = true;
								}
							}
							// �}�b�v�ŏ㕔
							else if (i < Width)
							{
								if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (PanelDatas[j].GetHoalData().up == false))
								{
									MapDataA.push_back(PanelDatas[j]);
									next = true;
								}
							}
							// �}�b�v�ŉ���
							else if (i >= Width * (Width - 1))
							{
								if (i % Width == 0)
								{
									if ((PanelDatas[j].GetHoalData().left == false) && (MapDataA[MapDataA.size() - Width].GetHoalData().down == PanelDatas[j].GetHoalData().up) && (PanelDatas[j].GetHoalData().down == false))
									{
										MapDataA.push_back(PanelDatas[j]);
										next = true;
									}
								}
								else if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (MapDataA[MapDataA.size() - Width].GetHoalData().down == PanelDatas[j].GetHoalData().up) && (PanelDatas[j].GetHoalData().down == false))
								{
									MapDataA.push_back(PanelDatas[j]);
									next = true;
								}
							}
							// �}�b�v�ŉE��
							else if ((i + 1) % Width == 0)
							{
								if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (MapDataA[MapDataA.size() - Width].GetHoalData().down == PanelDatas[j].GetHoalData().up) && (PanelDatas[j].GetHoalData().right == false))
								{
									MapDataA.push_back(PanelDatas[j]);
									next = true;
								}
							}
							else
							{
								if ((MapDataA[MapDataA.size() - 1].GetHoalData().right == PanelDatas[j].GetHoalData().left) && (MapDataA[MapDataA.size() - Width].GetHoalData().down == PanelDatas[j].GetHoalData().up))
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
								{0, 1, 1, 1, 1},
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
		for (int i{ 0 }; i < Width; i++)
		{
			for (int j{ 0 }; j < PanelWidth; j++)
			{
				std::vector<int> MapWidthData;
				for (int k{ 0 }; k < Width; k++)
				{
					for (int l{ 0 }; l < PanelWidth; l++)
					{
						MapWidthData.push_back(MapDataA[i * Width + k].GetTileData(l, j));
					}
				}
				MapData.push_back(MapWidthData);
			}
		}

		// �}�b�v�̐��K��
		if (GetNormalizedPathMap(&MapData, 0, 2, 2, Width * PanelWidth - 3, Width * PanelWidth - 3))
			break;
		else
		{
			MapDataA.clear();
			MapData.clear();
		}
	}

	// �}�b�v��̃I�u�W�F�N�g�𐶐�����
	for (int i{ 0 }, c{ 0 }; i < MapData.size(); i++)
		for (int j{ 0 }; j < MapData[i].size(); j++, c++)
			if (MapData[i][j] == 0)
				mp_ObjectManager->AddObject
				(std::string("Wall") + std::to_string(c),
					std::make_unique<Box>
					(
						mp_Scene,
						DirectX::SimpleMath::Vector3((i - MapData.size() / 2.f) * 6.f, 3.f, (j - MapData.size() / 2.f) * 6.f)
					)
				);
}

/// <summary>
/// �X�V����
/// </summary>
void MapGenerator::Process(float elapsedTime)
{
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
