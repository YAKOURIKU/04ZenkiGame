#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include "json.hpp"

#include "Utility\SingletonTemplate.h"

//Json�Ǘ��N���X
template<typename T>
class JsonFileManager
	: public SingletonTemplate<JsonFileManager<T>>
{
public:
	friend class SingletonTemplate<JsonFileManager<T>>;

	//�t�@�C���̓ǂݍ���
	void load(const std::string& key, const std::string& filePath);
	//�t�@�C���̍ēǂݍ���
	void reloadAll();
	//���
	void unloadAll();
	//�擾
	const T& get(const std::string& key) const;
	//�S�Ď擾
	const std::unordered_map<std::string, T>& getAll() const;

protected:
	//�R���X�g���N�^���B��
	JsonFileManager() {};
	//�f�X�g���N�^���B��
	virtual ~JsonFileManager() {};

private:
	std::unordered_map<std::string, T> m_FileList;
	std::unordered_map<std::string, std::string> m_FilePathList;
};

template<typename T>
void JsonFileManager<T>::load(const std::string& key, const std::string& filePath)
{
	//�t�@�C���ǂݍ���
	std::ifstream ifs(filePath);

	//json�֕ϊ�
	nlohmann::json json;
	ifs >> json;
	ifs.close();

	//�X�e�[�^�X�ǂݍ���
	T file(json);

	//json�t�@�C����o�^
	if (m_FileList.contains(key))
		m_FileList.at(key) = file;
	else
		m_FileList.emplace(key, file);
	//�t�@�C���p�X��o�^
	if (!m_FilePathList.contains(key))
		m_FilePathList.emplace(key, filePath);
}

template<typename T>
void JsonFileManager<T>::reloadAll()
{
	//�t�@�C���p�X���X�g���Q�Ƃ��đS�ēǂݍ��݂Ȃ���
	for (const auto& pair : m_FilePathList)
	{
		load(pair.first, pair.second);
	}
}

template<typename T>
void JsonFileManager<T>::unloadAll()
{
	m_FileList.clear();
	m_FilePathList.clear();
}

template<typename T>
const T& JsonFileManager<T>::get(const std::string& key) const
{
	return m_FileList.at(key);
}

template<typename T>
const std::unordered_map<std::string, T>& JsonFileManager<T>::getAll() const
{
	return m_FileList;
}