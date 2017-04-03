

/******************************************************************************
 * Nome classe: AbstractBodyMessage											  *
 * ---------------------------------------------------------------------------*
 * Descrizione: classe astratta utilizzata come template per i body che		  *
 *				costituiscono la richiesta da inviare.		 				  *
 * Data:		27/02/2012													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _ABSTRACTBODYMESSAGE_H

	#define _ABSTRACTBODYMESSAGE_H

	#include "Solomon.h"
	//
	//definizione classe per evitare loop:
	class AbstractResponseMessage;
    class DataContainerReader;
    class DataContainerWriter;
	//
	// classe astratta che rappresenta la base per tutti i body specializzati:
	class DLL_ACTION AbstractBodyMessage {
        private:
            DataContainerWriter					*m_body; //conterrà il buffer della richiesta da effettuare

		private:
			AbstractBodyMessage(const AbstractBodyMessage&);
			AbstractBodyMessage& operator=(const AbstractBodyMessage&);

		public:
			//
			// Costruttore/distruttore:
			AbstractBodyMessage();
			virtual ~AbstractBodyMessage();
			//
			// funzioni:
			void								ClearBody(void); //Utilizzata automaticamente per permettere di impostare il body all'interno di un ciclo
            DataContainerWriter *               initBodyStream(size_t dimension); // crea oggetto stream per il body (precedente eliminato)
			//
			// funzioni virtuali:
            virtual u_short                     ReceiveDatagramSize(); // ritorna la dimensione del buffer da utilizzare per ricevere un pacchetto UDP (default DIM_DEFAULT_BUFFER_RCV)
			virtual DataContainerWriter *		GetBodyMessage(void) = 0; //Richiamata automaticamente quando viene assemblata tutta la richiesta da inviare al TN
			virtual AbstractResponseMessage *	CreateResponseObject(DataContainerReader *binary_response) = 0; // ritorna oggetto che conterra' messaggio di risposta
			virtual byte						IDService(void) = 0; // ritorna l'identificativo del servizio
            virtual byte						IDMessage(void) = 0; // ritorna l'identificativo del messaggio
	};

#endif // _ABSTRACTBODYMESSAGE_H
