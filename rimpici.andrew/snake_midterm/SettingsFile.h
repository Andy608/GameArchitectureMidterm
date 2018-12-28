#ifndef SETTINGS_FILE_H_
#define SETTINGS_FILE_H_

#include <Trackable.h>
#include <string>
#include <map>

class SettingsFile : public Trackable
{
public:
	SettingsFile(std::string fileSrc);
	~SettingsFile();

	std::string getSettingFromKey(std::string key);
	std::string getKeyFromSetting(std::string setting);

private:
	std::map<std::string, std::string> mSettingsMap;
};

#endif