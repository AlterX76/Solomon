
#ifndef SOLOMDATETIME
    #define SOLOMDATETIME

    #include "Solomon.h"
    //
    // forward declaration:
    class DataContainerWriter;
    class DataContainerReader;
    //
    // Struttura finalizzata al contenimento delle informazioni sulla data, ora e secondi:
    class DLL_ACTION SolomDateTime {
        private:
            u_short					m_anno; // contiene l'anno
            byte					m_mese; // contiene il mese
            byte					m_giorno; // contiene il giorno
            byte					m_ora; // contiene l'ora
            byte					m_minuti; // contiene i minuti
            byte					m_secondi; // contiene i secondi
            u_short					m_yday; // giorno dell'anno calcolato nella forma giuliana (1 - 366)
            //
            // popola i membri interni con la struttura passata come parametro:
            void					InternalFillFields(struct tm *datetime);

        public:
            //
            // costruttori:
            SolomDateTime(DataContainerReader *reader);
            SolomDateTime(boolean utc = FALSE); // inizializza con la data e ora corrente
            SolomDateTime(buffer_pointer dateTime, boolean utc); // crea l'oggetto, eventualmente in formato UTC, effettuando il parse del primo parametro (yyyy-mm-dd hh:mm:ss)
            //
            // funzioni pubbliche:
            static u_short			DayOfYear(void); // restituisce il giorno dell'anno nella forma giuliana (1 - 366). Versione statica
            u_short					GetDayOfYear(void); // restituisce il giorno dell'anno nella forma giuliana (1 - 366). Versione d'istanza
            u_integer				GetTotalMicroSecs(void); // restituisce il totale in millisecondi di ora, minuti e secondi memorizzati nella struttura
            u_short					GetYear(void); // restituisce l'anno
            void					SetYear(u_short year); // imposta l'anno
            byte					GetMonth(void); // restituisce il mese
            void					SetMonth(byte month); // imposta il mese
            byte					GetDay(void); // restituisce il giorno
            void					SetDay(byte day); // imposta il giorno
            byte					GetHour(void); // restituisce l'ora
            void					SetHour(byte hour); // imposta l'ora
            byte					GetMinute(void); // restituisce i minuti
            void					SetMinute(byte minute); // imposta i minuti
            byte					GetSecond(void); // restituisce i secondi
            void					SetSecond(byte second); // imposta i secondi
            void					GetDate(buffer_pointer *returned, caracter dateSeparator = '/'); // returns date as yyyy/mm/dd - allocated memory pointed by returned need to be deallocated
            void					GetTime(buffer_pointer *returned, caracter timeSeparator = ':'); // returns time as hh:mm:ss  - allocated memory pointed by returned need to be deallocated
            void					GetDateTime(buffer_pointer *returned, caracter dateSeparator = '/', caracter timeSeparator = ':'); // restituisce la rappresentazione stringa dei dati con i separatori specificati  - allocated memory pointed by returned need to be deallocated
            u_short					GetSizeOfSolomDateTime(void); // dimension of internal storage to contain info
            void					WriteIn(DataContainerWriter *writer);
    };

#endif // SOLOMDATETIME

