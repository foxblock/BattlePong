
#include <enet/enet.h>
#include <string>

class Network
{

	private:
		ENetAddress serverAddress;
		ENetHost*		localHost;
		ENetPeer*		networkPeer;

		Network( int Port );
		Network( std::string Server, int Port );

	public:
		static Network* ActiveConnection;

		static Network* StartHost( int Port );
		static Network* StartClient( std::string Server, int Port );
		static void Disconnect();

		~Network();

		bool IsActive();
		bool IsConnected();

		void Update();

};