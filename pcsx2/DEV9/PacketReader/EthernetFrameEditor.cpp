// SPDX-FileCopyrightText: 2002-2025 PCSX2 Dev Team
// SPDX-License-Identifier: GPL-3.0+

#include "EthernetFrameEditor.h"

#ifdef _WIN32
#include "winsock.h"
#else
#include <arpa/inet.h>
#endif

namespace PacketReader
{
	EthernetFrameEditor::EthernetFrameEditor(NetPacket* pkt)
		: basePkt{pkt}
	{
		headerLength = 14; //(6+6+2)

		//Note: we don't have to worry about the Ethernet Frame CRC as it is not included in the packet
		//Note: We don't support tagged frames

		payload = std::make_unique<PayloadPtrEditor>((u8*)&basePkt->buffer[14], pkt->size - headerLength);
	}

	MAC_Address EthernetFrameEditor::GetDestinationMAC() const
	{
		return *(MAC_Address*)&basePkt->buffer[0];
	}
	void EthernetFrameEditor::SetDestinationMAC(MAC_Address value)
	{
		*(MAC_Address*)&basePkt->buffer[0] = value;
	}

	MAC_Address EthernetFrameEditor::GetSourceMAC() const
	{
		return *(MAC_Address*)&basePkt->buffer[6];
	}
	void EthernetFrameEditor::SetSourceMAC(MAC_Address value)
	{
		*(MAC_Address*)&basePkt->buffer[6] = value;
	}

	u16 EthernetFrameEditor::GetProtocol() const
	{
		return ntohs(*(u16*)&basePkt->buffer[12]);
	}

	PayloadPtrEditor* EthernetFrameEditor::GetPayload() const
	{
		return payload.get();
	}
} // namespace PacketReader
