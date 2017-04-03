

/*****************************************************************************
 * Classe base per contenere dati e operare sugli stessi; per l'uso interno  *
 * ed esterno alla libreria.												 *
 *****************************************************************************/


#ifndef _GENERALCONTAINER_H

	#define _GENERALCONTAINER_H

	#include "Solomon.h"


	// Oggetto che rappresenta un contenitore di dati generico con funzionalità di base
	class DLL_ACTION GeneralContainer {
		public:
			// funzioni pubbliche:
            u_buffer_pointer        GetBytes(void);
            u_buffer_pointer *      GetBufferPointer();
			size_t					GetCurLen(void);
			size_t					GetMaxLen(void);
			void					MemoryClear(void);
			boolean					IsContained(size_t size);
			void					SetBufferPos(size_t newPos);
			//
			// membri pubblici della classe:
			u_buffer_pointer		m_buffer; // Membro che rappresenta un buffer di dati in cui memorizzare le informazioni
			size_t					m_curPos; // posizione corrente nel buffer
			size_t					m_maxDimension; // dimensione massima allocata
			//
            // costruttore/distruttore pubblico:
            GeneralContainer(GeneralContainer&);
            GeneralContainer(size_t size);
			virtual ~GeneralContainer();
			//
			// membro statico pubblico:
            static const integer    RESET_BUFFER;
            //
            // funzioni per la scrittura:
            void					Write(u_buffer_pointer aByte);		
	};

#endif // _GENERALCONTAINER_H
