#include "FriendManager.hpp"


void FriendManager::add_friend(std::string name) {
    printf("added a friend! %s\n", name.c_str());
    friends.push_back(name);
}

void FriendManager::remove_friend(std::string name) {
    printf("removed a friend! %s\n", name.c_str());
    friends.erase(std::remove(friends.begin(), friends.end(), name), friends.end());
}

bool FriendManager::is_exist(std::string name) {
    return std::find(friends.begin(), friends.end(), name) != friends.end();
}