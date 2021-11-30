#include "keymsg.h"

void Keymsg::update()
{
	msg.clear();
	while (kbmsg()) {
		key_msg k = getkey();
		msg.push_back(k);
		bool flag = (k.msg == key_msg_down);
		if (flag || k.msg == key_msg_up) {
			switch (k.key) {
			case key_left:
				left_key = flag;
				break;
			case key_right:
				right_key = flag;
				break;
			case key_down:
				down_key = flag;
				break;
			case 'S':
				S_key = flag;
				break;
			}
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
