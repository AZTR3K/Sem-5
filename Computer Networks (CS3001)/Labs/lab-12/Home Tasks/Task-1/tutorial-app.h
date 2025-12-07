#ifndef TUTORIAL_APP_H
#define TUTORIAL_APP_H

#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"

namespace ns3
{

	class Application;

	class TutorialApp : public Application
	{
	  public:
		TutorialApp();
		~TutorialApp() override;

		static TypeId GetTypeId();

		/**
		 * Setup the socket.
		 * @param socket The socket.
		 * @param address The destination address.
		 * @param packetSize The packet size to transmit.
		 * @param nPackets The number of packets to transmit.
		 * @param dataRate the data rate to use.
		 */
		void Setup(Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets,
				   DataRate dataRate);

	  private:
		void StartApplication() override;
		void StopApplication() override;

		void ScheduleTx();
		void SendPacket();

		Ptr<Socket> m_socket;	//!< The transmission socket.
		Address m_peer;			//!< The destination address.
		uint32_t m_packetSize;	//!< The packet size.
		uint32_t m_nPackets;	//!< The number of packets to send.
		DataRate m_dataRate;	//!< The data rate to use.
		EventId m_sendEvent;	//!< Send event.
		bool m_running;			//!< True if the application is running.
		uint32_t m_packetsSent; //!< The number of packets sent.
	};

} // namespace ns3

#endif /* TUTORIAL_APP_H */
