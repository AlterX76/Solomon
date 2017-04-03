

/******************************************************************************
 * Nome classe: AbstractServiceClass													  *
 * ---------------------------------------------------------------------------*
 * Descrizione: super classe utilizzata in tutte le comunicazioni da e verso  *
 *				il server. Implementa tutta la logica che va dalla creazione  *
 *				della richiesta al reperimento della risposta fino ad arrivare*
 *				all'elaborazione dei buffer raw ottenuti per la creazione di  *
 *				oggetti da utilizzare programmaticamente ed alla restituzione *
 *				degli stessi dati in formato stringa XML.					  *
 * Data:		27/02/2012													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _AbstractServiceClass_H

    #define _AbstractServiceClass_H

	#include "Solomon.h"
    #include <openssl/ssl.h>
	//
    // dichiarazione delle classe:
	class AbstractBodyMessage;
    class AbstractResponseMessage;
    class AbstractHeaderMessage;
    class ResponseGenericMessage;
    class DataContainerReader;
    class ClientEnvironment;
    class ConiEnvironment;
    class TInfoConnection;
    //
	//
	// classe base astratta che incapsula tutta la logica di invio/ricezione dei dati, nonchè il parsing delle
	// informazioni ottenute. Ereditata da tutti gli oggetti  che implementano servizi di comunicazione specifici.
    class DLL_ACTION AbstractServiceClass {
		private:
			size_t							LenOfResponse; // dimensione in bytes dei dati ottenuti come risposta
            u_integer                       m_sequenceId; // mantiene il contatore delle richieste

		public:
			//
			// costruttori:
            AbstractServiceClass();
			//
			// Distruttore:
            virtual ~AbstractServiceClass();
			//
			// funzioni:            
			DataContainerReader *			GetInternalReader(void); // restituisce il reader interno
            //
            // funzione per l'invio di messaggi:
            ResponseGenericMessage *        SendRequest(ClientEnvironment *clientEnv, AbstractHeaderMessage *header, AbstractBodyMessage *body);
            AbstractResponseMessage *		SendTcpRequest(SSL *ssl, ClientEnvironment *clientEnv, AbstractBodyMessage *body, AbstractHeaderMessage *checker, u_short timeout);
            //
            //// funzione per l'invio di messaggi di risposta: usata solo dal server
            ResponseGenericMessage *        SendResponse(ConiEnvironment *clientEnv, AbstractHeaderMessage *header, AbstractResponseMessage *body);
						
		protected:
            AbstractResponseMessage *		SendRequest(AbstractBodyMessage *body, AbstractHeaderMessage *checker, u_short timeout);
			// 
			// oggetti visibili nelle derivate:
			class ConiEnvironment			*m_pConiEnv; //Conserva internamente le informazioni utilizzate per l'header della richiesta da inviare al TN
            //
            // funzioni interne:
            void							InternalCreateConiEnv(TInfoConnection *RemoteHostInfo, TInfoConnection *LocalHostInfo, AbstractHeaderMessage *header, AbstractBodyMessage *body);
	};

#endif // _AbstractServiceClass_H
