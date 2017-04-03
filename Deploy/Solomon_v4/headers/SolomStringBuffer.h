


/******************************************************************************
 * Nome classe: SolomStringBuffer											  *
 * ---------------------------------------------------------------------------*
 * Descrizione: oggetto per memorizzare informazioni stringa con operazioni   *
 *				necessarie in base alle specifiche dei protocolli.			  *
 * Data:		15/02/2007													  *
 * Autore:		Giovanni Romano												  *
 ******************************************************************************/


#ifndef _SOLOMSTRINGBUFFER_H

    #define _SOLOMSTRINGBUFFER_H

	#include "Solomon.h"
    //
    //
    class DataContainerReader;
	//
	//
	// Oggetto che rappresenta un buffer di caratteri generico da utilizzare come supporto per i protocolli:	
    class DLL_ACTION SolomStringBuffer {
		private:
			u_buffer_pointer			descr; // Buffer interno utilizzato per contenere le informazioni
            u_buffer_pointer			m_FilledDescr; // utilizzato SOLO per contenere la descrizione del campo su definito, ma con il fill dei caratteri a destra

		public:
			//
			// costruttori/distruttore:
            SolomStringBuffer(u_short dimDescr);
            ~SolomStringBuffer();
			//
			// membri:
            const u_short               DimensionOfSolomDescription; //Conterrà la dimensione attuale del buffer creato
			//
			// funzioni:
            u_buffer_pointer			getDescription(void); //Proprietà che reperisce il testo da inserire nella struttura
            void						setDescription(buffer_pointer value); //Proprietà che setta il testo da inserire nella struttura
            u_short                     getDescriptionLength(); // ritorna la lunghezza del testo
            u_buffer_pointer			getFilledDescription(void); //Proprietà che reperisce il testo da inserire nella struttura (ha effetto solo se usata la corrispondente funzione per il settaggio della descrizione)
            void						setFilledDescription(buffer_pointer value, caracter carToFill = DEFAULT_CHAR_TO_RPAD); // Proprietà che setta il testo eseguendo il filling dei caratteri fino alla lunghezza massima del buffer (reperire il testo con l'omonima funzione)
            void						setRawDescription(u_buffer_pointer value);
			//
			// funzioni statiche:
            static void					toUpper(buffer_pointer text, buffer_pointer *returned); // restituisce il testo passato come parametro, convertito in maiuscolo - allocated memory pointed by returned need to be deallocated
            static SolomStringBuffer **	createArrayOfSolomStringBuffer(DataContainerReader *reader, byte LenOfEachString, integer NumOfElements);
            static void					deleteArrayOfSolomStringBuffer(SolomStringBuffer **aSolomStringBuffer, integer NumOfElements);
            static integer				convertCarToInt(byte value); // Converte un carattere nella sua rappresentazione intera
            static void					replaceAll(const buffer_pointer source, buffer_pointer *returned, const byte to_find, const buffer_pointer replace_with); // sostituisce tutte le occorrenze di un carattere con uno o più caratteri; non sostituisce caratteri accentati - allocated memory pointed by returned need to be deallocated
            static integer              lastIndexOf(buffer_pointer s1, caracter car);
	};

#endif // _SOLOMSTRINGBUFFER_H
