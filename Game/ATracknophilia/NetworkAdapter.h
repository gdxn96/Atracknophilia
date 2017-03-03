#pragma once
#include "LuaEngine.h"
#include "../dependancies/MetaSystem/MetaSystem.h"

#define INCOMING_MESSAGE(x) namespace MessageType {	namespace INCOMING { static const char* x = #x;	}	}
#define OUTGOING_MESSAGE(x) namespace MessageType {	namespace OUTGOING { static const char* x = #x;	}	}

INCOMING_MESSAGE(PONG)
OUTGOING_MESSAGE(PING)

struct Message
{
	META_DATA(Message);
	const char* messageType = "";
	const char * data;
	Message(const char * _data, const char* _messageType) : data(_data), messageType(_messageType) {}

	const char* toJson()
	{
		return Variable(this).ToJson().c_str();
	}
};

DEFINE_META(Message)
{
	ADD_MEMBER(messageType);
	ADD_MEMBER(data);
}

class REST_Response
{
public:
	int code;
	const char* body;

	REST_Response(int rc, const char * rb) :code(rc), body(rb)
	{

	}

	bool valid()
	{
		return code > 199 && code < 300;
	}
};

struct Lobby
{
	META_DATA(Lobby);
	int id;
	int num_players;
	int max_players;
};

DEFINE_META(Lobby)
{
	ADD_MEMBER(id);
	ADD_MEMBER(num_players);
	ADD_MEMBER(max_players);
};

class NetworkAdapter
{
public:
	NetworkAdapter() : m_serverUri("http://127.0.0.1:5001/")
	{
		m_lua.LoadScripts({
			"networking.lua"
		});

		luabridge::getGlobalNamespace(m_lua.L())
			.beginNamespace("CPP")
				.beginClass<REST_Response>("REST_Response")
					.addConstructor<void(*)(int, const char*)>()
				.endClass()
			.endNamespace();
		
		luabridge::getGlobalNamespace(m_lua.L())
			.beginNamespace("CPP")
				.beginClass<Message>("Message")
					.addConstructor<void(*)(const char*, const char *)>()
					.addFunction("toJson", &Message::toJson)
				.endClass()
			.endNamespace();
	}

	const char* getJson(rapidjson::Value& d)
	{
		StringBuffer buffer;
		Writer<StringBuffer> writer(buffer);
		d.Accept(writer);

		return buffer.GetString();
	}

	std::vector<Lobby> getLobbies()
	{
		std::vector<Lobby> lobbies;
		const char * data = serverGet("lobbies").body;

		rapidjson::Document d;
		d.Parse(data);
		assert(d.IsObject());
		for (auto& lobby : d["lobbies"].GetArray())
		{
			Lobby l;
			Variable(&l).FromJson<Lobby>(lobby.GetString());
			lobbies.push_back(l);
		}
		return lobbies;
	}

	REST_Response serverGet(const char* uriPath)
	{
		return m_lua.ExecuteFunction("get_request")(std::string(m_serverUri) + uriPath);
	}

	bool joinLobbyById(int lobbyId)
	{
		auto response = serverGet((std::string("lobbies/join/") + std::to_string(lobbyId)).c_str());
		if (response.valid())
		{
			m_lobbyId = std::stoi(response.body);
		}
		return response.valid();
	}

	bool leaveLobby()
	{
		auto response = serverGet((std::string("lobbies/leave/") + std::to_string(m_lobbyId)).c_str());
		if (response.valid())
		{
			m_lobbyId = 0; //reset lobbyid
		}
		return response.valid();
	}

	bool hostNewLobby()
	{
		auto response = serverGet((std::string("lobbies/new/") + std::to_string(4)).c_str());//maxplayers
		if (response.valid())
		{
			m_lobbyId = std::stoi(response.body); //get lobbyid
		}
		return response.valid();
	}

	bool receieveMessage()
	{

	}

private:
	LuaEngine m_lua;
	const char * m_serverUri;
	int m_lobbyId;
};
