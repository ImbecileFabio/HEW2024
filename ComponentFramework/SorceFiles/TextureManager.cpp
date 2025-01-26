//=================================================================
// [TextureManager.cpp] �e�N�X�`���Ǘ��N���X
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F����Ȋ���
//=================================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include "TextureManager.h"
#include "TileMapManager.h"
#include "SubSystem/stb_image.h"
#include "Renderer.h"

//-----------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------
TextureManager::TextureManager()
{
}

//-----------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------
TextureManager::~TextureManager()
{
	this->ClearCache();
}

void TextureManager::RegisterTextureInfo(const std::string& _textureName, const TextureInfo& _textureInfo)
{
	texture_info_[_textureName] = _textureInfo;
}

//-----------------------------------------------------------------
// ����������
//-----------------------------------------------------------------
void TextureManager::Init()
{
	RegisterAllTextures();
}

//-----------------------------------------------------------------
// �I������
//-----------------------------------------------------------------
void TextureManager::Uninit()
{
	ClearCache();
}


//-----------------------------------------------------------------
// @param  _imgName �摜��, _fileName �t�@�C���p�X
// @brief  �e�N�X�`���̓o�^
//-----------------------------------------------------------------
// �A�j���[�V�����t��
void TextureManager::RegisterTexture(const std::string& _imgName, const std::string& _fileName, bool _loopFlg, int _cutU, int _cutV, float _anmSpeed)
{
	RegisterTexture(_imgName, _fileName, DirectX::SimpleMath::Vector2(0.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f), _loopFlg, _cutU, _cutV, _anmSpeed);
}
// ���ׂ�
void TextureManager::RegisterTexture(const std::string& _textureName, const std::string& _fileName, const DirectX::SimpleMath::Vector2& _offsetPos, const DirectX::SimpleMath::Vector2& _offsetSize, bool _loopFlg, int _cutU, int _cutV, float _anmSpeed)
{
	texture_info_[_textureName] = { _fileName, _offsetPos, _offsetSize, _loopFlg, _cutU, _cutV, _anmSpeed };
}

//-----------------------------------------------------------------
// @param  _imgName �摜��
// @brief  �ǂݍ��񂾃e�N�X�`���̎擾
// @return ���݂��Ă����it->second, �Ȃ���ΐ�������texture, �����ł��Ȃ����nullptr
//-----------------------------------------------------------------
std::shared_ptr<Texture> TextureManager::GetTexture(const std::string& _texrureName)
{
	// ���łɓǂݍ��܂�Ă��邩�m�F
	auto it = texture_cache_.find(_texrureName);
	if (it != texture_cache_.end())
	{
		// ���łɓǂݍ��܂�Ă���
		std::cout << std::format("\n��TextureManager�� -> {} is already loaded\n\n", _texrureName);
		return it->second;
	}

	// ���݂��Ă��Ȃ��̂Ő�������
	auto texInfo = texture_info_[_texrureName];
	auto texture = std::make_shared<Texture>(texInfo.offsetPos, texInfo.offsetSize, texInfo.loop, texInfo.cutU, texInfo.cutV, texInfo.animationSpeed);
	if (texture->Load(texInfo.filePath)) {
		// �L���b�V���ɓo�^
		texture_cache_[_texrureName] = texture;
		std::cout << std::format("��TextureManager�� -> {} GetTexture Success\n", _texrureName);
		return texture;
	}

	// ���s
	std::cout << std::format("��TextureManager�� -> {} GetTexture Error\n", _texrureName);
	return nullptr;

}

//-----------------------------------------------------------------
// @brief  ���ׂẴe�N�X�`����o�^����
// 
// �e�N�X�`����offset��ݒ肷���
// 
// �|�W�V����: ��px���点�΃I�u�W�F�N�g�̒��S�ɂȂ邩
// ��F �摜�̃T�C�Y�̍����� 80px �ŁA�I�u�W�F�N�g�̉e����� 10px�A���� 6px ����ꍇ
//		������� 2px ���点�΂����̂�
//		{0.0f, 2.0f} ���L�q���ĂˁB
//
// �T�C�Y: �摜�T�C�Y�����{�ɂ���΃^�C���̃T�C�Y�ɍ�����
// ��F �摜�̃T�C�Y������ 80px �ŁA�e���������I�u�W�F�N�g�̃T�C�Y�� 64px �̏ꍇ
// 		�I�u�W�F�N�g�̃T�C�Y�� 80px �ɂ������̂ŁA
//		80 / 64 = 1.25f �� {1.0f, 1.25f} ���L�q���ĂˁB
// 
// ���X���G�ł��߂�Ȃ���
//-----------------------------------------------------------------
void TextureManager::RegisterAllTextures()
{
	//���O���K���Ȃ��̑����̂Œ��������肢���܂�

	// Hogehoge
	RegisterTexture("hoge", TEXTURE_PATH"hogehoge.png");
	RegisterTexture("piyo", TEXTURE_PATH"piyo.jpg", true, 8, 12, 0.05f);

	
	// �C���Q�[���̃I�u�W�F�N�g�n
	/*--------------- ���{�b�g ---------------*/
	RegisterTexture("robot_drop" , TEXTURE_PATH"robot/v03/robot_dorp_01.png", false, 3, 1, 0.05f);	// ����
	RegisterTexture("robot_still", TEXTURE_PATH"robot/v03/robot_still_01.png");	// �Î~
	RegisterTexture("robot_walk" , TEXTURE_PATH"robot/v03/robot_walk_01.png", true, 2, 1, 0.5f);	// ���s

	/*--------------- �U��q ---------------*/
	RegisterTexture("ball", TEXTURE_PATH"huriko/v02/ball_01.png", {0.0f, 0.0f}, {1.25f, 1.25f});		// �{�[��
	RegisterTexture("stick", TEXTURE_PATH"huriko/v03/stick_01.png", {0.0f, 0.0f}, { 0.75f, 1.0f});	// �_

	/*--------------- �^�C�� ---------------*/
	// ��
	RegisterTexture("tile_center", TEXTURE_PATH"tile/v02/tile_center_01.png", { 0.0f, -3.0f }, {1.0f, 1.501f});	// ����
	RegisterTexture("tile_left", TEXTURE_PATH"tile/v02/tile_left_01.png", { -6.0f, -3.0f }, { 1.2f, 1.5f });	// ��
	RegisterTexture("tile_right", TEXTURE_PATH"tile/v02/tile_right_01.png", { 6.0f, -3.0f }, { 1.2f, 1.5f });	// �E
	// ��
	RegisterTexture("tile_wall", TEXTURE_PATH"tile/v02/tile_wall_01.png", { 13.0f, 0.0f }, { 1.48f, 1.0f });		// ��

	/*--------------- �M�~�b�N ---------------*/
	// ���t�g
	RegisterTexture("lift_floor_center", GIMMICK_PATH"lift/v02/lift_floor_center_01.png", { 0.0f, 8.0f }, { 1.0f, 1.25f });	// ����
	RegisterTexture("lift_floor_left", GIMMICK_PATH"lift/v02/lift_floor_left_01.png", { -7.9f, 8.0f }, { 1.25f, 1.25f });		// ��
	RegisterTexture("lift_floor_right", GIMMICK_PATH"lift/v02/lift_floor_right_01.png", {8.0f, 8.0f}, { 1.25f, 1.25f });	// �E
	RegisterTexture("lift_circle", GIMMICK_PATH"lift/v02/lift_circle_01.png");					// ���ߋ�
	RegisterTexture("lift_rail", GIMMICK_PATH"lift/v02/lift_rail_01.png");						// ���[��
	// �Ƃ��� �i�X���������́j
	RegisterTexture("weakfloor_center", GIMMICK_PATH"weakfloor/v01/weakfloor_center_01.png", { 0.0f, -3.0f }, {1.0f, 1.501f});	// ����
	RegisterTexture("weakfloor_left", GIMMICK_PATH"weakfloor/v01/weakfloor_left_01.png", { -6.0f, -3.0f }, { 1.2f, 1.5f });		// ��
	RegisterTexture("weakfloor_right", GIMMICK_PATH"weakfloor/v01/weakfloor_right_01.png", { 6.5f, -3.0f }, { 1.2f, 1.5f });	// �E
	// �S��
	RegisterTexture("steelpillar_floor_center", GIMMICK_PATH"steelpillar/v02/steelpillar_floor_center_01.png");			// ��, ����
	RegisterTexture("steelpillar_floor_end_01", GIMMICK_PATH"steelpillar/v02/steelpillar_floor_end_01.png");			// ��, ��
	RegisterTexture("steelpillar_floor_end_02", GIMMICK_PATH"steelpillar/v02/steelpillar_floor_end_02.png");			// ��, �E

	RegisterTexture("steelpillar_pillar_top", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_top_01.png");					// ��, ��
	RegisterTexture("steelpillar_pillar_bottom", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_bottom_01.png");			// ��, ��
	RegisterTexture("steelpillar_pillar_break", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_break_01.png");				// ��, ���
	RegisterTexture("steelpillar_pillar_normal", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_normal_01.png");			// ��, �ʏ�
	RegisterTexture("steelpillar_pillar_still", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_normal_01.png");			// ��, ����
	// ��
	RegisterTexture("smoke01", GIMMICK_PATH"smoke/v01/smoke_bace_back_01.png");		// ���̉�
	RegisterTexture("smoke02", GIMMICK_PATH"smoke/v01/smoke_bace_front_01.png");		// ���̎�O
	// ����
	//RegisterTexture("pulley", GIMMICK_PATH"pulley/v01/pulley_01.png");
	// �^�C���]�[��
	RegisterTexture("timezone", TEXTURE_PATH"kouka/v02/pendulum_area_01.png");	// ���~




	// ���̑��̔w�i�AUI�Ȃ�
	/*--------------- �o�b�N�h���b�v ---------------*/
	RegisterTexture("backdrop_01", TEXTURE_PATH"backdrop/v02/backdrop_01.png");
	RegisterTexture("backdrop_02", TEXTURE_PATH"backdrop/v02/backdrop_02.png");

	/*--------------- UI ---------------*/
	// �n���}�[
	RegisterTexture("hammer", UI_PATH"v01/hammer_01.png");
	// �q�b�g�G�t�F�N�g
	RegisterTexture("hammer_hit_effect", UI_PATH"v01/hit_effect_01.png", false, 4, 2);
	// �M�A
	RegisterTexture("gear", UI_PATH"v02/gear_01.png");
	// ����
	RegisterTexture("numbers", UI_PATH"v02/numbers_01.png", false, 4, 3);
	// �|�[�Y�{�^��
	RegisterTexture("pause_button", UI_PATH"v02/pause_button_01.png");
	// �X�e�[�WUI
	RegisterTexture("stageUI", UI_PATH"v02/stage_ui_01.png");
	/*--------------- SCENE ---------------*/
	// ��������摜
	RegisterTexture("instruction_window", SCENE_PATH"instruction/v02/window_instruction_01.png");
	// �`�[�����S
	//RegisterTexture("introduction_backdrop", SCENE_PATH"introduction/v01/backdrop_introduction_01.png");
	//RegisterTexture("introduction_teamlogo", SCENE_PATH"introduction/v01/teamlogo_01.png");
	// �I�v�V����
	RegisterTexture("option_window", SCENE_PATH"option/v01/window_option_01.png");
	RegisterTexture("option_return", SCENE_PATH"option/v01/return_option_01.png");
	RegisterTexture("option_frame_slider", SCENE_PATH"option/v01/frame_slider_01.png");
	RegisterTexture("option_stick_slider", SCENE_PATH"option/v01/color_stick_slider_01.png");
	RegisterTexture("option_bgm_button", SCENE_PATH"option/v01/button_bgm_01.png");
	RegisterTexture("option_se_button", SCENE_PATH"option/v01/button_se_01.png");
	RegisterTexture("option_ball_slider", SCENE_PATH"option/v01/ball_slider_01.png");
	RegisterTexture("option_arrow_right", SCENE_PATH"option/v01/arrow_right_01.png");
	RegisterTexture("option_arrow_left", SCENE_PATH"option/v01/arrow_left_01.png");
	// �|�[�Y
	RegisterTexture("pose_window", SCENE_PATH"pose/v01/window_pose_01.png");
	RegisterTexture("pose_return_game", SCENE_PATH"pose/v01/return_game_button_01.png");
	RegisterTexture("pose_restart", SCENE_PATH"pose/v01/restart_button_01.png");
	RegisterTexture("pose_select", SCENE_PATH"pose/v01/stage_select_button_01.png");
	RegisterTexture("pose_instruction", SCENE_PATH"pose/v01/instruction_button_01.png");
	RegisterTexture("pose_option", SCENE_PATH"pose/v01/option_button_01.png");

	// ���U���g
	RegisterTexture("result_backdrop", SCENE_PATH"result/v01/backdrop_result_01.png");
	RegisterTexture("result_front_ribbon", SCENE_PATH"result/v01/front_ribbon_01.png");
	RegisterTexture("result_select", SCENE_PATH"result/v01/select_button_01.png");
	RegisterTexture("result_next", SCENE_PATH"result/v01/next_button_01.png");
	// �^�C�g��
	RegisterTexture("title_ribbon", SCENE_PATH"title/v01/ribbon_title_01.png");
	RegisterTexture("title_logo", SCENE_PATH"title/v01/titlelogo_01.png");
	RegisterTexture("title_start", SCENE_PATH"title/v01/start_button_01.png");
	RegisterTexture("title_end", SCENE_PATH"title/v01/end_button_01.png");
	RegisterTexture("title_option", SCENE_PATH"title/v01/option_button_01.png");
	RegisterTexture("title_cursor", SCENE_PATH"title/v01/cursor_01.png");
	RegisterTexture("transition_01", SCENE_PATH"title/v01/transition_01.png");
	RegisterTexture("transition_02", SCENE_PATH"title/v01/transition_02.png");

	// �X�e�[�W�Z���N�g
	RegisterTexture("stageselect_option", SCENE_PATH"stageselect/v01/option_select_button_01.png");
	RegisterTexture("stageselect_return", SCENE_PATH"stageselect/v01/return_title_button_01.png");
	RegisterTexture("stageselect_right", SCENE_PATH"stageselect/v01/right_button_01.png");
	RegisterTexture("stageselect_left", SCENE_PATH"stageselect/v01/left_button_01.png");
	RegisterTexture("stageselect_chapter", SCENE_PATH"stageselect/v01/chapter_numbers_01.png");
	RegisterTexture("stageselect_gear_left", SCENE_PATH"stageselect/v01/gear_left_rotation_01.png");
	RegisterTexture("stageselect_gear_right", SCENE_PATH"stageselect/v01/gear_right_rotation_01.png");
	RegisterTexture("stageselect_stage_numbers_m", SCENE_PATH"stageselect/v01/stage_numbers_m_01.png");
	RegisterTexture("stageselect_stage_numbers_s", SCENE_PATH"stageselect/v01/stage_numbers_s_01.png");
	RegisterTexture("stageselect_stage_numbers_w", SCENE_PATH"stageselect/v01/stage_numbers_w_01.png");

}

//-----------------------------------------------------------------
// @brief �L���b�V���̃N���A
//-----------------------------------------------------------------
void TextureManager::ClearCache(void)
{
	texture_cache_.clear();
}
