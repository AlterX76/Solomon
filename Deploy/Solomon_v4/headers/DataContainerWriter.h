

/******************************************************************************
 * Nome classe: DataContainerWriter											  *
 * ---------------------------------------------------------------------------*
 * Descrizione: Rappresenta la specializzazione del contenitore generale	  *
 *				ottimizzato per memorizzare informazioni nel buffer.		  *
 *				Implementa tutte le logiche e le funzioni necessarie per	  *
 *				essere conforme alle specifiche dei protocolli.				  *
 * Data:		08/02/2007													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _DATACONTAINERWRITER_H

	#define _DATACONTAINERWRITER_H

	#include "Solomon.h"
	//
	// include la dichiarazione della classe base e tutto l'occorrente per il funzionamento del software:
	#include "GeneralContainer.h"

    class BinaryWriter;

	class DLL_ACTION DataContainerWriter : public GeneralContainer {
		private:
			BinaryWriter	*m_BinaryWriter; // oggetto che manipolerà il buffer passato al costruttore

            //void            Put(const string *aByte);

		public:
			DataContainerWriter(integer size = MAX_BUFFER_DATA_CONTAINERS);
			~DataContainerWriter();
			//
			// funzioni pubbliche della classe:
            void            Put(byte dato);
            void            Put(geo dato);
            void            Put(integer dato);
            void            Put(u_integer dato);
            void            Put(u_longer dato);
            void            Put(shorter dato);
            void            Put(u_short dato);
            void            Put(u_buffer_pointer aByte, size_t len);
	};

#endif // _DATACONTAINERWRITER_H
