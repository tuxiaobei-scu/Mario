#include "keymsg.h"
#include "level.h"
void Keymsg::update()
{
	msg.clear();
	while (kbmsg()) {
		key_msg k = getkey();
		msg.push_back(k);
		bool flag = (k.msg == key_msg_down);
		if (flag || k.msg == key_msg_up) {
			if (!is_down[k.key])
				down_time[k.key] = level.now_time;
			is_down[k.key] = flag;
		}
			
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
