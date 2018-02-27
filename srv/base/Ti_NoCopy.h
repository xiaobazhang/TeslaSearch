/**
 * Created by suli on 18/2/12.
 */

#ifndef TIALLOY_TI_NOCOPY_H
#define TIALLOY_TI_NOCOPY_H

#include <iostream>

namespace TiAlloy {
class Ti_NoCopy {
 protected:
	Ti_NoCopy() {
	}
	virtual ~Ti_NoCopy() {
	}
 private:
	Ti_NoCopy(const Ti_NoCopy &copy) {
	}
	const Ti_NoCopy &operator=(const Ti_NoCopy &copy) {
	}
};

}

#endif //TIALLOY_TI_NOCOPY_H
