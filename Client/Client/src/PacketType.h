#pragma once
#include "SFML/System.hpp"

///
/// Tworzy nowy typ zmiennej zapisanej na 8 bitach.
///
typedef sf::Uint8 PacketType;

///
/// Okre�la typ pakietu dla przekazania nazwy klienta.
///
const PacketType INITIAL_NAME_DATA = 0;

///
/// Okre�la typ pakietu dla wiadomo�ci wysy�anych przez klient�w.
///
const PacketType GENERAL_MSG = 1;

///
/// Okre�la typ pakietu dla wiadomo�ci wysy�anych przez serwer.
///
const PacketType SERVER_MSG = 2;