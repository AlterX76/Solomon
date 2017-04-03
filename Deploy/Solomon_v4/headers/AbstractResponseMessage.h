

/******************************************************************************
 * Nome classe: AbstractResponseMessage										  *
 * ---------------------------------------------------------------------------*
 * Descrizione: classe astratta utilizzata come base per le risposte		  *
 *				ritornate dal server in risposta ad un messaggio. Usata sia	  *
 *				dal client che dal server per estrarre e creare il messaggio  *
 * Data:		01/03/2012													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _ABSTRACTRESPONSEMESSAGE_H

    #define _ABSTRACTRESPONSEMESSAGE_H

    #include "Solomon.h"
    #include "AbstractBodyMessage.h"
    //
    // classe astratta che rappresenta la base per tutti i messaggi di risposta e messaggi di invio dal server:
    class DLL_ACTION AbstractResponseMessage : public AbstractBodyMessage {
        private:
            //
            // costruttori disabilitati:
            AbstractResponseMessage& operator=(const AbstractResponseMessage&);
            AbstractResponseMessage(const AbstractResponseMessage&);

        protected:
            byte			m_result;
            //
            // costruttore di default solo per le derivate:
            AbstractResponseMessage();

        public:
            ~AbstractResponseMessage();
            //
            // funzioni di accesso alla classe:
            void			SetResultCode(byte value);
            byte			GetResultCode(void);
            u_short			DimensionOfGenericResponse(void);
            //
            // funzioni virtuali pure da implementare nelle specializzate:
            virtual void	ParseBinary(DataContainerReader *reader) = 0; // viene utilizzato dal client per parsare la risposta ricevuta dal server
    };

#endif // _ABSTRACTRESPONSEMESSAGE_H
