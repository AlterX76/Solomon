



#ifndef _CLIENT_ENVIRONMENT_H

	#define _CLIENT_ENVIRONMENT_H

	#include "Solomon.h"

    class AbstractTcpEmbeddedServerGame;
	//
	// Definizione del tipo per la creazione di un ambiente da utilizzare per l'invio delle informazioni.
	class DLL_ACTION ClientEnvironment {
		private:
            ip_string                       m_ServerIPAddr; // IP del server remoto da utilizzare per effettuare la richiesta
            ip_string                       m_ClientIPAddr; // IP del client locale che intende effettuare la richiesta verso il TN
            integer                         m_ServerUDPPort; // Porta del server remoto da utilizzare per effettuare la richiesta
            integer                         m_ClientUDPPort; // Porta del client locale da utilizzare per creare una connessione
            byte                            m_id_servizio; // Nel protocollo PSI e PSS il settaggio del servizio appropriato è automatico nel momento in cui si utilizzano i metodi di un oggetto specializzato
            byte                            m_id_messaggio; // Identifica il tipo di messaggio della richiesta da inviare al TN
            u_short                         m_timeout; // timeout ricezione udp
            AbstractTcpEmbeddedServerGame   *ServerTcpEmbedded;

		public:
			//
			// Costruttore/Distruttore:
			ClientEnvironment();
			//
			// interfaccia utente:
            buffer_pointer                  GetServerIPAddr(void); // Proprietà per reperire l'indirizzo IP del server di destinazione
            void                            SetServerIPAddr(ip_string ip); // Proprietà per settare l'indirizzo IP del server di destinazione
            integer                         GetServerUDPPort(void); // Proprietà per reperire la porta UDP del server di destinazione
            void                            SetServerUDPPort(integer port); // Proprietà per settare la porta UDP del server di destinazione
            buffer_pointer                  GetClientIPAddr(void); // Proprietà per reperire l'indirizzo IP del client locale
            void                            SetClientIPAddr(ip_string ip); // Proprietà per settare l'indirizzo IP del client locale
            integer                         GetClientUDPPort(void); // Proprietà per reperire la porta UDP del client locale
            void                            SetClientUDPPort(integer port); // Proprietà per settare la porta UDP del client locale
            byte                            GetIDServizio(void); // Proprietà per il reperimento del servizio da utilizzare per la richiesta
            void                            SetIDServizio(byte id_servizio); // Proprietà per il settaggio del servizio da utilizzare per la richiesta
            byte                            GetIDMessaggio(void); // Proprietà per il reperimento del messaggio da utilizzare per la richiesta
            void                            SetIDMessaggio(byte id_messaggio); // Proprietà per il settaggio del messaggio da utilizzare per la richiesta
            u_short                         GetRcvTimeout(void);
            void                            SetRcvTimeout(byte value);
            AbstractTcpEmbeddedServerGame * GetTcpClient();
            void                            SetTcpClient(AbstractTcpEmbeddedServerGame *client);
    };

#endif // _CLIENT_ENVIRONMENT_H
