#include "SetInventoryPacket.h"

#define ITEM_DEF_SIZE	(0x70)

CSetInventoryPacket::CSetInventoryPacket()
{
	m_commandId = 0x14B;
	m_packetSize = 0;
}

CSetInventoryPacket::~CSetInventoryPacket()
{

}

void CSetInventoryPacket::SetItemBase(unsigned int itemBase)
{
	m_itemBase = itemBase;
}

void CSetInventoryPacket::SetItemCount(unsigned int itemCount)
{
	m_itemCount = itemCount;
	m_packetSize = (itemCount * ITEM_DEF_SIZE) + PACKET_HEADER_SIZE;
}

PacketData CSetInventoryPacket::ToPacketData() const
{
	auto result = CBasePacket::ToPacketData();

	//Weathered Bow
	static const uint8 s_itemBlockSrc[] =
	{
		0x43, 0x7E, 0x26, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x71, 0x1A, 0x3E, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0xFD, 0x02, 0x02, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x27, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	};

	for(unsigned int i = 0; i < m_itemCount; i++)
	{
		auto itemBlockPtr = result.data() + PACKET_HEADER_SIZE + (i * ITEM_DEF_SIZE);
		memcpy(itemBlockPtr, s_itemBlockSrc, ITEM_DEF_SIZE);
		*reinterpret_cast<uint8*>(itemBlockPtr + 0x10) = m_itemBase + i; //Set Item Index
	}

	return result;
}