


/******************************************************************************
 * Nome classe: AttachedLinkMessage											  *
 * ---------------------------------------------------------------------------*
 * Descrizione: Il messaggio viene utilizzato per inviare al client un link a *
 *              che punta ad un file sul server.                              *
 * Data:		04/12/2013													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _ATTACHED_LINK_MESSAGE_H

    #define _ATTACHED_LINK_MESSAGE_H

    #include "Solomon.h"
    #include "AbstractBodyMessage.h"
    //
    //
    class SolomLargeString;
    //
    //
    // Body per l'invio di un messaggio di testo:
    class DLL_ACTION AttachedLinkMessage : public AbstractBodyMessage {
        private:
            SolomLargeString 			*_linkFile;

        public:
            //
            // Costruttori/distruttori:
            AttachedLinkMessage();
            AttachedLinkMessage(DataContainerReader *buffer);
            virtual ~AttachedLinkMessage();
            //
            // funzioni di accesso alla classe:
            void                        SetLinkFile(buffer_pointer value);
            SolomLargeString *          GetLinkFile();
            //
            // funzione virtuale da reimplementare:
            AbstractResponseMessage *   CreateResponseObject(DataContainerReader *binary_response);
            //
            // funzioni virtuali da implementare:
            DataContainerWriter *		GetBodyMessage(void); //Richiamata automaticamente quando viene assemblata tutta la richiesta da inviare al TN
            byte                        IDService(void); // ritorna l'identificativo del servizio
            byte                        IDMessage(void); // ritorna l'identificativo del messaggio
	};

#endif // _ATTACHED_LINK_MESSAGE_H
