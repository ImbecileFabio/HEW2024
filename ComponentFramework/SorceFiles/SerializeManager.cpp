#include "SerializeManager.h"
#include "GameObjects/GameObject.h"
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
SerializeManager::~SerializeManager()
{
}
//--------------------------------------------------
// �Q�[���I�u�W�F�N�g���V���A���C�Y����֐�
//--------------------------------------------------
std::string SerializeManager::SerializeGameObject(const GameObject* _gameObject)
{
	if (!_gameObject)
		return "";
    std::ostringstream oss;
    oss << "GameObject," << _gameObject->GetObjectName();

    for (const auto& component : _gameObject->GetComponents())
    {
        oss << "\n" << SerializeComponent(component);
    }

	return oss.str();   // ������ɕϊ����ĕԂ�S
}
//--------------------------------------------------
// �Q�[���I�u�W�F�N�g���f�V���A���C�Y����֐�
//--------------------------------------------------
GameObject* SerializeManager::DeserializeGameObject(const std::string& _data)
{
    if (_data.empty())
        return nullptr;

    std::istringstream iss(_data);
    std::string line;
    GameObject* newObject = nullptr;

    while (std::getline(iss, line))
    {
        std::istringstream lineStream(line);
        std::string type;
        std::getline(lineStream, type, ',');
    }

    return nullptr;
}
//--------------------------------------------------
// �R���|�[�l���g���V���A���C�Y����֐�
//--------------------------------------------------
std::string SerializeManager::SerializeComponent(const Component* _component)
{
   if (!_component) return "";

   std::ostringstream oss;
   // �R���|�[�l���g�̎�ނɂ����CSV�ɑΉ������f�[�^�ɕϊ�
   switch (_component->GetComponentType())
   {
   case Component::TypeID::TransformComponent:
   {
       const TransformComponent* transform = dynamic_cast<const TransformComponent*>(_component);
       oss << "TransformComponent,"
           << transform->GetPosition().x << ","
           << transform->GetPosition().y << ","
           << transform->GetPosition().z << ","
           << transform->GetRotation().x << ","
           << transform->GetRotation().y << ","
           << transform->GetRotation().z << ","
           << transform->GetScale().x << ","
           << transform->GetScale().y << ","
		   << transform->GetScale().z << ","
		   << transform->GetSize().x << ","
		   << transform->GetSize().y << ","
		   << transform->GetSize().z; 
   }
   break;
   default:
       break;
   }
   return oss.str();
}
//--------------------------------------------------
// �R���|�[�l���g���f�V���A���C�Y����֐�
//--------------------------------------------------
Component* SerializeManager::DeserializeComponent(const std::string& _data)
{
	return nullptr;
}
