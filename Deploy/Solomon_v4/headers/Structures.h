

/*****************************************************************************
 * Strutture di vario utilizzo per l'uso interno ed esterno alla libreria.   *
 *****************************************************************************/


#ifndef _STRUCTURES_H

	#define _STRUCTURES_H
	//
	// include tutto ciò che server per il corretto funzionamento del software.
	#include "Solomon.h"
	#include <time.h>    
	//
	// dichiarazione della classe contenitore:
	class DataContainerReader;
    class AbstractServerGame;
    class AbstractTcpServerGame;
    class BaseInfoClient;
    //
	//
	// Struttura finalizzata al contenimento delle informazioni di connessione: indirizzo IP e porta:
    class DLL_ACTION TInfoConnection {
		private:
            in_addr_t 				RemoteIP;
            u_short					RemotePort;

		public:
            TInfoConnection(in_addr_t address, integer port);
            TInfoConnection(const u_buffer_pointer address, integer port);
			//	
			// interfaccia pubblica della classe:
            void					SetAddress(in_addr_t address);
            void					SetListenPort(const u_short port);
            char *                  GetIP();
            in_addr_t             	GetAddress(void);
            u_short					GetListenPort(void);            
	};
    //
    // enumerativo per identificare internamente le operazioni di smistamento delle richieste:
    typedef enum TTypeOfRequest {
        typeOfEndUserRequest = 0,
        typeOfInternalStreamRequest,
        typeOfCleaningRequest,
        typeOfHotPluginNotify,
        typeOfAcceptNewConnection
    } TTypeOfRequest;
    //
    // struttura per il recupero di richieste ricevute dal server:
    typedef struct ClientContainer {
        TInfoConnection         *client; // indirizzo IP e Porta del client che ha inviato richiesta
        DataContainerReader		*buffer; // buffer binario
        AbstractServerGame		*udpServer; // istanza server udp
        AbstractTcpServerGame   *tcpServer; // istanza server tcp per esegure invio di risposta
        TTypeOfRequest          typeOfRequest; // contiene informazioni sul tipo di richiesta
        BaseInfoClient          *infoTcpClient; // se NULL richiesta proveniente da udp; altrimenti proveniente da tcp

        ClientContainer();
    } ClientContainer;

#endif  // _STRUCTURES_H
