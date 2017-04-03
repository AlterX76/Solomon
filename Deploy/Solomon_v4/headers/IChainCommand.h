#ifndef ICHAIN_H
    #define ICHAIN_H

    #ifndef MOBILE_BUILD

    #include "Solomon.h"
    //
    // definizione della classe:
    class IChainCommand;
    class AbstractHeaderMessage;
    class ClientContainer;
    class SingleChainInfo;
    //
    // definizione di una lista di chain:
    typedef struct SingleChainInfo *    CommandsChainQueue;
    //
    //
    // Interfaccia da utilizzare per la creazione dei moduli della chain
    class IChainCommand {
        protected:
            IChainCommand               *next; // rappresenta l'elemento successivo della catena
            IChainCommand               *prev; // rappresenta l'elemento precedente della catena
            void                        *dynReference; // mantiene il riferimento al plugin caricato; usata per la chiusura del plugin

        public:
            IChainCommand();
            virtual ~IChainCommand();

            const buffer_pointer        getChainCommandFileName();
            //
            // funzione per la discesa nella catena alla ricerca di command in grado di gestire la richiesta del client:
            static IChainCommand *      goThruChain(IChainCommand *starter, AbstractHeaderMessage *header, ClientContainer *clientRequest); // WARNING: IT IS NOT THREAD-SAFE
            static CommandsChainQueue   buildChain(buffer_pointer path, byte idService = 0, byte idMessage = 0, IChainCommand **shortcut = NULL); // WARNING: IT IS NOT THREAD-SAFE
            static void                 destroyChain(CommandsChainQueue *chains); // WARNING: IT IS NOT THREAD-SAFE
            static IChainCommand *      addNode(IChainCommand *start, IChainCommand *command); // WARNING: IT IS NOT THREAD-SAFE
            static IChainCommand *      removeNode(IChainCommand *start, const buffer_pointer pluginFileName); // WARNING: IT IS NOT THREAD-SAFE
            static IChainCommand *      replaceNode(IChainCommand *start, buffer_pointer path, const buffer_pointer pluginFileName); // WARNING: IT IS NOT THREAD-SAFE
            static IChainCommand *      createChainCommand(buffer_pointer pathAndPluginName, buffer_pointer soName);
            static bool                 destroyChainCommand(IChainCommand **command); // WARNING: IT IS NOT THREAD-SAFE
            //
            // funzioni virtuali da implementare:
            virtual boolean             canManage(byte service, byte message) = 0;
            virtual IChainCommand *     handler(AbstractHeaderMessage *header, ClientContainer *clientRequest) = 0;

        private:
            buffer_pointer              soFileName; // plugin name
    };

    #endif
#endif // ICHAIN_H
