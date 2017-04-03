

/******************************************************************************
 * Nome classe: DataContainerReader											  *
 * ---------------------------------------------------------------------------*
 * Descrizione: Rappresenta la specializzazione del contenitore generale	  *
 *				ottimizzato per estrarre informazioni dal buffer.			  *
 *				Implementa tutte le logiche e le funzioni necessarie per	  *
 *				essere conforme alle specifiche dei protocolli.				  *
 * Data:		08/02/2007													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _DATACONTAINERREADER_H

	#define _DATACONTAINERREADER_H

	//
	// include la dichiarazione della classe base e tutto l'occorrente per il funzionamento del software:
	#include "Solomon.h"	
	#include "GeneralContainer.h"
	//
	// dichiarazione della classe per evitare loop di inclusioni:
    class BinaryReader;
	//
	//
	// contenitore di dati usato esclusivamente per l'estrazione delle informazioni:
	class DLL_ACTION DataContainerReader : public GeneralContainer {
		private:
			u_buffer_pointer		m_dataHeader; // Membro che conterrà, se specificato all'atto della creazione, l'header della risposta ottenuta
			BinaryReader			*m_BinaryReader; // oggetto che manipolerà il buffer passato al costruttore
            u_short                 m_dimOfHeader;
			//
			// Costruttori privati:
			DataContainerReader(const DataContainerReader&);
			DataContainerReader& operator=(const DataContainerReader&);
			//
			// funzioni private per uso interno:
            void					ReadDataHeader(u_short dimOfHeader);

            void					Extract(string& aByte, integer count);
            void					Extract(string& aByte, caracter count);

		public:
			//
			// Costruttori pubblici:
            DataContainerReader(u_buffer_pointer block, size_t len, u_short dimOfHeader, boolean skipHeader = TRUE);
            DataContainerReader(u_buffer_pointer block, size_t len, caracter resetPos);
			~DataContainerReader();
			//
			// funzioni pubbliche della classe:
			DataContainerReader	*	GetDataHeader(void);
			void					SetBufferPos(integer newPos);
			void					Extract(u_buffer_pointer dato);
			void					Extract(integer *dato);
			void					Extract(caracter *dato);
			void					Extract(geo *dato);
			void					Extract(u_integer *dato);
            void					Extract(u_longer *dato);
			void					Extract(shorter *dato);
			void					Extract(u_short *dato);
			void					Extract(u_buffer_pointer *aByte, integer count);
			void					Extract(u_buffer_pointer *aByte, byte count);
            void                    Extract(GeneralContainer *container);
	};

#endif // _DATACONTAINERREADER_H
