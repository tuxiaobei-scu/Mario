#include "keymsg.h"

void Keymsg::update()
{
	msg.clear();
	while (kbmsg()) {
		msg.push_back(getkey());
	}
}

bool Keymsg::getmsg(key_msg& m, int key)
{
	for (auto i = msg.rbegin(); i != msg.rend(); i++) {
		if (i->key == key) {
			m = *i;
			return true;
		}
	}
	return false;
}
Keymsg keymsg;
