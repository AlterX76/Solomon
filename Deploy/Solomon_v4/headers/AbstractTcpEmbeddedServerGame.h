
/******************************************************************************
 * Nome classe: AbstractTcpEmbeddedServerGame								  *
 * ---------------------------------------------------------------------------*
 * Descrizione: Classe generica che implementa la logica di base per la       *
 *				creazione di server game embedded  implementando operazioni	  *
 *				comuni. CREARE UNA SOLA ISTANZA DELLA CLASSE DERIVATA         *
 * Data:		22/12/2012													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _ABSTRACT_TCP_EMBEDDED_SERVER_GAME_H

    #define _ABSTRACT_TCP_EMBEDDED_SERVER_GAME_H
	//
	// include tutto ciò che server per il corretto funzionamento del software.
	#include "Solomon.h"
    //
    // definizioni classi necessarie per i prototipi di funzione:
    class AbstractHeaderMessage;
    class AbstractBodyMessage;
    class DataContainerReader;
    class IClientBridgeProvider;
    class CTCPSocket;
    //
    // inclusioni relative ad i vari sistemi operativi:
    #if defined (WIN32)
        #include <winbase.h>
    #elif defined (LINUX)
        #include <signal.h>
        #include <semaphore.h>
        #include <sys/time.h>
    #endif
    #include <openssl/ssl.h>
    //
	//
	//dichiarazione della classe:
    class DLL_ACTION AbstractTcpEmbeddedServerGame {
		private:
            CTCPSocket				*m_bgServer; // oggetto principale per la creazione del socket UDP e join nel multicast
            SSL                     *m_ssl_socket;
            in_addr_t   			m_remoteIP; // Indirizzo IP numerico big-endian
            u_short					m_remotePort; // porta remota da utilizzare per il server
            in_addr_t   			m_localIP; // Indirizzo IP locale big-endian
            u_short					m_localPort; // porta locale da utilizzare per il server
            u_integer               verificationToken; // session id che verra' verificato per terminare il server
            boolean                 m_isFileUploadGrant; // valore booleano che indica se il server ha garantito o negato la procedura di upload file
            DataContainerReader     *m_receivedResponse; // mantiene traccia di risposta da restituire
            u_short                 m_secTimeoutResponse; // numero di sec dopo il quale termina di attendere una risposta
            pthread_t               m_serverGamePthreadId;
            pthread_t               m_waiter;
            pthread_mutex_t         mutexTimeout;
            pthread_mutex_t         mutexReadyToSendFile;
            pthread_mutex_t         mutexSendFile;
            pthread_cond_t          condTimeout;
            pthread_cond_t          condReadyToSendFile;
        
        #ifndef IPHONE
            #if defined WIN32
            HANDLE                  m_waitResponse;
            #else
            sem_t                   m_waitResponse; // semaforo utilizzato quando si attende una risposta tramite tcp
            #endif
        #else
            sem_t                   *m_waitResponse; // semaforo utilizzato quando si attende una risposta tramite tcp
        #endif
            pthread_mutex_t			m_mutex;
            boolean                 m_isValidRequest;
            u_integer               m_answerSeqId; // contiene id univoco della risposta che si attende
			//
			// costruttori:
            AbstractTcpEmbeddedServerGame(const AbstractTcpEmbeddedServerGame&);
			//
			// redifinizione operatore:
            AbstractTcpEmbeddedServerGame& operator=(const AbstractTcpEmbeddedServerGame&);

            void					LockQueue(pthread_mutex_t *mutex); // effettua il lock per m_QueueLocker
            void					UnlockQueue(pthread_mutex_t *mutex); // effettua l'unlock per m_QueueLocker
            //
            // funzione per l'avvio del server game:
            friend void *           StartGameTcpServer(void *info); // avvia il server per la ricezione richieste
            friend void *           threadTimeout(void *);

        protected:
            //
            // costruttore:
            AbstractTcpEmbeddedServerGame(IClientBridgeProvider *bridge, buffer_pointer localIP, u_short localPort, buffer_pointer remoteIP, u_short remotePort, u_short secTimeoutResponse = 8);
            //
            // usata dalla derivata per segnalare arrivo di un messaggio dal server:
            void                    SignalResponseFromServer(DataContainerReader *reader, AbstractHeaderMessage *receivedHeader);
            //
            // funzione virtuale pura da implementare. Contiene la specializzazione della logica da applicare e verrà richiamata automaticamente:
            virtual void			BackgroundParser(void *tmpDataContainerReader) = 0; // specializzazione della derivata che conterrà la logica da applicare; il parametro è il buffer della notifica ricevuta
            virtual void            ConnectionDown(); // quando keep alive non viene restituito
            // Da utilizzare per qualsiasi richiesta verso il server remoto o per comunicare al gestore lato server su quale porta inviare al server embedded.
            // La funzione e' asincrona per cui eventuale risposta sara' inviata alla funzione BackgroundParser().
            // Ritorna: true se la richiesta e' stata inoltrata (senza certezza che sia arrivata), false altrimenti.
            boolean                 PostSendRequest(SSL *ssl, AbstractHeaderMessage *header, AbstractBodyMessage *body);
            //
            // consente di inviare file con header:
            boolean                 SendFile(SSL *ssl, AbstractHeaderMessage *header, u_integer id, const buffer_pointer file);
            void                    StartUploadSignal(boolean grant);
            //
            // membro utilizzabile nella derivata:
            IClientBridgeProvider   *_bridge;

		public:
			//
			// Distruttore:
            virtual                 ~AbstractTcpEmbeddedServerGame();
            //
            // funzioni:
            CTCPSocket *            getTcpSocketObject();
            SSL *                   getSslSocketObject(); // it might return 0
            void                    StartListenServer(AbstractHeaderMessage *checker, boolean require_SSL_TLS); // avvia il server e ritorna immediatamente (avvia il server su un nuovo thread)
            u_integer               StopServer();
            DataContainerReader *   WaitResponseFromServer(u_short timeout, u_integer seq_id); // se zero usa il valore passato nel costruttore
            bool                    isServerStarted();
            virtual integer         getClientTicket() = 0; // recupera id univoco per comunicare con il server tcp centrale
	};
	
#endif // _ABSTRACT_TCP_EMBEDDED_SERVER_GAME_H
