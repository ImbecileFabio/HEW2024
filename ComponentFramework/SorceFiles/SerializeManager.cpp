#include "SerializeManager.h"
#include "GameObjects/GameObject.h"
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
SerializeManager::~SerializeManager()
{
}
//--------------------------------------------------
// ゲームオブジェクトをシリアライズする関数
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

	return oss.str();   // 文字列に変換して返すS
}
//--------------------------------------------------
// ゲームオブジェクトをデシリアライズする関数
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
// コンポーネントをシリアライズする関数
//--------------------------------------------------
std::string SerializeManager::SerializeComponent(const Component* _component)
{
   if (!_component) return "";

   std::ostringstream oss;
   // コンポーネントの種類によってCSVに対応したデータに変換
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
// コンポーネントをデシリアライズする関数
//--------------------------------------------------
Component* SerializeManager::DeserializeComponent(const std::string& _data)
{
	return nullptr;
}
