

/******************************************************************************
 * Nome classe: DynamicContainer                                              *
 * ---------------------------------------------------------------------------*
 * Descrizione: Rappresenta la specializzazione del contenitore generale	  *
 *				con caratteristiche di espansione dinamica del buffer.		  *
 * Data:		21/04/2012													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _DYNAMIC_CONTAINER_H

    #define _DYNAMIC_CONTAINER_H

	//
	// include la dichiarazione della classe base e tutto l'occorrente per il funzionamento del software:
	#include "Solomon.h"	
    //
    // forward declarations:
    class GeneralContainer;
    class BinaryWriter;
	//
	//
    // contenitore di dati usato in circostanze in cui non si conosce a priori la dimensione di un buffer:
    class DLL_ACTION DynamicContainer {
		private:
            GeneralContainer        *m_container;
            BinaryWriter            *m_binaryStream;
            u_short                 m_memBlock;
			//
			// Costruttori privati:
            DynamicContainer(u_buffer_pointer block, size_t len, caracter resetPos);
            DynamicContainer(const DynamicContainer&);
            DynamicContainer& operator=(const DynamicContainer&);

        public:
			//
			// Costruttori pubblici:
            DynamicContainer(u_short memoryBlock);
            ~DynamicContainer();
            //
            // funzioni di manipolazione del buffer:
            u_buffer_pointer        GetBuffer(void); // in caso non e' stato inserito niente, ritorna NULL
            u_short                 GetCurLen();
            u_short                 GetMaxLen();
            void                    Append(u_buffer_pointer buffer, u_short len_buffer);
	};

#endif // _DYNAMIC_CONTAINER_H
