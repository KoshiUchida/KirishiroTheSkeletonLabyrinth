/**
 * @file   MapGenerator.h
 *
 * @brief  �}�b�v�W�F�l���[�^�[�̃w�b�_�[�t�@�C��
 *
 * @author CatCode
 */

#pragma once
#include "ObjectBace.h"

/// <summary>
/// �p�l���̈�ӂ̃}�X��
/// </summary>
static constexpr int PanelWidth{ 5 };

/// <summary>
/// �}�b�v�����@�N���X
/// </summary>
class MapGenerator :
    public ObjectBace
{
private:
	// �}�b�v��ӂ̃p�l���̐�
	int m_Width{ 5 };

	// �}�b�v�f�[�^
	std::vector<std::vector<int>> m_MapData;

public:
	// Main System
	MapGenerator(SceneBace* pScene, int width = 5) noexcept;
	~MapGenerator() noexcept;

	void Initialize() override final;
	void Process(float elapsedTime) override final;

private:
	// ��������
	void GenerateMap();
	void GenerateObject();
};

class PanelData
{
private:
	// �p�l���̃^�C�����
	int m_tileDatas[PanelWidth][PanelWidth];

	// �u���v�̏��
	struct Hoal
	{
		bool up;
		bool down;
		bool left;
		bool right;
	} m_hoal;

	// ���̃p�l���̊m��
	int m_parcent;

public:
	PanelData(int data[PanelWidth][PanelWidth], int popParcent = 1000);
	~PanelData();

	int GetTileData(int x, int y);
	int  GetParcent()  const { return m_parcent; }
	Hoal GetHoalData() const { return m_hoal; }
};

bool GetNormalizedPathMap(std::vector<std::vector<int>>* _map, const int _wallNumber, const int _startX, const int _startY, const int _goalX, const int _goalY);
