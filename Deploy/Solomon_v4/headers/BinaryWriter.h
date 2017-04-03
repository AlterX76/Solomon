

#ifndef _BINARYWRITER_H

	#define _BINARYWRITER_H

	#include "Solomon.h"	
	#include "GeneralContainer.h"	
	

	// Oggetto che rappresenta un consumatore binario per un contenitore di dati generico:
	class BinaryWriter {
		private:
            GeneralContainer    *m_Writer; // puntatore interno all'oggetto da manipolare (DA NON LIBERARE NEL DISTRUTTORE)

            void                Put(const string *aByte);

		public:
            BinaryWriter(GeneralContainer *writer); // il parametro non viene eliminato alla distruzione dell'oggetto (aggregato)
			~BinaryWriter();
			//
			// funzioni per l'elaborazione sul buffer:
            void                Put(byte dato);
            void                Put(geo dato);
            void                Put(integer dato);
            void                Put(u_integer dato);
            void                Put(u_longer dato);
            void                Put(shorter dato);
            void                Put(u_short dato);
            void                Put(u_buffer_pointer aByte, size_t len);            
            void                MemoryClear(void);
            void                SetGeneralContainer(GeneralContainer *container);
	};

#endif // _BINARYWRITER_H
