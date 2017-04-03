
/******************************************************************************
 * Nome classe: AbstractEmbeddedServerGame									  *
 * ---------------------------------------------------------------------------*
 * Descrizione: Classe generica che implementa la logica di base per la       *
 *				creazione di server game embedded  implementando operazioni	  *
 *				comuni.														  *
 * Data:		02/03/2012													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _ABSTRACT_EMBEDDED_SERVER_GAME_H

	#define _ABSTRACT_EMBEDDED_SERVER_GAME_H
	//
	// include tutto ciò che server per il corretto funzionamento del software.
	#include "Solomon.h"
    //
    // definizioni classi necessarie per i prototipi di funzione:
    class AbstractBodyMessage;
    class AbstractHeaderMessage;
    class CUDPSocket;
    class IClientBridgeProvider;
	//
	//
	//dichiarazione della classe:
	class DLL_ACTION AbstractEmbeddedServerGame {
		private:
			CUDPSocket				*m_bgServer; // oggetto principale per la creazione del socket UDP e join nel multicast
            in_addr_t   			m_remoteIP; // Indirizzo IP numerico big-endian
            u_short					m_remotePort; // porta remota da utilizzare per il server
            in_addr_t   			m_localIP; // Indirizzo IP locale big-endian
            u_short					m_localPort; // porta locale da utilizzare per il server
            u_short                 m_intervalSecPing;
            u_short                 m_datagramSize;
            u_int                   verificationToken; // session id che verra' verificato per terminare il server
            pthread_t               m_serverGamePthreadId;
            pthread_t               m_pingerThreadID;
            boolean                 m_activePing;
			//
			// costruttori:
			AbstractEmbeddedServerGame(const AbstractEmbeddedServerGame&);
			//
			// redifinizione operatore:
			AbstractEmbeddedServerGame& operator=(const AbstractEmbeddedServerGame&);
            //
            // funzione per il ping periodico al server:
            // invia un solo byte al server: si puo' evitare che venga gestito come una normale richiesta agendo sulla funzione dropReceivedPacketLessOrEqualTo
            // presente sull'interfaccia del server remoto.
            friend void *           server_ping(void *param);
            //
            // funzione per l'avvio del server game:
            friend void *           StartGameServer(void *info); // avvia il server per la ricezione richieste

        protected:
            //
            // costruttore:
            AbstractEmbeddedServerGame(IClientBridgeProvider *bridge, buffer_pointer localIP, u_short localPort, buffer_pointer remoteIP, u_short remotePort, u_short datagramSize, boolean activePing);
            //
            // funzione virtuale pura da implementare. Contiene la specializzazione della logica da applicare e verrà richiamata automaticamente:
            virtual void			BackgroundParser(void *tmpDataContainerReader) = 0; // specializzazione della derivata che conterrà la logica da applicare; il parametro è il buffer della notifica ricevuta
            //
            // membro utilizzabile nella derivata:
            IClientBridgeProvider   *_bridge;

		public:
			//
			// Distruttore:
			virtual ~AbstractEmbeddedServerGame();
            //
            // funzioni:
            CUDPSocket *            getUdpSocketObject();
            void                    StartServer(AbstractHeaderMessage *checker, u_short pingInterval); // avvia il server e ritorna immediatamente (avvia il server su un nuovo thread)
            u_integer               StopServer();
            bool                    isServerStarted();
            //
            // Invia richiesta utilizzando la porta che il server embedded utilizza per consentire la ricezione di pacchetti (NAT hole punching)
            // Da utilizzare per qualsiasi richiesta verso il server remoto o per comunicare al gestore lato server su quale porta inviare al server embedded.
            // La funzione e' asincrona per cui eventuale risposta sara' inviata alla funzione BackgroundParser().
            // Ritorna: true se la richiesta e' stata inoltrata (senza certezza che sia arrivata), false altrimenti.
            boolean                 PostSendRequest(AbstractHeaderMessage *header, AbstractBodyMessage *body);
	};
	
#endif // _ABSTRACT_EMBEDDED_SERVER_GAME_H
