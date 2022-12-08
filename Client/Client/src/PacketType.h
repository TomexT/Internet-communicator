#pragma once
#include "SFML/System.hpp"

///
/// Tworzy nowy typ zmiennej zapisanej na 8 bitach.
///
typedef sf::Uint8 PacketType;

///
/// Okreœla typ pakietu dla przekazania nazwy klienta.
///
const PacketType INITIAL_NAME_DATA = 0;

///
/// Okreœla typ pakietu dla wiadomoœci wysy³anych przez klientów.
///
const PacketType GENERAL_MSG = 1;

///
/// Okreœla typ pakietu dla wiadomoœci wysy³anych przez serwer.
///
const PacketType SERVER_MSG = 2;