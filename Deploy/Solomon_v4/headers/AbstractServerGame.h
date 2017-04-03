
/******************************************************************************
 * Nome classe: AbstractServerGame											  *
 * ---------------------------------------------------------------------------*
 * Descrizione: Classe generica che implementa la logica di base per la       *
 *				creazione di server game implementando operazioni comuni.	  *
 * Data:		29/02/2012													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _ABSTRACT_SERVER_GAME_H

	#define _ABSTRACT_SERVER_GAME_H

#ifndef MOBILE_BUILD
	//
	// include tutto ciò che server per il corretto funzionamento del software.
	#include "Solomon.h"
    #include "Structures.h"
    //
    // dichiarazione classe server tcp di supporto:
    class AbstractTcpServerGame;
    class CUDPSocket;
    class ClientEnvironment;
    class IServerBridgeProvider;
    class ISpecializedPlugin;
    class AbstractHeaderMessage;
    class AbstractBodyMessage;
    class ClientContainer;
    class SingleChainInfo;
	//
	//
	//dichiarazione della classe:
	class DLL_ACTION AbstractServerGame {
        protected:
            SingleChainInfo         *queueCommands;

		private:
			CUDPSocket				*m_bgServer; // oggetto principale per la creazione del socket UDP e join nel multicast
            AbstractTcpServerGame   *m_bgTcpServer; // eventuale server tcp usato per risposte dal server ai satelliti
			ClientEnvironment		*m_Env; // oggetto di alto livello che conterrà tutte le informazioni per le richieste
            u_integer               m_maxPacketSize; // max dimension for udp or tcp requests
            u_short                 m_dropPacketLen;
            boolean                 m_useTcpServer; // se deve utilizzare server tcp
            void                    *threadStorageInfo; // sturttura utilizzata per trasportare le informazioni
            u_short					numberThreadWorker;
            u_short					numberThreadsInPool;
            IServerBridgeProvider   *_bridge;
            ISpecializedPlugin		*m_plugin; // gestisce le operazioni specializzate recuperate dal plugin
			//
			// costruttori:
			AbstractServerGame(const AbstractServerGame&);
			//
			// redifinizione operatore:
			AbstractServerGame& operator=(const AbstractServerGame&);

            void                    InizializeThreadPools();
            void                    DestroyThreadPools();
			//
			// funzioni amiche private:
#if defined (WIN32)
			friend void				InternalExecutionQueue(void *threadInfo); // effettua l'estrazione dalla coda logica e se le condizioni lo permettono (connessione, elementi nella coda, ecc...) effettua l'elaborazione. Intervallo di tempo ad un secondo.
#elif defined (LINUX)
			friend void	*			InternalExecutionQueue(void *threadInfo); // effettua l'estrazione dalla coda logica e se le condizioni lo permettono (connessione, elementi nella coda, ecc...) effettua l'elaborazione. Intervallo di tempo ad un secondo.
#endif
			//
			// funzione statica utilizzata come wrapper per richiamare funzione membro virtuale:
#if defined (WIN32)			
			static void				StartThread(void *container);
#elif defined (LINUX)
			static void	*			StartThread(void *container);
#endif
            friend void *           ClearPendingSocket(void *info);
            friend void *           StartTcpSupportedServer(void *raw);
            friend class            AbstractTcpServerGame;
            friend class            AsyncServerUploadInfo;

		protected:
			//
			// costruttore:
            AbstractServerGame(IServerBridgeProvider *bridge, u_integer maxPacketSize, boolean responseThruTcp = TRUE);
			//
			// funzione per l'avvio del server:
            boolean					StartGameServer(); // avvia il server per la ricezione richieste
            ///
            /// impostazione che permette di eliminare pacchetti ricevuti con una lunghezza minore o uguale a len; se len=zero (impostazione di default), viene disabilitato il check
            void                    dropReceivedPacketLessOrEqualTo(u_short binaryLen);
            ///
            /// Evento generato dal server per ogni richiesta ricevuta ed estratta dalla catena di gestione.
            /// L'EVENTO VIENE ESEGUITO IN UN CONTESTO MULTI-THREAD ED ESEGUITO IN UN CONTESTO SICURO IN CASO DI ERRORI O ECCEZIONI NON GESTITE.
            /// L'IMPLEMENTATORE E' RESPONSABILE DELLA DISTRUZIONE DEI SOLI OGGETTI CHE VENGONO ALLOCATI AL SUO INTERNO.
            virtual void			BackgroundParser(const ClientContainer *tmpClientContainer) = 0; // non e' necessario deallocare la memoria del parametro.
            //
            // funzioni di utilita' interna:
            void					LockQueue(pthread_mutex_t *mutex) const; // effettua il lock per m_QueueLocker
            void					UnlockQueue(pthread_mutex_t *mutex) const; // effettua l'unlock per m_QueueLocker
            void					WaitEmptyQueue(pthread_cond_t *cond, pthread_mutex_t *mutex); // effettua il lock per m_QueueCond
            void					WakeNoEmptyQueue(pthread_cond_t *cond) const; // effettua l'unlock per m_QueueCond
            void                    EnqueueRequest(ClientContainer *request) const;

		public:
			//
			// Distruttore:
			virtual ~AbstractServerGame();
			//
			// funzioni per la sincronizzazione delle informazioni:
            AbstractTcpServerGame * getTcpServer() const;
            const SingleChainInfo * getChains() const;
            ISpecializedPlugin *    getPlugin() const;
            IServerBridgeProvider * getBridgeProvider() const;
            u_integer               getMaxPacketRequestInByte();
            //
            // funzioni per la comunicazione tra cluster di server:
            boolean                 EnqueueNotificationOverCluster(TInfoConnection& remoteServer, sock id_client, AbstractHeaderMessage *header, AbstractBodyMessage *body);
	};

#endif
	
#endif // _ABSTRACT_SERVER_GAME_H
