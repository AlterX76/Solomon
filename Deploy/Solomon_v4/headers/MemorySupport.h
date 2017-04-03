



#ifndef _MEMORY_SUPPORT_H

	#define _MEMORY_SUPPORT_H

	#include "Solomon.h"


namespace MemoryUtil {
	//
	// prototipo di funzione con template per la pulizia della memoria allocata:
	template<typename MyObject>
	void DeleteMemory(MyObject **Memory, boolean isObject)
	{
		 if (*Memory != NULL) {
			 if (isObject == TRUE)
				delete (*Memory);
			 else
				delete[] (*Memory);
			 *Memory = NULL;
		 }
	}
}

#endif // _MEMORY_SUPPORT_H
