

#ifndef _BINARYREADER_H

	#define _BINARYREADER_H

	#include "Solomon.h"	
	#include "GeneralContainer.h"	
	
	// Oggetto che rappresenta un consumatore binario per un contenitore di dati generico:
	class BinaryReader {
		private:
            GeneralContainer    *m_Reader; // puntatore interno all'oggetto da manipolare (DA NON LIBERARE NEL DISTRUTTORE)

		public:
			BinaryReader(GeneralContainer *reader);
			~BinaryReader();
			//
			// funzioni per l'elaborazione sul buffer:
            void                Extract(u_buffer_pointer dato);
            void                Extract(geo *dato);
            void                Extract(caracter *dato);
            void                Extract(integer *dato);
            void                Extract(u_integer *dato);
            void                Extract(u_longer *dato);
            void                Extract(shorter *dato);
            void                Extract(u_short *dato);
            void                Extract(u_buffer_pointer *aByte, integer count); // ritorna buffer allocato dinamicamente in aByte se tutto ok
            bool                Extract(u_buffer_pointer *allocated, size_t count); // estrae i dati in allocated gia' di dimensione count
            void                MemoryClear(void);
            void                Write(buffer_pointer aByte);
            void                SetBufferPos(integer newPos);
	};

#endif // _BINARYREADER_H
