


/******************************************************************************
 * Nome classe: ClusterNotificationMessage  								  *
 * ---------------------------------------------------------------------------*
 * Descrizione: Il messaggio viene utilizzato per inviare un messaggio ad un  *
 *              server interno usato come cluster.                            *
 * Data:		05/08/2014													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/

#ifndef MOBILE_BUILD

#ifndef _CLUSTER_NOTIFICATION_MESSAGE_H

    #define _CLUSTER_NOTIFICATION_MESSAGE_H

	#include "Solomon.h"
    #include "Types.h"
    #include "AbstractBodyMessage.h"
    #include <string>
    //
    //
    using namespace Solomon::Types;
    using std::string;
	//
	//
    // Container per l'invio di un messaggio interno tra server in ambiente cluster:
    class DLL_ACTION ClusterNotificationMessage : public AbstractBodyMessage {
		private:
            SmallString                 _trustedInternalPassword;
            SocketHandle                _client_id; // id del client sul server destinazione
            Byte                        _idBodyService;
            Byte                        _idBodyMessage;
            AbstractBodyMessage         *_innerBody; // real body to send to

		public:
			//
			// Costruttori/distruttori:
            ClusterNotificationMessage();
            ClusterNotificationMessage(DataContainerReader *buffer);
            virtual ~ClusterNotificationMessage();
			//
			// funzioni di accesso alla classe:
            void						SetClientId(sock client_id);
            sock                        GetClientId();
            void                        SetBody(AbstractBodyMessage *body);
            void                        SetTrustedPassword(buffer_pointer password);
            const u_buffer_pointer      GetTrustedPassword();
            byte                        GetIdBodyService();
            byte                        GetIdBodyMessage();
			//
			// funzione virtuale da reimplementare:
			AbstractResponseMessage *	CreateResponseObject(DataContainerReader *binary_response);
			//
			// funzioni virtuali da implementare:
			DataContainerWriter *		GetBodyMessage(void); //Richiamata automaticamente quando viene assemblata tutta la richiesta da inviare al TN
            byte						IDService(void); // ritorna l'identificativo del servizio
            byte						IDMessage(void); // ritorna l'identificativo del messaggio
	};

#endif

#endif // _CLUSTER_NOTIFICATION_MESSAGE_H
