#ifndef PARKH
#define PARKH

#include "cclass.h"


CLASS(Park)
	unsigned int state_;
METHODS
	enum Signal ParkGetSignals(Park *me);
	void ParkInit(Park *me);
	void ParkTran_(Park *me, unsigned int dest);
	void ParkDispatch(Park *me);
END_CLASS

#endif // PARKH