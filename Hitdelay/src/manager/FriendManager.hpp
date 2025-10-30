#pragma once
#include <vector>
#include <string>

namespace FriendManager {
	inline std::vector<std::string> friends;

	void add_friend(std::string name);
	void remove_friend(std::string name);
	bool is_exist(std::string name);
}